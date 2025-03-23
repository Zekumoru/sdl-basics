#pragma once
#include "Texture.h"
#include <SDL3\SDL_render.h>
#include <SDL3\SDL_video.h>

/* Global Variables */
// The window we'll be rendering to
extern SDL_Window *gWindow;

// The renderer used to draw to the window
extern SDL_Renderer *gRenderer;

namespace KeyEvents
{
/* Constants */
constexpr const char *kTitle{ "SDL Texture Tutorial" };

// Screen dimension constants
constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };

// The directional images
extern LTexture gUpTexture, gDownTexture, gLeftTexture, gRightTexture;

/* Function declarations */
bool init();

bool loadMedia();

void close();

int main(int argc, char *args[]);
} // namespace KeyEvents
