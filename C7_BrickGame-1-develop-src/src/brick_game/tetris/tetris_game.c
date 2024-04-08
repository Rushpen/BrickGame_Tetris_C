#include "../../brick_game.h"
#include "../fsm.h"

int main() {
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  halfdelay(MOVE_SPEED);
  GameLoop();
  endwin();
  return 0;
}

void GameLoop() {
  int signal = 0;
  ObjectState state = START;
  bool break_flag = TRUE;
  PlayerPos figure = {4, 0};
  bool paused = false;
  BrickgameInfo board;
  ResetBgInfo(&board);
  FillBoardWithSpaces(&board);
  Shape current = {0};
  Shape newcurrent = {0};

  while (break_flag) {
    PrintOverlay(board, paused);
    if (state == EXIT_STATE) break_flag = FALSE;

    Sigact(GetSignal(signal), &state, &figure, &paused, &board, &current,
           &newcurrent);
    signal = getch();

    refresh();
  }
}
