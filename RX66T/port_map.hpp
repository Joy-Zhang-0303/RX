#pragma once
//=====================================================================//
/*!	@file
	@brief	RX66T グループ・ポート・マッピング
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX66T/peripheral.hpp"
#include "RX66T/port.hpp"
#include "RX66T/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MTUx（マルチ・ファンクション・タイマ） チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			A,		///< MTUx A (MTIOCxA)
			B,		///< MTUx B (MTIOCxB)
			C,		///< MTUx C (MTIOCxC)
			D,		///< MTUx D (MTIOCxD)

			U,		///< MTU5 U (MTIC5U) P24
			V,		///< MTU5 V (MTIC5V) P23
			W,		///< MTU5 W (MTIC5W) P22
			U2,		///< MTU5 U (MTIC5U) P82
			V2,		///< MTU5 V (MTIC5V) P81
			W2,		///< MTU5 W (MTIC5W) P80

			CLK_AB,	///< MTCLKA, MTCLKB 1ST: P33/P32, 2ND: P21/P20 
			CLK_CD,	///< MTCLKC, MTCLKD 1ST: P31/P30, 2ND: P11/P10, 3RD: PE4/PE3
		};

	private:

		static bool sub_1st_(peripheral t, bool enable) noexcept
		{
			switch(t) {

			case peripheral::RIIC0:
				{
					uint8_t sel = enable ? 0b01111 : 0;
					PORTB::PMR.B1 = 0;
					PORTB::PMR.B2 = 0;
					MPC::PB1PFS.PSEL = sel;  // PB1/SCL (34/100)
					MPC::PB2PFS.PSEL = sel;  // PB2/SDA (33/100)
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B2 = enable;
				}
				break;

			case peripheral::RSPI0:
				{
					uint8_t sel = enable ? 0b01101 : 0;
					MPC::P22PFS.PSEL = sel;  // P22/MISOA  (66/100)
					MPC::P23PFS.PSEL = sel;  // P23/MOSIA  (65/100)
					MPC::P24PFS.PSEL = sel;  // P24/RSPCKA (64/100)
					PORT2::PMR.B2 = enable;
					PORT2::PMR.B3 = enable;
					PORT2::PMR.B4 = enable;
				}
				break;

			case peripheral::SCI1C:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PD4PFS.PSEL = sel;  // PD4/SCK1 (21/100)
					PORTD::PMR.B4 = enable;
				}
			case peripheral::SCI1:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PD3PFS.PSEL = sel;  // PD3/TXD1 (22/100)
					MPC::PD5PFS.PSEL = sel;  // PD5/RXD1 (20/100)
					PORTD::PMR.B3 = enable;
					PORTD::PMR.B5 = enable;
				}
				break;

			case peripheral::SCI5C:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PB7PFS.PSEL = sel;  // PB7/SCK5 (26/100)
					PORTB::PMR.B7 = enable;
				}
			case peripheral::SCI5:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PB5PFS.PSEL = sel;  // PB5/TXD5 (28/100)
					MPC::PB6PFS.PSEL = sel;  // PB6/RXD5 (27/100)
					PORTB::PMR.B5 = enable;
					PORTB::PMR.B6 = enable;
				}
				break;

			case peripheral::SCI6C:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PA4PFS.PSEL = sel;  // PA4/SCK6 (37/100)
					PORTA::PMR.B4 = enable;
				}
			case peripheral::SCI6:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PB0PFS.PSEL = sel;  // PB0/TXD6 (35/100)
					MPC::PA5PFS.PSEL = sel;  // PA5/RXD6 (36/100)
					PORTB::PMR.B0 = enable;
					PORTA::PMR.B5 = enable;
				}
				break;

			default:
				return false;
				break;
			}
			return true;
		}


		static bool sub_2nd_(peripheral t, bool enable) noexcept
		{
			switch(t) {

//			case peripheral::SCI5C:
//				{
//					uint8_t sel = enable ? 0b01010 : 0;
//					MPC::PB7PFS.PSEL = sel;  // PB7/SCK5 (26/100)
//					PORTB::PMR.B7 = enable;
//				}
			case peripheral::SCI5:  // Version B device only
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PE0PFS.PSEL = sel;  // PE0/TXD5 (17/100)
					MPC::PD7PFS.PSEL = sel;  // PD7/RXD5 (18/100)
					PORTE::PMR.B0 = enable;
					PORTD::PMR.B7 = enable;
				}
				break;

			case peripheral::SCI6C:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PB3PFS.PSEL = sel;  // PB3/SCK6 (32/100)
					PORTB::PMR.B3 = enable;
				}
			case peripheral::SCI6:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PB2PFS.PSEL = sel;  // PB2/TXD6 (33/100)
					MPC::PB1PFS.PSEL = sel;  // PB1/RXD6 (34/100)
					PORTB::PMR.B2 = enable;
					PORTB::PMR.B1 = enable;
				}
				break;

			default:
				return false;
				break;
			}
			return true;
		}


		static bool sub_can_(ORDER opt, bool enable)
		{
			uint8_t sel = enable ? 0b10000 : 0;
			switch(opt) {
			case ORDER::FIRST:
				// PE0/CRX0 (22/144) (17/100)
				// PD7/CTX0 (23/144) (18/100)
				PORTE::PMR.B0 = 0;
				PORTD::PMR.B7 = 0;
				MPC::PE0PFS.PSEL = sel;
				MPC::PD7PFS.PSEL = sel;
				PORTE::PMR.B0 = enable;
				PORTD::PMR.B7 = enable;
				break;
			case ORDER::SECOND:
				// PB6/CRX0 (40/144) (27/100)
				// PB5/CTX0 (41/144) (28/100)
				PORTB::PMR.B6 = 0;
				PORTB::PMR.B5 = 0;
				MPC::PB6PFS.PSEL = sel;
				MPC::PB5PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B5 = enable;
				break;
			case ORDER::THIRD:
				// PA1/CRX0 (58/144) (40/100)
				// PA0/CTX0 (59/144) (41/100)
				PORTA::PMR.B1 = 0;
				PORTA::PMR.B0 = 0;
				MPC::PA1PFS.PSEL = sel;
				MPC::PA0PFS.PSEL = sel;
				PORTA::PMR.B1 = enable;
				PORTA::PMR.B0 = enable;
				break;
			case ORDER::FOURTH:
				// P23/CTX0 (96/144) (66/100)
				// P22/CRX0 (97/144) (67/100)
				PORT2::PMR.B3 = 0;
				PORT2::PMR.B2 = 0;
				MPC::P23PFS.PSEL = sel;
				MPC::P22PFS.PSEL = sel;
				PORT2::PMR.B3 = enable;
				PORT2::PMR.B2 = enable;
				break;
			case ORDER::FIFTH:
				// PF3/CRX0 (31/144)
				// PF2/CTX0 (32/144)
				PORTF::PMR.B3 = 0;
				PORTF::PMR.B2 = 0;
				MPC::PF3PFS.PSEL = sel;
				MPC::PF3PFS.PSEL = sel;
				PORTF::PMR.B3 = enable;
				PORTF::PMR.B2 = enable;
				break;
			case ORDER::SIXTH:
				// PA7/CRX0 (52/144)
				// PA6/CTX0 (53/144)
				PORTA::PMR.B7 = 0;
				PORTA::PMR.B6 = 0;
				MPC::PA7PFS.PSEL = sel;
				MPC::PA6PFS.PSEL = sel;
				PORTA::PMR.B7 = enable;
				PORTA::PMR.B6 = enable;
				break;
			case ORDER::SEVENTH:
				// PC6/CRX0 (62/144)
				// PC5/CTX0 (63/144)
				PORTC::PMR.B6 = 0;
				PORTC::PMR.B5 = 0;
				MPC::PC6PFS.PSEL = sel;
				MPC::PC5PFS.PSEL = sel;
				PORTC::PMR.B6 = enable;
				PORTC::PMR.B5 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  USB ポート専用切り替え
			@param[in]	sel		USB ポート選択
			@param[in]	ena		無効にする場合「false」
			@param[in]	odr		ポート・マップ・オプション（ポート候補）
			@return 無効な場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn_usb(USB_PORT sel, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return false;

			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(sel) {
			case USB_PORT::VBUS:
				switch(odr) {
				// PC0 o
				// PD2 o
				case ORDER::FIRST:
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = ena ? 0b010001 : 0;
					PORTC::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = ena ? 0b010001 : 0;
					PORTD::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::EXICEN:
				// PA0 o
				// PC1 o
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = ena ? 0b010001 : 0;
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = ena ? 0b010001 : 0;
					PORTC::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::VBUSEN:
				// PA0 o
				// PC1 o
				// PB5 o
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = ena ? 0b010010 : 0;
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = ena ? 0b010010 : 0;
					PORTC::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = ena ? 0b010001 : 0;
					PORTB::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::OVRCURA:
				// PA1 o
				// PB6 o
				// PC2 o
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = ena ? 0b010010 : 0;
					PORTA::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = ena ? 0b010001 : 0;
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = ena ? 0b010010 : 0;
					PORTC::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::OVRCURB:
				// P34 o
				// PB4 o
				// PB7 o
				// PE0 o
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = ena ? 0b010001 : 0;
					PORT3::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B4 = 0;
					MPC::PB4PFS.PSEL = ena ? 0b010001 : 0;
					PORTB::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = ena ? 0b010001 : 0;
					PORTB::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = ena ? 0b010001 : 0;
					PORTE::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::ID:
				// PA1 o
				// PC2 o
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = ena ? 0b010001 : 0;
					PORTA::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = ena ? 0b010001 : 0;
					PORTC::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			default:
				ret = false;
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ena	無効にする場合「false」
			@param[in]	opt	候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral per, bool ena = true, ORDER opt = ORDER::FIRST) noexcept
		{
			if(opt == ORDER::BYPASS) return false;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			if(per == peripheral::CAN0) {
				ret = sub_can_(opt, ena);
			} else if(opt == ORDER::FIRST) {
				ret = sub_1st_(per, ena);
			} else if(opt == ORDER::SECOND) {
				ret = sub_2nd_(per, ena);
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  MTU3 関係、チャネル別ポート切り替え
			@param[in]	t	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	opt	候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral t, channel ch, bool ena = true, ORDER opt = ORDER::FIRST)
			noexcept
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			uint8_t sel = 0;
			switch(t) {
			case peripheral::MTU0:
				sel = ena ? 0b00001 : 0;
				switch(ch) {
				case channel::A:
					MPC::PB3PFS.PSEL = sel;  // MTIOC0A (32/100)
					PORTB::PMR.B3 = ena;
					break;
				case channel::B:
					MPC::PB2PFS.PSEL = sel;  // MTIOC0B (33/100)
					PORTB::PMR.B2 = ena;
					break;
				case channel::C:
					MPC::PB1PFS.PSEL = sel;  // MTIOC0C (34/100)
					PORTB::PMR.B1 = ena;
					break;
				case channel::D:
					MPC::PB0PFS.PSEL = sel;  // MTIOC0D (35/100)
					PORTB::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU1:
				switch(ch) {
				case channel::A:
					sel = ena ? 0b00001 : 0;
					MPC::PA5PFS.PSEL = sel;  // MTIOC1A (36/100)
					PORTA::PMR.B5 = ena;
					break;
				case channel::B:
					sel = ena ? 0b00001 : 0;
					MPC::PA4PFS.PSEL = sel;  // MTIOC1B (37/100)
					PORTA::PMR.B4 = ena;
					break;
				case channel::CLK_AB:
					sel = ena ? 0b00010 : 0;
					if(opt == ORDER::FIRST) {
						MPC::P33PFS.PSEL = sel;
						PORT3::PMR.B3 = ena;
						MPC::P32PFS.PSEL = sel;
						PORT3::PMR.B2 = ena;
					} else if(opt == ORDER::SECOND) {
						MPC::P21PFS.PSEL = sel;
						PORT2::PMR.B1 = ena;
						MPC::P20PFS.PSEL = sel;
						PORT2::PMR.B0 = ena;
					} else {
						ret = false;
					}
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU2:
				switch(ch) {
				case channel::A:					
					MPC::PA3PFS.PSEL = sel;  // MTIOC2A (38/100)
					PORTA::PMR.B3 = ena;
					break;
				case channel::B:
					MPC::PA2PFS.PSEL = sel;  // MTIOC2B (39/100)
					PORTA::PMR.B2 = ena;
					break;
				case channel::CLK_AB:
					sel = ena ? 0b00010 : 0;
					if(opt == ORDER::FIRST) {
						MPC::P33PFS.PSEL = sel;  // 
						PORT3::PMR.B3 = ena;
						MPC::P32PFS.PSEL = sel;
						PORT3::PMR.B2 = ena;
					} else if(opt == ORDER::SECOND) {
						MPC::P21PFS.PSEL = sel;
						PORT2::PMR.B1 = ena;
						MPC::P20PFS.PSEL = sel;
						PORT2::PMR.B0 = ena;
					} else {
						ret = false;
					}
					break;
				case channel::CLK_CD:
					sel = ena ? 0b00010 : 0;
					if(opt == ORDER::FIRST) {
						MPC::P31PFS.PSEL = sel;
						PORT3::PMR.B1 = ena;
						MPC::P30PFS.PSEL = sel;
						PORT3::PMR.B0 = ena;
					} else if(opt == ORDER::SECOND) {
						MPC::P11PFS.PSEL = sel;
						PORT1::PMR.B1 = ena;
						MPC::P10PFS.PSEL = sel;
						PORT1::PMR.B0 = ena;
					} else if(opt == ORDER::THIRD) {
						MPC::PE4PFS.PSEL = sel;
						PORTE::PMR.B4 = ena;
						MPC::PE3PFS.PSEL = sel;
						PORTE::PMR.B3 = ena;
					} else {
						ret = false;
					}
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU3:
				switch(ch) {
				case channel::A:					
					MPC::P33PFS.PSEL = sel;  // MTIOC3A (58/100)
					PORT3::PMR.B3 = ena;
					break;
				case channel::B:
					MPC::P71PFS.PSEL = sel;  // MTIOC3B (56/100)
					PORT7::PMR.B1 = ena;
					break;
				case channel::C:
					MPC::P32PFS.PSEL = sel;  // MTIOC3C (59/100)
					PORT3::PMR.B2 = ena;
					break;
				case channel::D:
					MPC::P74PFS.PSEL = sel;  // MTIOC3D (53/100)
					PORT7::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU4:
				switch(ch) {
				case channel::A:					
					MPC::P72PFS.PSEL = sel;  // MTIOC4A (55/100)
					PORT7::PMR.B2 = ena;
					break;
				case channel::B:
					MPC::P73PFS.PSEL = sel;  // MTIOC4B (54/100)
					PORT7::PMR.B3 = ena;
					break;
				case channel::C:
					MPC::P75PFS.PSEL = sel;  // MTIOC4C (52/100)
					PORT7::PMR.B5 = ena;
					break;
				case channel::D:
					MPC::P76PFS.PSEL = sel;  // MTIOC4D (51/100)
					PORT7::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU5:
				switch(ch) {
				case channel::U:
					MPC::P24PFS.PSEL = sel;  // MTIOC5U (64/100)
					PORT2::PMR.B4 = ena;
					break;
				case channel::V:
					MPC::P23PFS.PSEL = sel;  // MTIOC5V (65/100)
					PORT2::PMR.B3 = ena;
					break;
				case channel::W:
					MPC::P22PFS.PSEL = sel;  // MTIOC5W (66/100)
					PORT2::PMR.B2 = ena;
					break;
				case channel::U2:
					MPC::P82PFS.PSEL = sel;  // MTIOC5U (96/100)
					PORT8::PMR.B2 = ena;
					break;
				case channel::V2:
					MPC::P81PFS.PSEL = sel;  // MTIOC5V (97/100)
					PORT8::PMR.B1 = ena;
					break;
				case channel::W2:
					MPC::P80PFS.PSEL = sel;  // MTIOC5W (98/100)
					PORT8::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU6:
				switch(ch) {
				case channel::A:
					MPC::PA1PFS.PSEL = sel;  // MTIOC6A (40/100)
					PORTA::PMR.B1 = ena;
					break;
				case channel::B:
					MPC::P95PFS.PSEL = sel;  // MTIOC6B (45/100)
					PORT9::PMR.B5 = ena;
					break;
				case channel::C:
					MPC::PA0PFS.PSEL = sel;  // MTIOC6C (41/100)
					PORTA::PMR.B0 = ena;
					break;
				case channel::D:
					MPC::P92PFS.PSEL = sel;  // MTIOC6D (48/100)
					PORT9::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			case peripheral::MTU7:
				switch(ch) {
				case channel::A:
					MPC::P94PFS.PSEL = sel;  // MTIOC7A (46/100)
					PORT9::PMR.B4 = ena;
					break;
				case channel::B:
					MPC::P93PFS.PSEL = sel;  // MTIOC7B (47/100)
					PORT9::PMR.B3 = ena;
					break;
				case channel::C:
					MPC::P91PFS.PSEL = sel;  // MTIOC7C (49/100)
					PORT9::PMR.B1 = ena;
					break;
				case channel::D:
					MPC::P90PFS.PSEL = sel;  // MTIOC7D (50/100)
					PORT9::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;

			default:
				ret = false;
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
