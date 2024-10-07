#ifndef DRAW_HPP_BA97BA20_4B0E_45D8_97D4_65267FFA2EA6
#define DRAW_HPP_BA97BA20_4B0E_45D8_97D4_65267FFA2EA6

#include "forward.hpp"

#include "../vmlib/vec2.hpp"

void draw_rectangle_solid(
	Surface&,	// a mutable Surface reference. 
	Vec2f aMinCorner, Vec2f aMaxCorner,	// coordinates for the min and max corners of the rec 
	ColorU8_sRGB	// to specify the color in which the rec should be drawn 
);

void draw_rectangle_outline(
	Surface&, // To draw axis-aligned rectangles into the passed-in surface
	Vec2f aMinCorner, Vec2f aMaxCorner,	// vec2f is defined in vec2.hpp 
	ColorU8_sRGB
);



#endif // DRAW_HPP_BA97BA20_4B0E_45D8_97D4_65267FFA2EA6
