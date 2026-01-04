#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

typedef struct {
  int **grid;      // Actual grid
  int **next_grid; // buffer
  int height;      // real height of the actual window
  int width;       // real width of the actual window
  bool is_running; // Control of the main loop
  bool is_paused;  // Pause control
  int speed;       // Simulation speed
} GameState;

void setup_ncurses();
void init_game(GameState *game);
void process_input(GameState *game);
void update_state(GameState *game);
void render_game(GameState *game);
void cleanup_game(GameState *game);

#endif
