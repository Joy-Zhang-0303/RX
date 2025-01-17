#pragma once
//=========================================================================//
/*!	@file
	@brief	RX64M/RX71M ポートアウトプットイネーブル 3（POE3a）定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポートアウトプットイネーブル 3 クラス
		@param[in]	base	POE3 モジュール先頭アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct poe3_t {

		static constexpr auto PERIPHERAL = peripheral::POE3;	///< ペリフェラル型
		static constexpr auto OEI1 = ICU::GROUPBL1::OEI1;		///< アウトプットイネーブル割り込み1
		static constexpr auto OEI2 = ICU::GROUPBL1::OEI2;		///< アウトプットイネーブル割り込み2
		static constexpr auto OEI3 = ICU::GROUPBL1::OEI3;		///< アウトプットイネーブル割り込み3
		static constexpr auto OEI4 = ICU::GROUPBL1::OEI4;		///< アウトプットイネーブル割り込み4
		static constexpr auto OEI5 = ICU::VECTOR::NONE;			///< アウトプットイネーブル割り込み5


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 1（ICSR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE0M;

			bit_rw_t <io_, bitpos::B8>     PIE1;

			bit_rw_t <io_, bitpos::B12>    POE0F;
		};
		typedef icsr1_t<base + 0x00> ICSR1_;
		static  ICSR1_ ICSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 2（ICSR2）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr2_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE4M;

			bit_rw_t <io_, bitpos::B8>     PIE2;

			bit_rw_t <io_, bitpos::B12>    POE4F;
		};
		typedef icsr2_t<base + 0x04> ICSR2_;
		static  ICSR2_ ICSR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 3（ICSR3）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr3_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE8M;

			bit_rw_t <io_, bitpos::B8>     PIE3;
			bit_rw_t <io_, bitpos::B9>     POE8E;

			bit_rw_t <io_, bitpos::B12>    POE8F;
		};
		typedef icsr3_t<base + 0x08> ICSR3_;
		static  ICSR3_ ICSR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 4（ICSR4）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr4_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE10M;

			bit_rw_t <io_, bitpos::B8>     PIE4;
			bit_rw_t <io_, bitpos::B9>     POE10E;

			bit_rw_t <io_, bitpos::B12>    POE10F;
		};
		typedef icsr4_t<base + 0x16> ICSR4_;
		static  ICSR4_ ICSR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 5（ICSR5）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr5_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE11M;

			bit_rw_t <io_, bitpos::B8>     PIE5;
			bit_rw_t <io_, bitpos::B9>     POE11E;

			bit_rw_t <io_, bitpos::B12>    POE11F;
		};
		typedef icsr5_t<base + 0x18> ICSR5_;
		static  ICSR5_ ICSR5;
	

		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 6（ICSR6）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr6_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B9>     OSTSTE;

			bit_rw_t <io_, bitpos::B12>    OSTSTF;
		};
		typedef icsr6_t<base + 0x1C> ICSR6_;
		static  ICSR6_ ICSR6;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 1（OCSR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ocsr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   OIE1;
			bit_rw_t<io_, bitpos::B9>   OCE1;

			bit_rw_t<io_, bitpos::B15>  OSF1;
		};
		typedef ocsr1_t<base + 0x02> OCSR1_;
		static  OCSR1_ OCSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 2（OCSR2）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ocsr2_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   OIE2;
			bit_rw_t<io_, bitpos::B9>   OCE2;

			bit_rw_t<io_, bitpos::B15>  OSF2;
		};
		typedef ocsr2_t<base + 0x06> OCSR2_;
		static  OCSR2_ OCSR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 1（ALR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct alr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  OLSG0A;
			bit_rw_t<io_, bitpos::B1>  OLSG0B;
			bit_rw_t<io_, bitpos::B2>  OLSG1A;
			bit_rw_t<io_, bitpos::B3>  OLSG1B;
			bit_rw_t<io_, bitpos::B4>  OLSG2A;
			bit_rw_t<io_, bitpos::B5>  OLSG2B;

			bit_rw_t<io_, bitpos::B7>  OLSEN;
		};
		typedef alr1_t<base + 0x1A> ALR1_;
		static  ALR1_ ALR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	ソフトウェアポートアウトプットイネーブルレジスタ（SPOER）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct spoer_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTUCH34HIZ;
			bit_rw_t<io_, bitpos::B1>  MTUCH67HIZ;
			bit_rw_t<io_, bitpos::B2>  MTUCH0HIZ;
			bit_rw_t<io_, bitpos::B3>  GPT01HIZ;
			bit_rw_t<io_, bitpos::B4>  GPT03HIZ;
		};
		typedef spoer_t<base + 0x0A> SPOER_;
		static  SPOER_ SPOER;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 1（POECR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU0AZE;
			bit_rw_t<io_, bitpos::B1>  MTU0BZE;
			bit_rw_t<io_, bitpos::B2>  MTU0CZE;
			bit_rw_t<io_, bitpos::B3>  MTU0DZE;
		};
		typedef poecr1_t<base + 0x0B> POECR1_;
		static  POECR1_ POECR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 2（POECR2）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr2_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU7BDZE;
			bit_rw_t<io_, bitpos::B1>  MTU7ACZE;
			bit_rw_t<io_, bitpos::B2>  MTU6BDZE;

			bit_rw_t<io_, bitpos::B8>  MTU4BDZE;
			bit_rw_t<io_, bitpos::B9>  MTU4ACZE;
			bit_rw_t<io_, bitpos::B10> MTU3BDZE;
		};
		typedef poecr2_t<base + 0x0C> POECR2_;
		static  POECR2_ POECR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 3（POECR3）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr3_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   GPT0ABZE;
			bit_rw_t<io_, bitpos::B1>   GPT1ABZE;

			bit_rw_t<io_, bitpos::B8>   GPT2ABZE;
			bit_rw_t<io_, bitpos::B9>   GPT3ABZE;
		};
		typedef poecr3_t<base + 0x0E> POECR3_;
		static  POECR3_ POECR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 4（POECR4）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr4_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B2>  IC2ADDMT34ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT34ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT34ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT34ZE;

			bit_rw_t<io_, bitpos::B9>  IC1ADDMT67ZE;

			bit_rw_t<io_, bitpos::B11> IC3ADDMT67ZE;
			bit_rw_t<io_, bitpos::B12> IC4ADDMT67ZE;
			bit_rw_t<io_, bitpos::B13> IC5ADDMT67ZE;
		};
		typedef poecr4_t<base + 0x10> POECR4_;
		static  POECR4_ POECR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 5（POECR5）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr5_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B1>  IC1ADDMT0ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT0ZE;

			bit_rw_t<io_, bitpos::B4>  IC4ADDMT0ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT0ZE;
		};
		typedef poecr5_t<base + 0x12> POECR5_;
		static  POECR5_ POECR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 6（POECR6）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr6_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B1>  IC1ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDGPT01ZE;

			bit_rw_t<io_, bitpos::B5>  IC5ADDGPT01ZE;

			bit_rw_t<io_, bitpos::B9>  IC1ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B10> IC2ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B11> IC3ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B12> IC4ADDGPT23ZE;
		};
		typedef poecr6_t<base + 0x14> POECR6_;
		static  POECR6_ POECR6;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPT0 端子選択レジスタ（G0SELR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct g0selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G0ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G0BSEL;
		};
		typedef g0selr_t<base + 0x20> G0SELR_;
		static  G0SELR_ G0SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPT1 端子選択レジスタ（G1SELR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct g1selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G1ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G1BSEL;
		};
		typedef g1selr_t<base + 0x21> G1SELR_;
		static  G1SELR_ G1SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPT2 端子選択レジスタ（G2SELR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct g2selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G2ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G2BSEL;
		};
		typedef g2selr_t<base + 0x22> G2SELR_;
		static  G2SELR_ G2SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPT3 端子選択レジスタ（G3SELR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct g3selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G3ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G3BSEL;
		};
		typedef g3selr_t<base + 0x23> G3SELR_;
		static  G3SELR_ G3SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU0 端子選択レジスタ 1（M0SELR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct m0selr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M0ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M0BSEL;
		};
		typedef m0selr1_t<base + 0x24> M0SELR1_;
		static  M0SELR1_ M0SELR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU0 端子選択レジスタ 2（M0SELR2）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct m0selr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M0CSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M0DSEL;
		};
		typedef m0selr2_t<base + 0x25> M0SELR2_;
		static  M0SELR2_ M0SELR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU3 端子選択レジスタ（M3SELR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct m3selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M3ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M3BSEL;
		};
		typedef m3selr_t<base + 0x26> M3SELR_;
		static  M3SELR_ M3SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU4 端子選択レジスタ 1（M4SELR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct m4selr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M4ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M4CSEL;
		};
		typedef m4selr1_t<base + 0x27> M4SELR1_;
		static  M4SELR1_ M4SELR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU4 端子選択レジスタ 2（M4SELR2）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct m4selr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M4BSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M4DSEL;
		};
		typedef m4selr2_t<base + 0x27> M4SELR2_;
		static  M4SELR2_ M4SELR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU/GPT 端子機能選択レジスタ（MGSELR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct mgselr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  M3G0SEL;
			bit_rw_t<io_, bitpos::B1>  M4G1SEL;
			bit_rw_t<io_, bitpos::B2>  M4G2SEL;
		};
		typedef mgselr_t<base + 0x29> MGSELR_;
		static  MGSELR_ MGSELR;
	};
	template <uint32_t base> typename poe3_t<base>::ICSR1_ poe3_t<base>::ICSR1;
	template <uint32_t base> typename poe3_t<base>::ICSR2_ poe3_t<base>::ICSR2;
	template <uint32_t base> typename poe3_t<base>::ICSR3_ poe3_t<base>::ICSR3;
	template <uint32_t base> typename poe3_t<base>::ICSR4_ poe3_t<base>::ICSR4;
	template <uint32_t base> typename poe3_t<base>::ICSR5_ poe3_t<base>::ICSR5;
	template <uint32_t base> typename poe3_t<base>::ICSR6_ poe3_t<base>::ICSR6;
	template <uint32_t base> typename poe3_t<base>::OCSR1_ poe3_t<base>::OCSR1;
	template <uint32_t base> typename poe3_t<base>::OCSR2_ poe3_t<base>::OCSR2;
	template <uint32_t base> typename poe3_t<base>::ALR1_ poe3_t<base>::ALR1;
	template <uint32_t base> typename poe3_t<base>::SPOER_ poe3_t<base>::SPOER;
	template <uint32_t base> typename poe3_t<base>::POECR1_ poe3_t<base>::POECR1;
	template <uint32_t base> typename poe3_t<base>::POECR2_ poe3_t<base>::POECR2;
	template <uint32_t base> typename poe3_t<base>::POECR3_ poe3_t<base>::POECR3;
	template <uint32_t base> typename poe3_t<base>::POECR4_ poe3_t<base>::POECR4;
	template <uint32_t base> typename poe3_t<base>::POECR5_ poe3_t<base>::POECR5;
	template <uint32_t base> typename poe3_t<base>::POECR6_ poe3_t<base>::POECR6;
	template <uint32_t base> typename poe3_t<base>::G0SELR_ poe3_t<base>::G0SELR;
	template <uint32_t base> typename poe3_t<base>::G1SELR_ poe3_t<base>::G1SELR;
	template <uint32_t base> typename poe3_t<base>::G2SELR_ poe3_t<base>::G2SELR;
	template <uint32_t base> typename poe3_t<base>::G3SELR_ poe3_t<base>::G3SELR;	
	template <uint32_t base> typename poe3_t<base>::M0SELR1_ poe3_t<base>::M0SELR1;
	template <uint32_t base> typename poe3_t<base>::M0SELR2_ poe3_t<base>::M0SELR2;
	template <uint32_t base> typename poe3_t<base>::M3SELR_ poe3_t<base>::M3SELR;
	template <uint32_t base> typename poe3_t<base>::M4SELR1_ poe3_t<base>::M4SELR1;
	template <uint32_t base> typename poe3_t<base>::M4SELR2_ poe3_t<base>::M4SELR2;
	template <uint32_t base> typename poe3_t<base>::MGSELR_ poe3_t<base>::MGSELR;

	typedef poe3_t<0x0008'C4C0> POE3;
}
