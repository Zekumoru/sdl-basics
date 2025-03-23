#include "Texture.h"
#include <SDL3\SDL_error.h>
#include <SDL3\SDL_events.h>
#include <SDL3\SDL_init.h>
#include <SDL3\SDL_log.h>
#include <SDL3\SDL_rect.h>
#include <SDL3\SDL_render.h>
#include <SDL3\SDL_stdinc.h>
#include <SDL3\SDL_surface.h>
#include <SDL3\SDL_video.h>
#include <SDL3_image\SDL_image.h>
#include <string>

/* Class Implementations */
// LTexture Implementation
LTexture::LTexture()
    : // Initialize texture variables
      mTexture{ nullptr }, mWidth{ 0 }, mHeight{ 0 }
{
}

LTexture::~LTexture()
{
  // Clean up texture
  destroy();
}

bool LTexture::loadFromFile(std::string path)
{
  // Clean up texture if it already exists
  destroy();

  // Load surface
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == nullptr)
  {
    SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(),
            SDL_GetError());
  }
  else
  {
    // Create texture from surface
    mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (mTexture == nullptr)
    {
      SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n",
              SDL_GetError());
    }
    else
    {
      // Get image dimensions
      mWidth = loadedSurface->w;
      mHeight = loadedSurface->h;
    }
  }

  // Clean up loaded surface
  SDL_DestroySurface(loadedSurface);

  // Return success if texture loaded
  return mTexture != nullptr;
}

void LTexture::destroy()
{
  // Clean up texture
  SDL_DestroyTexture(mTexture);
  mTexture = nullptr;
  mWidth = 0;
  mHeight = 0;
}

void LTexture::render(float x, float y)
{
  // Set texture position
  SDL_FRect dstRect = { x, y, static_cast<float>(mWidth),
                        static_cast<float>(mHeight) };

  // Render texture
  SDL_RenderTexture(gRenderer, mTexture, nullptr, &dstRect);
}

int LTexture::getWidth() const { return mWidth; }

int LTexture::getHeight() const { return mHeight; }

namespace Texture
{
LTexture gPngTexture;

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
  // Load splash image
  if (!gPngTexture.loadFromFile("loaded.png"))
  {
    SDL_Log("Unable to load png image!\n");
    return false;
  }

  return true;
}

void close()
{
  // Clean up texture
  gPngTexture.destroy();

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

  // The main loop
  while (quit == false)
  {
    // Get event data
    while (SDL_PollEvent(&e))
    {
      // If event is quit type
      // End the main loop
      quit = e.type == SDL_EVENT_QUIT;
    }

    // Fill the background white
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    // Render image on screen
    gPngTexture.render(0.f, 0.f);

    // Update screen
    SDL_RenderPresent(gRenderer);
  }

  // Clean up
  close();

  return 0;
}
} // namespace Texture
