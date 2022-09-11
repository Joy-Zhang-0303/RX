#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX72M/RX65N/RX66T/RX72T/RX72N グループ D/A 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  D/A 制御クラス
		@param[in]	DAC		D/A デバイス・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class DAC>
	class dac_out {
	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	出力タイプ
		 */
		//-----------------------------------------------------------------//
		enum class output : uint8_t {
			NONE,	///< 出力禁止
			CH0,	///< チャネル０
			CH1,	///< チャネル１
			CH0_CH1	///< チャネル０、１
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		dac_out() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief	スタート @n
					※RX66T は ampe は機能なし。
			@param[in]	otype	出力タイプ
			@param[in]	ampe	アンプ許可の場合「true」
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start(output otype, bool ampe) const noexcept
		{
			if(otype == output::NONE) {
				power_mgr::turn(DAC::PERIPHERAL);
				DAC::DACR.DAE = 0;
				DAC::DACR = DAC::DACR.DAE.b(0) | DAC::DACR.DAOE0.b(0) | DAC::DACR.DAOE1.b(0);
				power_mgr::turn(DAC::PERIPHERAL, false);
				return true;
			}

			power_mgr::turn(DAC::PERIPHERAL);

			DAC::DADPR.DPSEL = 1;  // 左詰め（下位４ビット無視）

			DAC::DACR.DAE = 0;

			bool ch0 = false;
			bool ch1 = false;
			if(otype == output::CH0) {
				ch0 = true;
			} else if(otype == output::CH1) {
				ch1 = true;
			} else if(otype == output::CH0_CH1) {
				ch0 = true;
				ch1 = true;
			} else {
				return false;
			}

			if(ch0) {
				DAC::DACR.DAOE0 = 1;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX72N)
				DAC::DAAMPCR.DAAMP0 = ampe;
#elif defined(SIG_RX66T) || defined(SIG_RX72T)
				DAC::DADSELR.OUTDA0 = 1;
#endif
				DAC::enable(DAC::analog::DA0);
			}
			if(ch1) {
				DAC::DACR.DAOE1 = 1;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX72N)
				DAC::DAAMPCR.DAAMP1 = ampe;
#elif defined(SIG_RX66T) || defined(SIG_RX72T)
				DAC::DADSELR.OUTDA1 = 1;
#endif
				DAC::enable(DAC::analog::DA1);
			}

			utils::delay::micro_second(3);  // amp start setup time

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	電圧出力０（１６ビット値）
			@param[in]	value	値
		 */
		//-----------------------------------------------------------------//
		void out0(uint16_t value) const noexcept
		{
			DAC::DADR0 = value;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	電圧出力０ポートアドレスの取得
			@return 電圧出力０ポートアドレス
		 */
		//-----------------------------------------------------------------//
		uint32_t get_out0_adr() const noexcept
		{
			return DAC::DARD0.address;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	電圧出力１（１６ビット値）
			@param[in]	value	値
		 */
		//-----------------------------------------------------------------//
		void out1(uint16_t value) const noexcept
		{
			DAC::DADR1 = value;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	電圧出力０ポートアドレスの取得
			@return 電圧出力０ポートアドレス
		 */
		//-----------------------------------------------------------------//
		uint32_t get_out1_adr() const noexcept
		{
			return DAC::DARD1.address;
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  D/A 制御クラス（レガシー）互換性の為残してある。
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class dac_out_ {
	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	出力タイプ
		 */
		//-----------------------------------------------------------------//
		enum class output : uint8_t {
			NONE,	///< 出力禁止
			CH0,	///< チャネル０
			CH1,	///< チャネル１
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		dac_out_() { }


		//-----------------------------------------------------------------//
		/*!
			@brief	スタート
			@param[in]	otype	出力タイプ
			@param[in]	ampe	アンプ許可の場合「true」
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start(output otype, bool ampe)
		{
			if(otype == output::NONE) {
				R12DA::DACR = R12DA::DACR.DAE.b(0) | R12DA::DACR.DAOE0.b(0) | R12DA::DACR.DAOE1.b(0);
				power_mgr::turn(R12DA::PERIPHERAL, false);
				return true;
			}

			power_mgr::turn(R12DA::PERIPHERAL);

			R12DA::DADPR.DPSEL = 1;  // 左詰め（上位１２ビット無視）

			R12DA::DACR.DAE = 0;

			if(otype == output::CH0) {
				R12DA::DACR.DAOE0 = 1;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX72N)
				R12DA::DAAMPCR.DAAMP0 = ampe;
#endif
				MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
				MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可
				MPC::P03PFS.ASEL = 1;
				MPC::PWPR = device::MPC::PWPR.B0WI.b();
			} else if(otype == output::CH1) {
				R12DA::DACR.DAOE1 = 1;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX72N)
				R12DA::DAAMPCR.DAAMP1 = ampe;
#endif
				MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
				MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可
				MPC::P05PFS.ASEL = 1;
				MPC::PWPR = device::MPC::PWPR.B0WI.b();
			} else {
				return false;
			}

			utils::delay::micro_second(3);  // amp start setup time

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	電圧出力０（下位４ビットが無効な１６ビット値）
			@param[in]	value	値
		 */
		//-----------------------------------------------------------------//
		void out0(uint16_t value)
		{
			R12DA::DADR0 = value;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	電圧出力１（下位４ビットが無効な１６ビット値）
			@param[in]	value	値
		 */
		//-----------------------------------------------------------------//
		void out1(uint16_t value)
		{
			R12DA::DADR1 = value;
		}
	};
}
