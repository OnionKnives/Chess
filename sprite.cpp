#include <SDL.h>
#include <string>
#include <SDL_image.h>

#include "graphics.h"
#include "piece.h"

struct SpriteLibrary {
	SDL_Texture* whitePawn = nullptr;
	SDL_Texture* whiteRook = nullptr;
	SDL_Texture* whiteKnight = nullptr;
	SDL_Texture* whiteBishop = nullptr;
	SDL_Texture* whiteQueen = nullptr;
	SDL_Texture* whiteKing = nullptr;

	SDL_Texture* blackPawn = nullptr;
	SDL_Texture* blackRook = nullptr;
	SDL_Texture* blackKnight = nullptr;
	SDL_Texture* blackBishop = nullptr;
	SDL_Texture* blackQueen = nullptr;
	SDL_Texture* blackKing = nullptr;
} spriteLibrary;

SDL_Texture* loadTextureFromFile(const char* filepath) {
	SDL_Surface* surface = IMG_Load(filepath);
	SDL_Texture* finalTexture = nullptr;

	try {
		if (surface == nullptr)
			throw IMG_GetError();

		finalTexture = SDL_CreateTextureFromSurface(getRenderer(), surface);
		if (finalTexture == nullptr)
			throw IMG_GetError();

		SDL_FreeSurface(surface);
	}
	catch (const char* error) {
		SDL_Log("%s, %s", error, SDL_GetError());
	}

	return finalTexture;
}

void initializeSprites() {
	std::string FilePath = "assets\\art\\";

	spriteLibrary.whitePawn = loadTextureFromFile((FilePath + "pawn.png").c_str());
	spriteLibrary.whiteRook = loadTextureFromFile((FilePath + "rook.png").c_str());
	spriteLibrary.whiteKnight = loadTextureFromFile((FilePath + "knight.png").c_str());
	spriteLibrary.whiteBishop = loadTextureFromFile((FilePath + "bishop.png").c_str());
	spriteLibrary.whiteQueen = loadTextureFromFile((FilePath + "queen.png").c_str());
	spriteLibrary.whiteKing = loadTextureFromFile((FilePath + "king.png").c_str());

	spriteLibrary.blackPawn = loadTextureFromFile((FilePath + "pawn1.png").c_str());
	spriteLibrary.blackRook = loadTextureFromFile((FilePath + "rook1.png").c_str());
	spriteLibrary.blackKnight = loadTextureFromFile((FilePath + "knight1.png").c_str());
	spriteLibrary.blackBishop = loadTextureFromFile((FilePath + "bishop1.png").c_str());
	spriteLibrary.blackQueen = loadTextureFromFile((FilePath + "queen1.png").c_str());
	spriteLibrary.blackKing = loadTextureFromFile((FilePath + "king1.png").c_str());
}

void Piece::setSprite() {
	switch (type) {
	case Type::Pawn:
		team == Team::White ? spriteLibrary.whitePawn : spriteLibrary.blackPawn;
		break;
	case Type::Rook:
		team == Team::White ? spriteLibrary.whiteRook : spriteLibrary.blackRook;
		break;
	case Type::Knight:
		team == Team::White ? spriteLibrary.whiteKnight : spriteLibrary.blackKnight;
		break;
	case Type::Bishop:
		team == Team::White ? spriteLibrary.whiteBishop : spriteLibrary.blackBishop;
		break;
	case Type::Queen:
		team == Team::White ? spriteLibrary.whiteQueen : spriteLibrary.blackQueen;
		break;
	case Type::King:
		team == Team::White ? spriteLibrary.whiteKing : spriteLibrary.blackKing;
		break;
	default:
		break;
	}
}
