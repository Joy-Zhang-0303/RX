#pragma once
//=====================================================================//
/*!	@file
	@brief	ラップタイム
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/format.hpp"
#include "scenes_base.hpp"
#include "common/fixed_fifo.hpp"
#include "common/file_io.hpp"

namespace app {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ラップタイム・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class laptime : public utils::scene {

		uint32_t	lap_best_t_;
		uint32_t	lap_best_n_;

		typedef scenes_base::RENDER RENDER;
		typedef RENDER::glc_type GLC;
		typedef graphics::def_color DEF_COLOR;

		void make_file_name_(time_t t, char* out, uint32_t len)
		{
			struct tm *m = localtime(&t);
			utils::sformat("%04d%s%02d%02d%02d", out, len)
				% static_cast<uint32_t>(m->tm_year + 1900)
				% get_mon(m->tm_mon)
				% static_cast<uint32_t>(m->tm_mday)
				% static_cast<uint32_t>(m->tm_hour)
				% static_cast<uint32_t>(m->tm_min)
			;
		}

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		laptime() :
			lap_best_t_(0), lap_best_n_(0)
		{ }


		//-------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-------------------------------------------------------------//
		void init() override
		{
			at_scenes_base().at_cmt().at_func().enable();
			lap_best_t_ = 0;
			lap_best_n_ = 0;

			auto& render = at_scenes_base().at_render();
			render.clear(DEF_COLOR::Black);
			render.set_fore_color(DEF_COLOR::White);
			render.set_back_color(DEF_COLOR::Black);

		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service() override
		{
			auto& render = at_scenes_base().at_render();
			auto& res = at_scenes_base().at_resource();
			auto& watch = at_scenes_base().at_cmt().at_func();

			auto t = watch.get();
			auto pos = watch.get_lap_pos();
			uint32_t dt = t;
			if(pos > 0) {
				dt -= watch.get_lap(pos - 1);
			}

			vtx::spos loc(0);
			res.draw_lap_state(loc, pos, t, dt);
//			res.draw_lap_24(x + 16, y, lap_best_n_, lap_best_t_);

			// プログレスバー表示
			render.set_fore_color(DEF_COLOR::White);
			render.frame(vtx::srect(0, GLC::height - 10, GLC::width, 10));
			uint32_t bt = 0;
			if(pos > 0) {
				bt = watch.get_lap(pos - 1);
				if(pos > 1) {
					bt -= watch.get_lap(pos - 2);
				}
				if(lap_best_t_ == 0 || lap_best_t_ > bt) {
					lap_best_t_ = bt;
					lap_best_n_ = pos;
				}
			}
			if(bt > 0) {
				uint32_t ref = RENDER::glc_type::width - 2;
				uint32_t per = ref * dt / bt;
				auto fc = DEF_COLOR::Lime;
				if(per > ref) {
					per = ref;
					fc = DEF_COLOR::Red;
				}
				auto bc = DEF_COLOR::Black;
				render.set_fore_color(bc);
				render.set_back_color(fc);
				render.fill_box(vtx::srect(1, RENDER::glc_type::height - 10 + 1, ref - per, 10 - 2));
				render.swap_color();
				render.fill_box(vtx::srect(1, RENDER::glc_type::height - 10 + 1, per, 10 - 2));
			}

			for(uint32_t i = 0; i < 4; ++i) {
				if(i >= pos) {
					break;
				}
				auto t = watch.get_lap(pos - i - 1);
				if(pos > 1) {
					t -= watch.get_lap(pos - i - 2);
				}
				res.draw_short_lap(vtx::spos(0, 48 + 28 * 4 - i * 28), pos - i, t);
			}

			// GPS 書き込みサービス
//			auto& nmea = at_scenes_base().at_nmea();
//			auto n = nmea.get_satellite_num();
		}


		//-------------------------------------------------------------//
		/*!
			@brief	シーンの終了
		*/
		//-------------------------------------------------------------//
		void exit() override { }
	};
}
