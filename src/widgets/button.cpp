#include "widgets/button.hpp"

glgui::widget::Button::Button(

	std::int32_t x,
	std::int32_t y,
	std::int32_t width,
	std::int32_t height,
	std::function<void(void*)> callbackClick
)
: glgui::widget::Base(x, y, width, height), callbackClick(callbackClick)
{

	
}