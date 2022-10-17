#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・S12AD 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX24T/peripheral.hpp"
#include "RX600/port.hpp"
#include "RX24T/mpc.hpp"
#include "RX24T/icu.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD 共通定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct s12ad_t {

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

			bits_rw_t<io_, bitpos::B0, 3>  ADC;
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


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D グループ C トリガ選択レジスタ（ADGCTRGR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adgctrgr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  TRSC;
			bit_rw_t <io_, bitpos::B6>     GCADIE;
			bit_rw_t <io_, bitpos::B7>     GRCE;
		};
		typedef adgctrgr_t<base + 0xD9>  ADGCTRGR_;
		static  ADGCTRGR_ ADGCTRGR;


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
			bit_rw_t<io_, bitpos::B14>  LGRRS;
			bit_rw_t<io_, bitpos::B15>  GBRP;
		};
		typedef adgspcr_t<base + 0x80>  ADGSPCR_;
		static  ADGSPCR_ ADGSPCR;

	};
	template <uint32_t base> typename s12ad_t<base>::ADDR0_ s12ad_t<base>::ADDR0;
	template <uint32_t base> typename s12ad_t<base>::ADDR1_ s12ad_t<base>::ADDR1;
	template <uint32_t base> typename s12ad_t<base>::ADDR2_ s12ad_t<base>::ADDR2;
	template <uint32_t base> typename s12ad_t<base>::ADDR3_ s12ad_t<base>::ADDR3;
	template <uint32_t base> typename s12ad_t<base>::ADDBLDR_ s12ad_t<base>::ADDBLDR;
	template <uint32_t base> typename s12ad_t<base>::ADDBLDRA_ s12ad_t<base>::ADDBLDRA;
	template <uint32_t base> typename s12ad_t<base>::ADDBLDRB_ s12ad_t<base>::ADDBLDRB;
	template <uint32_t base> typename s12ad_t<base>::ADCSR_ s12ad_t<base>::ADCSR;
	template <uint32_t base> typename s12ad_t<base>::ADADC_ s12ad_t<base>::ADADC;
	template <uint32_t base> typename s12ad_t<base>::ADCER_ s12ad_t<base>::ADCER;
	template <uint32_t base> typename s12ad_t<base>::ADSTRGR_ s12ad_t<base>::ADSTRGR;
	template <uint32_t base> typename s12ad_t<base>::ADGCTRGR_ s12ad_t<base>::ADGCTRGR;
	template <uint32_t base> typename s12ad_t<base>::ADDISCR_ s12ad_t<base>::ADDISCR;
	template <uint32_t base> typename s12ad_t<base>::ADGSPCR_ s12ad_t<base>::ADGSPCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD0 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct s12ad0_t : public s12ad_t<base> {

		static constexpr auto PERIPHERAL = per;  ///< ペリフェラル型
		static constexpr auto S12ADI = ICU::VECTOR::S12ADI;	///< スキャン終了割り込みベクター
		static constexpr auto GBADI  = ICU::VECTOR::GBADI;	///< グループＢスキャン終了割り込みベクター
		static constexpr auto GCADI  = ICU::VECTOR::GCADI;	///< グループＣスキャン終了割り込みベクター
		static constexpr uint32_t ANALOG_NUM = 5;	///< アナログ入力数

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
			AIN016 = 0x10,
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
			case ANALOG::AIN016:
				PORT2::PDR.B0 = 0;
				MPC::P20PFS.ASEL = f;
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
			uint16_t operator() (ANALOG an) {
				return rd16_(base + 0x20 + static_cast<uint32_t>(an) * 2);
			}
		};
		typedef addr_t ADDR_;
		static  ADDR_ ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 16（ADDR16）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x40> ADDR16_;
		static  ADDR16_ ADDR16;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ定義 (ADANS)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t {
			void set(ANALOG an, bool f = true) {
				uint32_t n = static_cast<uint32_t>(an);
				uint32_t ros = ofs;
				if(n >= 4) {
					n -= 4;
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
				if(n >= 4) {
					n -= 4;
					ros += 2;
				}
				return (rd16_(ros) >> n) & 1;
			}
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 A
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0x04> ADANSA_;
		static  ADANSA_ ADANSA;


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

			bit_rw_t<io_, bitpos::B0>  ANSA100;
		};
		typedef adansa1_t<base + 0x06>   ADANSA1_;
		static  ADANSA1_ ADANSA1;


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
		};
		typedef adansb0_t<base + 0x14>   ADANSB0_;
		static  ADANSB0_ ADANSB0;


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

			bit_rw_t<io_, bitpos::B0>  ANSB100;
		};
		typedef adansb1_t<base + 0x16>   ADANSB1_;
		static  ADANSB1_ ADANSB1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0xD4> ADANSC_;
		static  ADANSC_ ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0（ADANSC0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSC000;
			bit_rw_t<io_, bitpos::B1>  ANSC001;
			bit_rw_t<io_, bitpos::B2>  ANSC002;
			bit_rw_t<io_, bitpos::B3>  ANSC003;
		};
		typedef adansc0_t<base + 0xD4>   ADANSC0_;
		static  ADANSC0_ ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C1（ADANSC1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSC100;
		};
		typedef adansc1_t<base + 0xD6>   ADANSC1_;
		static  ADANSC1_ ADANSC1;


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
		};
		typedef adads0_t<base + 0x08>   ADADS0_;
		static  ADADS0_ ADADS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換値加算 / 平均機能チャネル選択レジスタ 1（ADADS1）
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

			bit_rw_t<io_, bitpos::B0>  ADS100;
		};
		typedef adads1_t<base + 0x0A>   ADADS1_;
		static  ADADS1_ ADADS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		struct adsstr_t {
			void set(ANALOG an, uint8_t v) {
				if(an == ANALOG::AIN016) {
					wr8_(base + 0xDD + static_cast<uint32_t>(an), v);
				} else {
					wr8_(base + 0xE0 + static_cast<uint32_t>(an), v);
				}
			}
		};
		typedef adsstr_t ADSSTR_;
		static  ADSSTR_ ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDD> ADSSTRL_;
		static  ADSSTRL_ ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE0> ADSSTR0_;
		static  ADSSTR0_ ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE1> ADSSTR1_;
		static  ADSSTR1_ ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE2> ADSSTR2_;
		static  ADSSTR2_ ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE3> ADSSTR3_;
		static  ADSSTR3_ ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D プログラマブルゲインアンプコントロールレジスタ（ADPGACR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adpgacr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B1>  P000SEL1;
			bit_rw_t<io_, bitpos::B2>  P000ENAMP;
		};
		typedef adpgacr_t<base + 0x1A0>  ADPGACR_;
		static  ADPGACR_ ADPGACR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D プログラマブルゲインアンプゲイン設定レジスタ 0（ADPGAGS0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adpgags0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  P000GAIN;
		};
		typedef adpgags0_t<base + 0x1A2>  ADPGAGS0_;
		static  ADPGAGS0_ ADPGAGS0;
	};
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADDR_ s12ad0_t<base, per>::ADDR;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADDR16_ s12ad0_t<base, per>::ADDR16;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADANSA_ s12ad0_t<base, per>::ADANSA;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADANSA0_ s12ad0_t<base, per>::ADANSA0;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADANSA1_ s12ad0_t<base, per>::ADANSA1;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADANSB_ s12ad0_t<base, per>::ADANSB;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADANSB0_ s12ad0_t<base, per>::ADANSB0;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADANSB1_ s12ad0_t<base, per>::ADANSB1;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADANSC_ s12ad0_t<base, per>::ADANSC;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADANSC0_ s12ad0_t<base, per>::ADANSC0;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADANSC1_ s12ad0_t<base, per>::ADANSC1;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADADS0_ s12ad0_t<base, per>::ADADS0;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADADS1_ s12ad0_t<base, per>::ADADS1;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADSSTR_ s12ad0_t<base, per>::ADSSTR;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADSSTRL_ s12ad0_t<base, per>::ADSSTRL;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADSSTR0_ s12ad0_t<base, per>::ADSSTR0;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADSSTR1_ s12ad0_t<base, per>::ADSSTR1;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADSSTR2_ s12ad0_t<base, per>::ADSSTR2;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADSSTR3_ s12ad0_t<base, per>::ADSSTR3;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADPGACR_ s12ad0_t<base, per>::ADPGACR;
	 template <uint32_t base, peripheral per> typename s12ad0_t<base, per>::ADPGAGS0_ s12ad0_t<base, per>::ADPGAGS0;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD1 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct s12ad1_t : public s12ad_t<base> {

		static constexpr auto PERIPHERAL = per;  ///< ペリフェラル型
		static constexpr auto S12ADI = ICU::VECTOR::S12ADI1;	///< スキャン終了割り込みベクター
		static constexpr auto GBADI  = ICU::VECTOR::GBADI1;		///< グループＢスキャン終了割り込みベクター
		static constexpr auto GCADI  = ICU::VECTOR::GCADI1;		///< グループＣスキャン終了割り込みベクター
		static constexpr uint32_t ANALOG_NUM = 5;	///< アナログ入力数


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
			AIN116 = 0x10,
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
				PORT4::PDR.B4 = 0;
				MPC::P44PFS.ASEL = f;
				break;
			case ANALOG::AIN101:
				PORT4::PDR.B5 = 0;
				MPC::P45PFS.ASEL = f;
				break;
			case ANALOG::AIN102:
				PORT4::PDR.B6 = 0;
				MPC::P46PFS.ASEL = f;
				break;
			case ANALOG::AIN103:
				PORT4::PDR.B7 = 0;
				MPC::P47PFS.ASEL = f;
				break;
			case ANALOG::AIN116:
				PORT2::PDR.B1 = 0;
				MPC::P21PFS.ASEL = f;
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
			uint16_t operator() (ANALOG an) {
				return rd16_(base + 0x20 + static_cast<uint32_t>(an) * 2);
			}
		};
		typedef addr_t ADDR_;
		static  ADDR_ ADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ 16（ADDR16）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x40> ADDR16_;
		static  ADDR16_ ADDR16;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ定義 (ADANS)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct adans_t {
			void set(ANALOG an, bool f = true) {
				uint32_t n = static_cast<uint32_t>(an);
				uint32_t ros = ofs;
				if(n >= 4) {
					n -= 4;
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
				if(n >= 4) {
					n -= 4;
					ros += 2;
				}
				return (rd16_(ros) >> n) & 1;
			}
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 A
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0x04> ADANSA_;
		static  ADANSA_ ADANSA;


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

			bit_rw_t<io_, bitpos::B0>  ANSA100;
		};
		typedef adansa1_t<base + 0x06>   ADANSA1_;
		static  ADANSA1_ ADANSA1;


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
		};
		typedef adansb0_t<base + 0x14>   ADANSB0_;
		static  ADANSB0_ ADANSB0;


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

			bit_rw_t<io_, bitpos::B0>  ANSB100;
		};
		typedef adansb1_t<base + 0x16>   ADANSB1_;
		static  ADANSB1_ ADANSB1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0xD4> ADANSC_;
		static  ADANSC_ ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0（ADANSC0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSC000;
			bit_rw_t<io_, bitpos::B1>  ANSC001;
			bit_rw_t<io_, bitpos::B2>  ANSC002;
			bit_rw_t<io_, bitpos::B3>  ANSC003;
		};
		typedef adansc0_t<base + 0xD4>   ADANSC0_;
		static  ADANSC0_ ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C1（ADANSC1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSC100;
		};
		typedef adansc1_t<base + 0xD6>   ADANSC1_;
		static  ADANSC1_ ADANSC1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ
		*/
		//-----------------------------------------------------------------//
		struct adsstr_t {
			void set(ANALOG an, uint8_t v) {
				if(an == ANALOG::AIN016) {
					wr8_(base + 0xDD + static_cast<uint32_t>(an), v);
				} else {
					wr8_(base + 0xE0 + static_cast<uint32_t>(an), v);
				}
			}
		};
		typedef adsstr_t ADSSTR_;
		static  ADSSTR_ ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ L（ADSSTRL）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xDD> ADSSTRL_;
		static  ADSSTRL_ ADSSTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE0> ADSSTR0_;
		static  ADSSTR0_ ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE1> ADSSTR1_;
		static  ADSSTR1_ ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE2> ADSSTR2_;
		static  ADSSTR2_ ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE3> ADSSTR3_;
		static  ADSSTR3_ ADSSTR3;


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
	};
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADDR_ s12ad1_t<base, per>::ADDR;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADDR16_ s12ad1_t<base, per>::ADDR16;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADANSA_ s12ad1_t<base, per>::ADANSA;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADANSA0_ s12ad1_t<base, per>::ADANSA0;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADANSA1_ s12ad1_t<base, per>::ADANSA1;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADANSB_ s12ad1_t<base, per>::ADANSB;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADANSB0_ s12ad1_t<base, per>::ADANSB0;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADANSB1_ s12ad1_t<base, per>::ADANSB1;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADANSC_ s12ad1_t<base, per>::ADANSC;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADANSC0_ s12ad1_t<base, per>::ADANSC0;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADANSC1_ s12ad1_t<base, per>::ADANSC1;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADSSTR_ s12ad1_t<base, per>::ADSSTR;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADSSTRL_ s12ad1_t<base, per>::ADSSTRL;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADSSTR0_ s12ad1_t<base, per>::ADSSTR0;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADSSTR1_ s12ad1_t<base, per>::ADSSTR1;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADSSTR2_ s12ad1_t<base, per>::ADSSTR2;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADSSTR3_ s12ad1_t<base, per>::ADSSTR3;
	template <uint32_t base, peripheral per> typename s12ad1_t<base, per>::ADSHCR_ s12ad1_t<base, per>::ADSHCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  S12AD2 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct s12ad2_t : public s12ad_t<base> {

		static constexpr auto PERIPHERAL = per;					///< ペリフェラル型
		static constexpr auto S12ADI = ICU::VECTOR::S12ADI2;	///< スキャン終了割り込みベクター
		static constexpr auto GBADI  = ICU::VECTOR::GBADI2;		///< グループＢスキャン終了割り込みベクター
		static constexpr auto GCADI  = ICU::VECTOR::GCADI2;		///< グループＣスキャン終了割り込みベクター
		static constexpr uint32_t ANALOG_NUM = 12;	///< アナログ入力数


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			AIN200,
			AIN201,
			AIN202,
			AIN203,
			AIN204,
			AIN205,
			AIN206,
			AIN207,
			AIN208,
			AIN209,
			AIN210,
			AIN211,
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
			case ANALOG::AIN200:
				PORT6::PDR.B0 = 0;
				MPC::P60PFS.ASEL = f;
				break;
			case ANALOG::AIN201:
				PORT6::PDR.B1 = 0;
				MPC::P61PFS.ASEL = f;
				break;
			case ANALOG::AIN202:
				PORT6::PDR.B2 = 0;
				MPC::P62PFS.ASEL = f;
				break;
			case ANALOG::AIN203:
				PORT6::PDR.B3 = 0;
				MPC::P63PFS.ASEL = f;
				break;
			case ANALOG::AIN204:
				PORT6::PDR.B4 = 0;
				MPC::P64PFS.ASEL = f;
				break;
			case ANALOG::AIN205:
				PORT6::PDR.B5 = 0;
				MPC::P65PFS.ASEL = f;
				break;
			case ANALOG::AIN206:
				PORT5::PDR.B0 = 0;
				MPC::P50PFS.ASEL = f;
				break;
			case ANALOG::AIN207:
				PORT5::PDR.B1 = 0;
				MPC::P51PFS.ASEL = f;
				break;
			case ANALOG::AIN208:
				PORT5::PDR.B2 = 0;
				MPC::P52PFS.ASEL = f;
				break;
			case ANALOG::AIN209:
				PORT5::PDR.B3 = 0;
				MPC::P53PFS.ASEL = f;
				break;
			case ANALOG::AIN210:
				PORT5::PDR.B4 = 0;
				MPC::P54PFS.ASEL = f;
				break;
			case ANALOG::AIN211:
				PORT5::PDR.B5 = 0;
				MPC::P55PFS.ASEL = f;
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
			uint16_t operator() (ANALOG an) {
				return rd16_(base + 0x20 + static_cast<uint32_t>(an) * 2);
			}
		};
		typedef addr_t ADDR_;
		static  ADDR_ ADDR;


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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D チャネル選択レジスタ定義 (ADANS)
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
		typedef adans_t<base + 0x04> ADANSA_;
		static  ADANSA_ ADANSA;


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
			bit_rw_t<io_, bitpos::B4>  ANSB004;
			bit_rw_t<io_, bitpos::B5>  ANSB005;
			bit_rw_t<io_, bitpos::B6>  ANSB006;
			bit_rw_t<io_, bitpos::B7>  ANSB007;
			bit_rw_t<io_, bitpos::B8>  ANSB008;
			bit_rw_t<io_, bitpos::B9>  ANSB009;
			bit_rw_t<io_, bitpos::B10> ANSB010;
			bit_rw_t<io_, bitpos::B11> ANSB011;
		};
		typedef adansa0_t<base + 0x04>   ADANSA0_;
		static  ADANSA0_ ADANSA0;


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
			bit_rw_t<io_, bitpos::B8>  ANSB008;
			bit_rw_t<io_, bitpos::B9>  ANSB009;
			bit_rw_t<io_, bitpos::B10> ANSB010;
			bit_rw_t<io_, bitpos::B11> ANSB011;
		};
		typedef adansb0_t<base + 0x14>   ADANSB0_;
		static  ADANSB0_ ADANSB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ設定 C
		*/
		//-----------------------------------------------------------------//
		typedef adans_t<base + 0xD4> ADANSC_;
		static  ADANSC_ ADANSC;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D チャネル選択レジスタ C0（ADANSC0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adansc0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  ANSC000;
			bit_rw_t<io_, bitpos::B1>  ANSC001;
			bit_rw_t<io_, bitpos::B2>  ANSC002;
			bit_rw_t<io_, bitpos::B3>  ANSC003;
			bit_rw_t<io_, bitpos::B4>  ANSB004;
			bit_rw_t<io_, bitpos::B5>  ANSB005;
			bit_rw_t<io_, bitpos::B6>  ANSB006;
			bit_rw_t<io_, bitpos::B7>  ANSB007;
			bit_rw_t<io_, bitpos::B8>  ANSB008;
			bit_rw_t<io_, bitpos::B9>  ANSB009;
			bit_rw_t<io_, bitpos::B10> ANSB010;
			bit_rw_t<io_, bitpos::B11> ANSB011;
		};
		typedef adansc0_t<base + 0xD4>   ADANSC0_;
		static  ADANSC0_ ADANSC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 内部基準電圧データレジスタ（ADOCDR）
		*/
		//-----------------------------------------------------------------//
		typedef ro16_t<base + 0x1C> ADOCDR_;
		static  ADOCDR_ ADOCDR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換拡張入力コントロールレジスタ（ADEXICR）
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

			bit_rw_t<io_, bitpos::B1>  OCSAD;
			bit_rw_t<io_, bitpos::B9>  OCSA;
		};
		typedef adexicr_t<base + 0x12>  ADEXICR_;
		static  ADEXICR_ ADEXICR;


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
			@brief  A/D サンプリングステートレジスタ 0（ADSSTR0）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE0> ADSSTR0_;
		static  ADSSTR0_ ADSSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 1（ADSSTR1）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE1> ADSSTR1_;
		static  ADSSTR1_ ADSSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 2（ADSSTR2）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE2> ADSSTR2_;
		static  ADSSTR2_ ADSSTR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 3（ADSSTR3）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE3> ADSSTR3_;
		static  ADSSTR3_ ADSSTR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 4（ADSSTR4）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE4> ADSSTR4_;
		static  ADSSTR4_ ADSSTR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 5（ADSSTR5）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE5> ADSSTR5_;
		static  ADSSTR5_ ADSSTR5;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 6（ADSSTR6）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE6> ADSSTR6_;
		static  ADSSTR6_ ADSSTR6;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 7（ADSSTR7）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE7> ADSSTR7_;
		static  ADSSTR7_ ADSSTR7;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 8（ADSSTR8）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE8> ADSSTR8_;
		static  ADSSTR8_ ADSSTR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 9（ADSSTR9）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xE9> ADSSTR9_;
		static  ADSSTR9_ ADSSTR9;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 10（ADSSTR10）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xEA> ADSSTR10_;
		static  ADSSTR10_ ADSSTR10;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ 11（ADSSTR11）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0xEB> ADSSTR11_;
		static  ADSSTR11_ ADSSTR11;
	};
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADDR_ s12ad2_t<base, per>::ADDR;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADDR4_ s12ad2_t<base, per>::ADDR4;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADDR5_ s12ad2_t<base, per>::ADDR5;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADDR6_ s12ad2_t<base, per>::ADDR6;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADDR7_ s12ad2_t<base, per>::ADDR7;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADDR8_ s12ad2_t<base, per>::ADDR8;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADDR9_ s12ad2_t<base, per>::ADDR9;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADDR10_ s12ad2_t<base, per>::ADDR10;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADDR11_ s12ad2_t<base, per>::ADDR11;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADANSA_ s12ad2_t<base, per>::ADANSA;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADANSA0_ s12ad2_t<base, per>::ADANSA0;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADANSB_ s12ad2_t<base, per>::ADANSB;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADANSB0_ s12ad2_t<base, per>::ADANSB0;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADANSC_ s12ad2_t<base, per>::ADANSC;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADANSC0_ s12ad2_t<base, per>::ADANSC0;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADOCDR_ s12ad2_t<base, per>::ADOCDR;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADEXICR_ s12ad2_t<base, per>::ADEXICR;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADSSTR_ s12ad2_t<base, per>::ADSSTR;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADSSTR0_ s12ad2_t<base, per>::ADSSTR0;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADSSTR1_ s12ad2_t<base, per>::ADSSTR1;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADSSTR2_ s12ad2_t<base, per>::ADSSTR2;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADSSTR3_ s12ad2_t<base, per>::ADSSTR3;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADSSTR4_ s12ad2_t<base, per>::ADSSTR4;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADSSTR5_ s12ad2_t<base, per>::ADSSTR5;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADSSTR6_ s12ad2_t<base, per>::ADSSTR6;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADSSTR7_ s12ad2_t<base, per>::ADSSTR7;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADSSTR8_ s12ad2_t<base, per>::ADSSTR8;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADSSTR9_ s12ad2_t<base, per>::ADSSTR9;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADSSTR10_ s12ad2_t<base, per>::ADSSTR10;
	template <uint32_t base, peripheral per> typename s12ad2_t<base, per>::ADSSTR11_ s12ad2_t<base, per>::ADSSTR11;

	typedef s12ad0_t<0x00089000, peripheral::S12AD>  S12AD;
	typedef s12ad1_t<0x00089200, peripheral::S12AD1> S12AD1;
	typedef s12ad2_t<0x00089400, peripheral::S12AD2> S12AD2;
}
