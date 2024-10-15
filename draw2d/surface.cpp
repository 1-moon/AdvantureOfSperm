#include "surface.hpp"
#include "color.hpp"

#include <utility>

#include <cstring>  // This defines std::memset()...

Surface::Surface( Index aWidth, Index aHeight )
	: mSurface( nullptr )
	, mWidth( aWidth )
	, mHeight( aHeight )
{
	mSurface = new std::uint8_t[ mWidth * mHeight * 4 ];
}
Surface::~Surface()
{
	delete [] mSurface;
}

Surface::Surface( Surface&& aOther ) noexcept
	: mSurface( std::exchange( aOther.mSurface, nullptr ) )
	, mWidth( std::exchange( aOther.mWidth, 0 ) )
	, mHeight( std::exchange( aOther.mHeight, 0 ) )
{}
Surface& Surface::operator=( Surface&& aOther ) noexcept
{
	std::swap( mSurface, aOther.mSurface );
	std::swap( mWidth, aOther.mWidth );
	std::swap( mHeight, aOther.mHeight );
	return *this;
}


void Surface::clear() noexcept
{
	//std::memset( mSurface, 0, sizeof(std::uint8_t)*mWidth*mHeight*4 ); // all black 
	
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			mSurface[(y * mWidth + x) * 4 + 0] = 255; // red
			mSurface[(y * mWidth + x) * 4 + 1] = 182; // green
			mSurface[(y * mWidth + x) * 4 + 2] = 193; // blue
			mSurface[(y * mWidth + x) * 4 + 3] = 255; // alpha
		}
	}
}

void Surface::fill( ColorU8_sRGB aColor ) noexcept
{
	// This can be optimized quite a bit. 8 bit loads and stores are generally
	// not the most efficient.
	auto const limit = mWidth * mHeight * 4;
	for( std::size_t i = 0; i < limit; i += 4 )
	{
		mSurface[i+0] = aColor.r;
		mSurface[i+1] = aColor.g;
		mSurface[i+2] = aColor.b;
		mSurface[i+3] = 0;
	}
}

std::uint8_t const* Surface::get_surface_ptr() const noexcept
{
	return mSurface;
}

