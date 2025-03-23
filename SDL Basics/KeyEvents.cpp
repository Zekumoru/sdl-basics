#include "KeyEvents.h"
#include "Texture.h"
#include <SDL3\SDL_events.h>
#include <SDL3\SDL_init.h>
#include <SDL3\SDL_keyboard.h>
#include <SDL3\SDL_keycode.h>
#include <SDL3\SDL_log.h>
#include <SDL3\SDL_pixels.h>
#include <SDL3\SDL_render.h>
#include <SDL3\SDL_scancode.h>
#include <SDL3\SDL_stdinc.h>
#include <SDL3\SDL_video.h>

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

namespace KeyEvents
{
LTexture gUpTexture, gDownTexture, gLeftTexture, gRightTexture;

/* Function Implementations */
bool init()
{
  // Initialize SDL
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
    return false;
  }

  // Create window with renderer
  if (!SDL_CreateWindowAndRenderer(
          "SDL3 Tutorial: Textures and Extension Libraries", kScreenWidth,
          kScreenHeight, 0, &gWindow, &gRenderer))
  {
    SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

bool loadMedia()
{
  // File loading flag
  bool success{ true };

  // Load directional images
  success &= gUpTexture.loadFromFile("up.png");
  if (!success)
  {
    SDL_Log("Unable to load up image!\n");
  }

  success &= gDownTexture.loadFromFile("down.png");
  if (!success)
  {
    SDL_Log("Unable to load down image!\n");
  }
  success &= gLeftTexture.loadFromFile("left.png");
  if (!success)
  {
    SDL_Log("Unable to load left image!\n");
  }
  success &= gRightTexture.loadFromFile("right.png");
  if (!success)
  {
    SDL_Log("Unable to load right image!\n");
  }

  return success;
}

void close()
{
  // Clean up texture
  gUpTexture.destroy();
  gDownTexture.destroy();
  gLeftTexture.destroy();
  gRightTexture.destroy();

  // Destroy window
  SDL_DestroyRenderer(gRenderer);
  gRenderer = nullptr;
  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  // Quit SDL subsystems
  SDL_Quit();
}

int main(int argc, char *args[])
{
  // Initialize
  if (!init())
  {
    SDL_Log("Unable to initialize program!\n");
    return 1;
  }

  // Load media
  if (!loadMedia())
  {
    SDL_Log("Unable to load media!\n");
    return 2;
  }

  // The quit flag
  bool quit{ false };

  // The event data
  SDL_Event e;
  SDL_zero(e);

  // The currently rendered texture
  LTexture *currentTexture = &gUpTexture;

  // Background color defaults to white
  SDL_Color bgColor = { 0xFF, 0xFF, 0xFF, 0xFF };

  // The main loop
  while (quit == false)
  {
    // Get event data//Get event data
    while (SDL_PollEvent(&e))
    {
      // If event is quit type
      if (e.type == SDL_EVENT_QUIT)
      {
        // End the main loop
        quit = true;
      }
      // On keyboard key press
      else if (e.type == SDL_EVENT_KEY_DOWN)
      {
        // Set texture
        if (e.key.key == SDLK_UP)
        {
          currentTexture = &gUpTexture;
        }
        else if (e.key.key == SDLK_DOWN)
        {
          currentTexture = &gDownTexture;
        }
        else if (e.key.key == SDLK_LEFT)
        {
          currentTexture = &gLeftTexture;
        }
        else if (e.key.key == SDLK_RIGHT)
        {
          currentTexture = &gRightTexture;
        }
      }
    }

    // Reset background color to white
    bgColor.r = 0xFF;
    bgColor.g = 0xFF;
    bgColor.b = 0xFF;

    // Set background color based on key state
    const bool *keyStates = SDL_GetKeyboardState(nullptr);
    if (keyStates[SDL_SCANCODE_UP])
    {
      // Red
      bgColor.r = 0xFF;
      bgColor.g = 0x00;
      bgColor.b = 0x00;
    }
    else if (keyStates[SDL_SCANCODE_DOWN])
    {
      // Green
      bgColor.r = 0x00;
      bgColor.g = 0xFF;
      bgColor.b = 0x00;
    }
    else if (keyStates[SDL_SCANCODE_LEFT])
    {
      // Yellow
      bgColor.r = 0xFF;
      bgColor.g = 0xFF;
      bgColor.b = 0x00;
    }
    else if (keyStates[SDL_SCANCODE_RIGHT])
    {
      // Blue
      bgColor.r = 0x00;
      bgColor.g = 0x00;
      bgColor.b = 0xFF;
    }

    // Fill the background
    SDL_SetRenderDrawColor(gRenderer, bgColor.r, bgColor.g, bgColor.b, 0xFF);
    SDL_RenderClear(gRenderer);

    // Render image on screen
    currentTexture->render((kScreenWidth - currentTexture->getWidth()) / 2.f,
                           (kScreenHeight - currentTexture->getHeight()) / 2.f);

    // Update screen
    SDL_RenderPresent(gRenderer);
  }

  // Clean up
  close();

  return 0;
}
} // namespace KeyEvents
