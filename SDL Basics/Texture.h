#pragma once

#include <SDL3\SDL_render.h>
#include <SDL3\SDL_video.h>
#include <string>

namespace Texture
{
/* Constants */
constexpr const char *kTitle{ "SDL Texture Tutorial" };

// Screen dimension constants
constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };

/* Class prototypes */
class LTexture
{
public:
  // Initializes texture variables
  LTexture();

  // Cleans up texture variables
  ~LTexture();

  // Loads texture from disk
  bool loadFromFile(std::string path);

  // Cleans up texture
  void destroy();

  // Draws texture
  void render(float x, float y);

  // Gets texture dimensions
  int getWidth() const;
  int getHeight() const;

private:
  // Contains texture data
  SDL_Texture *mTexture;

  // Texture dimensions
  int mWidth;
  int mHeight;
};

/* Global Variables */
// The window we'll be rendering to
extern SDL_Window *gWindow;

// The renderer used to draw to the window
extern SDL_Renderer *gRenderer;

// The PNG image we will render
extern LTexture gPngTexture;

/* Function Implementations */
bool init();

bool loadMedia();

void close();

int main(int argc, char *args[]);
} // namespace Texture
