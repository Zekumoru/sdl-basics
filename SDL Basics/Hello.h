#pragma once

#include <SDL3\SDL_surface.h>
#include <SDL3\SDL_video.h>

namespace Hello
{
/* Constants */
constexpr const char *kTitle{ "SDL Tutorial" };

// Screen dimension constants
constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };

/* Function prototypes */
// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// Main program
int main(int argc, char *args[]);

/* Global variables */
// The window we'll be rendering to
extern SDL_Window *gWindow;

// The surface contained by the window
extern SDL_Surface *gScreenSurface;

// The image we will load and show on the screen
extern SDL_Surface *gHelloWorld;
} // namespace Hello
