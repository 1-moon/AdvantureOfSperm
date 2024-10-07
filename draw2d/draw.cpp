#include "draw.hpp"

#include <algorithm>

#include <cmath>

#include "color.hpp"
#include "surface.hpp"
/*
	aMinCorner - coordinate over left upper corner of rectangle 
	aMaxCorner - coordinate over right lower corner of rectangle
*/
void draw_rectangle_solid( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	// 1. calculate location and size of retangle using aMin,aMaxCorner.
	float minX = aMinCorner.x;
	float minY = aMinCorner.y;
	float maxX = aMaxCorner.x;
	float maxY = aMaxCorner.y;
	// 2. fill speicified color in the rantangle
	// looks to need using loop...   
	for (float x = minX; x < maxX; x++)
		for (float y = minY; y < maxY; y++)
			//  set_pixel_srgb func requires the object of Surface.
			//  need to convert float type to Surface::Index  using 'static_cast' 
			aSurface.set_pixel_srgb(static_cast<Surface::Index>(x), static_cast<Surface::Index>(y), aColor);
	

}

void draw_rectangle_outline( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	// 1. calculate location and size of retangle using aMin,aMaxCorner.
	float minX = aMinCorner.x;
	float minY = aMinCorner.y;
	float maxX = aMaxCorner.x;
	float maxY = aMaxCorner.y;
	// 2. calculate the four lines of the rectangle 
	// top line 
	for (float x = minX; x < maxX; x++)
		aSurface.set_pixel_srgb(static_cast<Surface::Index>(x), minY, aColor);
	// left line 
	for (float y = minY; y < maxY; y++)
		aSurface.set_pixel_srgb(minX, static_cast<Surface::Index>(y), aColor);
	// bottom line 
	for (float x = minX; x < maxX; x++)
		aSurface.set_pixel_srgb(static_cast<Surface::Index>(x), maxY, aColor);
	// right line 
	for (float y = minY; y < maxY; y++)
		aSurface.set_pixel_srgb(maxX, static_cast<Surface::Index>(y), aColor);
}

