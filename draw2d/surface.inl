/* Inline functions need to have a definition that is visible to the compiler
 * whenever the function is used. THey could be define in the header that
 * declares the function. However, to keep the definitions and declarations
 * somewhat apart, it is a common practice to move them to an "inline" file
 * such as this one (*.inl extension). This file is then #include:ed at the end
 * of the header, to ensure that whoever includes the header also automatically
 * includes the inline file.
 *
 * Inlining allows us to avoid any overheads related to call (when building in
 * "release mode" / with optimizations enabled). This makes functions like
 * set_pixel_srgb() zero overhead abstractions.
 *
 */

 
inline
void Surface::set_pixel_srgb( Index aX, Index aY, ColorU8_sRGB const& aColor )
{
	assert( aX < mWidth && aY < mHeight ); // IMPORTANT! This line must remain the first line in this function!

	// To calculate the linear memory index 
	Index linearIndex = get_linear_index(aX, aY);

	// Calculate the starting index for the pixel in the 1D image data array
	Index startIndex = linearIndex * 4; // Multiply by 4 since each pixel has 4 components (R, G, B, and padding)

	// Set the color components (R, G, B) for the pixel
	mSurface[startIndex + 0] = aColor.r; // Red component
	mSurface[startIndex + 1] = aColor.g; // Green component
	mSurface[startIndex + 2] = aColor.b; // Blue component
	// Padding component (usually not used, set to 0)
	mSurface[startIndex + 3] = 0;

}

inline 
auto Surface::get_width() const noexcept -> Index
{
	return mWidth;
}
inline
auto Surface::get_height() const noexcept -> Index
{
	return mHeight;
}

// should return the linear memory index of the pixel inside the mSurface array 
inline
Surface::Index Surface::get_linear_index( Index aX, Index aY ) const noexcept
{	
	// aY = row index, aX = column index 
	return aY * get_width() + aX;
}
