#pragma once

#include "pch.hpp"
#include "utils.hpp"
#include "widgets/base.hpp"
#include "texture.hpp"
#include "image.hpp"

namespace glgui::widget
{
	struct Button : public glgui::widget::Base
	{

		Button(

			Rect rect,
			glgui::Color color,
			std::function<void(void*)> callbackClick
		);

		Button(const Button &button) = delete;
		virtual ~Button();

		virtual void draw() override;

		glgui::Color color;
		glgui::Color colorH;
		std::function<void(void*)> callbackClick;

		bool mouseHover;
		
		Texture *txr;
		Image *img;

		Texture *txrH;
	};

}