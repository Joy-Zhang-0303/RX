#pragma once
//=========================================================================//
/*!	@file
	@brief	RX24T グループ・D/A 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"
#include "RX24T/mpc.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  D/A コンバータ（DA, DAa）@n
				※チップバージョンＡとＢでチャネル数が異なる
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct da_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			DA0,	///< P24/DA0 出力
			DA1,	///< P23/DA1 出力
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A ポートをアナログ出力に設定
			@param[in]	an		アナログ型
			@param[in]	ena		不許可の場合は「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(ANALOG an, bool ena = true) noexcept
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case ANALOG::DA0:
				PORT2::PCR.B4 = 0;  // disable pull-up
				MPC::P24PFS.ASEL = 1;
				break;
			case ANALOG::DA1:
				PORT2::PCR.B3 = 0;  // disable pull-up
				MPC::P23PFS.ASEL = 1;
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		} 


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A データレジスタ 0（DADR0）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000880C0> DADR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A データレジスタ 1（DADR1）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x000880C2> DADR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A 制御レジスタ（DACR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dacr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6> DAOE0;
			bit_rw_t<io_, bitpos::B7> DAOE1;
		};
		static inline dacr_t<0x000880C4> DACR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DADR0 フォーマット選択レジスタ（DADPR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dadpr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B7> DPSEL;
		};
		static inline dadpr_t<0x000880C5> DADPR;
	};
	typedef da_t<0x0008'80C0, peripheral::DA> DA;
}
