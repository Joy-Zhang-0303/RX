#pragma once
//=========================================================================//
/*!	@file
	@brief	RX63T グループ・GPT 定義
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
		@brief  GPT タイマクラス (0, 1, 2, 3)
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct gpt_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマソフトウェアスタートレジスタ (GTSTR)
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtstr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CST0;
			bit_rw_t<io_, bitpos::B1>  CST1;
			bit_rw_t<io_, bitpos::B2>  CST2;
			bit_rw_t<io_, bitpos::B3>  CST3;
		};
		typedef gtstr_t<base + 0x00> GTSTR_;
		static  GTSTR_ GTSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェア要因スタート / ストップ制御レジスタ（GTHSCR）
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gthscr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2>  CSHW0;
			bits_rw_t<io_, bitpos::B2,  2>  CSHW1;
			bits_rw_t<io_, bitpos::B4,  2>  CSHW2;
			bits_rw_t<io_, bitpos::B6,  2>  CSHW3;
			bits_rw_t<io_, bitpos::B8,  2>  CPHW0;
			bits_rw_t<io_, bitpos::B10, 2>  CPHW1;
			bits_rw_t<io_, bitpos::B12, 2>  CPHW2;
			bits_rw_t<io_, bitpos::B14, 2>  CPHW3;
		};
		typedef gthscr_t<base + 0x04> GTHSCR_;
		static  GTHSCR_ GTHSCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェア要因クリア制御レジスタ（GTHCCR）
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gthccr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CCHW0;
			bits_rw_t<io_, bitpos::B2, 2>  CCHW1;
			bits_rw_t<io_, bitpos::B4, 2>  CCHW2;
			bits_rw_t<io_, bitpos::B6, 2>  CCHW3;
			bit_rw_t <io_, bitpos::B8>     CCSW0;
			bit_rw_t <io_, bitpos::B9>     CCSW1;
			bit_rw_t <io_, bitpos::B10>    CCSW2;
			bit_rw_t <io_, bitpos::B11>    CCSW3;
		};
		typedef gthccr_t<base + 0x06> GTHCCR_;
		static  GTHCCR_ GTHCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェアスタート要因セレクトレジスタ (GTHSSR)
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gthssr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4>  CSHSL0;
			bits_rw_t<io_, bitpos::B4,  4>  CSHSL1;
			bits_rw_t<io_, bitpos::B8,  4>  CSHSL2;
			bits_rw_t<io_, bitpos::B12, 4>  CSHSL3;
		};
		typedef gthssr_t<base + 0x08> GTHSSR_;
		static  GTHSSR_ GTHSSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェアストップ / クリア要因セレクトレジスタ（GTHPSR）
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gthpsr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4>  CSHPL0;
			bits_rw_t<io_, bitpos::B4,  4>  CSHPL1;
			bits_rw_t<io_, bitpos::B8,  4>  CSHPL2;
			bits_rw_t<io_, bitpos::B12, 4>  CSHPL3;
		};
		typedef gthpsr_t<base + 0x0A> GTHPSR_;
		static  GTHPSR_ GTHPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ書き込み保護レジスタ (GTWP)
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gtwp_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   WP0;
			bit_rw_t<io_, bitpos::B1>   WP1;
			bit_rw_t<io_, bitpos::B2>   WP2;
			bit_rw_t<io_, bitpos::B3>   WP3;
		};
		typedef gtwp_t<base + 0x0C> GTWP_;
		static  GTWP_ GTWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマシンクロレジスタ (GTSYNC)
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gtsync_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2>  SYNC0;
			bits_rw_t<io_, bitpos::B4,  2>  SYNC1;
			bits_rw_t<io_, bitpos::B8,  2>  SYNC2;
			bits_rw_t<io_, bitpos::B12, 2>  SYNC3;
		};
		typedef gtsync_t<base + 0x0E> GTSYNC_;
		static  GTSYNC_ GTSYNC;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ外部トリガ入力割り込みレジスタ (GTETINT)
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gtetint_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>      ETIPEN;
			bit_rw_t< io_, bitpos::B1>      ETINEN;

			bit_rw_t< io_, bitpos::B8>      ETIPF;
			bit_rw_t< io_, bitpos::B9>      ETINF;
		};
		typedef gtetint_t<base + 0x10> GTETINT_;
		static  GTETINT_ GTETINT;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマバッファ動作禁止レジスタ (GTBDR)
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gtbdr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>    BD00;
			bit_rw_t<io_, bitpos::B1>    BD01;
			bit_rw_t<io_, bitpos::B2>    BD02;
			bit_rw_t<io_, bitpos::B3>    BD03;
			bit_rw_t<io_, bitpos::B4>    BD10;
			bit_rw_t<io_, bitpos::B5>    BD11;
			bit_rw_t<io_, bitpos::B6>    BD12;
			bit_rw_t<io_, bitpos::B7>    BD13;
			bit_rw_t<io_, bitpos::B8>    BD20;
			bit_rw_t<io_, bitpos::B9>    BD21;
			bit_rw_t<io_, bitpos::B10>   BD22;
			bit_rw_t<io_, bitpos::B11>   BD23;
			bit_rw_t<io_, bitpos::B12>   BD30;
			bit_rw_t<io_, bitpos::B13>   BD31;
			bit_rw_t<io_, bitpos::B14>   BD32;
			bit_rw_t<io_, bitpos::B15>   BD33;
		};
		typedef gtbdr_t<base + 0x14> GTBDR_;
		static  GTBDR_ GTBDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマスタート書き込み保護レジスタ (GTSWP)
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gtswp_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SWP0;
			bit_rw_t<io_, bitpos::B1>  SWP1;
			bit_rw_t<io_, bitpos::B2>  SWP2;
			bit_rw_t<io_, bitpos::B3>  SWP3;
		};
		typedef gtswp_t<base + 0x18> GTSWP_;
		static  GTSWP_ GTSWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウントコントロールレジスタ（LCCR）
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct lccr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     LCNTE;
			bit_rw_t <io_, bitpos::B1>     LCNTCR;
			bit_rw_t <io_, bitpos::B2>     LCNTS;

			bit_rw_t <io_, bitpos::B4>     LCINTC;
			bit_rw_t <io_, bitpos::B5>     LCINTD;
			bit_rw_t <io_, bitpos::B6>     LCINTO;

			bits_rw_t<io_, bitpos::B8, 3>  LCTO;
			bit_rw_t <io_, bitpos::B11>    LCNTAT;
			bits_rw_t<io_, bitpos::B12, 2> TPSC;
			bits_rw_t<io_, bitpos::B14, 2> LPSC;
		};
		typedef lccr_t<base + 0x80> LCCR_;
		static LCCR_ LCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウントステータスレジスタ（LCST）
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct lcst_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  LISC;
			bit_rw_t<io_, bitpos::B1>  LISD;
			bit_rw_t<io_, bitpos::B2>  LISO;
		};
		typedef lcst_t<base + 0x82> LCST_;
		static LCST_ LCST;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント値レジスタ（LCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 84> LCNT_;
		static LCNT_ LCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント結果平均レジスタ（LCNTA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x86> LCNTA_;
		static LCNTA_ LCNTA;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント結果レジスタ n（LCNTn）(n=00 ～ 15) 
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x88> LCNT00_;
		static LCNT00_ LCNT00;
		typedef rw16_t<base + 0x8A> LCNT01_;
		static LCNT01_ LCNT01;
		typedef rw16_t<base + 0x8C> LCNT02_;
		static LCNT02_ LCNT02;
		typedef rw16_t<base + 0x8E> LCNT03_;
		static LCNT03_ LCNT03;
		typedef rw16_t<base + 0x90> LCNT04_;
		static LCNT04_ LCNT04;
		typedef rw16_t<base + 0x92> LCNT05_;
		static LCNT05_ LCNT05;
		typedef rw16_t<base + 0x94> LCNT06_;
		static LCNT06_ LCNT06;
		typedef rw16_t<base + 0x96> LCNT07_;
		static LCNT07_ LCNT07;
		typedef rw16_t<base + 0x98> LCNT08_;
		static LCNT08_ LCNT08;
		typedef rw16_t<base + 0x9A> LCNT09_;
		static LCNT09_ LCNT09;
		typedef rw16_t<base + 0x9C> LCNT10_;
		static LCNT10_ LCNT10;
		typedef rw16_t<base + 0x9E> LCNT11_;
		static LCNT11_ LCNT11;
		typedef rw16_t<base + 0xA0> LCNT12_;
		static LCNT12_ LCNT12;
		typedef rw16_t<base + 0xA2> LCNT13_;
		static LCNT13_ LCNT13;
		typedef rw16_t<base + 0xA4> LCNT14_;
		static LCNT14_ LCNT14;
		typedef rw16_t<base + 0xA6> LCNT15_;
		static LCNT15_ LCNT15;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント上限／下限許容偏差値レジスタ（LCNTDU、LCNTDL）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0xA8> LCNTDU_;
		static LCNTDU_ LCNTDU;
		typedef rw16_t<base + 0xAA> LCNTDL_;
		static LCNTDL_ LCNTDL;
	};
	template <uint32_t base> typename gpt_t<base>::GTSTR_ gpt_t<base>::GTSTR;
	template <uint32_t base> typename gpt_t<base>::GTHSCR_ gpt_t<base>::GTHSCR;
	template <uint32_t base> typename gpt_t<base>::GTHCCR_ gpt_t<base>::GTHCCR;
	template <uint32_t base> typename gpt_t<base>::GTHSSR_ gpt_t<base>::GTHSSR;
	template <uint32_t base> typename gpt_t<base>::GTHPSR_ gpt_t<base>::GTHPSR;
	template <uint32_t base> typename gpt_t<base>::GTWP_ gpt_t<base>::GTWP;
	template <uint32_t base> typename gpt_t<base>::GTSYNC_ gpt_t<base>::GTSYNC;
	template <uint32_t base> typename gpt_t<base>::GTETINT_ gpt_t<base>::GTETINT;
	template <uint32_t base> typename gpt_t<base>::GTBDR_ gpt_t<base>::GTBDR;
	template <uint32_t base> typename gpt_t<base>::GTSWP_ gpt_t<base>::GTSWP;
	template <uint32_t base> typename gpt_t<base>::LCCR_ gpt_t<base>::LCCR;
	template <uint32_t base> typename gpt_t<base>::LCNT_ gpt_t<base>::LCNT;
	template <uint32_t base> typename gpt_t<base>::LCNTA_ gpt_t<base>::LCNTA;
	template <uint32_t base> typename gpt_t<base>::LCNT00_ gpt_t<base>::LCNT00;
	template <uint32_t base> typename gpt_t<base>::LCNT01_ gpt_t<base>::LCNT01;
	template <uint32_t base> typename gpt_t<base>::LCNT02_ gpt_t<base>::LCNT02;
	template <uint32_t base> typename gpt_t<base>::LCNT03_ gpt_t<base>::LCNT03;
	template <uint32_t base> typename gpt_t<base>::LCNT04_ gpt_t<base>::LCNT04;
	template <uint32_t base> typename gpt_t<base>::LCNT05_ gpt_t<base>::LCNT05;
	template <uint32_t base> typename gpt_t<base>::LCNT06_ gpt_t<base>::LCNT06;
	template <uint32_t base> typename gpt_t<base>::LCNT07_ gpt_t<base>::LCNT07;
	template <uint32_t base> typename gpt_t<base>::LCNT08_ gpt_t<base>::LCNT08;
	template <uint32_t base> typename gpt_t<base>::LCNT09_ gpt_t<base>::LCNT09;
	template <uint32_t base> typename gpt_t<base>::LCNT10_ gpt_t<base>::LCNT10;
	template <uint32_t base> typename gpt_t<base>::LCNT11_ gpt_t<base>::LCNT11;
	template <uint32_t base> typename gpt_t<base>::LCNT12_ gpt_t<base>::LCNT12;
	template <uint32_t base> typename gpt_t<base>::LCNT13_ gpt_t<base>::LCNT13;
	template <uint32_t base> typename gpt_t<base>::LCNT14_ gpt_t<base>::LCNT14;
	template <uint32_t base> typename gpt_t<base>::LCNT15_ gpt_t<base>::LCNT15;
	template <uint32_t base> typename gpt_t<base>::LCNTDU_ gpt_t<base>::LCNTDU;
	template <uint32_t base> typename gpt_t<base>::LCNTDL_ gpt_t<base>::LCNTDL;

	typedef gpt_t<0x000C'2000> GPT;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPTB タイマクラス (4, 5, 6, 7)
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct gptb_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマソフトウェアスタートレジスタ (GTSTR)
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtstr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CST4;
			bit_rw_t<io_, bitpos::B1>  CST5;
			bit_rw_t<io_, bitpos::B2>  CST6;
			bit_rw_t<io_, bitpos::B3>  CST7;
		};
		typedef gtstr_t<base + 0x00> GTSTR_;
		static  GTSTR_ GTSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェア要因スタート / ストップ制御レジスタ（GTHSCR）
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gthscr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2>  CSHW4;
			bits_rw_t<io_, bitpos::B2,  2>  CSHW5;
			bits_rw_t<io_, bitpos::B4,  2>  CSHW6;
			bits_rw_t<io_, bitpos::B6,  2>  CSHW7;
			bits_rw_t<io_, bitpos::B8,  2>  CPHW4;
			bits_rw_t<io_, bitpos::B10, 2>  CPHW5;
			bits_rw_t<io_, bitpos::B12, 2>  CPHW6;
			bits_rw_t<io_, bitpos::B14, 2>  CPHW7;
		};
		typedef gthscr_t<base + 0x04> GTHSCR_;
		static  GTHSCR_ GTHSCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェア要因クリア制御レジスタ（GTHCCR）
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gthccr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CCHW4;
			bits_rw_t<io_, bitpos::B2, 2>  CCHW5;
			bits_rw_t<io_, bitpos::B4, 2>  CCHW6;
			bits_rw_t<io_, bitpos::B6, 2>  CCHW7;
			bit_rw_t <io_, bitpos::B8>     CCSW4;
			bit_rw_t <io_, bitpos::B9>     CCSW5;
			bit_rw_t <io_, bitpos::B10>    CCSW6;
			bit_rw_t <io_, bitpos::B11>    CCSW7;
		};
		typedef gthccr_t<base + 0x06> GTHCCR_;
		static  GTHCCR_ GTHCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェアスタート要因セレクトレジスタ (GTHSSR)
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gthssr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4>  CSHSL4;
			bits_rw_t<io_, bitpos::B4,  4>  CSHSL5;
			bits_rw_t<io_, bitpos::B8,  4>  CSHSL6;
			bits_rw_t<io_, bitpos::B12, 4>  CSHSL7;
		};
		typedef gthssr_t<base + 0x08> GTHSSR_;
		static  GTHSSR_ GTHSSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェアストップ / クリア要因セレクトレジスタ（GTHPSR）
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gthpsr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4>  CSHPL4;
			bits_rw_t<io_, bitpos::B4,  4>  CSHPL5;
			bits_rw_t<io_, bitpos::B8,  4>  CSHPL6;
			bits_rw_t<io_, bitpos::B12, 4>  CSHPL7;
		};
		typedef gthpsr_t<base + 0x0A> GTHPSR_;
		static  GTHPSR_ GTHPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ書き込み保護レジスタ (GTWP)
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gtwp_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   WP4;
			bit_rw_t<io_, bitpos::B1>   WP5;
			bit_rw_t<io_, bitpos::B2>   WP6;
			bit_rw_t<io_, bitpos::B3>   WP7;
		};
		typedef gtwp_t<base + 0x0C> GTWP_;
		static  GTWP_ GTWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマシンクロレジスタ (GTSYNC)
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gtsync_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2>  SYNC4;
			bits_rw_t<io_, bitpos::B4,  2>  SYNC5;
			bits_rw_t<io_, bitpos::B8,  2>  SYNC6;
			bits_rw_t<io_, bitpos::B12, 2>  SYNC7;
		};
		typedef gtsync_t<base + 0x0E> GTSYNC_;
		static  GTSYNC_ GTSYNC;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ外部トリガ入力割り込みレジスタ (GTETINT)
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gtetint_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>      ETIPEN;
			bit_rw_t< io_, bitpos::B1>      ETINEN;

			bit_rw_t< io_, bitpos::B8>      ETIPF;
			bit_rw_t< io_, bitpos::B9>      ETINF;
		};
		typedef gtetint_t<base + 0x10> GTETINT_;
		static  GTETINT_ GTETINT;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマバッファ動作禁止レジスタ (GTBDR)
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gtbdr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>    BD40;
			bit_rw_t<io_, bitpos::B1>    BD41;
			bit_rw_t<io_, bitpos::B2>    BD42;
			bit_rw_t<io_, bitpos::B3>    BD43;
			bit_rw_t<io_, bitpos::B4>    BD50;
			bit_rw_t<io_, bitpos::B5>    BD51;
			bit_rw_t<io_, bitpos::B6>    BD52;
			bit_rw_t<io_, bitpos::B7>    BD53;
			bit_rw_t<io_, bitpos::B8>    BD60;
			bit_rw_t<io_, bitpos::B9>    BD61;
			bit_rw_t<io_, bitpos::B10>   BD62;
			bit_rw_t<io_, bitpos::B11>   BD63;
			bit_rw_t<io_, bitpos::B12>   BD70;
			bit_rw_t<io_, bitpos::B13>   BD71;
			bit_rw_t<io_, bitpos::B14>   BD72;
			bit_rw_t<io_, bitpos::B15>   BD73;
		};
		typedef gtbdr_t<base + 0x14> GTBDR_;
		static  GTBDR_ GTBDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマスタート書き込み保護レジスタ (GTSWP)
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct gtswp_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SWP4;
			bit_rw_t<io_, bitpos::B1>  SWP5;
			bit_rw_t<io_, bitpos::B2>  SWP6;
			bit_rw_t<io_, bitpos::B3>  SWP7;
		};
		typedef gtswp_t<base + 0x18> GTSWP_;
		static  GTSWP_ GTSWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウントコントロールレジスタ（LCCR）
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct lccr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     LCNTE;
			bit_rw_t <io_, bitpos::B1>     LCNTCR;
			bit_rw_t <io_, bitpos::B2>     LCNTS;

			bit_rw_t <io_, bitpos::B4>     LCINTC;
			bit_rw_t <io_, bitpos::B5>     LCINTD;
			bit_rw_t <io_, bitpos::B6>     LCINTO;

			bits_rw_t<io_, bitpos::B8, 3>  LCTO;
			bit_rw_t <io_, bitpos::B11>    LCNTAT;
			bits_rw_t<io_, bitpos::B12, 2> TPSC;
			bits_rw_t<io_, bitpos::B14, 2> LPSC;
		};
		typedef lccr_t<base + 0x80> LCCR_;
		static LCCR_ LCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウントステータスレジスタ（LCST）
			@param[in]	ofs		オフセットアドレス
		*/
		//-----------------------------------------------------------------//
		template<uint32_t ofs>
		struct lcst_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  LISC;
			bit_rw_t<io_, bitpos::B1>  LISD;
			bit_rw_t<io_, bitpos::B2>  LISO;
		};
		typedef lcst_t<base + 0x82> LCST_;
		static LCST_ LCST;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント値レジスタ（LCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 84> LCNT_;
		static LCNT_ LCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント結果平均レジスタ（LCNTA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x86> LCNTA_;
		static LCNTA_ LCNTA;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント結果レジスタ n（LCNTn）(n=00 ～ 15) 
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x88> LCNT00_;
		static LCNT00_ LCNT00;
		typedef rw16_t<base + 0x8A> LCNT01_;
		static LCNT01_ LCNT01;
		typedef rw16_t<base + 0x8C> LCNT02_;
		static LCNT02_ LCNT02;
		typedef rw16_t<base + 0x8E> LCNT03_;
		static LCNT03_ LCNT03;
		typedef rw16_t<base + 0x90> LCNT04_;
		static LCNT04_ LCNT04;
		typedef rw16_t<base + 0x92> LCNT05_;
		static LCNT05_ LCNT05;
		typedef rw16_t<base + 0x94> LCNT06_;
		static LCNT06_ LCNT06;
		typedef rw16_t<base + 0x96> LCNT07_;
		static LCNT07_ LCNT07;
		typedef rw16_t<base + 0x98> LCNT08_;
		static LCNT08_ LCNT08;
		typedef rw16_t<base + 0x9A> LCNT09_;
		static LCNT09_ LCNT09;
		typedef rw16_t<base + 0x9C> LCNT10_;
		static LCNT10_ LCNT10;
		typedef rw16_t<base + 0x9E> LCNT11_;
		static LCNT11_ LCNT11;
		typedef rw16_t<base + 0xA0> LCNT12_;
		static LCNT12_ LCNT12;
		typedef rw16_t<base + 0xA2> LCNT13_;
		static LCNT13_ LCNT13;
		typedef rw16_t<base + 0xA4> LCNT14_;
		static LCNT14_ LCNT14;
		typedef rw16_t<base + 0xA6> LCNT15_;
		static LCNT15_ LCNT15;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント上限／下限許容偏差値レジスタ（LCNTDU、LCNTDL）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0xA8> LCNTDU_;
		static LCNTDU_ LCNTDU;
		typedef rw16_t<base + 0xAA> LCNTDL_;
		static LCNTDL_ LCNTDL;
	};
	template <uint32_t base> typename gptb_t<base>::GTSTR_ gptb_t<base>::GTSTR;
	template <uint32_t base> typename gptb_t<base>::GTHSCR_ gptb_t<base>::GTHSCR;
	template <uint32_t base> typename gptb_t<base>::GTHCCR_ gptb_t<base>::GTHCCR;
	template <uint32_t base> typename gptb_t<base>::GTHSSR_ gptb_t<base>::GTHSSR;
	template <uint32_t base> typename gptb_t<base>::GTHPSR_ gptb_t<base>::GTHPSR;
	template <uint32_t base> typename gptb_t<base>::GTWP_ gptb_t<base>::GTWP;
	template <uint32_t base> typename gptb_t<base>::GTSYNC_ gptb_t<base>::GTSYNC;
	template <uint32_t base> typename gptb_t<base>::GTETINT_ gptb_t<base>::GTETINT;
	template <uint32_t base> typename gptb_t<base>::GTBDR_ gptb_t<base>::GTBDR;
	template <uint32_t base> typename gptb_t<base>::GTSWP_ gptb_t<base>::GTSWP;
	template <uint32_t base> typename gptb_t<base>::LCCR_ gptb_t<base>::LCCR;
	template <uint32_t base> typename gptb_t<base>::LCNT_ gptb_t<base>::LCNT;
	template <uint32_t base> typename gptb_t<base>::LCNTA_ gptb_t<base>::LCNTA;
	template <uint32_t base> typename gptb_t<base>::LCNT00_ gptb_t<base>::LCNT00;
	template <uint32_t base> typename gptb_t<base>::LCNT01_ gptb_t<base>::LCNT01;
	template <uint32_t base> typename gptb_t<base>::LCNT02_ gptb_t<base>::LCNT02;
	template <uint32_t base> typename gptb_t<base>::LCNT03_ gptb_t<base>::LCNT03;
	template <uint32_t base> typename gptb_t<base>::LCNT04_ gptb_t<base>::LCNT04;
	template <uint32_t base> typename gptb_t<base>::LCNT05_ gptb_t<base>::LCNT05;
	template <uint32_t base> typename gptb_t<base>::LCNT06_ gptb_t<base>::LCNT06;
	template <uint32_t base> typename gptb_t<base>::LCNT07_ gptb_t<base>::LCNT07;
	template <uint32_t base> typename gptb_t<base>::LCNT08_ gptb_t<base>::LCNT08;
	template <uint32_t base> typename gptb_t<base>::LCNT09_ gptb_t<base>::LCNT09;
	template <uint32_t base> typename gptb_t<base>::LCNT10_ gptb_t<base>::LCNT10;
	template <uint32_t base> typename gptb_t<base>::LCNT11_ gptb_t<base>::LCNT11;
	template <uint32_t base> typename gptb_t<base>::LCNT12_ gptb_t<base>::LCNT12;
	template <uint32_t base> typename gptb_t<base>::LCNT13_ gptb_t<base>::LCNT13;
	template <uint32_t base> typename gptb_t<base>::LCNT14_ gptb_t<base>::LCNT14;
	template <uint32_t base> typename gptb_t<base>::LCNT15_ gptb_t<base>::LCNT15;
	template <uint32_t base> typename gptb_t<base>::LCNTDU_ gptb_t<base>::LCNTDU;
	template <uint32_t base> typename gptb_t<base>::LCNTDL_ gptb_t<base>::LCNTDL;

	typedef gptb_t<0x000C'2800> GPTB;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPTn 定義基底クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct gptn_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ I/O コントロールレジスタ (GTIOR)
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtior_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6> GTIOA;
			bit_rw_t <io_, bitpos::B6>    OADFLT;
			bit_rw_t <io_, bitpos::B7>    OAHLD;
			bits_rw_t<io_, bitpos::B8, 6> GTIOB;
			bit_rw_t <io_, bitpos::B14>   OBDFLT;
			bit_rw_t <io_, bitpos::B15>   OBHLD;
		};
		typedef gtior_t<base + 0x00> GTIOR_;
		static  GTIOR_ GTIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ 割り込み出力設定レジスタ (GTINTAD)
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtintad_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>    GTINTA;
			bit_rw_t< io_, bitpos::B1>    GTINTB;
			bit_rw_t< io_, bitpos::B2>    GTINTC;
			bit_rw_t< io_, bitpos::B3>    GTINTD;
			bit_rw_t< io_, bitpos::B4>    GTINTE;
			bit_rw_t< io_, bitpos::B5>    GTINTF;
			bits_rw_t<io_, bitpos::B6, 2> GTINTPR;

			bit_rw_t< io_, bitpos::B11>   EINT;
			bit_rw_t< io_, bitpos::B12>   ADTRAUEN;
			bit_rw_t< io_, bitpos::B13>   ADTRADEN;
			bit_rw_t< io_, bitpos::B14>   ADTRBUEN;
			bit_rw_t< io_, bitpos::B15>   ADTRBDEN;
		};
		typedef gtintad_t<base + 0x02> GTINTAD_;
		static  GTINTAD_ GTINTAD;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマコントロールレジスタ (GTCR)
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  3>  MD;
			bits_rw_t<io_, bitpos::B8,  4>  TPCS;
			bits_rw_t<io_, bitpos::B12, 2>  CCLR;
		};
		typedef gtcr_t<base + 0x04> GTCR_;
		static  GTCR_ GTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマバッファイネーブルレジスタ (GTBER)
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtber_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CCRA;
			bits_rw_t<io_, bitpos::B2, 2>  CCRB;
			bits_rw_t<io_, bitpos::B4, 2>  PR;
			bit_rw_t< io_, bitpos::B6>     CCRSWT;

			bits_rw_t<io_, bitpos::B8, 2>  ADTTA;
			bit_rw_t< io_, bitpos::B10>    ADTDA;
			bits_rw_t<io_, bitpos::B12, 2> ADTTB;
			bit_rw_t< io_, bitpos::B14>    ADTDB;
		};
		typedef gtber_t<base + 0x06> GTBER_;
		static  GTBER_ GTBER;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマカウント方向レジスタ (GTUDC)
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtudc_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>     UD;
			bit_rw_t< io_, bitpos::B1>     UDF;
			bits_rw_t<io_, bitpos::B8, 2>  OADTY;
			bit_rw_t< io_, bitpos::B10>    OADTYF;
			bit_rw_t< io_, bitpos::B11>    OADTYR;
			bits_rw_t<io_, bitpos::B12, 2> OBDTY;
			bit_rw_t< io_, bitpos::B14>    OBDTYF;
			bit_rw_t< io_, bitpos::B15>    OBDTYR;
		};
		typedef gtudc_t<base + 0x08> GTUDC_;
		static  GTUDC_ GTUDC;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ割り込み、A/D 変換開始要求間引き設定レジスタ (GTITC)
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtitc_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>     ITLA;
			bit_rw_t< io_, bitpos::B1>     ITLB;
			bit_rw_t< io_, bitpos::B2>     ITLC;
			bit_rw_t< io_, bitpos::B3>     ITLD;
			bit_rw_t< io_, bitpos::B4>     ITLE;
			bit_rw_t< io_, bitpos::B5>     ITLF;
			bits_rw_t<io_, bitpos::B6, 2 > IVTC;
			bits_rw_t<io_, bitpos::B8, 3 > IVTT;

			bit_rw_t< io_, bitpos::B12>    ADTAL;

			bit_rw_t< io_, bitpos::B14>    ADTBL;
		};
		typedef gtitc_t<base + 0x0A> GTITC_;
		static  GTITC_ GTITC;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマステータスレジスタ (GTST)
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtst_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>    TCFA;
			bit_rw_t< io_, bitpos::B1>    TCFB;
			bit_rw_t< io_, bitpos::B2>    TCFC;
			bit_rw_t< io_, bitpos::B3>    TCFD;
			bit_rw_t< io_, bitpos::B4>    TCFE;
			bit_rw_t< io_, bitpos::B5>    TCFF;
			bit_rw_t< io_, bitpos::B6>    TCFPO;
			bit_rw_t< io_, bitpos::B7>    TCFPU;
			bits_rw_t<io_, bitpos::B8, 3> ITCNT;
			bit_rw_t< io_, bitpos::B11>   DTEF;

			bit_rw_t< io_, bitpos::B15>   TUCF;
		};
		typedef gtst_t<base + 0x0C> GTST_;
		static  GTST_ GTST;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマカウンタ (GTCNT)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x0E> GTCNT_;
		static  GTCNT_ GTCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマコンペアキャプチャレジスタ m（GTCCRm）（m = A ～ F）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x10> GTCCRA_;
		static  GTCCRA_ GTCCRA;
		typedef rw16_t<base + 0x12> GTCCRB_;
		static  GTCCRB_ GTCCRB;
		typedef rw16_t<base + 0x14> GTCCRC_;
		static  GTCCRC_ GTCCRC;
		typedef rw16_t<base + 0x16> GTCCRD_;
		static  GTCCRD_ GTCCRD;
		typedef rw16_t<base + 0x18> GTCCRE_;
		static  GTCCRE_ GTCCRE;
		typedef rw16_t<base + 0x1A> GTCCRF_;
		static  GTCCRF_ GTCCRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ周期設定レジスタ (GTPR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x1C> GTPR_;
		static  GTPR_ GTPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ周期設定バッファレジスタ (GTPBR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x1E> GTPBR_;
		static  GTPBR_ GTPBR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ周期設定ダブルバッファレジスタ (GTPDBR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x20> GTPDBR_;
		static  GTPDBR_ GTPDBR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングレジスタｍ (GTADTRm)(m=A, B)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x24> GTADTRA_;
		static  GTADTRA_ GTADTRA;
		typedef rw16_t<base + 0x2C> GTADTRB_;
		static  GTADTRB_ GTADTRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングバッファレジスタｍ (GTADTBRm)(m=A, B)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x26> GTADTBRA_;
		static  GTADTBRA_ GTADTBRA;
		typedef rw16_t<base + 0x2E> GTADTBRB_;
		static  GTADTBRB_ GTADTBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングダブルバッファレジスタｍ (GTADTDBRm)(m=A, B)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x28> GTADTDBRA_;
		static  GTADTDBRA_ GTADTDBRA;
		typedef rw16_t<base + 0x30> GTADTDBRB_;
		static  GTADTDBRB_ GTADTDBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ出力ネゲートコントロールレジスタ (GTONCR)
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtoncr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>    NEA;
			bit_rw_t< io_, bitpos::B1>    NEB;
			bit_rw_t< io_, bitpos::B2>    NVA;
			bit_rw_t< io_, bitpos::B3>    NVB;
			bits_rw_t<io_, bitpos::B4, 4> NFS;
			bit_rw_t< io_, bitpos::B8>    NFV;

			bit_rw_t< io_, bitpos::B12>   SWN;

			bit_rw_t< io_, bitpos::B14>   OAE;
			bit_rw_t< io_, bitpos::B15>   OBE;
		};
		typedef gtoncr_t<base + 0x34> GTONCR_;
		static  GTONCR_ GTONCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマデッドタイムコントロールレジスタ (GTDTCR)
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtdtcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>  TDE;
			bit_rw_t< io_, bitpos::B4>  TDBUE;
			bit_rw_t< io_, bitpos::B5>  TDBDE;
			bit_rw_t< io_, bitpos::B8>  TDFER;
		};
		typedef gtdtcr_t<base + 0x36> GTDTCR_;
		static  GTDTCR_ GTDTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマデッドタイム値レジスタｍ (GTDVm)(m=U, D)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x38> GTDVU_;
		static  GTDVU_ GTDVU;
		typedef rw16_t<base + 0x3A> GTDVD_;
		static  GTDVD_ GTDVD;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマデッドタイムバッファレジスタｍ (GTDBm)(m=U, D)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x3C> GTDBU_;
		static  GTDBU_ GTDBU;
		typedef rw16_t<base + 0x3E> GTDBD_;
		static  GTDBD_ GTDBD;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ出力保護機能ステータスレジスタ (GTSOS)
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtsos_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  SOS;
		};
		typedef gtsos_t<base + 0x40> GTSOS_;
		static  GTSOS_ GTSOS;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ出力保護機能一時解除レジスタ (GTSOTR)
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtsotr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SOTR;
		};
		typedef gtsos_t<base + 0x42> GTSOTR_;
		static  GTSOTR_ GTSOTR;
	};
	template <uint32_t base> typename gptn_t<base>::GTIOR_ gptn_t<base>::GTIOR;
	template <uint32_t base> typename gptn_t<base>::GTINTAD_ gptn_t<base>::GTINTAD;
	template <uint32_t base> typename gptn_t<base>::GTCR_ gptn_t<base>::GTCR;
	template <uint32_t base> typename gptn_t<base>::GTBER_ gptn_t<base>::GTBER;
	template <uint32_t base> typename gptn_t<base>::GTUDC_ gptn_t<base>::GTUDC;
	template <uint32_t base> typename gptn_t<base>::GTITC_ gptn_t<base>::GTITC;
	template <uint32_t base> typename gptn_t<base>::GTST_ gptn_t<base>::GTST;
	template <uint32_t base> typename gptn_t<base>::GTCNT_ gptn_t<base>::GTCNT;
	template <uint32_t base> typename gptn_t<base>::GTCCRA_ gptn_t<base>::GTCCRA;
	template <uint32_t base> typename gptn_t<base>::GTCCRB_ gptn_t<base>::GTCCRB;
	template <uint32_t base> typename gptn_t<base>::GTCCRC_ gptn_t<base>::GTCCRC;
	template <uint32_t base> typename gptn_t<base>::GTCCRD_ gptn_t<base>::GTCCRD;
	template <uint32_t base> typename gptn_t<base>::GTCCRE_ gptn_t<base>::GTCCRE;
	template <uint32_t base> typename gptn_t<base>::GTCCRF_ gptn_t<base>::GTCCRF;
	template <uint32_t base> typename gptn_t<base>::GTPR_ gptn_t<base>::GTPR;
	template <uint32_t base> typename gptn_t<base>::GTPBR_ gptn_t<base>::GTPBR;
	template <uint32_t base> typename gptn_t<base>::GTPDBR_ gptn_t<base>::GTPDBR;
	template <uint32_t base> typename gptn_t<base>::GTADTRA_ gptn_t<base>::GTADTRA;
	template <uint32_t base> typename gptn_t<base>::GTADTRB_ gptn_t<base>::GTADTRB;
	template <uint32_t base> typename gptn_t<base>::GTADTBRA_ gptn_t<base>::GTADTBRA;
	template <uint32_t base> typename gptn_t<base>::GTADTBRB_ gptn_t<base>::GTADTBRB;
	template <uint32_t base> typename gptn_t<base>::GTADTDBRA_ gptn_t<base>::GTADTDBRA;
	template <uint32_t base> typename gptn_t<base>::GTADTDBRB_ gptn_t<base>::GTADTDBRB;
	template <uint32_t base> typename gptn_t<base>::GTONCR_ gptn_t<base>::GTONCR;
	template <uint32_t base> typename gptn_t<base>::GTDTCR_ gptn_t<base>::GTDTCR;
	template <uint32_t base> typename gptn_t<base>::GTDVU_ gptn_t<base>::GTDVU;
	template <uint32_t base> typename gptn_t<base>::GTDVD_ gptn_t<base>::GTDVD;
	template <uint32_t base> typename gptn_t<base>::GTDBU_ gptn_t<base>::GTDBU;
	template <uint32_t base> typename gptn_t<base>::GTDBD_ gptn_t<base>::GTDBD;
	template <uint32_t base> typename gptn_t<base>::GTSOS_ gptn_t<base>::GTSOS;
	template <uint32_t base> typename gptn_t<base>::GTSOTR_ gptn_t<base>::GTSOTR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT[0123] 定義クラス
		@param[in]	chno	チャネル番号
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t chno>
	struct gptm_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  PWM 出力遅延制御レジスタ （GTDLYCR)
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtdlycr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SOTR;
		};
		typedef gtdlycr_t<0x000C'2300 + (chno * 2)> GTDLYCR_;
		static GTDLYCR_ GTDLYCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  GTIOCA 立ち上がり出力遅延レジスタ（GTDLYRA）
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct gtdlyrx_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  DLY;
		};
		typedef gtdlyrx_t<0x000C'2318 + (chno * 2)> GTDLYRA_;
		static GTDLYRA_ GTDLYRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  GTIOCA 立ち上がり出力遅延レジスタ（GTDLYFA）
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		typedef gtdlyrx_t<0x000C'2328 + (chno * 2)> GTDLYFA_;
		static GTDLYFA_ GTDLYFA;


		//-----------------------------------------------------------------//
		/*!
			@brief  GTIOCB 立ち上がり出力遅延レジスタ（GTDLYRB）
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		typedef gtdlyrx_t<0x000C'231A + (chno * 2)> GTDLYRB_;
		static GTDLYRB_ GTDLYRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  GTIOCB 立ち上がり出力遅延レジスタ（GTDLYFB）
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		typedef gtdlyrx_t<0x000C'232A + (chno * 2)> GTDLYFB_;
		static GTDLYFB_ GTDLYFB;
	};
	template <uint32_t chno> typename gptm_t<chno>::GTDLYCR_ gptm_t<chno>::GTDLYCR;
	template <uint32_t chno> typename gptm_t<chno>::GTDLYRA_ gptm_t<chno>::GTDLYRA;
	template <uint32_t chno> typename gptm_t<chno>::GTDLYFA_ gptm_t<chno>::GTDLYFA;
	template <uint32_t chno> typename gptm_t<chno>::GTDLYRB_ gptm_t<chno>::GTDLYRB;
	template <uint32_t chno> typename gptm_t<chno>::GTDLYFB_ gptm_t<chno>::GTDLYFB;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT 共通定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct gpt_defs {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマハードウェアスタート要因型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GTHSCR_CSHW : uint8_t {
			NONE,		///< スタートしない
			POSITIVE,	///< 立上りエッジでスタート
			NEGATIVE,	///< 立下りエッジでスタート
			BOSE,		///< 両エッジでスタート
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマハードウェアストップ要因型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GTHSCR_CPHW : uint8_t {
			NONE,		///< スタートしない
			POSITIVE,	///< 立上りエッジでスタート
			NEGATIVE,	///< 立下りエッジでスタート
			BOSE,		///< 両エッジでスタート
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマハードウェアクリア要因型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GTHCCR_CCHW : uint8_t {
			NONE,		///< スタートしない
			POSITIVE,	///< 立上りエッジでスタート
			NEGATIVE,	///< 立下りエッジでスタート
			BOSE,		///< 両エッジでスタート
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマハードウェアスタート要因選択型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GTHSSR_CSHSL : uint8_t {
			AN000 = 0b0000,		///< AN000 コンパレーター検出
			AN001 = 0b0001,		///< AN001 コンパレーター検出
			AN002 = 0b0010,		///< AN002 コンパレーター検出

			AN100 = 0b0100,		///< AN100 コンパレーター検出
			AN101 = 0b0101,		///< AN101 コンパレーター検出
			AN102 = 0b0110,		///< AN102 コンパレーター検出

			INA   = 0b1000,		///< GTIOC3A 端子入力（GPT[4567]: GTIOC7A）
			INB   = 0b1001,		///< GTIOC3B 端子入力（GPT[4567]: GTIOC7B）

			OUTA  = 0b1010,		///< GTIOC3A 端子出力（GPT[4567]: GTIOC7A）
			OUTB  = 0b1011,		///< GTIOC3B 端子出力（GPT[4567]: GTIOC7A）

			TRG0  = 0b1100,		///< GTETRG0 端子入力
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマハードウェアストップ要因選択型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GTHPSR_CSHPL : uint8_t {
			AN000 = 0b0000,		///< AN000 コンパレーター検出
			AN001 = 0b0001,		///< AN001 コンパレーター検出
			AN002 = 0b0010,		///< AN002 コンパレーター検出

			AN100 = 0b0100,		///< AN100 コンパレーター検出
			AN101 = 0b0101,		///< AN101 コンパレーター検出
			AN102 = 0b0110,		///< AN102 コンパレーター検出

			INA   = 0b1000,		///< GTIOC3A 端子入力（GPT[4567]: GTIOC7A）
			INB   = 0b1001,		///< GTIOC3B 端子入力（GPT[4567]: GTIOC7B）

			OUTA  = 0b1010,		///< GTIOC3A 端子出力（GPT[4567]: GTIOC7A）
			OUTB  = 0b1011,		///< GTIOC3B 端子出力（GPT[4567]: GTIOC7A）

			TRG0  = 0b1100,		///< GTETRG0 端子入力
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT0123 定義クラス
		@param[in]	base	ベース・アドレス
		@param[in]	chno	チャネル番号
		@param[in]	per		ペリフェラル型
		@param[in]	veca	A 割り込みベクター型
		@param[in]	vecb	B 割り込みベクター型
		@param[in]	vecc	C 割り込みベクター型
		@param[in]	vece	E 割り込みベクター型
		@param[in]	vecv	V 割り込みベクター型
		@param[in]	veci	I 割り込みベクター型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, uint32_t chno, peripheral per,
		ICU::VECTOR veca, ICU::VECTOR vecb, ICU::VECTOR vecc, ICU::VECTOR vece, ICU::VECTOR vecv, ICU::VECTOR veci>
	struct gpt0123_t : public gpt_defs, GPT, gptn_t<base>, gptm_t<chno> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto CHNO = chno;		///< チャネル番号
		static constexpr auto PCLK = clock_profile::PCLKA;  ///< クロック周期
		static constexpr auto GTCIA = veca;		///< GTCIA 割り込みベクター
		static constexpr auto GTCIB = vecb;		///< GTCIB 割り込みベクター
		static constexpr auto GTCIC = vecc;		///< GTCIC 割り込みベクター
		static constexpr auto GTCIE = vece;		///< GTCIE 割り込みベクター
		static constexpr auto GTCIV = vecv;		///< GTCIV 割り込みベクター
		static constexpr auto LOCOI = veci;		///< LOCOI 割り込みベクター


		//-----------------------------------------------------------------//
		/*!
			@brief  GPT 開始
			@param[in]	ena		停止の場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true) noexcept
		{
			switch(CHNO) {
			case 0: GTSTR.CST0 = ena; break;
			case 1: GTSTR.CST1 = ena; break;
			case 2: GTSTR.CST2 = ena; break;
			case 3: GTSTR.CST3 = ena; break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマハードウェア要因スタートコントロールレジスタ（GTHSCR）
			@param[in]	cshw	スタート要因
			@param[in]	cphw	ストップ要因
		*/
		//-----------------------------------------------------------------//
		static void set(GTHSCR_CSHW cshw, GTHSCR_CPHW cphw) noexcept
		{
			switch(CHNO) {
			case 0:
				GTHSCR = GTHSCR.CSHW0.b(static_cast<uint8_t>(cshw)) | GTHSCR.CPHW0.b(static_cast<uint8_t>(cphw));
				break;
			case 1:
				GTHSCR = GTHSCR.CSHW1.b(static_cast<uint8_t>(cshw)) | GTHSCR.CPHW1.b(static_cast<uint8_t>(cphw));
				break;
			case 2:
				GTHSCR = GTHSCR.CSHW2.b(static_cast<uint8_t>(cshw)) | GTHSCR.CPHW2.b(static_cast<uint8_t>(cphw));
				break;
			case 3:
				GTHSCR = GTHSCR.CSHW3.b(static_cast<uint8_t>(cshw)) | GTHSCR.CPHW3.b(static_cast<uint8_t>(cphw));
				break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマハードウェア要因クリアコントロールレジスタ（GTHCCR）
			@param[in]	cshw	クリア要因
			@param[in]	ena		クリアを行う場合「true」
		*/
		//-----------------------------------------------------------------//
		static void set(GTHCCR_CCHW cchw, bool ena) noexcept
		{
			switch(CHNO) {
			case 0:
				GTHCCR = GTHCCR.CCHW0.b(static_cast<uint8_t>(cchw)) | GTHCCR.CCSW0.b(ena);
				break;
			case 1:
				GTHCCR = GTHCCR.CCHW1.b(static_cast<uint8_t>(cchw)) | GTHCCR.CCSW1.b(ena);
				break;
			case 2:
				GTHCCR = GTHCCR.CCHW2.b(static_cast<uint8_t>(cchw)) | GTHCCR.CCSW2.b(ena);
				break;
			case 3:
				GTHCCR = GTHCCR.CCHW3.b(static_cast<uint8_t>(cchw)) | GTHCCR.CCSW3.b(ena);
				break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマハードウェアスタート要因セレクトレジスタ（GTHSSR）
			@param[in]	cshsl	スタート要因
		*/
		//-----------------------------------------------------------------//
		static void set(GTHSSR_CSHSL cshsl) noexcept
		{
			switch(CHNO) {
			case 0:
				GTHSSR.CSHSL0 = static_cast<uint8_t>(cshsl);
				break;
			case 1:
				GTHSSR.CSHSL1 = static_cast<uint8_t>(cshsl);
				break;
			case 2:
				GTHSSR.CSHSL2 = static_cast<uint8_t>(cshsl);
				break;
			case 3:
				GTHSSR.CSHSL3 = static_cast<uint8_t>(cshsl);
				break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマハードウェアストップ・クリア要因セレクトレジスタ（GTHPSR）
			@param[in]	cshsl	スタート要因
		*/
		//-----------------------------------------------------------------//
		static void set(GTHPSR_CSHPL cshpl) noexcept
		{
			switch(CHNO) {
			case 0:
				GTHPSR.CSHPL0 = static_cast<uint8_t>(cshpl);
				break;
			case 1:
				GTHPSR.CSHPL1 = static_cast<uint8_t>(cshpl);
				break;
			case 2:
				GTHPSR.CSHPL2 = static_cast<uint8_t>(cshpl);
				break;
			case 3:
				GTHPSR.CSHPL3 = static_cast<uint8_t>(cshpl);
				break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ書き込み保護レジスタ（GTWP）
			@param[in]	ena		保護の場合「true」
		*/
		//-----------------------------------------------------------------//
		static void write_protect(bool ena = true) noexcept
		{
			switch(CHNO) {
			case 0: GTWP.WP0 = ena; break;
			case 1: GTWP.WP1 = ena; break;
			case 2: GTWP.WP2 = ena; break;
			case 3: GTWP.WP3 = ena; break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマシンクロレジスタ（GTSYNC）
			@param[in]	ch		同期チャネル（０～３）
		*/
		//-----------------------------------------------------------------//
		static void sync(uint8_t ch) noexcept
		{
			switch(CHNO) {
			case 0: GTSYNC.SYNC0 = ch; break;
			case 1: GTSYNC.SYNC1 = ch; break;
			case 2: GTSYNC.SYNC2 = ch; break;
			case 3: GTSYNC.SYNC3 = ch; break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作禁止レジスタ（GTBDR）
			@param[in]	ccr		GTCCR  バッファを禁止する場合「true」
			@param[in]	pr		GTPR   バッファを禁止する場合「true」
			@param[in]	adtr	GTADTR バッファを禁止する場合「true」
			@param[in]	dv		GTDV   バッファを禁止する場合「true」
		*/
		//-----------------------------------------------------------------//
		static void buffer_disable(bool ccr, bool pr, bool adtr, bool dv) noexcept
		{
			switch(CHNO) {
			case 0:
				GTBDR.BD00 = ccr;
				GTBDR.BD01 = pr;
				GTBDR.BD02 = adtr;
				GTBDR.BD03 = dv;
				break;
			case 1:
				GTBDR.BD10 = ccr;
				GTBDR.BD11 = pr;
				GTBDR.BD12 = adtr;
				GTBDR.BD13 = dv;
				break;
			case 2:
				GTBDR.BD20 = ccr;
				GTBDR.BD21 = pr;
				GTBDR.BD22 = adtr;
				GTBDR.BD23 = dv;
				break;
			case 3:
				GTBDR.BD30 = ccr;
				GTBDR.BD31 = pr;
				GTBDR.BD32 = adtr;
				GTBDR.BD33 = dv;
				break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマスタート書き込み保護レジスタ（GTSWP）
			@param[in]	ena		保護の場合「true」
		*/
		//-----------------------------------------------------------------//
		static void start_protect(bool ena = true) noexcept
		{
			switch(CHNO) {
			case 0: GTSWP.SWP0 = ena; break;
			case 1: GTSWP.SWP1 = ena; break;
			case 2: GTSWP.SWP2 = ena; break;
			case 3: GTSWP.SWP3 = ena; break;
			default:
				break;
			}
		}
	};
	typedef gpt0123_t<0x000C'2100, 0, peripheral::GPT0,
		ICU::VECTOR::GTCIA0, ICU::VECTOR::GTCIB0, ICU::VECTOR::GTCIC0, ICU::VECTOR::GTCIE0, ICU::VECTOR::GTCIV0, ICU::VECTOR::LOCOI0> GPT0;
	typedef gpt0123_t<0x000C'2180, 1, peripheral::GPT1,
		ICU::VECTOR::GTCIA1, ICU::VECTOR::GTCIB1, ICU::VECTOR::GTCIC1, ICU::VECTOR::GTCIE1, ICU::VECTOR::GTCIV1, ICU::VECTOR::NONE> GPT1;
	typedef gpt0123_t<0x000C'2200, 2, peripheral::GPT2,
		ICU::VECTOR::GTCIA2, ICU::VECTOR::GTCIB2, ICU::VECTOR::GTCIC2, ICU::VECTOR::GTCIE2, ICU::VECTOR::GTCIV2, ICU::VECTOR::NONE> GPT2;
	typedef gpt0123_t<0x000C'2280, 3, peripheral::GPT3,
		ICU::VECTOR::GTCIA3, ICU::VECTOR::GTCIB3, ICU::VECTOR::GTCIC3, ICU::VECTOR::GTCIE3, ICU::VECTOR::GTCIV3, ICU::VECTOR::NONE> GPT3;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT04567 定義クラス
		@param[in]	base	ベース・アドレス
		@param[in]	chno	チャネル番号
		@param[in]	per		ペリフェラル型
		@param[in]	veca	A 割り込みベクター型
		@param[in]	vecb	B 割り込みベクター型
		@param[in]	vecc	C 割り込みベクター型
		@param[in]	vece	E 割り込みベクター型
		@param[in]	vecv	V 割り込みベクター型
		@param[in]	veci	I 割り込みベクター型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, uint32_t chno, peripheral per,
		ICU::VECTOR veca, ICU::VECTOR vecb, ICU::VECTOR vecc, ICU::VECTOR vece, ICU::VECTOR vecv, ICU::VECTOR veci>
	struct gpt4567_t : public gpt_defs, GPTB, gptn_t<base> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto CHNO = chno;		///< チャネル番号
		static constexpr auto PCLK = clock_profile::PCLKA;  ///< クロック周期
		static constexpr auto GTCIA = veca;		///< GTCIA 割り込みベクター
		static constexpr auto GTCIB = vecb;		///< GTCIB 割り込みベクター
		static constexpr auto GTCIC = vecc;		///< GTCIC 割り込みベクター
		static constexpr auto GTCIE = vece;		///< GTCIE 割り込みベクター
		static constexpr auto GTCIV = vecv;		///< GTCIV 割り込みベクター
		static constexpr auto LOCOI = veci;		///< LOCOI 割り込みベクター


		//-----------------------------------------------------------------//
		/*!
			@brief  GPT 開始
			@param[in]	ena		停止の場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true) noexcept
		{
			switch(CHNO) {
			case 4: GTSTR.CST4 = ena; break;
			case 5: GTSTR.CST5 = ena; break;
			case 6: GTSTR.CST6 = ena; break;
			case 7: GTSTR.CST7 = ena; break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマハードウェア要因スタートコントロールレジスタ（GTHSCR）
			@param[in]	cshw	スタート要因
			@param[in]	cphw	ストップ要因
		*/
		//-----------------------------------------------------------------//
		static void set(GTHSCR_CSHW cshw, GTHSCR_CPHW cphw) noexcept
		{
			switch(CHNO) {
			case 4:
				GTHSCR = GTHSCR.CSHW4.b(static_cast<uint8_t>(cshw)) | GTHSCR.CPHW4.b(static_cast<uint8_t>(cphw));
				break;
			case 5:
				GTHSCR = GTHSCR.CSHW5.b(static_cast<uint8_t>(cshw)) | GTHSCR.CPHW5.b(static_cast<uint8_t>(cphw));
				break;
			case 6:
				GTHSCR = GTHSCR.CSHW6.b(static_cast<uint8_t>(cshw)) | GTHSCR.CPHW6.b(static_cast<uint8_t>(cphw));
				break;
			case 7:
				GTHSCR = GTHSCR.CSHW7.b(static_cast<uint8_t>(cshw)) | GTHSCR.CPHW7.b(static_cast<uint8_t>(cphw));
				break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマハードウェア要因クリアコントロールレジスタ（GTHCCR）
			@param[in]	cshw	クリア要因
			@param[in]	ena		クリアを行う場合「true」
		*/
		//-----------------------------------------------------------------//
		static void set(GTHCCR_CCHW cchw, bool ena) noexcept
		{
			switch(CHNO) {
			case 4:
				GTHCCR = GTHCCR.CCHW4.b(static_cast<uint8_t>(cchw)) | GTHCCR.CCSW4.b(ena);
				break;
			case 5:
				GTHCCR = GTHCCR.CCHW5.b(static_cast<uint8_t>(cchw)) | GTHCCR.CCSW5.b(ena);
				break;
			case 6:
				GTHCCR = GTHCCR.CCHW6.b(static_cast<uint8_t>(cchw)) | GTHCCR.CCSW6.b(ena);
				break;
			case 7:
				GTHCCR = GTHCCR.CCHW7.b(static_cast<uint8_t>(cchw)) | GTHCCR.CCSW7.b(ena);
				break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマハードウェアスタート要因セレクトレジスタ（GTHSSR）
			@param[in]	cshsl	スタート要因
		*/
		//-----------------------------------------------------------------//
		static void set(GTHSSR_CSHSL cshsl) noexcept
		{
			switch(CHNO) {
			case 4:
				GTHSSR.CSHSL4 = static_cast<uint8_t>(cshsl);
				break;
			case 5:
				GTHSSR.CSHSL5 = static_cast<uint8_t>(cshsl);
				break;
			case 6:
				GTHSSR.CSHSL6 = static_cast<uint8_t>(cshsl);
				break;
			case 7:
				GTHSSR.CSHSL7 = static_cast<uint8_t>(cshsl);
				break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマハードウェアストップ・クリア要因セレクトレジスタ（GTHPSR）
			@param[in]	cshsl	スタート要因
		*/
		//-----------------------------------------------------------------//
		static void set(GTHPSR_CSHPL cshpl) noexcept
		{
			switch(CHNO) {
			case 4:
				GTHPSR.CSHPL4 = static_cast<uint8_t>(cshpl);
				break;
			case 5:
				GTHPSR.CSHPL5 = static_cast<uint8_t>(cshpl);
				break;
			case 6:
				GTHPSR.CSHPL6 = static_cast<uint8_t>(cshpl);
				break;
			case 7:
				GTHPSR.CSHPL7 = static_cast<uint8_t>(cshpl);
				break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマシンクロレジスタ（GTSYNC）
			@param[in]	ch		同期チャネル（４～７）
		*/
		//-----------------------------------------------------------------//
		static void sync(uint8_t ch) noexcept
		{
			switch(CHNO) {
			case 4: GTSYNC.SYNC4 = ch; break;
			case 5: GTSYNC.SYNC5 = ch; break;
			case 6: GTSYNC.SYNC6 = ch; break;
			case 7: GTSYNC.SYNC7 = ch; break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ書き込み保護レジスタ（GTWP）
			@param[in]	ena		保護の場合「true」
		*/
		//-----------------------------------------------------------------//
		static void write_protect(bool ena = true) noexcept
		{
			switch(CHNO) {
			case 4: GTWP.WP4 = ena; break;
			case 5: GTWP.WP5 = ena; break;
			case 6: GTWP.WP6 = ena; break;
			case 7: GTWP.WP7 = ena; break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作禁止レジスタ（GTBDR）
			@param[in]	ccr		GTCCR  バッファを禁止する場合「true」
			@param[in]	pr		GTPR   バッファを禁止する場合「true」
			@param[in]	adtr	GTADTR バッファを禁止する場合「true」
			@param[in]	dv		GTDV   バッファを禁止する場合「true」
		*/
		//-----------------------------------------------------------------//
		static void buffer_disable(bool ccr, bool pr, bool adtr, bool dv) noexcept
		{
			switch(CHNO) {
			case 4:
				GTBDR.BD40 = ccr;
				GTBDR.BD41 = pr;
				GTBDR.BD42 = adtr;
				GTBDR.BD43 = dv;
				break;
			case 5:
				GTBDR.BD50 = ccr;
				GTBDR.BD51 = pr;
				GTBDR.BD52 = adtr;
				GTBDR.BD53 = dv;
				break;
			case 6:
				GTBDR.BD60 = ccr;
				GTBDR.BD61 = pr;
				GTBDR.BD62 = adtr;
				GTBDR.BD63 = dv;
				break;
			case 7:
				GTBDR.BD70 = ccr;
				GTBDR.BD71 = pr;
				GTBDR.BD72 = adtr;
				GTBDR.BD73 = dv;
				break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマスタート書き込み保護レジスタ（GTSWP）
			@param[in]	ena		保護の場合「true」
		*/
		//-----------------------------------------------------------------//
		static void start_protect(bool ena = true) noexcept
		{
			switch(CHNO) {
			case 4: GTSWP.SWP4 = ena; break;
			case 5: GTSWP.SWP5 = ena; break;
			case 6: GTSWP.SWP6 = ena; break;
			case 7: GTSWP.SWP7 = ena; break;
			default:
				break;
			}
		}
	};
	typedef gpt4567_t<0x000C'2900, 4, peripheral::GPT4,
		ICU::VECTOR::GTCIA4, ICU::VECTOR::GTCIB4, ICU::VECTOR::GTCIC4, ICU::VECTOR::GTCIE4, ICU::VECTOR::GTCIV4, ICU::VECTOR::LOCOI4> GPT4;
	typedef gpt4567_t<0x000C'2980, 5, peripheral::GPT5,
		ICU::VECTOR::GTCIA5, ICU::VECTOR::GTCIB5, ICU::VECTOR::GTCIC5, ICU::VECTOR::GTCIE5, ICU::VECTOR::GTCIV5, ICU::VECTOR::NONE> GPT5;
	typedef gpt4567_t<0x000C'2A00, 6, peripheral::GPT6,
		ICU::VECTOR::GTCIA6, ICU::VECTOR::GTCIB6, ICU::VECTOR::GTCIC6, ICU::VECTOR::GTCIE6, ICU::VECTOR::GTCIV6, ICU::VECTOR::NONE> GPT6;
	typedef gpt4567_t<0x000C'2A80, 7, peripheral::GPT7,
		ICU::VECTOR::GTCIA7, ICU::VECTOR::GTCIB7, ICU::VECTOR::GTCIC7, ICU::VECTOR::GTCIE7, ICU::VECTOR::GTCIV7, ICU::VECTOR::NONE> GPT7;
}
