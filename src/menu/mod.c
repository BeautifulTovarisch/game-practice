#include <ncurses.h>

void draw_menu(int selection) {
  char main_menu[] = "Main Menu";

  char menu[4][21] = {
    "Query",
    "New Record",
    "Update Record",
    "Delete Record"
  };

  clear();

  addstr(main_menu);

  for(int i = 0; i < 4; i++) {

    if(i == selection) {
      attron(A_REVERSE);
    }

    mvaddstr(3 + (i * 2), 20, menu[i]);
    attroff(A_REVERSE);

    mvaddstr(17, 25, "Use arrow keys to move, Enter to select.");
    refresh();
  }
}
