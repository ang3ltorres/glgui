#pragma once

#include "pch.hpp"
#include "widgets/base.hpp"
#include "texture.hpp"
#include "image.hpp"

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
		virtual ~Button();

		virtual void draw() override;

		std::function<void(void*)> callbackClick;
		Texture *txr;
		Image *img;
	};

}