//=====================================================================//
/*! @file
    @brief  RX24T / BMP180/BMP280 サンプル @n
			・P00(4) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/cmt_mgr.hpp"
#include "common/sci_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include "common/iica_io.hpp"
#include "common/si2c_io.hpp"
#include "common/command.hpp"
#include "chip/BMP180.hpp"
#include "chip/BMP280.hpp"

namespace {

	class cmt_task {
	public:
		void operator() () {
		}
	};

	device::cmt_mgr<device::CMT0, cmt_task>  cmt_;

	typedef utils::fixed_fifo<char, 128> buffer;
	device::sci_io<device::SCI1, buffer, buffer> sci_;

#ifdef SOFT_I2C
	typedef device::PORT<device::PORTB, device::bitpos::B2> SDA;
	typedef device::PORT<device::PORTB, device::bitpos::B1> SCL;
	typedef device::si2c_io<SDA, SCL> I2C;
#else
	typedef device::iica_io<device::RIIC0> I2C;
#endif
	I2C i2c_;

	chip::BMP180<I2C> bmpx_(i2c_);
//	chip::BMP280<I2C> bmpx_(i2c_);

	utils::command<128> command_;
}

extern "C" {

	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci_.puts(str);
	}

	char sci_getch(void)
	{
		return sci_.getch();
	}

	uint16_t sci_length()
	{
		return sci_.recv_length();
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::boost_master_clock();

	{  // タイマー設定（６０Ｈｚ）
		auto intr_level = device::ICU::LEVEL::_4;
		cmt_.start(60, intr_level);
	}

	{  // SCI 設定
		auto intr_level = device::ICU::LEVEL::_2;
		sci_.start(115200, intr_level);
	}

	{  // IICA(I2C) の開始
		if(!i2c_.start(I2C::MODE::MASTER, I2C::SPEED::FAST)) {
///		uint8_t intr_level = 0;
///		if(!i2c_.start(I2C::speed::fast, intr_level)) {
			utils::format("IICA start error (%d)\n") % static_cast<uint32_t>(i2c_.get_last_error());
		}
	}

	utils::format("RX24T BMP180/BMP280 sample\n");

	// BMPx の開始
	if(!bmpx_.start()) {
		utils::format("Stall BMP180/BMP280 start (%d)\n") % static_cast<uint32_t>(i2c_.get_last_error());
	}

//	command_.set_prompt("# ");

	device::PORT0::PDR.B0 = 1; // output

	uint32_t cnt = 0;
	uint32_t n = 0;
	while(1) {
		cmt_.sync();

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORT0::PODR.B0 = (cnt < 10) ? 0 : 1;

		++n;
		if(n >= 60) {
			n = 0;

			auto t = bmpx_.get_temperature();
			utils::format("Temperature: %5.2f C\n") % (static_cast<float>(t) / 100.0f);

//			auto h = bmpx_.get_humidity();
//			utils::format("Humi: %3.1f\n") % h;

			auto p = bmpx_.get_pressure();
			utils::format("Pressure: %7.2f hPa\n") % (static_cast<float>(p) / 100.0f);

			auto a = bmpx_.get_altitude();
			utils::format("Altitude: %7.2f m\n") % a;
		}
	}
}
