#ifndef BRICK_GAME_H
#define BRICK_GAME_H

#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define START_LEVEL 1
#define START_SCORE 0
#define FIELD_WIDTH 11
#define FIELD_HEIGHT 22
#define EXIT_KEY 27
#define ENTER_KEY '\n'
#define PAUSE_KEY 112
#define MOVE_SPEED 4

typedef struct
{
    int x;
    int y;
} PlayerPos;

typedef struct {
    char array[4][4];
    int width, height, col;
} Shape;

typedef struct {
    char cells[FIELD_HEIGHT][FIELD_WIDTH];
    Shape *shape;
    Shape *next_shape;
    int level;
    int score;
    int maxScore;
    int speed;
} BrickgameInfo;

void FillBoardWithSpaces(BrickgameInfo *BgInfo);
void PrintRectangle( BrickgameInfo *BgInfo);
void PrintField(BrickgameInfo *BgInfo);
void PrintInfo(BrickgameInfo Info, bool paused);
void PrintOverlay(BrickgameInfo BgInfo, bool paused);
void PrintGameoverText(BrickgameInfo BgInfo, bool *gameover);

//Operations with figures
void UpdateFigure(Shape *figure);
void CopyFigure(Shape *dst, Shape *src);
void ResetBgInfo(BrickgameInfo *bGInfo);

void ResetElements(PlayerPos *object_pos, Shape shape, BrickgameInfo *BgInfo);
void SetElements(PlayerPos *object_pos, Shape shape, BrickgameInfo *BgInfo);

void ShiftTetrominoDown(PlayerPos *object_pos, Shape shape,
    BrickgameInfo *BgInfo, Shape *newcurrent);
void MoveTetrominoRight(PlayerPos *object_pos, BrickgameInfo *BgInfo);
void MoveTetrominoLeft(PlayerPos *object_pos, BrickgameInfo *BgInfo);

//Functions for rotate
void RotateClockwise(const Shape *src, Shape *dst);
void ShiftShapeDown(Shape *shape);
void ShiftShapeRight(Shape *shape);
void TryRotate(PlayerPos *object_pos, BrickgameInfo *bGInfo);

void PutFigure2Field(BrickgameInfo *bGInfo, PlayerPos *pos);
int FigureDescByOneString(BrickgameInfo *bGInfo, PlayerPos *pos);

void ScoreAndLevel(int count, BrickgameInfo *BgInfo);
void CheckLines(BrickgameInfo *BgInfo);
int CheckEndGame(PlayerPos *pos, BrickgameInfo *bGInfo);
int GetMaxScore();
void PutMaxScore(int score); 

void GameLoop();

#endif