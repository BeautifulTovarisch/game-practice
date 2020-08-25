#include "mod.h"

// Store positions of button entities
static int num_buttons = 0;
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

void Menu_AddButton(Entity button) {
  buttons[num_buttons] = button;
  num_buttons++;
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
