#pragma once

#include <SDL.h>
#include <vector>

enum class Team {
	Black, White
};

enum class Type {
	Pawn, Rook, Knight,
	Bishop, Queen, King
};

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
	Type getType();
	SDL_Point getPosition();
	SDL_Texture* getSprite();
	bool checkIfMoved();

	bool operator==(const Piece& p);
	void move(SDL_Point);
	void render(SDL_Rect);
	void calculateValidMoves();

private:
	void renderValidMoves();
	void renderGhost();

	void validateMove();

	bool alive;
	bool hasMoved;
	bool isActive;
	Team team;
	Type type;
	SDL_Point position;
	SDL_Texture* sprite;
	std::vector<SDL_Point> validMoves;
};