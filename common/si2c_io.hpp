#pragma once
//=====================================================================//
/*!	@file
	@brief	ソフト制御 I2C テンプレートクラス @n
			※ポートは、オープンドレイン指定が可能な事 @n
			※速度指定は、正確ではなく目安程度 @n
			※「FAST_PLUS」は選択出来ない、エラーとなる
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "common/delay.hpp"
#include "common/i2c_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  I2C テンプレートクラス
		@param[in]	SDA	SDA ポート定義クラス
		@param[in]	SCL	SCL ポート定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SDA, class SCL>
	class si2c_io : public i2c_base {
		uint8_t		clock_;
		ERROR		error_;
		uint16_t	busy_;

		static constexpr uint8_t slow_clock_ = 10 / 2;
		static constexpr uint8_t fast_clock_ = 4 / 2;

		void start_() const {
			SDA::P = 0;
			utils::delay::micro_second(clock_);
			SCL::P = 0;
			utils::delay::micro_second(clock_);
		}


		bool ack_() const {
			SDA::P = 1;
			utils::delay::micro_second(clock_);
			SCL::P = 1;
			SDA::DIR = 0;
			utils::delay::micro_second(clock_);
			bool f = SDA::P();
			SDA::P = 0;
			SDA::DIR = 1;
			SCL::P = 0;
			return f;
		}


		void out_ack_(bool b) const {
			utils::delay::micro_second(clock_);
			SDA::P = b;
			SCL::P = 1;
			utils::delay::micro_second(clock_);
			SCL::P = 0;
		}


		bool wait_() const {
			uint16_t cnt = busy_;
			SCL::DIR = 0;
			while(SCL::P() == 0) {
				utils::delay::micro_second(1);
				if(cnt) {
					--cnt;
				} else {
					SCL::DIR = 1;
					return false;  // wait stall
				}
			}
			SCL::DIR = 1;
			return true;
		}


		void stop_() const {
			utils::delay::micro_second(clock_);
			SCL::P = 1;
			utils::delay::micro_second(clock_);
			SDA::P = 1;
		}


		bool write_(uint8_t val, bool sync) const {
			for(uint8_t n = 0; n < 8; ++n) {
				SDA::P = (val & 0x80) != 0 ? 1 : 0;
				utils::delay::micro_second(clock_);
				SCL::P = 1;
				if(n == 0 && sync) {
					if(!wait_()) return false;
				}
				val <<= 1;
				utils::delay::micro_second(clock_);
				SCL::P = 0;
			}
			return true;
		}


		bool write_(uint8_t data) const {
			if(!write_(data, true)) {
				stop_();
				return false;
			}
			if(ack_()) {
				stop_();
				return false;
			}
			return true;
		}


		bool write_(const uint8_t* src, uint8_t num) const {
			for(uint8_t n = 0; n < num; ++n) {
				if(!write_(*src, true)) {
					stop_();
					return false;
				}
				++src;
				if(ack_()) {
					stop_();
					return false;
				}
			}
			return true;
		}


		bool read_(uint8_t& val, bool sync) const {
			SDA::DIR = 0;
			for(uint8_t n = 0; n < 8; ++n) {
				utils::delay::micro_second(clock_);
				val <<= 1;
				SCL::P = 1;
				if(n == 0 && sync) {
					if(!wait_()) {
						SDA::DIR = 1;
						return false;
					}
				}
				utils::delay::micro_second(clock_);
				if(SDA::P()) val |= 1;
				SCL::P = 0;
			}
			SDA::DIR = 1;
			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		si2c_io() noexcept : clock_(slow_clock_), error_(ERROR::NONE), busy_(200) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
			@param[in]	mode	動作モード（現在は「master」のみ）
			@param[in]	spd		スピード
			@param[in]	lvl		割り込みレベル（設定しても無効）
			@param[in]	pullup	プルアップを有効にする場合「true」
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(MODE mode, SPEED spd, uint8_t lvl = 0, bool pullup = false) noexcept
		{
			SCL::OD = SCL::OD_TYPE::N_CH;
			SDA::OD = SDA::OD_TYPE::N_CH;
			if(pullup) {
				SCL::PU = 1;
				SDA::PU = 1;
			}
			SCL::DIR = 1;
			SDA::DIR = 1;
			SCL::P = 1;
			SDA::P = 1;
			switch(spd) {	
			case SPEED::STANDARD:
				set_standard();
				break;
			case SPEED::FAST:
				set_fast();
				break;
			default:
				error_ = ERROR::START;
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  クロック設定
			@param[in]	clock	パルス５０％待ち時間（単位マイクロ秒）
		*/
		//-----------------------------------------------------------------//
		void set_clock(uint8_t clock) noexcept { clock_ = clock; }


		//-----------------------------------------------------------------//
		/*!
			@brief  標準速度指定（maybe 100KBPS）
		*/
		//-----------------------------------------------------------------//
		void set_standard() noexcept { clock_ = slow_clock_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  高速指定（maybe 400KBPS）
		*/
		//-----------------------------------------------------------------//
		void set_fast() noexcept { clock_ = fast_clock_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  スレーブデバイスの「待ち」時間の最大値を設定
			@param[in]	busy	待ち時間（単位マイクロ秒）
		*/
		//-----------------------------------------------------------------//
		void set_busy(uint16_t busy) noexcept { busy_ = busy; }


		//-----------------------------------------------------------------//
		/*!
			@brief	最終エラーの取得
			@return エラー・タイプ
		 */
		//-----------------------------------------------------------------//
		ERROR get_last_error() const noexcept { return error_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  受信（リード）
			@param[in] address	スレーブアドレス（７ビット）
			@param[out]	dst		先
			@param[in]	num		数
			@return 失敗なら「false」が返る
		*/
		//-----------------------------------------------------------------//
		bool recv(uint8_t address, void* dst, uint8_t num) noexcept {
			start_();
			write_((address << 1) | 1, false);
			if(ack_()) {
				stop_();
				error_ = ERROR::ADDRESS;
				return false;
			}

			uint8_t* p = static_cast<uint8_t*>(dst);
			for(uint8_t n = 0; n < num; ++n) {
				if(!read_(*p, true)) {
					stop_();
					error_ = ERROR::RECV_DATA;
					return false;
				}
				bool f = 0;
				if(n == (num - 1)) f = 1;
				out_ack_(f);
				++p;
			}
			stop_();
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  送信（ライト）
			@param[in] address スレーブアドレス（７ビット）
			@param[in]	src	元
			@param[in]	num	数
			@return 失敗なら「false」が返る
		*/
		//-----------------------------------------------------------------//
		bool send(uint8_t address, const void* src, uint8_t num) noexcept {
			start_();
			write_(address << 1, false);
			if(ack_()) {
				stop_();
				error_ = ERROR::ADDRESS;
				return false;
			}

			if(!write_(static_cast<const uint8_t*>(src), num)) {
				stop_();
				error_ = ERROR::SEND_DATA;
				return false;
			}
			stop_();
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  送信（ライト）
			@param[in] address スレーブアドレス（７ビット）
			@param[in]	first	ファーストデータ
			@param[in]	src	元
			@param[in]	num	数
			@return 失敗なら「false」が返る
		*/
		//-----------------------------------------------------------------//
		bool send(uint8_t address, uint8_t first, const void* src, uint8_t num) noexcept
		{
			start_();
			write_(address << 1, false);
			if(ack_()) {
				stop_();
				error_ = ERROR::ADDRESS;
				return false;
			}

			if(!write_(first)) {
				stop_();
				error_ = ERROR::SEND_DATA;
				return false;
			}

			if(!write_(static_cast<const uint8_t*>(src), num)) {
				stop_();
				error_ = ERROR::SEND_DATA;
				return false;
			}
			stop_();
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  送信（ライト）
			@param[in] address スレーブアドレス（７ビット）
			@param[in]	first	ファースト・データ
			@param[in]	second	セカンド・データ
			@param[in]	src	元
			@param[in]	num	数
			@return 失敗なら「false」が返る
		*/
		//-----------------------------------------------------------------//
		bool send(uint8_t address, uint8_t first, uint8_t second, const void* src, uint8_t num) {
			start_();
			write_(address << 1, false);
			if(ack_()) {
				stop_();
				error_ = ERROR::ADDRESS;
				return false;
			}

			if(!write_(first)) {
				stop_();
				error_ = ERROR::SEND_DATA;
				return false;
			}
			if(!write_(second)) {
				stop_();
				error_ = ERROR::SEND_DATA;
				return false;
			}
			if(!write_(static_cast<const uint8_t*>(src), num)) {
				stop_();
				error_ = ERROR::SEND_DATA;
				return false;
			}
			stop_();
			return true;
		}
	};
}
