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

std::string svg = fmt::format(
R"(
<svg id="a" data-name="Layer 1" xmlns="http://www.w3.org/2000/svg" width="105" height="105" viewBox="0 0 105 105">
	<rect x="2.5" y="2.5" width="100" height="100" rx="10" ry="10" style="fill: #c81922; stroke: #000; stroke-miterlimit: 10; stroke-width: 5px;"/>
</svg>
)",
fmt::arg("x_plus_5", x+5),
fmt::arg("y_plus_5", y+5),
fmt::arg("width", width),
fmt::arg("height", height),
fmt::arg("width_plus_5", width+5),
fmt::arg("height_plus_5", height+5)
);

	txr = new Texture(svg.c_str(), svg.size(), width+5, height+5);
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