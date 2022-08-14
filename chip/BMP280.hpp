#pragma once
//=====================================================================//
/*!	@file
	@brief	BMP280 デジタル圧力センサー・ドライバー @n
			Bosch Sensotec / Digital Pressure Sensor @n
			https://www.bosch-sensortec.com/bst/products/all_products/bmp280
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include <cmath>
#include "common/iica_io.hpp"
#include "common/delay.hpp"

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  BMP280 テンプレートクラス
		@param[in]	I2C_IO	i2c I/O クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class I2C_IO>
	class BMP280 {
	public:
		// R/W ビットを含まない７ビット値
		// ※ SDO:L ---> 0x76, SDO:H ---> 0x77
		static constexpr uint8_t I2C_ADR = 0x77;

	private:
		I2C_IO& i2c_io_;

		uint8_t	addr_;

		enum class REG : uint8_t {
      		DIG_T1        = 0x88,
      		DIG_T2        = 0x8A,
      		DIG_T3        = 0x8C,

      		DIG_P1        = 0x8E,
      		DIG_P2        = 0x90,
      		DIG_P3        = 0x92,
      		DIG_P4        = 0x94,
      		DIG_P5        = 0x96,
      		DIG_P6        = 0x98,
      		DIG_P7        = 0x9A,
      		DIG_P8        = 0x9C,
      		DIG_P9        = 0x9E,

      		CHIPID        = 0xD0,
      		VERSION       = 0xD1,
      		SOFTRESET     = 0xE0,

      		CAL26         = 0xE1,  // R calibration stored in 0xE1-0xF0

      		CONTROL       = 0xF4,
      		CONFIG        = 0xF5,
      		PRESSUREDATA  = 0xF7,
      		TEMPDATA      = 0xFA,
			HUMIDDATA     = 0xFD,
		};

    	struct calib_t {
			uint16_t	dig_T1;
			int16_t		dig_T2;
			int16_t		dig_T3;

			uint16_t	dig_P1;
			int16_t		dig_P2;
			int16_t		dig_P3;
			int16_t		dig_P4;
			int16_t		dig_P5;
			int16_t		dig_P6;
			int16_t		dig_P7;
			int16_t		dig_P8;
			int16_t		dig_P9;

			uint8_t		dig_H1;
			int16_t		dig_H2;
			uint8_t		dig_H3;
			int16_t		dig_H4;
			int16_t		dig_H5;
			int8_t		dig_H6;
		};

		calib_t		calib_;

		int32_t		t_fine_;

		uint8_t read8_(REG adr) noexcept {
			uint8_t reg[1];
			reg[0] = static_cast<uint8_t>(adr);
			i2c_io_.send(addr_, reg, 1);
			i2c_io_.recv(addr_, reg, 1);
			return reg[0];
		}

		uint16_t read16_(REG adr) noexcept {
			uint8_t reg[2];
			reg[0] = static_cast<uint8_t>(adr);
			i2c_io_.send(addr_, reg, 1);
			i2c_io_.recv(addr_, reg, 2);
			return (reg[0] << 8) | reg[1];
		}

		uint32_t read24_(REG adr) noexcept {
			uint8_t reg[3];
			reg[0] = static_cast<uint8_t>(adr);
			i2c_io_.send(addr_, reg, 1);
			i2c_io_.recv(addr_, reg, 3);
			return (static_cast<uint32_t>(reg[0]) << 16) | (static_cast<uint32_t>(reg[1]) << 8) | reg[2];
		}

		uint16_t read16le_(REG adr) noexcept {
			uint8_t reg[2];
			reg[0] = static_cast<uint8_t>(adr);
			i2c_io_.send(addr_, reg, 1);
			i2c_io_.recv(addr_, reg, 2);
			return (reg[1] << 8) | reg[0];
		}

		void write8_(REG a, uint8_t data) noexcept {
			uint8_t reg[2];
			reg[0] = static_cast<uint8_t>(a);
			reg[1] = data;
			i2c_io_.send(addr_, reg, 2);
		}

		void get_coefficients_() noexcept {
			calib_.dig_T1 = read16le_(REG::DIG_T1);
			calib_.dig_T2 = read16le_(REG::DIG_T2);
			calib_.dig_T3 = read16le_(REG::DIG_T3);

			calib_.dig_P1 = read16le_(REG::DIG_P1);
			calib_.dig_P2 = read16le_(REG::DIG_P2);
			calib_.dig_P3 = read16le_(REG::DIG_P3);
			calib_.dig_P4 = read16le_(REG::DIG_P4);
			calib_.dig_P5 = read16le_(REG::DIG_P5);
			calib_.dig_P6 = read16le_(REG::DIG_P6);
			calib_.dig_P7 = read16le_(REG::DIG_P7);
			calib_.dig_P8 = read16le_(REG::DIG_P8);
			calib_.dig_P9 = read16le_(REG::DIG_P9);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	i2c_io	iica_io クラスを参照で渡す
		 */
		//-----------------------------------------------------------------//
		BMP280(I2C_IO& i2c_io) noexcept : i2c_io_(i2c_io), addr_(0), calib_(), t_fine_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	addr	オプションの I2C アドレス @n
								※ SDO:L ---> 0x76, SDO:H ---> 0x77 (default)
			@return エラーなら「false」を返す
		 */
		//-----------------------------------------------------------------//
		bool start(uint8_t addr = I2C_ADR) noexcept
		{
			addr_ = addr;

			if(read8_(REG::CHIPID) != 0x58) {  // チップＩＤの確認
				addr_ = 0;
				return false;
			}

			get_coefficients_();  // 補正データ取得

			// Ex: Ultra high resolution
			// setting control
			// osrs_t(X2): 010, osrs_p(X16): 101, mode(Normal): 11
			uint8_t mode = 0b010'000'00 | 0b000'101'00 | 0b000'000'11;
			write8_(REG::CONTROL, mode);

			// setting config
			// t_sb(0.5ms): 000, filter(16): 100, xxx(0): 0, spi3w_en(0): 0
			uint8_t conf = 0b000'000'0'0 | 0b000'100'0'0 | 0b000'000'0'0 | 0b000'000'0'0;
			write8_(REG::CONFIG, conf);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	温度を返す（℃ * 100）
			@return 温度
		 */
		//-----------------------------------------------------------------//
		int32_t get_temperature() noexcept
		{
			if(addr_ == 0) return 0;

			int32_t adc_T = read24_(REG::TEMPDATA);
			adc_T >>= 4;

  			int32_t var1  = ((((adc_T>>3) - (static_cast<int32_t>(calib_.dig_T1) << 1))) *
				(static_cast<int32_t>(calib_.dig_T2))) >> 11;

			int32_t var2  = (((((adc_T>>4) - (static_cast<int32_t>(calib_.dig_T1))) *
				((adc_T>>4) - (static_cast<int32_t>(calib_.dig_T1)))) >> 12) *
				(static_cast<int32_t>(calib_.dig_T3))) >> 14;

			t_fine_ = var1 + var2;

			return (t_fine_ * 5 + 128) >> 8;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	湿度を返す（％）(for BME280)
			@return 湿度
		 */
		//-----------------------------------------------------------------//
		float get_humidity() noexcept
		{
			if(addr_ == 0) return 0;

			get_temperature(); // must be done first to get t_fine

			int32_t adc_H = read16_(REG::HUMIDDATA);

			int32_t v_x1_u32r = (t_fine_ - (static_cast<int32_t>(76800)));

			v_x1_u32r = (((((adc_H << 14) - ((static_cast<int32_t>(calib_.dig_H4)) << 20) -
				((static_cast<int32_t>(calib_.dig_H5)) * v_x1_u32r)) + (static_cast<int32_t>(16384))) >> 15) *
				(((((((v_x1_u32r * (static_cast<int32_t>(calib_.dig_H6))) >> 10) *
				(((v_x1_u32r * (static_cast<int32_t>(calib_.dig_H3))) >> 11) +
				(static_cast<int32_t>(32768)))) >> 10) +
				(static_cast<int32_t>(2097152))) * (static_cast<int32_t>(calib_.dig_H2)) + 8192) >> 14));

			v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *
				(static_cast<int32_t>(calib_.dig_H1))) >> 4));

			v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
			v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
			float h = (v_x1_u32r>>12);
			return  h / 1024.0f;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	圧力を返す [hPa * 100]
			@return 圧力
		 */
		//-----------------------------------------------------------------//
		int32_t get_pressure() noexcept
		{
			if(addr_ == 0) return 0;

			// Must be done first to get the t_fine variable set up
			get_temperature();

			int32_t adc_P = read24_(REG::PRESSUREDATA);
			adc_P >>= 4;

			int64_t var1 = (static_cast<int64_t>(t_fine_)) - 128000;
			int64_t var2 = var1 * var1 * static_cast<int64_t>(calib_.dig_P6);
			var2 = var2 + ((var1 * static_cast<int64_t>(calib_.dig_P5)) << 17);
			var2 = var2 + ((static_cast<int64_t>(calib_.dig_P4)) << 35);
			var1 = ((var1 * var1 * static_cast<int64_t>(calib_.dig_P3)) >> 8) +
				((var1 * static_cast<int64_t>(calib_.dig_P2)) << 12);
			var1 = ((((static_cast<int64_t>(1)) << 47) + var1)) * (static_cast<int64_t>(calib_.dig_P1)) >> 33;

			if(var1 == 0) {
				return 0.0f;  // avoid exception caused by division by zero
			}

			int64_t p = 1048576 - adc_P;
			p = (((p << 31) - var2) * 3125) / var1;
			var1 = ((static_cast<int64_t>(calib_.dig_P9)) * (p >> 13) * (p >> 13)) >> 25;
			var2 = ((static_cast<int64_t>(calib_.dig_P8)) * p) >> 19;

			p = ((p + var1 + var2) >> 8) + ((static_cast<int64_t>(calib_.dig_P7)) << 4);

			return p >> 8;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	高度を返す
			@param[in]	seaLevelhPa 海面ヘクトパスカル
			@return 高度
		 */
		//-----------------------------------------------------------------//
		float get_altitude(float seaLevelhPa = 1013.25f) noexcept
		{
			if(addr_ == 0) return 0.0f;

			float pressure = static_cast<float>(get_pressure()) / 100.0f;
			float altitude = 44330.0f * (1.0f - std::pow(pressure / seaLevelhPa, 0.1903f));
			return altitude;
		}
	};
}
