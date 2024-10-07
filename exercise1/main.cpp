#include <glad.h>
#include <GLFW/glfw3.h>

#include <typeinfo>
#include <stdexcept>

#include <cstdio>

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

#include "../support/error.hpp"
#include "../support/context.hpp"
#include <iostream>
#include <vector>

struct Rectangle {
	double minX, minY, maxX, maxY;
	ColorU8_sRGB color;
};

// Store the rectangles in a list (e.g. std::vector)
std::vector<Rectangle> allRects;
Rectangle currentRect;
bool isDrawing = false;

namespace
{
	constexpr int kInitWindowWidth = 1280;
	constexpr int kInitWindowHeight = 720;
	constexpr char const* kWindowTitle = "Advanture of sperm";


	void glfw_callback_error_( int, char const* );

	void glfw_callback_key_( GLFWwindow*, int, int, int, int );
	// Task 1: Declare the cursor position callback function
	void glfw_callback_motion_(GLFWwindow* , double , double );
	// Task 2: Declare the mouse button callback function 
	void glfw_callback_button_(GLFWwindow*, int, int, int);

	struct GLFWCleanupHelper
	{
		~GLFWCleanupHelper();
	};

}

int main() try
{
	if( GLFW_TRUE != glfwInit() ){
		char const* msg = nullptr;
		int ecode = glfwGetError( &msg );
		throw Error( "glfwInit() failed with '%s' (%d)", msg, ecode );
	}

	// Ensure that we call glfwTerminate() at the end of the program.
	GLFWCleanupHelper cleanupHelper;

	glfwSetErrorCallback( &glfw_callback_error_ );

	glfwWindowHint( GLFW_SRGB_CAPABLE, GLFW_TRUE );
	glfwWindowHint( GLFW_DOUBLEBUFFER, GLFW_TRUE );

	glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE ); // Prevent resizing for now...

#	if !defined(__APPLE__)
	// Most platforms will support OpenGL 4.3
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
#	else // defined(__APPLE__)
	// Apple has at most OpenGL 4.1, so don't ask for something newer.
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
#	endif // ~ __APPLE__
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

#	if !defined(NDEBUG)
	// When building in debug mode, request an OpenGL debug context. This
	// enables additional debugging features. However, this can carry extra
	// overheads. We therefore do not do this for release builds.
	glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE );
#	endif // ~ !NDEBUG

	GLFWwindow* window = glfwCreateWindow(
		kInitWindowWidth,
		kInitWindowHeight,
		kWindowTitle,
		nullptr, nullptr
	);

	if( !window ){
		char const* msg = nullptr;
		int ecode = glfwGetError( &msg );
		throw Error( "glfwCreateWindow() failed with '%s' (%d)", msg, ecode );
	}

	int iwidth, iheight;
	glfwGetFramebufferSize( window, &iwidth, &iheight );

	float wscale = 1.f, hscale = 1.f;
#	if defined(__APPLE__)
	// HACK: Window content scaling on MacOS.
	//
	// This is a workaround for MacOS, where scaling affects retina displays.
	// Windows technically also does content scaling, but it seems to do this
	// more transparently. Either way, the behaviour doesn't seem to be
	// consistent across the platforms, though, which is slightly unfortunate.
	// (And not having a (retina) Mac to test on makes figuring this out a tad
	// more tricky.)
		glfwGetWindowContentScale( window, &wscale, &hscale );
