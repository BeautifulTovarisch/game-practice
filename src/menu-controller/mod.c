#include "mod.h"

#define NUM_BUTTONS 5

// Keep track of which button is which entity
static char *sprites[NUM_BUTTONS] = {
    "assets/play_button.png", "assets/play_button.png",
    "assets/play_button.png", "assets/play_button.png",
    "assets/play_button.png"};

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

/* Add Sprites and collision for buttons
 * Reusable method for hiding/showing menu at various points
 */
void Menu_Show(World *world, SDL_Renderer *renderer) {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    ECS_AddComponent(
        world, buttons[i],
        (Component){
            .type = C_SPRITE,
            .component.sprite = {
                .texture = DS_LoadTexture(sprites[i], renderer),
                .src = {.w = 64, .h = 64},
                .dest = {.x = 75, .y = 75 * (i + 1), .w = 64, .h = 48}}});

    ECS_AddComponent(
        world, buttons[i],
        (Component){.type = C_COLLISION,
                    .component.collision = {
                        .origin = (Vector){.x = 75, .y = 75 * (i + 1)},

                        .width = 64,
                        .height = 48}});
  }
}

/* Removing sprite and collision components will prevent the draw
 * and physics systems from handling the buttons void
 */
void Menu_Hide(World *world) {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    ECS_RemoveComponent(world, buttons[i], C_SPRITE);
    ECS_RemoveComponent(world, buttons[i], C_COLLISION);
  }
}

void Menu_Init(World *world, SDL_Renderer *renderer) {

  // Initialize buttons
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i] = ECS_CreateEntity();
  }

  Menu_Show(world, renderer);
}

void Menu_DetectSelection(World *world) {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    if (Physics_VectorCollision(world, buttons[i],
                                State_Get()->mouse.position)) {
      // Nested if here to only check for click when over a button
      if (State_Get()->mouse.buttons & SDL_BUTTON_LEFT) {
        handle_click(i);
      }
    }
  }
}
