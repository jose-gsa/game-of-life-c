#include "game.h"
#include <ncurses.h>

int main() {
  GameState game;

  // ncurses configuration and variables
  setup_ncurses();
  init_game(&game);

  // Main Game Loop
  while (game.is_running) {
    process_input(&game);

    if (!game.is_paused) {
      update_state(&game);
    }

    render_game(&game);

    // framerate control
    napms(game.speed);
  }

  cleanup_game(&game);
  return 0;
}
