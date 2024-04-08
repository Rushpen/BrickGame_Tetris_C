#include "../../brick_game.h"

void FillBoardWithSpaces(BrickgameInfo *BgInfo) {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      BgInfo->cells[i][j] = ' ';
    }
  }
}

void PrintRectangle(BrickgameInfo *BgInfo) {
  for (int i = 2; i <= FIELD_HEIGHT + 1; i++) {
    mvaddch(i, 1, ACS_VLINE);
    mvaddch(i, FIELD_WIDTH * 2 + 1, ACS_VLINE);
  }
  for (int i = 1; i <= FIELD_WIDTH * 2 + 1; i++) {
    mvaddch(2, i, ACS_HLINE);
    mvaddch(FIELD_HEIGHT + 1, i, ACS_HLINE);
  }

  mvaddch(2, 1, ACS_ULCORNER);
  mvaddch(2, FIELD_WIDTH * 2 + 1, ACS_URCORNER);
  mvaddch(FIELD_HEIGHT + 1, 1, ACS_LLCORNER);
  mvaddch(FIELD_HEIGHT + 1, FIELD_WIDTH * 2 + 1, ACS_LRCORNER);

  for (int i = 1; i < FIELD_HEIGHT - 2; i++) {
    for (int j = 1; j < FIELD_WIDTH; j++) {
      mvprintw(i + 3, j * 2 + 1, "%c", BgInfo->cells[i][j]);
      mvprintw(i + 3, j * 2 + 2, " ");
    }
  }
}

void PrintField(BrickgameInfo *BgInfo) {
  mvprintw(1, FIELD_WIDTH - 3, "BRICKGAME:");
  PrintRectangle(BgInfo);
}

void PrintInfo(BrickgameInfo Info, bool paused) {
  mvprintw(4, FIELD_WIDTH * 2 + 3, "LEVEL: %d", Info.level);
  mvprintw(7, FIELD_WIDTH * 2 + 3, "SCORE: %d", Info.score);
  mvprintw(10, FIELD_WIDTH * 2 + 3, "RECORD SCORE: %d", Info.maxScore);
  move(13, FIELD_WIDTH * 2 + 3);
  printw("NEXT FIGURE:");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      mvaddch(i + 13, j * 2 + 30, ' ');
      mvaddch(i + 13, j * 2 + 1 + 30, ' ');
      if (Info.next_shape != NULL && Info.next_shape->array[i][j] == '*') {
        mvaddch(i + 13, j * 2 + 30, ACS_CKBOARD);
        mvaddch(i + 13, j * 2 + 1 + 30, ACS_CKBOARD);
      }
    }
  }

  mvprintw(17, FIELD_WIDTH * 2 + 3, "Press 'Esc' to exit:");
  if (paused) {
    mvprintw(1, FIELD_WIDTH - 3, "  PAUSED  ");
  } else {
    mvprintw(1, FIELD_WIDTH - 3, "BRICKGAME:");
  }
}

void PrintGameoverText(BrickgameInfo BgInfo, bool *gameover) {
  if (*gameover) {
    mvprintw(9, 7, "             ");
    mvprintw(10, 7, " Game Over ");
    mvprintw(11, 7, "your score:");
    mvprintw(12, 7, "     %d ", BgInfo.score);
    mvprintw(13, 7, "             ");
    mvprintw(14, 7, "Press 'Enter'");
    mvprintw(15, 7, "  to play'");
    mvprintw(16, 7, "             ");
  }
}

void PrintOverlay(BrickgameInfo BgInfo, bool paused) {
  refresh();
  PrintField(&BgInfo);
  PrintInfo(BgInfo, paused);
}
