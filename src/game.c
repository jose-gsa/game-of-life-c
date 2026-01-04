#include "game.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

static int count_neightbors(GameState *game, int y, int x);

void setup_ncurses() {
  // initialize ncurses main setings
  initscr();
  nodelay(stdscr, TRUE);
  curs_set(0);
  noecho();
}

void init_game(GameState *game) {

  srand(time(NULL));

  // Init the main grid
  for (int i = 0; i < MAX_HEIGHT; i++) {
    for (int k = 0; k < MAX_WIDTH; k++) {

      int chance = rand() % 100; // 0 to 99
      if (chance < 15) {         // 15% spawn rate
        game->grid[i][k] = 1;
      } else {
        game->grid[i][k] = 0;
      }
    }
  }

  // initialize basic constants
  game->height = MAX_HEIGHT;
  game->width = MAX_WIDTH;
  game->is_running = TRUE;
  game->is_paused = FALSE;
  game->speed = 50; // This is for debuging
}

// No input for now
void process_input(GameState *game) {}

void update_state(GameState *game) {

  // Clean buffer
  for (int i = 0; i < game->height; i++) {
    for (int k = 0; k < game->width; k++) {
      game->next_grid[i][k] = 0;
    }
  }

  // Game rules
  for (int i = 0; i < game->height; i++) {
    for (int k = 0; k < game->width; k++) {

      int neighbors = count_neightbors(game, i, k);
      int is_alive = game->grid[i][k];

      if (is_alive) {
        // Rules (survival)

        if ((neighbors == 2) || (neighbors == 3)) {
          game->next_grid[i][k] = 1;
        }
      } else { // is dead

        // Rule (reprodution)

        if (neighbors == 3) {
          game->next_grid[i][k] = 1;
        }
      }
    }
  }

  // Copy the buffer for the main grid
  for (int i = 0; i < game->height; i++) {
    for (int k = 0; k < game->width; k++) {
      game->grid[i][k] = game->next_grid[i][k];
    }
  }
}

void render_game(GameState *game) {

  erase();

  for (int i = 0; i < game->height; i++) {
    for (int k = 0; k < game->width; k++) {

      if (game->grid[i][k] == 1) {
        mvaddch(i, k, ACS_CKBOARD | A_BOLD);
      }
    }
  }
  refresh();
}

void cleanup_game(GameState *game) { endwin(); }

int count_neightbors(GameState *game, int y, int x) {

  int neighbors = 0;

  for (int i = -1; i <= 1; i++) {
    for (int k = -1; k <= 1; k++) {

      // This will make the game works like pacman and prevent overflows
      int row = (y + i + game->height) % game->height;
      int col = (x + k + game->width) % game->width;

      // Sum of the (1 or 0)
      neighbors += game->grid[row][col];
    }
  }

  // Will not count himself
  neighbors -= game->grid[y][x];

  return neighbors;
}
