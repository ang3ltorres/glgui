#include "widgets/button.hpp"

glgui::widget::Button::Button(

	std::int32_t x,
	std::int32_t y,
	std::int32_t width,
	std::int32_t height,
	glgui::Color color,
	std::function<void(void*)> callbackClick
)
: glgui::widget::Base(x, y, width, height), color(color), callbackClick(callbackClick)
{
	std::string svg = fmt::format(
		R"(
		<svg id="a" data-name="Layer 1" xmlns="http://www.w3.org/2000/svg" width="{widthP3}" height="{heightP3}" viewBox="0 0 {widthP3} {heightP3}">
			<rect x="3" y="3" width="{width}" height="{height}" rx="20" ry="20" style="fill: #191919;"/>
			<rect x="0" y="0" width="{width}" height="{height}" rx="20" ry="20" style="fill: {color};"/>
		</svg>
		)",

		fmt::arg("widthP3", width+3),
		fmt::arg("heightP3", height+3),
		fmt::arg("width", width),
		fmt::arg("height", height),
		fmt::arg("color", color.rgbString())
	);

	txr = new Texture(svg.c_str(), svg.size(), width+3, height+3);
	img = new Image(txr, x, y);
}

glgui::widget::Button::~Button()
{
	delete img;
	delete txr;
}

void glgui::widget::Button::draw()
{
	img->draw();
}