#pragma once

#include "pch.hpp"
#include "widgets/base.hpp"

namespace glgui::widget
{
	struct Button : public glgui::widget::Base
	{

		Button(

			std::int32_t x,
			std::int32_t y,
			std::int32_t width,
			std::int32_t height,
			std::function<void(void*)> callbackClick
		);

		Button(const Button &button) = delete;
		virtual ~Button() = default;

		std::function<void(void*)> callbackClick;
	};

}