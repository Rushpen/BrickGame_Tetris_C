#include "../fsm.h"

#include "../../brick_game.h"

Signals GetSignal(int UserInput) {
  Signals rc = NOSIG;

  if (UserInput == KEY_UP)
    rc = ROTATE;
  else if (UserInput == KEY_DOWN)
    rc = MOVE_DOWN;
  else if (UserInput == KEY_LEFT)
    rc = MOVE_LEFT;
  else if (UserInput == KEY_RIGHT)
    rc = MOVE_RIGHT;
  else if (UserInput == EXIT_KEY)
    rc = EXIT_BTN;
  else if (UserInput == ENTER_KEY)
    rc = ENTER_BTN;
  else if (UserInput == PAUSE_KEY)
    rc = PAUSE_BTN;

  return rc;
}

void ClearFigureArray(Shape *figure) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figure->array[i][j] = ' ';
    }
  }
}

void CreateLineFigure(Shape *figure) {
  ClearFigureArray(figure);
  for (int j = 0; j < 4; j++) {
    figure->array[0][j] = '*';
  }
  figure->height = 1;
  figure->width = 4;
}

void CreateLFigure(Shape *figure) {
  ClearFigureArray(figure);
  figure->array[0][0] = '*';
  figure->array[1][0] = '*';
  figure->array[1][1] = '*';
  figure->array[1][2] = '*';
  figure->height = 2;
  figure->width = 3;
}

void CreateJFigure(Shape *figure) {
  ClearFigureArray(figure);
  figure->array[0][2] = '*';
  figure->array[1][0] = '*';
  figure->array[1][1] = '*';
  figure->array[1][2] = '*';
  figure->height = 2;
  figure->width = 3;
}

void CreateQuadrFigure(Shape *figure) {
  ClearFigureArray(figure);
  figure->array[0][0] = '*';
  figure->array[0][1] = '*';
  figure->array[1][0] = '*';
  figure->array[1][1] = '*';
  figure->height = 2;
  figure->width = 2;
}

void CreateSFigure(Shape *figure) {
  ClearFigureArray(figure);
  figure->array[0][1] = '*';
  figure->array[0][2] = '*';
  figure->array[1][0] = '*';
  figure->array[1][1] = '*';
  figure->height = 2;
  figure->width = 3;
}

void CreateTFigure(Shape *figure) {
  ClearFigureArray(figure);
  figure->array[0][1] = '*';
  figure->array[1][0] = '*';
  figure->array[1][1] = '*';
  figure->array[1][2] = '*';
  figure->height = 2;
  figure->width = 3;
}

void CreateZFigure(Shape *figure) {
  ClearFigureArray(figure);
  figure->array[0][0] = '*';
  figure->array[0][1] = '*';
  figure->array[1][1] = '*';
  figure->array[1][2] = '*';
  figure->height = 2;
  figure->width = 3;
}

void UpdateFigure(Shape *figure) {
  switch (rand() % 7) {
    case 0:
      CreateLineFigure(figure);
      break;
    case 1:
      CreateLFigure(figure);
      break;
    case 2:
      CreateJFigure(figure);
      break;
    case 3:
      CreateQuadrFigure(figure);
      break;
    case 4:
      CreateSFigure(figure);
      break;
    case 5:
      CreateTFigure(figure);
      break;
    case 6:
      CreateZFigure(figure);
      break;
  }
}

void CopyFigure(Shape *dst, Shape *src) {
  dst->height = src->height;
  dst->width = src->width;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      dst->array[i][j] = src->array[i][j];
    }
  }
}

void ResetBgInfo(BrickgameInfo *BgInfo) {
  BgInfo->level = 1;
  BgInfo->score = 0;
  BgInfo->speed = 0;
  BgInfo->maxScore = 0;
  BgInfo->shape = NULL;
  BgInfo->next_shape = NULL;
}

