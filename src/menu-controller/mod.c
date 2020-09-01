#include "mod.h"

#define NUM_BUTTONS 1

// Order of sprites here corresponds to below.
static char *sprites[NUM_BUTTONS] = {"assets/game_title.png"};

/* Buttons are identified by their static positions:
 *   Button 0 - Play
 *   Button 1 - Pause
 *   Button 2 - Resume
 *   Button 3 - Exit
 *   Button 4 - Quit
 */

static int current_selection;
static Entity buttons[NUM_BUTTONS];

// Set state depending on button pressed
static void handle_selection() {
  switch (current_selection) {
  case PLAY:
    State_Update(MENU_TOGGLE);
    State_Update(GAME_TOGGLE_PAUSE);
    break;
  case PAUSE:
    break;
  case RESUME:
    break;
  case EXIT:
    break;
  case QUIT:
    break;
  default:
    break;
  }
}

void Menu_HandleInput(SDL_Event event) {
  switch (event.type) {
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_RETURN:
      // Make Selection
      handle_selection();
      break;
    }
  default:
    break;
  }
}

/* Add Sprites for menu
 * Reusable method for hiding/showing menu at various points
 * TODO :: Consider removing entities and creating new each time
 */
void Menu_Show(SDL_Renderer *renderer) {
  int width, height, w_width, w_height;

  for (int i = 0; i < NUM_BUTTONS; i++) {
    SDL_Texture *tex = DS_LoadTexture(sprites[i], renderer);

    SDL_QueryTexture(tex, NULL, NULL, &width, &height);
    SDL_GetRendererOutputSize(renderer, &w_width, &w_height);

    int center_x = (w_width - width) / 2;
    int center_y = (w_height - height) / 2;

    ECS_AddComponent(buttons[i],
                     (Component){.type = C_SPRITE,
                                 .component.sprite = {.texture = tex,
                                                      .animated = 0,
                                                      .width = width,
                                                      .height = height}});

    ECS_AddComponent(buttons[i],
                     (Component){.type = C_POSITION,
                                 .component.vector =
                                     (Vector){.x = center_x, .y = center_y}});
  }

  // Set current menu option to the first button
  // TODO :: Update selection with arrow keys
  current_selection = 0;
}

/* Removing sprite and collision components will prevent the draw
 * and physics systems from handling the buttons void
 */
void Menu_Hide() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    ECS_RemoveComponent(buttons[i], C_POSITION);
    ECS_RemoveComponent(buttons[i], C_SPRITE);
  }
}

void Menu_Init(SDL_Renderer *renderer) {
  // Initialize buttons
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i] = ECS_CreateEntity();
  }

  Menu_Show(renderer);
}
