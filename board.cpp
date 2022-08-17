#include <vector>

#include "board.h"
#include "input.h"
#include "graphics.h"

Piece* board[8][8];
std::vector<Piece*> whiteGraveyard;
std::vector<Piece*> blackGraveyard;

int topOffset = 20;
int leftOffset;
SDL_Rect blackSquare;
SDL_Rect borderOutline;

void initializeBoard() {
	// Set Board Size
	blackSquare.h = (screenHeight() - topOffset * 2) / 8;
	blackSquare.w = blackSquare.h;

	leftOffset = (screenWidth() / 2) - (4 * blackSquare.w);

	borderOutline.h = blackSquare.h * 8 + 8;
	borderOutline.w = blackSquare.w * 8 + 8;
	borderOutline.x = screenWidth() / 2 - borderOutline.w / 2;
	borderOutline.y = topOffset - 4;

	// Set all spaces to null
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			board[col][row] = nullptr;
		}
	}

	// Pawns
	for (int col = 0; col < 8; ++col) {
		board[col][1] = new Piece({ Team::Black, Type::Pawn, {col, 1} });
		board[col][6] = new Piece({ Team::White, Type::Pawn, {col, 6} });
	}

	// Rooks
	{
		board[0][0] = new Piece({ Team::Black, Type::Rook, { 0, 0 } });
		board[7][0] = new Piece({ Team::Black, Type::Rook, { 7, 0 } });
		board[0][7] = new Piece({ Team::White, Type::Rook, { 0, 7 } });
		board[7][7] = new Piece({ Team::White, Type::Rook, { 7, 7 } });
	}

	// Knights
	{
		board[1][0] = new Piece({ Team::Black, Type::Knight, { 1, 0} });
		board[6][0] = new Piece({ Team::Black, Type::Knight, { 6, 0} });
		board[1][7] = new Piece({ Team::White, Type::Knight, { 1, 7} });
		board[6][7] = new Piece({ Team::White, Type::Knight, { 6, 7} });
	}

	// Bishops
	{
		board[2][0] = new Piece({ Team::Black, Type::Bishop, { 2, 0} });
		board[5][0] = new Piece({ Team::Black, Type::Bishop, { 5, 0} });
		board[2][7] = new Piece({ Team::White, Type::Bishop, { 2, 7} });
		board[5][7] = new Piece({ Team::White, Type::Bishop, { 5, 7} });
	}

	// Queens
	{
		board[3][0] = new Piece({ Team::Black, Type::Queen, { 3, 0} });
		board[3][7] = new Piece({ Team::White, Type::Queen, { 3, 7} });
	}

	// Kings
	{
		board[4][0] = new Piece({ Team::Black, Type::King, { 4, 0} });
		board[4][7] = new Piece({ Team::White, Type::King, { 4, 7} });
	}
}

void cellToPixels(SDL_Point& p) {
	p.y = p.y * blackSquare.h + topOffset;
	p.x = p.x * blackSquare.w + leftOffset;
}

void pixelsToCell(SDL_Point& p) {
	p.x = (p.x - leftOffset) / blackSquare.w;
	p.y = (p.y - topOffset) / blackSquare.h;
}

void renderValidMoveSquare(SDL_Point p) {
	SDL_Rect fillSquare = blackSquare;

	cellToPixels(p);
	fillSquare.y = p.y;
	fillSquare.x = p.x;

	SDL_SetRenderDrawColor(getRenderer(), 0xC1, 0x49, 0x33, 0x88);
	SDL_RenderFillRect(getRenderer(), &fillSquare);

	fillSquare.y += 10;
	fillSquare.x += 10;
	fillSquare.h -= 20;
	fillSquare.w -= 20;

	SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0xFF, 0x88);

	for (int i = 0; i < 4; ++i) {
		fillSquare.y += 1;
		fillSquare.x += 1;
		fillSquare.h -= 2;
		fillSquare.w -= 2;

		SDL_RenderDrawRect(getRenderer(), &fillSquare);
	}
}

void renderBoard() {
	SDL_SetRenderDrawColor(getRenderer(), 0x77, 0x77, 0x77, SDL_ALPHA_OPAQUE);

	// render border
	SDL_RenderFillRect(getRenderer(), &borderOutline);

	// render board
	bool white = true;

	for (int row = 0; row < 8; row += 1) {
		for (int col = 0; col < 8; col += 1) {
			if (white)
				SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
			else
				SDL_SetRenderDrawColor(getRenderer(), 0x55, 0x55, 0x55, SDL_ALPHA_OPAQUE);
			if (col < 7)
				white = !white;

			blackSquare.y = row * blackSquare.h + topOffset;
			blackSquare.x = col * blackSquare.w + leftOffset;

			SDL_RenderFillRect(getRenderer(), &blackSquare);
		}
	}
}

void renderPieces() {
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			Piece* piece = board[col][row];

			if (piece != nullptr) {

				SDL_Rect renderDest;
				renderDest.w = blackSquare.w - 4;
				renderDest.h = blackSquare.h - 4;
				renderDest.x = col * blackSquare.w + leftOffset + 2;
				renderDest.y = row * blackSquare.h + topOffset + 2;

				piece->render(renderDest);
			}
		}
	}
}

bool mouseInCell(SDL_Point cell) {
	SDL_Point pos;
	mousePosition(&pos);

	// if mouse outside board
	if (pos.x < borderOutline.x + 4 ||
		pos.y < borderOutline.y + 4 ||
		pos.x > borderOutline.x + borderOutline.w - 4 ||
		pos.y > borderOutline.y + borderOutline.h - 4) {
		return false;
	}
	else {
		pixelsToCell(pos);

		if (cell.x == pos.x && cell.y == pos.y)
			return true;
		else
			return false;
	}
}

Piece* checkIfMouseClickedOnCell() {
	SDL_Point pos;
	mousePosition(&pos);

	// if mouse outside board
	if (pos.x < borderOutline.x + 4 ||
		pos.y < borderOutline.y + 4 ||
		pos.x > borderOutline.x + borderOutline.w - 4 ||
		pos.y > borderOutline.y + borderOutline.h - 4) {
		return nullptr;
	}
	else {
		pixelsToCell(pos);

		return board[pos.x][pos.y];
	}
}

Piece* checkCell(SDL_Point point) {
	return board[point.x][point.y];
}

void getCellSize(SDL_Rect* r) {
	r->w = blackSquare.w - 4;
	r->h = blackSquare.h - 4;
}

void Piece::die() {
	if (team == Team::White)
		whiteGraveyard.push_back(this);
	else
		blackGraveyard.push_back(this);
}

void Piece::move(SDL_Point dest) {
	if (board[dest.x][dest.y] != nullptr)
		board[dest.x][dest.y]->die();

	board[position.x][position.y] = nullptr;

	position = dest;
	board[dest.x][dest.y] = this;
}