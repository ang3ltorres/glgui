#pragma once

#include "pch.hpp"
#include "utils.hpp"

namespace glgui::widget
{
	struct Base {

		Base(Rect rect);
		Base(const Base &base) = delete;
		virtual ~Base() = default;

		virtual void draw() = 0;

		Rect rect;
	};
}
