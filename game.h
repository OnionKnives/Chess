#pragma once
#include <SDL.h>

#include "piece.h"

void update();
void renderValidMoves();
Team activePlayer();
Piece* activePiece();