void ScoreAndLevel(int count, BrickgameInfo *BgInfo) {
  if (count == 1) {
    BgInfo->score += 100;
  } else if (count == 2) {
    BgInfo->score += 300;
  } else if (count == 3) {
    BgInfo->score += 700;
  } else if (count == 4) {
    BgInfo->score += 1500;
  }

  if (BgInfo->level < 11) {
    BgInfo->level = BgInfo->score / 600 + 1;
    if (BgInfo->level > 10) {
      BgInfo->level = 10;
    }
  }
  if (BgInfo->level % 2 == 0) {
    BgInfo->speed += 1;
  }
}

void CheckLines(BrickgameInfo *BgInfo) {
  int count = 0;
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    int sum = 0;
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (BgInfo->cells[i][j] == '*') sum++;
    }
    if (sum == 10) {
      count++;
      int l, k;
      for (k = i; k > 0; k--)
        for (l = 0; l < FIELD_WIDTH; l++)
          BgInfo->cells[k][l] = BgInfo->cells[k - 1][l];
      for (l = 0; l < FIELD_WIDTH; l++) BgInfo->cells[k][l] = ' ';
    }
  }
  ScoreAndLevel(count, BgInfo);
}

int GetMaxScore() {
  FILE *fp = fopen("tetris.dat", "r");
  if (fp == NULL) {
    return 0;
  }
  int score = 0;
  fscanf(fp, "%d", &score);
  fclose(fp);
  return score;
}

void PutMaxScore(int score) {
  FILE *fp = fopen("tetris.dat", "w");
  if (fp == NULL) {
    return;
  }
  fprintf(fp, "%d", score);
  fclose(fp);
  return;
}

void ResetElements(PlayerPos *object_pos, Shape shape, BrickgameInfo *BgInfo) {
  for (int i = 0; i < shape.height; ++i) {
    for (int j = 0; j < shape.width; ++j) {
      if (shape.array[i][j] == '*') {
        BgInfo->cells[object_pos->y + i][object_pos->x + j] = ' ';
      }
    }
  }
}

void SetElements(PlayerPos *object_pos, Shape shape, BrickgameInfo *BgInfo) {
  for (int i = 0; i < shape.height; ++i) {
    for (int j = 0; j < shape.width; ++j) {
      if (shape.array[i][j] == '*') {
        BgInfo->cells[object_pos->y + i][object_pos->x + j] = '*';
      }
    }
  }
}

void ShiftTetrominoDown(PlayerPos *object_pos, Shape shape,
                        BrickgameInfo *BgInfo, Shape *newcurrent) {
  ResetElements(object_pos, shape, BgInfo);
  while (FigureDescByOneString(BgInfo, object_pos))
    ;
  CopyFigure(BgInfo->shape, BgInfo->next_shape);
  UpdateFigure(newcurrent);
  CopyFigure(BgInfo->next_shape, newcurrent);
  object_pos->x = 4;
  object_pos->y = 0;
}

void MoveTetrominoRight(PlayerPos *object_pos, BrickgameInfo *BgInfo) {
  if (object_pos->x + BgInfo->shape->width == 11) return;
  for (int j = 0; j < BgInfo->shape->width; j++) {
    for (int i = 0; i < BgInfo->shape->height; i++) {
      if ((BgInfo->shape->array[i][j] == '*') &&
          (BgInfo->cells[i + object_pos->y][j + 1 + object_pos->x] == '*')) {
        return;
      }
    }
  }
  object_pos->x++;
}

void MoveTetrominoLeft(PlayerPos *object_pos, BrickgameInfo *BgInfo) {
  if (object_pos->x == 1) return;
  for (int j = 0; j < BgInfo->shape->width; j++) {
    for (int i = 0; i < BgInfo->shape->height; i++) {
      if ((BgInfo->shape->array[i][j] == '*') &&
          (BgInfo->cells[i + object_pos->y][j - 1 + object_pos->x] == '*')) {
        return;
      }
    }
  }
  object_pos->x--;
}

