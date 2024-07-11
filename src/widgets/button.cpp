#include "widgets/button.hpp"
#include "engine.hpp"

glgui::widget::Button::Button(

	glgui::Rect rect,
	glgui::Color color,
	std::function<void(void*)> callbackClick
)
: glgui::widget::Base(rect), color(color), colorH(255, 255, 255), callbackClick(callbackClick)
{
	mouseHover = false;
	std::string svg;

	// Normal texture
	svg = fmt::format(
		R"(
		<svg id="a" data-name="Layer 1" xmlns="http://www.w3.org/2000/svg" width="{widthP3}" height="{heightP3}" viewBox="0 0 {widthP3} {heightP3}">
			<rect x="3" y="3" width="{width}" height="{height}" rx="20" ry="20" style="fill: #191919;"/>
			<rect x="0" y="0" width="{width}" height="{height}" rx="20" ry="20" style="fill: {color};"/>
		</svg>
		)",

		fmt::arg("widthP3", rect.size.x+3),
		fmt::arg("heightP3", rect.size.y+3),
		fmt::arg("width", rect.size.x),
		fmt::arg("height", rect.size.y),
		fmt::arg("color", color.rgbString())
	);

	txr = new Texture(svg.c_str(), svg.size(), rect.size.x+3, rect.size.y+3);
	img = new Image(txr, rect.pos.x, rect.pos.y);

	// Hover texture
	svg = fmt::format(
		R"(
		<svg id="a" data-name="Layer 1" xmlns="http://www.w3.org/2000/svg" width="{widthP3}" height="{heightP3}" viewBox="0 0 {widthP3} {heightP3}">
			<rect x="3" y="3" width="{width}" height="{height}" rx="20" ry="20" style="fill: #191919;"/>
			<rect x="0" y="0" width="{width}" height="{height}" rx="20" ry="20" style="fill: {color};"/>
		</svg>
		)",

		fmt::arg("widthP3", rect.size.x+3),
		fmt::arg("heightP3", rect.size.y+3),
		fmt::arg("width", rect.size.x),
		fmt::arg("height", rect.size.y),
		fmt::arg("color", colorH.rgbString())
	);

	txrH = new Texture(svg.c_str(), svg.size(), rect.size.x+3, rect.size.y+3);

	// Add
	Engine::widgets.push_back(this);
	Engine::buttons.push_back(this);
}

glgui::widget::Button::~Button()
{
	delete img;
	delete txr;
	delete txrH;

	// Remove
	Engine::widgets.erase(std::find(Engine::widgets.begin(), Engine::widgets.end(), this));
	Engine::buttons.erase(std::find(Engine::buttons.begin(), Engine::buttons.end(), this));
}

void glgui::widget::Button::draw()
{
	// Check mouse position
	img->texture = rect.collision(Engine::mousePos) ? txrH : txr;
	img->draw();
}