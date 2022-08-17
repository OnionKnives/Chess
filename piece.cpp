#include <string>

#include "board.h"
#include "piece.h"
#include "graphics.h"

using namespace std;

extern SDL_Texture* setSprite(Type, Team);

Piece::Piece(Piece_Initializer i) {
	alive = true;
	hasMoved = false;
	team = i.team;
	type = i.type;
	position = i.position;
	sprite = setSprite(type, team);
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

SDL_Texture* Piece::getSprite() {
	return sprite;
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
}

void Piece::renderValidMoves() {

}