void RotateClockwise(const Shape *src, Shape *dst) {
  for (int i = 0; i < src->height; i++) {
    for (int j = 0; j < src->width; j++) {
      dst->array[j][src->height - i - 1] = src->array[i][j];
    }
  }
}

void ShiftShapeDown(Shape *shape) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      shape->array[i][j] = shape->array[(i + 1) % 3][j];
    }
  }
  for (int j = 0; j < 3; j++) {
    shape->array[3][j] = ' ';
  }
}

void ShiftShapeRight(Shape *shape) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      shape->array[i][j] = shape->array[i][(j + 1) % 3];
    }
  }
  for (int i = 0; i < 3; i++) {
    shape->array[i][3] = ' ';
  }
}

void TryRotate(PlayerPos *object_pos, BrickgameInfo *bGInfo) {
  Shape dst;
  dst.width = bGInfo->shape->height;
  dst.height = bGInfo->shape->width;

  if (object_pos->y + bGInfo->shape->height > 19 ||
      object_pos->y + bGInfo->shape->width > 19)
    return;

  if (dst.width != dst.height) {
    RotateClockwise(bGInfo->shape, &dst);
    if (dst.width == 4 || dst.height == 4) {
      RotateClockwise(bGInfo->shape, &dst);
    } else {
      if (dst.array[0][0] == ' ' && dst.array[0][1] == ' ' &&
          dst.array[0][2] == ' ') {
        ShiftShapeDown(&dst);
      }
      if (dst.array[0][0] == ' ' && dst.array[1][0] == ' ' &&
          dst.array[2][0] == ' ') {
        ShiftShapeRight(&dst);
      }
    }
    CopyFigure(bGInfo->shape, &dst);
  }
}

void PutFigure2Field(BrickgameInfo *bGInfo, PlayerPos *pos) {
  for (int i = 0; i < bGInfo->shape->height; i++) {
    for (int j = 0; j < bGInfo->shape->width; j++) {
      if (bGInfo->shape->array[i][j] == '*') {
        bGInfo->cells[pos->y + i][pos->x + j] = '*';
      }
    }
  }
}

int FigureDescByOneString(BrickgameInfo *bGInfo, PlayerPos *pos) {
  if (pos->y == 20 - bGInfo->shape->height) {
    PutFigure2Field(bGInfo, pos);
    return 0;
  }
  for (int j = 0; j < bGInfo->shape->width; j++) {
    for (int i = 0; i < bGInfo->shape->height; i++) {
      if ((bGInfo->shape->array[i][j] == '*') &&
          (bGInfo->cells[i + 1 + pos->y][j + pos->x] == '*')) {
        PutFigure2Field(bGInfo, pos);
        return 0;
      }
    }
  }
  pos->y++;
  return 1;
}

void Sigact(Signals sig, ObjectState *state, PlayerPos *tetris_pos,
            bool *paused, BrickgameInfo *BgInfo, Shape *current,
            Shape *newcurrent) {
  bool gameover = false;
  switch (*state) {
    case PAUSE:
      HandlePauseState(sig, state, paused);
      break;
    case START:
      HandleStartState(sig, state, current, BgInfo);
      break;
    case SPAWN:
      HandleSpawnState(newcurrent, BgInfo, state);
      break;
    case MOVING:
      HandleMovingState(sig, BgInfo, tetris_pos, current, newcurrent, state,
                        paused);
      break;
    case GAMEOVER:
      HandleGameoverState(BgInfo, &gameover, sig, state);
      break;
    default:
      break;
  }
}

void HandlePauseState(Signals sig, ObjectState *state, bool *paused) {
  switch (sig) {
    case ENTER_BTN:
      *state = MOVING;
      *paused = false;
      break;
    case EXIT_BTN:
      *state = EXIT_STATE;
      break;
    default:
      *state = PAUSE;
      break;
  }
}

void HandleStartState(Signals sig, ObjectState *state, Shape *current,
                      BrickgameInfo *BgInfo) {
  UpdateFigure(current);
  BgInfo->shape = current;
  switch (sig) {
    case EXIT_BTN:
      *state = EXIT_STATE;
      break;
    default:
      *state = SPAWN;
      break;
  }
}

