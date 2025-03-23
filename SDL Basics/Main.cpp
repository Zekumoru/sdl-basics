/* Headers */
#include "KeyEvents.h"
#include <SDL3\SDL_render.h>
#include <SDL3\SDL_video.h>

SDL_Window *gWindow{ nullptr };
SDL_Renderer *gRenderer{ nullptr };

int main(int argc, char *args[]) { return KeyEvents::main(argc, args); }
