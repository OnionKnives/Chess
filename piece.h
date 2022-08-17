#pragma once

#include <SDL.h>
#include <vector>

enum class Team {
	Black, White
};

enum class Type {
	Pawn, Rook, Knight,
	Bishop, Queen, King
} type;

struct Piece_Initializer {
	Team team;
	Type type;
	SDL_Point position;
};

class Piece {
public:
	Piece(Piece_Initializer);
	~Piece();

	void die();
	
	Team getTeam();
	SDL_Point getPosition();

	bool operator==(const Piece& p);
	void move(SDL_Point);
	void render(SDL_Rect);
	void calculateValidMoves();

private:
	void setSprite();

	void renderValidMoves();
	void renderGhost();

	void validateMove();

	bool hasMoved;
	Team team;
	Type type;
	SDL_Point position;
	SDL_Texture* sprite;
	vector<SDL_Point> validMoves;
};