#include <SDL2/SDL_image.h>

/* Asset Paths */
const char *ROBOT_SPRITE;

typedef struct Robot {
  SDL_Rect src;
  SDL_Rect dst;
} Robot;

void Robot_Draw(Robot robot);
