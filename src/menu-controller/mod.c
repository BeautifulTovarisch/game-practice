#include "mod.h"

// Keep track of which button is which entity
static char *sprites[5] = {"assets/play_button.png", "assets/play_button.png",
                           "assets/play_button.png", "assets/play_button.png",
                           "assets/play_button.png"};
static Entity buttons[5];

/* Buttons are identified by their static position in the above:
   Button 0 - Play
   Button 1 - Exit
*/

// Set state depending on button pressed
static void handle_click(int button) {
  switch (button) {
  case PLAY:
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
    return;
  }
}

void Menu_Init(World *world, SDL_Renderer *renderer) {

  // Initialize buttons
  for (int i = 0; i < 5; i++) {
    Entity button = ECS_CreateEntity();

    buttons[i] = button;

    // Add Sprites and collision for buttons
    ECS_AddComponent(
        world, button,
        (Component){
            .type = C_SPRITE,
            .component.sprite = {
                .texture = DS_LoadTexture(sprites[i], renderer),
                .src = {.w = 64, .h = 64},
                .dest = {.x = 75, .y = 75 * (i + 1), .w = 64, .h = 48}}});

    ECS_AddComponent(
        world, button,
        (Component){.type = C_COLLISION,
                    .component.collision = {
                        .origin = (Vector){.x = 75, .y = 75 * (i + 1)},

                        .width = 64,
                        .height = 48}});
  }
}

void Menu_DetectSelection(World *world) {
  for (int i = 0; i < 5; i++) {
    if (Physics_VectorCollision(world, buttons[i],
                                State_Get()->mouse.position)) {
      // Nested if here to only check for click when over a button
      if (State_Get()->mouse.buttons & SDL_BUTTON_LEFT) {
        handle_click(i);
      }
    }
  }
}
