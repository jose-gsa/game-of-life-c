#include <ncurses.h>

/* Test the ncurses lib and makefile */

int main() {

  char letter;

  initscr();
  printw("Prees any key");
  refresh();

  letter = getch();
  clear();
  printw("You pushed: %c", letter);
  refresh();

  getch();
  endwin();

  return 0;
}
