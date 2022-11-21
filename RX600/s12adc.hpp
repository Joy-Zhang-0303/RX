#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・S12ADC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"
#include "RX600/port.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12ADC 共通定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	cmpi	CMP 割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi>
	struct s12adc_t {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto CMP_VEC = cmpi;		///< CMP 割り込みベクター

		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 0（ADDR0）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x20> ADDR0_;
		static  ADDR0_ ADDR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 1（ADDR1）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x22> ADDR1_;
		static  ADDR1_ ADDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 2（ADDR2）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x24> ADDR2_;
		static  ADDR2_ ADDR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 3（ADDR3）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x26> ADDR3_;
		static  ADDR3_ ADDR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 4（ADDR4）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x28> ADDR4_;
		static  ADDR4_ ADDR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 5（ADDR5）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x2A> ADDR5_;
		static  ADDR5_ ADDR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 6（ADDR6）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x2C> ADDR6_;
		static  ADDR6_ ADDR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 7（ADDR7）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x2E> ADDR7_;
		static  ADDR7_ ADDR7;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ（ADDBLDR）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x18> ADDBLDR_;
		static  ADDBLDR_ ADDBLDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ A（ADDBLDRA）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x84> ADDBLDRA_;
		static  ADDBLDRA_ ADDBLDRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データ 2 重化レジスタ B（ADDBLDRB）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x86> ADDBLDRB_;
		static  ADDBLDRB_ ADDBLDRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 自己診断データレジスタ（ ADRD ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adrd_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 12>  AD;
			bits_rw_t<io_, bitpos::B14, 2>  DIAGST;
		};
		typedef adrd_t<base + 0x1E>  ADRD_;
		static  ADRD_ ADRD;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コントロールレジスタ（ADCSR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcsr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  DBLANS;
			bit_rw_t <io_, bitpos::B6>     GBADIE;
			bit_rw_t <io_, bitpos::B7>     DBLE;

			bit_rw_t <io_, bitpos::B8>     EXTRG;
			bit_rw_t <io_, bitpos::B9>     TRGE;
			bit_rw_t <io_, bitpos::B12>    ADIE;
			bits_rw_t<io_, bitpos::B13, 2> ADCS;
			bit_rw_t <io_, bitpos::B15>    ADST;
		};
		typedef adcsr_t<base + 0x00>  ADCSR_;
		static  ADCSR_ ADCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換値加算 / 平均回数選択レジスタ（ADADC）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adadc_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  ADC;
			bit_rw_t <io_, bitpos::B7>     AVEE;
		};
		typedef adadc_t<base + 0x0C>  ADADC_;
		static  ADADC_ ADADC;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コントロール拡張レジスタ（ADCER）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcer_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B1, 2>  ADPRC;
			bit_rw_t <io_, bitpos::B5>     ACE;
			bits_rw_t<io_, bitpos::B8, 2>  DIAGVAL;
			bit_rw_t <io_, bitpos::B10>    DIAGLD;
			bit_rw_t <io_, bitpos::B11>    DIAGM;
			bit_rw_t <io_, bitpos::B15>    ADRFMT;
		};
		typedef adcer_t<base + 0x0E>  ADCER_;
		static  ADCER_ ADCER;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換開始トリガ選択レジスタ（ADSTRGR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adstrgr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  TRSB;
			bits_rw_t<io_, bitpos::B8, 6>  TRSA;
		};
		typedef adstrgr_t<base + 0x10>  ADSTRGR_;
		static  ADSTRGR_ ADSTRGR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ x（ADSSTRx）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adsstrx_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  SST;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t<base + 0x60> ADSSTR0_;
		static  ADSSTR0_ ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t<base + 0x73> ADSSTR1_;
		static  ADSSTR1_ ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t<base + 0x74> ADSSTR2_;
		static  ADSSTR2_ ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t<base + 0x75> ADSSTR3_;
		static  ADSSTR3_ ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 4（ADSSTR4）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t<base + 0x76> ADSSTR4_;
		static  ADSSTR4_ ADSSTR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 5（ADSSTR5）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t<base + 0x77> ADSSTR5_;
		static  ADSSTR5_ ADSSTR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 6（ADSSTR6）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t<base + 0x78> ADSSTR6_;
		static  ADSSTR6_ ADSSTR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 7（ADSSTR7）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t<base + 0x79> ADSSTR7_;
		static  ADSSTR7_ ADSSTR7;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 断線検出コントロールレジスタ（ADDISCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct addiscr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  ADNDIS;
		};
		typedef addiscr_t<base + 0x7A>  ADDISCR_;
		static  ADDISCR_ ADDISCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D グループスキャン優先コントロールレジスタ（ADGSPCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adgspcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   PGS;
			bit_rw_t<io_, bitpos::B1>   GBRSCN;
			bit_rw_t<io_, bitpos::B15>  GBRP;
		};
		typedef adgspcr_t<base + 0x80>  ADGSPCR_;
		static  ADGSPCR_ ADGSPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアコントロールレジスタ（ ADCMPCR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B6>   WCMPE;
			bit_rw_t <io_, bitpos::B7>   CMPIE;
		};
		typedef adcmpcr_t<base + 0x90>  ADCMPCR_;
		static  ADCMPCR_ ADCMPCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアデータレジスタ 0 （ ADCMPDR0 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x9C> ADCMPDR0_;
		static  ADCMPDR0_ ADCMPDR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアデータレジスタ 1 （ ADCMPDR1 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x9E> ADCMPDR1_;
		static  ADCMPDR1_ ADCMPDR1;
	};
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADDR0_ s12adc_t<base, per, cmpi>::ADDR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADDR1_ s12adc_t<base, per, cmpi>::ADDR1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADDR2_ s12adc_t<base, per, cmpi>::ADDR2;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADDR3_ s12adc_t<base, per, cmpi>::ADDR3;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADDR4_ s12adc_t<base, per, cmpi>::ADDR4;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADDR5_ s12adc_t<base, per, cmpi>::ADDR5;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADDR6_ s12adc_t<base, per, cmpi>::ADDR6;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADDR7_ s12adc_t<base, per, cmpi>::ADDR7;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADDBLDR_ s12adc_t<base, per, cmpi>::ADDBLDR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADDBLDRA_ s12adc_t<base, per, cmpi>::ADDBLDRA;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADDBLDRB_ s12adc_t<base, per, cmpi>::ADDBLDRB;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADRD_ s12adc_t<base, per, cmpi>::ADRD;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADCSR_ s12adc_t<base, per, cmpi>::ADCSR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADADC_ s12adc_t<base, per, cmpi>::ADADC;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADCER_ s12adc_t<base, per, cmpi>::ADCER;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADSTRGR_ s12adc_t<base, per, cmpi>::ADSTRGR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADSSTR0_ s12adc_t<base, per, cmpi>::ADSSTR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADSSTR1_ s12adc_t<base, per, cmpi>::ADSSTR1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADSSTR2_ s12adc_t<base, per, cmpi>::ADSSTR2;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADSSTR3_ s12adc_t<base, per, cmpi>::ADSSTR3;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADSSTR4_ s12adc_t<base, per, cmpi>::ADSSTR4;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADSSTR5_ s12adc_t<base, per, cmpi>::ADSSTR5;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADSSTR6_ s12adc_t<base, per, cmpi>::ADSSTR6;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADSSTR7_ s12adc_t<base, per, cmpi>::ADSSTR7;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADDISCR_ s12adc_t<base, per, cmpi>::ADDISCR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADGSPCR_ s12adc_t<base, per, cmpi>::ADGSPCR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADCMPCR_ s12adc_t<base, per, cmpi>::ADCMPCR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADCMPDR0_ s12adc_t<base, per, cmpi>::ADCMPDR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12adc_t<base, per, cmpi>::ADCMPDR1_ s12adc_t<base, per, cmpi>::ADCMPDR1;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD0 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	cmpi	CMP 割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi>
	struct s12ad0_t : public s12adc_t<base, per, cmpi> {

		typedef s12adc_t<base, per, cmpi> base_class;
		static constexpr uint32_t ANALOG_NUM = 8;	///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AIN000,
			AIN001,
			AIN002,
			AIN003,
			AIN004,
			AIN005,
			AIN006,
			AIN007,
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	f	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool f = true) {
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case ANALOG::AIN000:
				PORT4::PDR.B0 = 0;
				MPC::P40PFS.ASEL = f;
				break;
			case ANALOG::AIN001:
				PORT4::PDR.B1 = 0;
				MPC::P41PFS.ASEL = f;
				break;
			case ANALOG::AIN002:
				PORT4::PDR.B2 = 0;
				MPC::P42PFS.ASEL = f;
				break;
			case ANALOG::AIN003:
				PORT4::PDR.B3 = 0;
				MPC::P43PFS.ASEL = f;
				break;
			case ANALOG::AIN004:
				PORT4::PDR.B4 = 0;
				MPC::P44PFS.ASEL = f;
				break;
			case ANALOG::AIN005:
				PORT4::PDR.B5 = 0;
				MPC::P45PFS.ASEL = f;
				break;
			case ANALOG::AIN006:
				PORT4::PDR.B6 = 0;
				MPC::P46PFS.ASEL = f;
				break;
			case ANALOG::AIN007:
				PORT4::PDR.B7 = 0;
				MPC::P47PFS.ASEL = f;
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ読み込み
			@param[in]	an	アナログ入力型
			@return A/D データレジスタ値
		*/
		//-----------------------------------------------------------------//
		struct addr_t {

			uint32_t get_address(ANALOG an) {
				return base + 0x20 + static_cast<uint32_t>(an) * 2;
			}

			uint16_t operator() (ANALOG an) {
				return rd16_(get_address(an));
			}

		};
		typedef addr_t ADDR_;
		static  ADDR_ ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A0（ADANSA0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSA000;
			bit_rw_t<io_, bitpos::B1>  ANSA001;
			bit_rw_t<io_, bitpos::B2>  ANSA002;
			bit_rw_t<io_, bitpos::B3>  ANSA003;
			bit_rw_t<io_, bitpos::B4>  ANSA004;
			bit_rw_t<io_, bitpos::B5>  ANSA005;
			bit_rw_t<io_, bitpos::B6>  ANSA006;
			bit_rw_t<io_, bitpos::B7>  ANSA007;
		};
		typedef adansa0_t<base + 0x04>   ADANSA0_;
		static  ADANSA0_ ADANSA0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ定義 (ADANS) unit0
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t {
			void set(ANALOG an, bool f = true) {
				uint32_t n = static_cast<uint32_t>(an);
				if(f) {
					wr16_(ofs, rd16_(ofs) |  (static_cast<uint16_t>(1) << n));
				} else {
					wr16_(ofs, rd16_(ofs) & ~(static_cast<uint16_t>(1) << n));
				}
			}

			bool operator() (ANALOG an) const {
				uint32_t n = static_cast<uint32_t>(an);
				return (rd16_(ofs) >> n) & 1;
			}
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 A
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0x04>   ADANSA_;
		static  ADANSA_ ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 B
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0x14> ADANSB_;
		static  ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B0（ADANSB0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSB000;
			bit_rw_t<io_, bitpos::B1>  ANSB001;
			bit_rw_t<io_, bitpos::B2>  ANSB002;
			bit_rw_t<io_, bitpos::B3>  ANSB003;
			bit_rw_t<io_, bitpos::B4>  ANSB004;
			bit_rw_t<io_, bitpos::B5>  ANSB005;
			bit_rw_t<io_, bitpos::B6>  ANSB006;
			bit_rw_t<io_, bitpos::B7>  ANSB007;
		};
		typedef adansb0_t<base + 0x14>   ADANSB0_;
		static  ADANSB0_ ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ 0（ADADS0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adads0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ADS000;
			bit_rw_t<io_, bitpos::B1>  ADS001;
			bit_rw_t<io_, bitpos::B2>  ADS002;
			bit_rw_t<io_, bitpos::B3>  ADS003;
			bit_rw_t<io_, bitpos::B4>  ADS004;
			bit_rw_t<io_, bitpos::B5>  ADS005;
			bit_rw_t<io_, bitpos::B6>  ADS006;
			bit_rw_t<io_, bitpos::B7>  ADS007;
		};
		typedef adads0_t<base + 0x08>   ADADS0_;
		static  ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		struct adsstr_t {
			void set(ANALOG an, uint8_t v) {
				wr8_(base + 0xE0 + static_cast<uint32_t>(an), v);
			}
		};
		typedef adsstr_t ADSSTR_;
		static  ADSSTR_ ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプル & ホールド回路コントロールレジスタ（ADSHCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adshcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  SSTSH;
			bits_rw_t<io_, bitpos::B8, 3>  SHANS;
		};
		typedef adshcr_t<base + 0x66>   ADSHCR_;
		static  ADSHCR_ ADSHCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプル＆ホールド動作モード選択レジスタ（ ADSHMSR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adshmsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SHMD;
		};
		typedef adshmsr_t<base + 0x7C>  ADSHMSR_;
		static  ADSHMSR_ ADSHMSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択レジスタ 0 （ ADCMPANSR0 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpansr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 8>  CMPS0;
		};
		typedef adcmpansr0_t<base + 0x94>  ADCMPANSR0_;
		static  ADCMPANSR0_ ADCMPANSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベルレジスタ 0 （ ADCMPLR0 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmplr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  CMPL0;
		};
		typedef adcmplr0_t<base + 0x98>  ADCMPLR0_;
		static  ADCMPLR0_ ADCMPLR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータスレジスタ 0 （ ADCMPSR0 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpsr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  CMPF0;
		};
		typedef adcmpsr0_t<base + 0xA0>  ADCMPSR0_;
		static  ADCMPSR0_ ADCMPSR0;
	};
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad0_t<base, per, cmpi>::ADDR_ s12ad0_t<base, per, cmpi>::ADDR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad0_t<base, per, cmpi>::ADANSA0_ s12ad0_t<base, per, cmpi>::ADANSA0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad0_t<base, per, cmpi>::ADANSA_ s12ad0_t<base, per, cmpi>::ADANSA;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad0_t<base, per, cmpi>::ADANSB_ s12ad0_t<base, per, cmpi>::ADANSB;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad0_t<base, per, cmpi>::ADANSB0_ s12ad0_t<base, per, cmpi>::ADANSB0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad0_t<base, per, cmpi>::ADADS0_ s12ad0_t<base, per, cmpi>::ADADS0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad0_t<base, per, cmpi>::ADSSTR_ s12ad0_t<base, per, cmpi>::ADSSTR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad0_t<base, per, cmpi>::ADSHCR_ s12ad0_t<base, per, cmpi>::ADSHCR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad0_t<base, per, cmpi>::ADSHMSR_ s12ad0_t<base, per, cmpi>::ADSHMSR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad0_t<base, per, cmpi>::ADCMPANSR0_ s12ad0_t<base, per, cmpi>::ADCMPANSR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad0_t<base, per, cmpi>::ADCMPLR0_ s12ad0_t<base, per, cmpi>::ADCMPLR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad0_t<base, per, cmpi>::ADCMPSR0_ s12ad0_t<base, per, cmpi>::ADCMPSR0;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD1 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	cmpi	CMP 割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi>
	struct s12ad1_t : public s12adc_t<base, per, cmpi> {

		typedef s12adc_t<base,per, cmpi> base_class;
		static constexpr uint32_t ANALOG_NUM = 20;	///< アナログ入力数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AIN100,
			AIN101,
			AIN102,
			AIN103,
			AIN104,
			AIN105,
			AIN106,
			AIN107,
			AIN108,
			AIN109,
			AIN110,
			AIN111,
			AIN112,
			AIN113,
			AIN114,
			AIN115,
			AIN116,
			AIN117,
			AIN118,
			AIN119,
			AIN120,
			AINT,		///< 温度センサ
			AINO,		///< 内部基準電圧
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	f	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(ANALOG an, bool f = true) {
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case ANALOG::AIN100:
				PORTE::PDR.B2 = 0;
				MPC::PE2PFS.ASEL = f;
				break;
			case ANALOG::AIN101:
				PORTE::PDR.B3 = 0;
				MPC::PE3PFS.ASEL = f;
				break;
			case ANALOG::AIN102:
				PORTE::PDR.B4 = 0;
				MPC::PE4PFS.ASEL = f;
				break;
			case ANALOG::AIN103:
				PORTE::PDR.B5 = 0;
				MPC::PE5PFS.ASEL = f;
				break;
			case ANALOG::AIN104:
				PORTE::PDR.B6 = 0;
				MPC::PE6PFS.ASEL = f;
				break;
			case ANALOG::AIN105:
				PORTE::PDR.B7 = 0;
				MPC::PE7PFS.ASEL = f;
				break;
			case ANALOG::AIN106:
				PORTD::PDR.B6 = 0;
				MPC::PD6PFS.ASEL = f;
				break;
			case ANALOG::AIN107:
				PORTD::PDR.B7 = 0;
				MPC::PD7PFS.ASEL = f;
				break;
			case ANALOG::AIN108:
				PORTD::PDR.B0 = 0;
				MPC::PD0PFS.ASEL = f;
				break;
			case ANALOG::AIN109:
				PORTD::PDR.B1 = 0;
				MPC::PD1PFS.ASEL = f;
				break;
			case ANALOG::AIN110:
				PORTD::PDR.B2 = 0;
				MPC::PD2PFS.ASEL = f;
				break;
			case ANALOG::AIN111:
				PORTD::PDR.B3 = 0;
				MPC::PD3PFS.ASEL = f;
				break;
			case ANALOG::AIN112:
				PORTD::PDR.B4 = 0;
				MPC::PD4PFS.ASEL = f;
				break;
			case ANALOG::AIN113:
				PORTD::PDR.B5 = 0;
				MPC::PD5PFS.ASEL = f;
				break;
			case ANALOG::AIN114:
				PORT9::PDR.B0 = 0;
				MPC::P90PFS.ASEL = f;
				break;
			case ANALOG::AIN115:
				PORT9::PDR.B1 = 0;
				MPC::P91PFS.ASEL = f;
				break;
			case ANALOG::AIN116:
				PORT9::PDR.B2 = 0;
				MPC::P92PFS.ASEL = f;
				break;
			case ANALOG::AIN117:
				PORT9::PDR.B3 = 0;
				MPC::P93PFS.ASEL = f;
				break;
			case ANALOG::AIN118:
				PORT0::PDR.B0 = 0;
				MPC::P00PFS.ASEL = f;
				break;
			case ANALOG::AIN119:
				PORT0::PDR.B1 = 0;
				MPC::P01PFS.ASEL = f;
				break;
			case ANALOG::AIN120:
				PORT0::PDR.B2 = 0;
				MPC::P02PFS.ASEL = f;
				break;
			default:
				break;
			}
			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 8（ADDR8）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x30> ADDR8_;
		static  ADDR8_ ADDR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 9（ADDR9）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x32> ADDR9_;
		static  ADDR9_ ADDR9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 10（ADDR10）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x34> ADDR10_;
		static  ADDR10_ ADDR10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 11（ADDR11）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x36> ADDR11_;
		static  ADDR11_ ADDR11;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 12（ADDR12）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x38> ADDR12_;
		static  ADDR12_ ADDR12;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 13（ADDR13）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x3A> ADDR13_;
		static  ADDR13_ ADDR13;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 14（ADDR14）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x3C> ADDR14_;
		static  ADDR14_ ADDR14;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 15（ADDR15）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x3E> ADDR15_;
		static  ADDR15_ ADDR15;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 16（ADDR16）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x40> ADDR16_;
		static  ADDR16_ ADDR16;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 17（ADDR17）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x42> ADDR17_;
		static  ADDR17_ ADDR17;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 18（ADDR18）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x44> ADDR18_;
		static  ADDR18_ ADDR18;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 19（ADDR19）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x46> ADDR19_;
		static  ADDR19_ ADDR19;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 20（ADDR20）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x48> ADDR20_;
		static  ADDR20_ ADDR20;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 温度センサデータレジスタ（ ADTSDR ）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x1A> ADTSDR_;
		static  ADTSDR_ ADTSDR;


		//-----------------------------------------------------------------//
		/*!
			@brief   A/D 内部基準電圧データレジスタ（ ADOCDR ）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x01C> ADOCDR_;
		static  ADOCDR_ ADOCDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ読み込み
			@param[in]	an	アナログ入力型
			@return A/D データレジスタ値
		*/
		//-----------------------------------------------------------------//
		struct addr_t {
			uint16_t operator() (ANALOG an) {
				return rd16_(base + 0x20 + static_cast<uint32_t>(an) * 2);
			}
		};
		typedef addr_t ADDR_;
		static  ADDR_ ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A0（ADANSA0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSA100;
			bit_rw_t<io_, bitpos::B1>  ANSA101;
			bit_rw_t<io_, bitpos::B2>  ANSA102;
			bit_rw_t<io_, bitpos::B3>  ANSA103;
			bit_rw_t<io_, bitpos::B4>  ANSA104;
			bit_rw_t<io_, bitpos::B5>  ANSA105;
			bit_rw_t<io_, bitpos::B6>  ANSA106;
			bit_rw_t<io_, bitpos::B7>  ANSA107;
			bit_rw_t<io_, bitpos::B8>  ANSA108;
			bit_rw_t<io_, bitpos::B9>  ANSA109;
			bit_rw_t<io_, bitpos::B10> ANSA110;
			bit_rw_t<io_, bitpos::B11> ANSA111;
			bit_rw_t<io_, bitpos::B12> ANSA112;
			bit_rw_t<io_, bitpos::B13> ANSA113;
			bit_rw_t<io_, bitpos::B14> ANSA114;
			bit_rw_t<io_, bitpos::B15> ANSA115;
		};
		typedef adansa0_t<base + 0x04>   ADANSA0_;
		static  ADANSA0_ ADANSA0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ A1（ADANSA1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansa1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSA116;
			bit_rw_t<io_, bitpos::B1>  ANSA117;
			bit_rw_t<io_, bitpos::B2>  ANSA118;
			bit_rw_t<io_, bitpos::B3>  ANSA119;
			bit_rw_t<io_, bitpos::B4>  ANSA120;
		};
		typedef adansa1_t<base + 0x06>   ADANSA1_;
		static  ADANSA1_ ADANSA1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ定義 (ADANS)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t {
			void set(ANALOG an, bool f = true) {
				uint32_t n = static_cast<uint32_t>(an);
				uint32_t ros = ofs;
				if(n >= 16) {
					n &= 15;
					ros += 2;
				}
				if(f) {
					wr16_(ros, rd16_(ros) |  (static_cast<uint16_t>(1) << n));
				} else {
					wr16_(ros, rd16_(ros) & ~(static_cast<uint16_t>(1) << n));
				}
			}

			bool operator() (ANALOG an) const {
				uint32_t n = static_cast<uint32_t>(an);
				uint32_t ros = ofs;
				if(n >= 16) {
					n &= 15;
					ros += 2;
				}
				return (rd16_(ros) >> n) & 1;
			}
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ（ADANSA）
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0x04> ADANSA_;
		static  ADANSA_ ADANSA;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B0（ADANSB0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSB100;
			bit_rw_t<io_, bitpos::B1>  ANSB101;
			bit_rw_t<io_, bitpos::B2>  ANSB102;
			bit_rw_t<io_, bitpos::B3>  ANSB103;
			bit_rw_t<io_, bitpos::B4>  ANSB104;
			bit_rw_t<io_, bitpos::B5>  ANSB105;
			bit_rw_t<io_, bitpos::B6>  ANSB106;
			bit_rw_t<io_, bitpos::B7>  ANSB107;
			bit_rw_t<io_, bitpos::B8>  ANSB108;
			bit_rw_t<io_, bitpos::B9>  ANSB109;
			bit_rw_t<io_, bitpos::B10> ANSB110;
			bit_rw_t<io_, bitpos::B11> ANSB111;
			bit_rw_t<io_, bitpos::B12> ANSB112;
			bit_rw_t<io_, bitpos::B13> ANSB113;
			bit_rw_t<io_, bitpos::B14> ANSB114;
			bit_rw_t<io_, bitpos::B15> ANSB115;
		};
		typedef adansb0_t<base + 0x14>   ADANSB0_;
		static  ADANSB0_ ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 B
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0x14> ADANSB_;
		static  ADANSB_ ADANSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ B1（ADANSB1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansb1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSB116;
			bit_rw_t<io_, bitpos::B1>  ANSB117;
			bit_rw_t<io_, bitpos::B2>  ANSB118;
			bit_rw_t<io_, bitpos::B3>  ANSB119;
			bit_rw_t<io_, bitpos::B4>  ANSB120;
		};
		typedef adansb1_t<base + 0x16>   ADANSB1_;
		static  ADANSB1_ ADANSB1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ 0（ADADS0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adads0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ADS100;
			bit_rw_t<io_, bitpos::B1>   ADS101;
			bit_rw_t<io_, bitpos::B2>   ADS102;
			bit_rw_t<io_, bitpos::B3>   ADS103;
			bit_rw_t<io_, bitpos::B4>   ADS104;
			bit_rw_t<io_, bitpos::B5>   ADS105;
			bit_rw_t<io_, bitpos::B6>   ADS106;
			bit_rw_t<io_, bitpos::B7>   ADS107;
			bit_rw_t<io_, bitpos::B8>   ADS108;
			bit_rw_t<io_, bitpos::B9>   ADS109;
			bit_rw_t<io_, bitpos::B10>  ADS110;
			bit_rw_t<io_, bitpos::B11>  ADS111;
			bit_rw_t<io_, bitpos::B12>  ADS112;
			bit_rw_t<io_, bitpos::B13>  ADS113;
			bit_rw_t<io_, bitpos::B14>  ADS114;
			bit_rw_t<io_, bitpos::B15>  ADS115;
		};
		typedef adads0_t<base + 0x08>   ADADS0_;
		static  ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均モード選択レジスタ 1 （ ADADS1 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adads1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   ADS116;
			bit_rw_t<io_, bitpos::B1>   ADS117;
			bit_rw_t<io_, bitpos::B2>   ADS118;
			bit_rw_t<io_, bitpos::B3>   ADS119;
			bit_rw_t<io_, bitpos::B4>   ADS120;
		};
		typedef adads1_t<base + 0x10>   ADADS1_;
		static  ADADS1_ ADADS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換拡張入力コントロールレジスタ（ ADEXICR ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adexicr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>      TSSAD;
			bit_rw_t<io_, bitpos::B1>      OCSAD;

			bit_rw_t<io_, bitpos::B8>      TSSA;
			bit_rw_t<io_, bitpos::B9>      OCSA;
			bit_rw_t<io_, bitpos::B10>     TSSB;
			bit_rw_t<io_, bitpos::B11>     OCSB;

			bits_rw_t<io_, bitpos::B13, 2> EXSEL;
			bit_rw_t<io_, bitpos::B15>     EXOEN;
		};
		typedef adexicr_t<base + 0x12>   ADEXICR_;
		static  ADEXICR_ ADEXICR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D サンプリングステートレジスタ x（ADSSTRx）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adsstrx_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  SST;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t<base + 0x61> ADSSTRL_;
		static  ADSSTRL_ ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ T（ADSSTRT）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t<base + 0x70> ADSSTRT_;
		static  ADSSTRT_ ADSSTRT;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ O（ADSSTRO）
		*/
		//-----------------------------------------------------------------//
		typedef adsstrx_t<base + 0x71> ADSSTRO_;
		static  ADSSTRO_ ADSSTRO;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		struct adsstr_t {
			void set(ANALOG an, uint8_t v) {
				wr8_(base + 0xE0 + static_cast<uint32_t>(an), v);
			}
		};
		typedef adsstr_t ADSSTR_;
		static  ADSSTR_ ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択レジスタ 0 （ ADCMPANSR0 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpansr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 16>  CMPS0;
		};
		typedef adcmpansr0_t<base + 0x94>  ADCMPANSR0_;
		static  ADCMPANSR0_ ADCMPANSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択レジスタ 1 （ ADCMPANSR1 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpansr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 5>  CMPS1;
		};
		typedef adcmpansr1_t<base + 0x96>  ADCMPANSR1_;
		static  ADCMPANSR1_ ADCMPANSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D コンペアチャネル選択拡張レジスタ（ ADCMPANSER ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpanser_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CMPSTS;
			bit_rw_t <io_, bitpos::B1>  CMPSOC;
		};
		typedef adcmpanser_t<base + 0x92>  ADCMPANSER_;
		static  ADCMPANSER_ ADCMPANSER;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベルレジスタ 0 （ ADCMPLR0 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmplr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>  CMPL0;
		};
		typedef adcmplr0_t<base + 0x98>  ADCMPLR0_;
		static  ADCMPLR0_ ADCMPLR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベルレジスタ 1 （ ADCMPLR1 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmplr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  CMPL1;
		};
		typedef adcmplr1_t<base + 0x9A>  ADCMPLR1_;
		static  ADCMPLR1_ ADCMPLR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアレベル拡張レジスタ（ ADCMPLER ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpler_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMPLTS;
			bit_rw_t<io_, bitpos::B0>  CMPLOC;
		};
		typedef adcmpler_t<base + 0x93>  ADCMPLER_;
		static  ADCMPLER_ ADCMPLER;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータスレジスタ 0 （ ADCMPSR0 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpsr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>  CMPF0;
		};
		typedef adcmpsr0_t<base + 0xA0>  ADCMPSR0_;
		static  ADCMPSR0_ ADCMPSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータスレジスタ 1 （ ADCMPSR1 ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpsr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  CMPF1;
		};
		typedef adcmpsr1_t<base + 0xA2>  ADCMPSR1_;
		static  ADCMPSR1_ ADCMPSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コンペアステータス拡張レジスタ（ ADCMPSER ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcmpser_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMPFTS;
			bit_rw_t<io_, bitpos::B1>  CMPFOC;
		};
		typedef adcmpser_t<base + 0xA4>  ADCMPSER_;
		static  ADCMPSER_ ADCMPSER;
	};
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADDR8_ s12ad1_t<base, per, cmpi>::ADDR8;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADDR9_ s12ad1_t<base, per, cmpi>::ADDR9;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADDR10_ s12ad1_t<base, per, cmpi>::ADDR10;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADDR11_ s12ad1_t<base, per, cmpi>::ADDR11;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADDR12_ s12ad1_t<base, per, cmpi>::ADDR12;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADDR13_ s12ad1_t<base, per, cmpi>::ADDR13;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADDR14_ s12ad1_t<base, per, cmpi>::ADDR14;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADDR15_ s12ad1_t<base, per, cmpi>::ADDR15;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADDR16_ s12ad1_t<base, per, cmpi>::ADDR16;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADDR17_ s12ad1_t<base, per, cmpi>::ADDR17;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADDR18_ s12ad1_t<base, per, cmpi>::ADDR18;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADDR19_ s12ad1_t<base, per, cmpi>::ADDR19;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADDR20_ s12ad1_t<base, per, cmpi>::ADDR20;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADTSDR_ s12ad1_t<base, per, cmpi>::ADTSDR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADOCDR_ s12ad1_t<base, per, cmpi>::ADOCDR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADDR_ s12ad1_t<base, per, cmpi>::ADDR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADANSA0_ s12ad1_t<base, per, cmpi>::ADANSA0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADANSA1_ s12ad1_t<base, per, cmpi>::ADANSA1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADANSA_ s12ad1_t<base, per, cmpi>::ADANSA;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADANSB0_ s12ad1_t<base, per, cmpi>::ADANSB0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADANSB_ s12ad1_t<base, per, cmpi>::ADANSB;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADANSB1_ s12ad1_t<base, per, cmpi>::ADANSB1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADADS0_ s12ad1_t<base, per, cmpi>::ADADS0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADADS1_ s12ad1_t<base, per, cmpi>::ADADS1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADEXICR_ s12ad1_t<base, per, cmpi>::ADEXICR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADSSTRL_ s12ad1_t<base, per, cmpi>::ADSSTRL;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADSSTRT_ s12ad1_t<base, per, cmpi>::ADSSTRT;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADSSTRO_ s12ad1_t<base, per, cmpi>::ADSSTRO;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADSSTR_ s12ad1_t<base, per, cmpi>::ADSSTR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADCMPANSR0_ s12ad1_t<base, per, cmpi>::ADCMPANSR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADCMPANSR1_ s12ad1_t<base, per, cmpi>::ADCMPANSR1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADCMPANSER_ s12ad1_t<base, per, cmpi>::ADCMPANSER;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADCMPLR0_ s12ad1_t<base, per, cmpi>::ADCMPLR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADCMPLR1_ s12ad1_t<base, per, cmpi>::ADCMPLR1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADCMPLER_ s12ad1_t<base, per, cmpi>::ADCMPLER;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADCMPSR0_ s12ad1_t<base, per, cmpi>::ADCMPSR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADCMPSR1_ s12ad1_t<base, per, cmpi>::ADCMPSR1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL1 cmpi> typename s12ad1_t<base, per, cmpi>::ADCMPSER_ s12ad1_t<base, per, cmpi>::ADCMPSER;


	typedef s12ad0_t<0x00089000, peripheral::S12AD,  ICU::VECTOR_BL1::S12CMPAI>   S12AD;
	typedef s12ad1_t<0x00089100, peripheral::S12AD1, ICU::VECTOR_BL1::S12CMPAI1>  S12AD1;
}
