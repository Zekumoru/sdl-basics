/* Headers */
#include <SDL3\SDL_error.h>
#include <SDL3\SDL_events.h>
#include <SDL3\SDL_init.h>
#include <SDL3\SDL_log.h>
#include <SDL3\SDL_stdinc.h>
#include <SDL3\SDL_surface.h>
#include <SDL3\SDL_video.h>
#include <string>

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

/* Global variables */
// The window we'll be rendering to
SDL_Window *gWindow{ nullptr };

// The surface contained by the window
SDL_Surface *gScreenSurface{ nullptr };

// The image we will load and show on the screen
SDL_Surface *gHelloWorld{ nullptr };

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
      quit = e.type == SDL_EVENT_QUIT;
    }

    // Fill the surface white
    SDL_FillSurfaceRect(gScreenSurface, nullptr,
                        SDL_MapSurfaceRGB(gScreenSurface, 0xFF, 0xFF, 0xFF));

    // Render image on screen
    SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);

    // Update the surface
    SDL_UpdateWindowSurface(gWindow);
  }

  // Clean up
  close();

  return 0;
}

/* Function implementations */
bool init()
{
  // Initialize SDL
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
    return false;
  }

  // Create window
  gWindow = SDL_CreateWindow(kTitle, kScreenWidth, kScreenHeight, 0);
  if (gWindow == nullptr)
  {
    SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
    return false;
  }

  // Get window surface
  gScreenSurface = SDL_GetWindowSurface(gWindow);
  return true;
}

bool loadMedia()
{
  // Load splash image
  std::string imagePath{ "hello-sdl3.bmp" };

  gHelloWorld = SDL_LoadBMP(imagePath.c_str());
  if (gHelloWorld == nullptr)
  {
    SDL_Log("Unable to load image %s! SDL error: %s\n", imagePath.c_str(),
            SDL_GetError());
    return false;
  }

  return true;
}

void close()
{
  // Clean up surface
  SDL_DestroySurface(gHelloWorld);
  gHelloWorld = nullptr;

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;
  gScreenSurface = nullptr;

  // Quit SDL subsystems
  SDL_Quit();
}
