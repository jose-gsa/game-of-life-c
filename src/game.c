#include "game.h"
#include <ncurses.h>

void init_game(GameState *game) {

  initscr();
  nodelay(stdscr, TRUE);
  curs_set(0);

  // Init the main grid whit 0
  for (int i = 0; i < MAX_HEIGHT; i++) {
    for (int k = 0; k < MAX_WIDTH; k++) {
      game->grid[i][k] = 0;
    }
  }

  game->grid[1][1] = 1;
}

// No input for now
void process_input(GameState *game) {}

void update_state(GameState *game) {}

void render_game(GameState *game) {}

void cleanup_game(GameState *game) {}