void HandleSpawnState(Shape *newcurrent, BrickgameInfo *BgInfo,
                      ObjectState *state) {
  UpdateFigure(newcurrent);
  BgInfo->next_shape = newcurrent;
  *state = MOVING;
}

void HandleMovingState(Signals sig, BrickgameInfo *BgInfo,
                       PlayerPos *tetris_pos, Shape *current, Shape *newcurrent,
                       ObjectState *state, bool *paused) {
  HandleGameLogic(BgInfo, tetris_pos, current, newcurrent, state, paused);
  HandleUserInput(sig, BgInfo, tetris_pos, current, newcurrent, state, paused);
}

void HandleGameLogic(BrickgameInfo *BgInfo, PlayerPos *tetris_pos,
                     Shape *current, Shape *newcurrent, ObjectState *state,
                     bool *paused) {
  CheckLines(BgInfo);
  BgInfo->maxScore = GetMaxScore();
  ResetElements(tetris_pos, *current, BgInfo);
  if (FigureDescByOneString(BgInfo, tetris_pos) == 0) {
    CopyFigure(BgInfo->shape, BgInfo->next_shape);
    UpdateFigure(newcurrent);
    CopyFigure(BgInfo->next_shape, newcurrent);
    tetris_pos->x = 4;
    tetris_pos->y = 0;
  }
  if (CheckEndGame(tetris_pos, BgInfo)) {
    *state = GAMEOVER;
    *paused = true;
  }
  SetElements(tetris_pos, *current, BgInfo);
  if (BgInfo->score > BgInfo->maxScore) PutMaxScore(BgInfo->score);
}

void HandleUserInput(int sig, BrickgameInfo *BgInfo, PlayerPos *tetris_pos,
                     Shape *current, Shape *newcurrent, ObjectState *state,
                     bool *paused) {
  switch (sig) {
    case ROTATE:
      ResetElements(tetris_pos, *current, BgInfo);
      TryRotate(tetris_pos, BgInfo);
      SetElements(tetris_pos, *current, BgInfo);
      break;
    case MOVE_DOWN:
      ShiftTetrominoDown(tetris_pos, *current, BgInfo, newcurrent);
      break;
    case MOVE_RIGHT:
      ResetElements(tetris_pos, *current, BgInfo);
      MoveTetrominoRight(tetris_pos, BgInfo);
      SetElements(tetris_pos, *current, BgInfo);
      break;
    case MOVE_LEFT:
      ResetElements(tetris_pos, *current, BgInfo);
      MoveTetrominoLeft(tetris_pos, BgInfo);
      SetElements(tetris_pos, *current, BgInfo);
      break;
    case PAUSE_BTN:
      *state = PAUSE;
      *paused = true;
      break;
    case EXIT_BTN:
      *state = EXIT_STATE;
      break;
    default:
      break;
  }
}

void HandleGameoverState(BrickgameInfo *BgInfo, bool *gameover, Signals sig,
                         ObjectState *state) {
  *gameover = true;
  FillBoardWithSpaces(BgInfo);
  PrintGameoverText(*BgInfo, gameover);
  switch (sig) {
    case ENTER_BTN:
      *state = START;
      *gameover = false;
      ResetBgInfo(BgInfo);
      break;
    case EXIT_BTN:
      *state = EXIT_STATE;
      break;
    default:
      *state = GAMEOVER;
      break;
  }
}

int CheckEndGame(PlayerPos *tetris_pos, BrickgameInfo *bGInfo) {
  int endGame = 0;
  for (int i = 0; i < bGInfo->shape->height; i++) {
    for (int j = 0; j < bGInfo->shape->width; j++) {
      if (bGInfo->shape->array[i][j] == '*' &&
          bGInfo->cells[tetris_pos->y + i][tetris_pos->x + j] == '*') {
        endGame = 1;
      }
    }
  }
  return endGame;
}