#	endif

	assert( iwidth >= 0 && iheight >= 0 && wscale != 0.f && hscale != 0.f );
	auto const fbwidth = std::uint32_t(iwidth / wscale);
	auto const fbheight = std::uint32_t(iheight / hscale);

	glfwSetKeyCallback( window, &glfw_callback_key_ );
	// set a cursor position callback. 
	glfwSetCursorPosCallback(window, glfw_callback_motion_);
	// set a mouse button callback. 
	glfwSetMouseButtonCallback(window, glfw_callback_button_);

	glfwMakeContextCurrent( window );
	glfwSwapInterval( 1 );

	Context context( fbwidth, fbheight );
	Surface surface( fbwidth, fbheight );

	//  call the render loop for handling window not to close 
	while( !glfwWindowShouldClose( window ) )
	{
		// Let GLFW process events
	 
		// Task 1: call the cursor position callback whenever the mouse is moved. 
		glfwWaitEvents();
		//glfwPollEvents();

		// Update state
		// Nothing to do at the moment...
	
		// Draw scene - clear the surface then prepare for drawing 
		surface.clear();

		//TODO: drawing code goes here
		surface.set_pixel_srgb(10, 100, { 255, 0, 255 });
		draw_rectangle_solid(
			surface,
			{ 50.f, 300.f },
			{ 200.f, 450.f },
			{ 255, 0, 0 } // red
		);
		draw_rectangle_outline(
			surface,
			{ 50.f, 300.f },
			{ 200.f, 450.f },
			{ 255, 255, 255 } // white
		);
		// Draw all the rectangles in the vector
		for (const Rectangle& rect : allRects) {
			draw_rectangle_solid(surface, { static_cast<float>(rect.minX), static_cast<float>(rect.minY) }, { static_cast<float>(rect.maxX), static_cast<float>(rect.maxY) }, { 255, 0, 0 }); // Red rectangles
		}
		if (isDrawing) {
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			currentRect.maxX = xpos;
			currentRect.maxY = ypos;
			draw_rectangle_solid(surface, { static_cast<float>(currentRect.minX), static_cast<float>(currentRect.minY) }, { static_cast<float>(currentRect.maxX), static_cast<float>(currentRect.maxY) }, { 255, 0, 0 });
		}


		context.draw( surface );

		// Display results
		// glfw: swap buffers 
		glfwSwapBuffers( window );
	}

	// Cleanup.
	// For now, all objects are automatically cleaned up when they go out of
	// scope.
	
	return 0;
} catch( std::exception const& eErr ){
	// exception handling 
	std::fprintf( stderr, "Top-level Exception (%s):\n", typeid(eErr).name() );
	std::fprintf( stderr, "%s\n", eErr.what() );
	std::fprintf( stderr, "Bye.\n" );
	return 1;
}

// ===================================================
namespace
{

	void glfw_callback_error_( int aErrNum, char const* aErrDesc )
	{
		std::fprintf( stderr, "GLFW error: %s (%d)\n", aErrDesc, aErrNum );
	}

	void glfw_callback_key_( GLFWwindow* aWindow, int aKey, int, int aAction, int )
	{
		if( GLFW_KEY_ESCAPE == aKey && GLFW_PRESS == aAction )
		{
			glfwSetWindowShouldClose( aWindow, GLFW_TRUE );
			return;
		}
	}
	

	void glfw_callback_motion_(GLFWwindow* aWindow, double aMouseXPos, double aMouuseYPos) { 
		
		if (isDrawing) {
			currentRect.maxX = aMouseXPos;
			currentRect.maxY = aMouuseYPos;
		}
	}



	void glfw_callback_button_(GLFWwindow* aWindow, int aButton, int aAction, int /*mods*/) {
		if (aButton == GLFW_MOUSE_BUTTON_LEFT) {
			double xpos, ypos;

			if (aAction == GLFW_PRESS) {
				 
				glfwGetCursorPos(aWindow, &xpos, &ypos);
				currentRect.minX = xpos;
				currentRect.minY = ypos;
				isDrawing = true;
			}
			else if (aAction == GLFW_RELEASE) { 
				glfwGetCursorPos(aWindow, &xpos, &ypos);
				currentRect.maxX = xpos;
				currentRect.maxY = ypos;
				isDrawing = false;
				allRects.push_back(currentRect);
			}
		}
	}

}

namespace
{
	GLFWCleanupHelper::~GLFWCleanupHelper()
	{
		glfwTerminate();
	}
}

