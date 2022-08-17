#include <string>

#include "board.h"
#include "piece.h"
#include "graphics.h"

using namespace std;

extern SDL_Texture* getSprite(Type, Team);

Piece::Piece(Piece_Initializer i) {
	alive = true;
	hasMoved = false;
	team = i.team;
	type = i.type;
	position = i.position;
	sprite = getSprite(type, team);
}

Piece::~Piece() {
	sprite = nullptr;
}

Team Piece::getTeam() {
	return team;
}

Type Piece::getType() {
	return type;
}

SDL_Point Piece::getPosition() {
	return position;
}

bool Piece::checkIfMoved() {
	return hasMoved;
}

bool Piece::operator==(const Piece& p) {
	return this->team == p.team;
}

void Piece::render(SDL_Rect dest) {
	renderValidMoves();
	SDL_RenderCopy(getRenderer(), sprite, nullptr, &dest);
	renderGhost();
}

void Piece::renderValidMoves() {

}

void Piece::renderGhost() {
	/*
	if (activePiece() != nullptr) {
		SDL_Point pos;
		SDL_Rect dest;

		mousePosition(&pos);
		getCellSize(&dest);

		dest.x = pos.x - (dest.w / 2);
		dest.y = pos.y - (dest.h / 2);

		SDL_RenderCopy(
			getRenderer(),
			getTexture(activePiece()),
			nullptr,
			&dest);
	}
	*/
}