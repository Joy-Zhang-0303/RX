#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・CRC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CRC 演算器クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct crc_t {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型

		//-----------------------------------------------------------------//
		/*!
			@brief  CRC コントロールレジスタ（CRCCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct crccr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  GPS;
			bit_rw_t <io_, bitpos::B2>     LMS;
			bit_rw_t <io_, bitpos::B7>     DORCLR;
		};
		typedef crccr_t<base + 0x00> CRCCR_;
		static CRCCR_ CRCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CRC データ入力レジスタ（CRCDIR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x01> CRCDIR_;
		static CRCDIR_ CRCDIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CRC データ出力レジスタ（CRCDOR）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x02> CRCDOR_;
		static CRCDOR_ CRCDOR;
	};
	template <uint32_t base, peripheral per>
		typename crc_t<base, per>::CRCCR_  crc_t<base, per>::CRCCR;
	template <uint32_t base, peripheral per>
		typename crc_t<base, per>::CRCDIR_ crc_t<base, per>::CRCDIR;
	template <uint32_t base, peripheral per>
		typename crc_t<base, per>::CRCDOR_ crc_t<base, per>::CRCDOR;


	typedef crc_t<0x00088280, peripheral::CRC> CRC;
}
