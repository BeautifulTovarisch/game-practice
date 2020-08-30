#include "mod.h"

#define NUM_BUTTONS 1

// Keep track of which button is which entity
static char *sprites[NUM_BUTTONS] = {"assets/pong_title.png"};

/* Buttons are identified by their static positions:
 *   Button 0 - Play
 *   Button 1 - Pause
 *   Button 2 - Resume
 *   Button 3 - Exit
 *   Button 4 - Quit
 */

static Entity buttons[NUM_BUTTONS];

// Set state depending on button pressed
static void handle_click(int button) {
  switch (button) {
  case PLAY:
    State_Update(MENU_CLOSE);
    State_Update(GAME_UNPAUSE);
    break;
  case PAUSE:
    State_Update(MENU_OPEN);
    State_Update(GAME_PAUSE);
    break;
  case RESUME:
    break;
  case EXIT:
    break;
  case QUIT:
    break;
  default:
    return;
  }
}

/* Add Sprites for menu
 * Reusable method for hiding/showing menu at various points
 * TODO :: Consider removing entities and creating new each time
 * TODO :: Show menu options contingent on current state
 */
void Menu_Show(World *world, SDL_Renderer *renderer) {
  int width, height, w_width, w_height;

  for (int i = 0; i < NUM_BUTTONS; i++) {
    SDL_Texture *tex = DS_LoadTexture(sprites[i], renderer);

    SDL_QueryTexture(tex, NULL, NULL, &width, &height);
    SDL_GetRendererOutputSize(renderer, &w_width, &w_height);

    int center_x = (w_width - width) / 2;
    int center_y = (w_height - height) / 2;

    ECS_AddComponent(world, buttons[i],
                     (Component){.type = C_SPRITE,
                                 .component.sprite = {.texture = tex,
                                                      .animated = 0,
                                                      .width = width,
                                                      .height = height}});

    ECS_AddComponent(world, buttons[i],
                     (Component){.type = C_POSITION,
                                 .component.vector =
                                     (Vector){.x = center_x, .y = center_y}});
  }
}

/* Removing sprite and collision components will prevent the draw
 * and physics systems from handling the buttons void
 */
void Menu_Hide(World *world) {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    ECS_RemoveComponent(world, buttons[i], C_SPRITE);
  }
}

void Menu_Init(World *world, SDL_Renderer *renderer) {

  // Initialize buttons
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i] = ECS_CreateEntity();
  }

  Menu_Show(world, renderer);
}
