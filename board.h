#pragma once

#include <SDL.h>

#include "piece.h"

void initializeBoard();
void renderValidMoveSquare(SDL_Point);
void renderBoard();
void renderPieces();

bool mouseInCell(SDL_Point);
Piece* checkIfMouseClickedOnCell();
Piece* checkCell(SDL_Point);
void getCellSize(SDL_Rect*);
void movePiece(Piece*, SDL_Point);