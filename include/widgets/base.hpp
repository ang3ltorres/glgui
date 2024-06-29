#pragma once

#include "pch.hpp"

namespace glgui::widget
{
	struct Base {

		Base(
			
			std::int32_t x,
			std::int32_t y,
			std::int32_t width,
			std::int32_t height
		);
		
		Base(const Base &base) = delete;
		virtual ~Base() = default;

		virtual void draw() = 0;

		std::int32_t x;
		std::int32_t y;
		std::int32_t width;
		std::int32_t height;
	};
}
