#pragma once
//=====================================================================//
/*! @file
    @brief  A/D 変換、キャプチャー制御クラス @n
			最大サンプルレート 2MHz (RX65N/RX72N) @n
			※「GLFW_SIM」を有効にする事で、キャプチャー動作をシュミレートする。
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2018, 2022 Kunihito Hiramatsu @n
                Released under the MIT license @n
                https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
// GLFW_SIM for simulate A/D conversion
#ifndef GLFW_SIM
#include "common/renesas.hpp"
#endif

#include "render_base.hpp"
#include "common/vtx.hpp"
#include "common/string_utils.hpp"

namespace dsos {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  キャプチャー・クラス
		@param[in]	CAPN	キャプチャー最大数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t CAPN>
	class capture : public render_base {

#ifndef GLFW_SIM
		typedef device::S12AD  ADC0;
		typedef device::S12AD1 ADC1;
#if defined(SIG_RX65N)
		static constexpr auto ADC_CH0 = ADC0::ANALOG::AIN000;  ///< P40 CN10(1)
		static constexpr auto ADC_CH1 = ADC1::ANALOG::AIN114;  ///< P90 CN10(5)
#elif defined(SIG_RX72N)
		static constexpr auto ADC_CH0 = ADC0::ANALOG::AIN007;  ///< P47 Pmod2(10) CN6
		static constexpr auto ADC_CH1 = ADC1::ANALOG::AIN108;  ///< PD0 Pmod2( 7) CN6
#endif
#endif

	public:
		static constexpr uint32_t ADC_QUANTIZE = 2048;  ///< A/D 変換量子化の半分
		// x:ch0, y:ch1
		typedef vtx::spos DATA;

		static constexpr uint32_t CAP_NUM = CAPN;	///< キャプチャー数
		static constexpr int16_t CAP_OFS = 2048;	///< 12bit A/D offset

		// キャプチャー・タスク
		class cap_task {
		public:
			DATA				data_[CAPN];

			volatile uint32_t	pos_;
			volatile uint32_t	before_count_;
			volatile uint32_t	after_count_;
			volatile uint16_t	cycle_;	
			volatile int16_t	trg_ref_;
			volatile uint32_t	trg_pos_;
			volatile TRG_MODE	trg_mode_main_;
			volatile TRG_MODE	trg_mode_;

			DATA	min_;
			DATA	max_;

#ifdef GLFW_SIM
			DATA	adv_;
#endif

			cap_task() noexcept :
				data_ { { CAP_OFS, CAP_OFS } }, pos_(0),
				before_count_(0), after_count_(0), cycle_(0),
				trg_ref_(0), trg_pos_(0),
				trg_mode_main_(TRG_MODE::NONE), trg_mode_(TRG_MODE::NONE),
				min_(4096 - 1), max_(0)
			{ }

			void operator() ()
			{
#ifdef GLFW_SIM
				DATA t = adv_;
#else
				DATA t(ADC0::ADDR(ADC_CH0) - CAP_OFS, ADC1::ADDR(ADC_CH1) - CAP_OFS);
				ADC0::ADCSR = ADC0::ADCSR.ADCS.b(0b01) | ADC0::ADCSR.ADST.b();
				ADC1::ADCSR = ADC1::ADCSR.ADCS.b(0b01) | ADC1::ADCSR.ADST.b();
#endif
				switch(trg_mode_) {
				case TRG_MODE::NONE:
					break;
				case TRG_MODE::SINGLE:
				case TRG_MODE::RUN:
					data_[pos_] = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(pos_ == (CAPN - 1)) {
						if(trg_mode_ == TRG_MODE::SINGLE) {
							trg_mode_ = TRG_MODE::NONE;
						}
						trg_pos_ = CAPN / 4;
						pos_ = 0;
						++cycle_;
					}
					break;
				case TRG_MODE::_TRG_BEFORE:
					data_[pos_] = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(before_count_ > 0) {
						before_count_--;
					} else {
						trg_mode_ = trg_mode_main_;
					}
					break;

				case TRG_MODE::CH0_POS:
					data_[pos_] = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(t.x < trg_ref_) {
						trg_mode_ = TRG_MODE::CH0_POSA;
					}
					break;
				case TRG_MODE::CH0_POSA:
					data_[pos_] = t;
					if(t.x >= trg_ref_) {
						trg_pos_ = pos_;
						trg_mode_ = TRG_MODE::_TRG_AFTER;
					}
					++pos_;
					pos_ &= CAPN - 1;
					break;

				case TRG_MODE::CH1_POS:
					data_[pos_] = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(t.y < trg_ref_) {
						trg_mode_ = TRG_MODE::CH1_POSA;
					}
					break;
				case TRG_MODE::CH1_POSA:
					data_[pos_] = t;
					if(t.y >= trg_ref_) {
						trg_pos_ = pos_;
						trg_mode_ = TRG_MODE::_TRG_AFTER;
					}
					++pos_;
					pos_ &= CAPN - 1;
					break;

				case TRG_MODE::CH0_NEG:
					data_[pos_] = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(t.x > trg_ref_) {
						trg_mode_ = TRG_MODE::CH0_NEGA;
					}
					break;
				case TRG_MODE::CH0_NEGA:
					data_[pos_] = t;
					if(t.x <= trg_ref_) {
						trg_pos_ = pos_;
						trg_mode_ = TRG_MODE::_TRG_AFTER;
					}
					++pos_;
					pos_ &= CAPN - 1;
					break;

				case TRG_MODE::CH1_NEG:
					data_[pos_] = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(t.y > trg_ref_) {
						trg_mode_ = TRG_MODE::CH1_NEGA;
					}
					break;
				case TRG_MODE::CH1_NEGA:
					data_[pos_] = t;
					if(t.y <= trg_ref_) {
						trg_pos_ = pos_;
						trg_mode_ = TRG_MODE::_TRG_AFTER;
					}
					++pos_;
					pos_ &= CAPN - 1;
					break;

				case TRG_MODE::_TRG_AFTER:
					data_[pos_] = t;
					++pos_;
					pos_ &= CAPN - 1;
					if(after_count_ > 0) {
						after_count_--;
					} else {
						trg_mode_ = TRG_MODE::NONE;
						++cycle_;
					}
					break;
				default:
					break;
				}
			}
		};

	private:

#ifndef GLFW_SIM
		typedef device::tpu_io<device::TPU0, cap_task> TPU0;
		TPU0        tpu0_;
#else
		cap_task	cap_task_;
#endif

		uint32_t	samplerate_;
		uint32_t	capture_samplerate_;

		float		volt_gain_[2];

		TRG_MODE	trg_mode_;


		static int16_t limit_(int16_t val) noexcept
		{
			if(val >= CAP_OFS) val = CAP_OFS - 1;
			else if(val < -CAP_OFS) val = -CAP_OFS;
			return val;
		}


		static float ftri_(float in) noexcept
		{
			auto a = fmod(in, 1.0f);
			if(a >= 0.5f) {
				a = 1.0f - a;
			}
			a -= 0.25f;
		   	return a * 4.0f;
		}


		static float fsqu_(float in) noexcept
		{
			auto a = fmod(in, 1.0f);
			if(a < 0.5f) {
				return 1.0f;
			} else {
				return -1.0f;
			}
		}


		static float fsquf_(float in, float& back) noexcept
		{
			auto a = fsqu_(in);
			auto d = (a - back) * 0.707f;
			auto ans = back + d;
			back = a; 
			return ans;
		}


		static int16_t pwave_(PWAVE_TYPE pw, float phase, float gain) noexcept
		{
			static float fsqu_s_ = 0;
			static float fsqu_c_ = 0;
			int16_t ret = 0;
			switch(pw) {
			case PWAVE_TYPE::SIN:
				ret = static_cast<int16_t>(sinf(phase * vtx::radian_f_) * gain);
				break;
			case PWAVE_TYPE::COS:
				ret = static_cast<int16_t>(cosf(phase * vtx::radian_f_) * gain);
				break;
			case PWAVE_TYPE::TRI_C:
				ret = static_cast<int16_t>(ftri_(phase) * gain);
				break;
			case PWAVE_TYPE::TRI_S:
				ret = static_cast<int16_t>(ftri_(phase + 0.25f) * gain);
				break;
			case PWAVE_TYPE::SQU_C:
				ret = static_cast<int16_t>(fsqu_(phase) * gain);
				break;
			case PWAVE_TYPE::SQU_S:
				ret = static_cast<int16_t>(fsqu_(phase + 0.25f) * gain);
				break;
			case PWAVE_TYPE::FSQU_C:
				ret = static_cast<int16_t>(fsquf_(phase, fsqu_c_) * gain);
				break;
			case PWAVE_TYPE::FSQU_S:
				ret = static_cast<int16_t>(fsquf_(phase + 0.25f, fsqu_s_) * gain);
				break;
			default:
				break;
			}
			return ret;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		capture() noexcept : samplerate_(2'000'000), capture_samplerate_(2'000'000),
			volt_gain_{ VOLT_DIV_L, VOLT_DIV_L },
			trg_mode_(TRG_MODE::NONE)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  サンプリング周波数の設定
			@param[in]	freq	サンプリング周波数
		*/
		//-----------------------------------------------------------------//
		void set_samplerate(uint32_t freq) noexcept
		{
#ifndef GLFW_SIM
			uint8_t intr_level = 5;
			if(!tpu0_.start(freq, intr_level)) {
				utils::format("TPU0 start error...\n");
			} else {
				auto vec = tpu0_.get_intr_vec();
				// スーパーバイザーモード中に、MVTC xxx,FINTV で割り込みベクタアドレスを設定する必要がある。
//				device::ICU::IER.enable(vec, false);
//				device::icu_mgr::enable_fast_interrupt(vec);
//				device::ICU::IER.enable(vec);
			}
#endif
			samplerate_ = freq;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  キャプチャーしたサンプリング周波数の取得
			@return	キャプチャーしたサンプリング周波数
		*/
		//-----------------------------------------------------------------//
		auto get_capture_samplerate() const noexcept { return capture_samplerate_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  電圧ゲインの設定
			@param[in]	ch		チャネル
			@param[in]	gain	電圧ゲイン
		*/
		//-----------------------------------------------------------------//
		void set_voltage_gain(uint32_t ch, float gain) noexcept {
			volt_gain_[ch & 1] = gain;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  電圧ゲインの取得
			@param[in]	ch		チャネル
			@return 電圧ゲイン
		*/
		//-----------------------------------------------------------------//
		auto get_voltage_gain(uint32_t ch) const noexcept { return volt_gain_[ch & 1]; }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	freq	サンプリング周波数
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq) noexcept
		{
			set_samplerate(freq);

#ifndef GLFW_SIM
			{  // A/D 設定
				device::power_mgr::turn(ADC0::PERIPHERAL);
				ADC0::enable(ADC_CH0);
				ADC0::ADANSA.set(ADC_CH0);
				ADC0::ADSSTR.set(ADC_CH0, 11);
				ADC0::ADSTRGR = ADC0::ADSTRGR.TRSA.b(0b100000) | ADC0::ADSTRGR.TRSB.b(0b111111);
				ADC0::ADSAM.SAM = 0;
				ADC0::ADCSR.ADCS = 0b01;

				device::power_mgr::turn(ADC1::PERIPHERAL);
				ADC1::enable(ADC_CH1);
				ADC1::ADANSA.set(ADC_CH1);
				ADC1::ADSSTR.set(ADC_CH1, 11);
				ADC1::ADSTRGR = ADC1::ADSTRGR.TRSA.b(0b100000) | ADC1::ADSTRGR.TRSB.b(0b111111);
				ADC1::ADSAM.SAM = 1;
				ADC1::ADCSR.ADCS = 0b01;
			}
#endif

#if 0
			{  // DMAC マネージャー開始
				uint8_t intr_level = 4;
				auto ret = dmac_mgr_.start(tpu0_.get_intr_vec(), DMAC_MGR::trans_type::SP_DN_32,
					reinterpret_cast<uint32_t>(sound_out_.get_wave()),
					DAC::DADR0.address(),
					sound_out_.size(), intr_level);
				if(!ret) {
					utils::format("DMAC Not start...\n");
				}
			}
#endif
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  キャプチャー・タスク参照
			@return キャプチャー・タスク
		*/
		//-----------------------------------------------------------------//
#ifdef GLFW_SIM
		auto& at_cap_task() noexcept { return cap_task_; }
#else
		auto& at_cap_task() noexcept { return tpu0_.at_task(); }
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief  キャプチャー・タスク参照(RO)
			@return キャプチャー・タスク
		*/
		//-----------------------------------------------------------------//
#ifdef GLFW_SIM
		const auto& get_cap_task() const noexcept { return cap_task_; }
#else
		const auto& get_cap_task() const noexcept { return tpu0_.get_task(); }
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief  最低値、最大値を検出
			@param[in]	org		開始位置
			@param[in]	end		終端位置
			@param[out]	min		最小値
			@param[in]	max		最大値
		*/
		//-----------------------------------------------------------------//
		void get_min_max(int32_t org, int32_t end, DATA& min, DATA& max) const noexcept
		{
			if(end < org) end += CAP_NUM;

			min.x = get(org).x;
			max.x = get(org).x;
			min.y = get(org).y;
			max.y = get(org).y;
			for(int32_t i = org + 1; i < end; ++i) {
				min.x = std::min(min.x, get(i).x);
				max.x = std::max(max.x, get(i).x);
				min.y = std::min(min.y, get(i).y);
				max.y = std::max(max.y, get(i).y);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー前キャプチャー数の取得
			@return トリガー前キャプチャー数
		*/
		//-----------------------------------------------------------------//
		auto get_before_count() const noexcept { return CAP_NUM / 4; }


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー後キャプチャー数の取得
			@return トリガー後キャプチャー数
		*/
		//-----------------------------------------------------------------//
		auto get_after_count() const noexcept { return CAPN / 2 + CAPN / 4; }


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー型設定（キャプチャー開始）
			@param[in]	trg		トリガー型
			@param[in]	ref		トリガー基準値
		*/
		//-----------------------------------------------------------------//
		void set_trg_mode(TRG_MODE trg_mode, int16_t ref) noexcept
		{
			at_cap_task().trg_ref_ = limit_(ref);
			at_cap_task().pos_ = 0;
			at_cap_task().before_count_ = get_before_count();
			at_cap_task().after_count_  = get_after_count();
			at_cap_task().trg_mode_main_ = trg_mode;
			trg_mode_ = trg_mode;
			if(trg_mode == TRG_MODE::CH0_POS || trg_mode == TRG_MODE::CH1_POS
				|| trg_mode == TRG_MODE::CH0_NEG || trg_mode == TRG_MODE::CH1_NEG) {
				at_cap_task().trg_mode_ = TRG_MODE::_TRG_BEFORE;
			} else {
				at_cap_task().trg_mode_ = trg_mode;
			}
			capture_samplerate_ = samplerate_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー型を取得
			@param[in]	real	現在の状態を知りたい場合「true」
			@return トリガー型
		*/
		//-----------------------------------------------------------------//
		auto get_trg_mode(bool real = false) const noexcept {
			if(real) {
				return get_cap_task().trg_mode_;
			} else {
				return trg_mode_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  トリガー設定文字列の取得
			@param[in]	real	現在の状態を知りたい場合「true」
			@return トリガー設定文字列
		*/
		//-----------------------------------------------------------------//
		const char* get_trigger_str(bool real = false) noexcept
		{
			static char tmp[16];
			auto pos = static_cast<uint32_t>(get_trg_mode(real));
			utils::str::get_word(TRG_MODE_STR, pos, tmp, sizeof(tmp), ',');
			return tmp;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  キャプチャー・サイクルの取得
			@return キャプチャー・サイクル
		*/
		//-----------------------------------------------------------------//
		auto get_capture_cycle() const noexcept { return get_cap_task().cycle_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  波形を取得
		*/
		//-----------------------------------------------------------------//
		const auto& get(uint32_t pos) const noexcept
		{
			return get_cap_task().data_[(pos + get_cap_task().trg_pos_) & (CAP_NUM - 1)];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  電圧を A/D 値に変換
			@param[in]	ch		チャネル（０，１）
			@param[in]	volt	電圧[V]
		*/
		//-----------------------------------------------------------------//
		int16_t voltage_to_value(int32_t ch, float volt) noexcept
		{
			return volt / get_voltage_gain(ch) * static_cast<float>(CAP_OFS);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  SIN/COS 波形を生成
			@param[in]	freq	周波数
			@param[in]	ppv		電圧 (peak to peak)
			@param[in]	num		生成数
			@param[in]	ch0		CH0 波形型
			@param[in]	ch1		CH1 波形型
		*/
		//-----------------------------------------------------------------//
		void make_wave(uint32_t freq, float ppv, uint32_t num, PWAVE_TYPE ch0, PWAVE_TYPE ch1) noexcept
		{
			static int32_t count = 0;
			auto smpl = samplerate_;
			auto& task = at_cap_task();
			auto unit = static_cast<float>(smpl) / static_cast<float>(freq);
			auto vgain0 = voltage_to_value(0, ppv);
			auto vgain1 = voltage_to_value(1, ppv);
			for(uint32_t i = 0; i < num; ++i) {
				auto a = static_cast<float>(count % static_cast<int32_t>(unit)) / unit;
				task.adv_.x = -pwave_(ch0, a, vgain0);
				task.adv_.y = -pwave_(ch1, a, vgain1);
				if(task.adv_.x < -CAP_OFS) task.adv_.x = -CAP_OFS;
				else if(task.adv_.x > (CAP_OFS-1)) task.adv_.x = CAP_OFS-1;
				if(task.adv_.y < -CAP_OFS) task.adv_.y = -CAP_OFS;
				else if(task.adv_.y > (CAP_OFS-1)) task.adv_.y = CAP_OFS-1;
				task();
				++count;
				if(count >= CAP_NUM) {
					count = 0;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  解析
			@param[in]	org		開始ポイント
			@param[in]	end		終了ポイント
			@param[out]	ch0		CH0 情報
			@param[out]	ch1		CH1 情報
		*/
		//-----------------------------------------------------------------//
		void analize(int32_t org, int32_t end, wave_info& ch0, wave_info& ch1) const noexcept
		{
			if(end < org) end += CAP_NUM;
			if((end - org) > static_cast<int32_t>(CAP_NUM)) end = org + CAP_NUM;
///			utils::format("Cap win width: %d\n") % static_cast<int>(end - org);

			DATA min;
			DATA max;
			get_min_max(org, end, min, max);
			ch0.min_ = min.x;
			ch0.max_ = max.x;
			ch1.min_ = min.y;
			ch1.max_ = max.y;

			ch0.setup();
			ch1.setup();
			for(int32_t i = org + 1; i < end; ++i) {
				ch0.update(get(i).x, i);
				ch1.update(get(i).y, i);
				if(ch0.probe() && ch1.probe()) break;
			}
			ch0.build(get_capture_samplerate());
			ch1.build(get_capture_samplerate());
		}
	};
}
