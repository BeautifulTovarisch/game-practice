#include "mod.h"

static int num_components;
static int current_selection;

static UIComponent components[5];

/* Buttons are identified by their static positions:
 *   Button 0 - Play
 *   Button 1 - Pause
 *   Button 2 - Resume
 *   Button 3 - Exit
 *   Button 4 - Quit
 */

// Set state depending on button pressed
static void handle_selection() {
  switch (current_selection) {
    // Play button should only be shown on main menu
  case PLAY:
    State_Update(GAME_START);
    break;
  case RESUME:
    break;
  case QUIT:
    // TODO :: Show confirmation
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
    case SDLK_UP:
      current_selection =
          current_selection > 0 ? current_selection-- : num_components;
      break;
    case SDLK_DOWN:
      current_selection =
          current_selection < num_components ? current_selection++ : 0;
      break;
    default:
      break;
    }
  }
}

/* Add Sprites for menu
 * Reusable method for hiding/showing menu at various points
 * TODO :: Consider removing entities and creating new each time
 */
void Menu_Show(SDL_Renderer *renderer, Menu type) {
  int width, height, w_width, w_height, num_components = 0;

  SDL_Texture *tex;

  SDL_GetRendererOutputSize(renderer, &w_width, &w_height);

  switch (type) {
  case M_MAIN:
    tex = DS_LoadTexture("assets/game_title.png", renderer);
    SDL_QueryTexture(tex, NULL, NULL, &width, &height);

    int center_x = (w_width - width) / 2;
    int center_y = (w_height - height) / 2;

    components[0] = (UIComponent){.x = center_x,
                                  .y = center_y,
                                  .width = width,
                                  .option = PLAY,
                                  .height = height,
                                  .texture = tex};
    num_components = 1;
    break;
  default:
    return;
  }

  // Draw ui components set above.
  for (int i = 0; i < num_components; i++) {
    UIComponent comp = components[i];
    SDL_Rect src = {.w = comp.width, .h = comp.height};
    SDL_Rect dest = {
        .x = comp.x, .y = comp.y, .w = comp.width, .h = comp.height};

    // Draw UI components
    if (SDL_RenderCopy(renderer, comp.texture, &src, &dest) != 0) {
      printf("Failed to draw texture: %s\n", SDL_GetError());
    }
  }

  // Set current menu option to the first button
  current_selection = 0;
}

// Close menu, free up textures.
void Menu_Destroy() {
  for (int i = 0; i < num_components; i++) {
    SDL_DestroyTexture(components[i].texture);
  }
}

void Menu_Init(SDL_Renderer *renderer) { num_components = 0; }
