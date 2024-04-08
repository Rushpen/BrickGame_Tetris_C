#include "../brick_game.h"

typedef enum
{
    START = 0,
    SPAWN,
    MOVING,
    SHIFTING,
    REACH,
    PAUSE,
    JOINING,
    GAMEOVER,
    EXIT_STATE
} ObjectState;

typedef enum
{
    PAUSE_BTN,
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    ROTATE,
    ENTER_BTN,
    EXIT_BTN,
    NOSIG
} Signals;

//Creating figures
void ClearFigureArray(Shape *figure);
void CreateLineFigure(Shape *figure);
void CreateLFigure(Shape *figure);
void CreateJFigure(Shape *figure);
void CreateQuadrFigure(Shape *figure);
void CreateSFigure(Shape *figure);
void CreateTFigure(Shape *figure);
void CreateZFigure(Shape *figure);

void HandleGameLogic(BrickgameInfo *BgInfo, PlayerPos *tetris_pos, Shape *current,
 Shape *newcurrent, ObjectState *state, bool *paused);

void HandleUserInput(int sig, BrickgameInfo *BgInfo, PlayerPos *tetris_pos, Shape *current,
 Shape *newcurrent, ObjectState *state, bool *paused);

//Handles States
void HandlePauseState(Signals sig, ObjectState *state, bool *paused);

void HandleStartState(Signals sig, ObjectState *state, Shape *current, BrickgameInfo *BgInfo);

void HandleSpawnState(Shape *newcurrent, BrickgameInfo *BgInfo, ObjectState *state);

void HandleMovingState(Signals sig, BrickgameInfo *BgInfo, PlayerPos *tetris_pos,
 Shape *current, Shape *newcurrent, ObjectState *state, bool *paused);

void HandleGameoverState(BrickgameInfo *BgInfo, bool *gameover, Signals sig, ObjectState *state);

//Processing control
Signals GetSignal(int user_input);

void Sigact(Signals sig, ObjectState *state, PlayerPos *tetris_pos, bool *paused,
    BrickgameInfo *BgInfo, Shape *current, Shape *newcurrent);