#include "game.h"
#include <ncurses.h>

void setup_ncurses() {
  // initialize ncurses main setings
  initscr();
  nodelay(stdscr, TRUE);
  curs_set(0);
  noecho();
}

void init_game(GameState *game) {

  // Init the main grid whit 0
  for (int i = 0; i < MAX_HEIGHT; i++) {
    for (int k = 0; k < MAX_WIDTH; k++) {
      game->grid[i][k] = 0;
    }
  }
  game->grid[0][0] = 1;

  // initialize basic constants
  game->height = MAX_HEIGHT;
  game->width = MAX_WIDTH;
  game->is_running = TRUE;
  game->is_paused = FALSE;
  game->speed = 1000; // This is 1 second
}

// No input for now
void process_input(GameState *game) {}

void update_state(GameState *game) {

  // Checks if the last positon has been reached
  if (game->grid[game->height - 1][game->width - 1] == 1) {
    game->is_running = FALSE;
    return;
  }

  for (int i = 0; i < game->height; i++) {
    for (int k = 0; k < game->width; k++) {
      game->next_grid[i][k] = 0;
    }
  }

  for (int y = 0; y < game->height; y++) {
    for (int x = 0; x < game->width; x++) {
      if (game->grid[y][x] == 1) {
        if ((x + 1) < game->width) {
          game->next_grid[y][x + 1] = 1;
        } else if (y < game->height - 1) {
          game->next_grid[y + 1][0] = 1;
        }
      }
    }
  }

  for (int i = 0; i < game->height; i++) {
    for (int k = 0; k < game->width; k++) {
      game->grid[i][k] = game->next_grid[i][k];
    }
  }
}

void render_game(GameState *game) {}

void cleanup_game(GameState *game) {}
