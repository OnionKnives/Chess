#include <vector>

#include "game.h"
#include "board.h"
#include "input.h"
#include "piece.h"

using std::vector;

struct GameData {
	Team activePlayer = Team::White;
	Piece* activePiece = nullptr;
	vector<SDL_Point> validMoves;
} data;

void switchTurn() {
	if (data.activePlayer == Team::White)
		data.activePlayer = Team::Black;
	else {
		data.activePlayer = Team::White;
	}

	// Check if current king is in check or checkmate
}

void addValidMove(SDL_Point p) {
	data.validMoves.push_back(p);
}

bool isEnemyPiece(Piece* p) {
	return checkPieceTeam(p) != data.activePlayer;
}

bool cellInBounds(SDL_Point p) {
	if (p.x < 0 || p.x > 7 ||
		p.y < 0 || p.y > 7)
		return false;
	return true;
}

bool validateMove(SDL_Point p) {
	// Validate point in bounds
	if (!cellInBounds(p))
		return false;

	// Validate cell is valid to move too
	if (checkCell(p) == nullptr) {
		// Check for all possible enemy move squares. King cannot move there. Other pieces cannot move if it would place the king in check.
		addValidMove(p);
		return true;
	}
	else if (checkPieceTeam(checkCell(p)) != data.activePlayer &&
		checkPieceType(checkCell(p)) != Type::King) {
		addValidMove(p);
		return false; // Move is valid, but don't check beyond
	}
	else
		return false;
}

bool validateMovePawn(SDL_Point p) {
	// Validate point in bounds
	if (cellInBounds(p)) {

		// Validate cell is valid to move too
		if (checkCell(p) == nullptr)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool validatePawnAttack(SDL_Point p) {
	if (checkCell(p) != nullptr &&
		checkPieceTeam(checkCell(p)) != data.activePlayer &&
		checkPieceType(checkCell(p)) != Type::King)
		return true;
	return false;
}

void pawnMoves() {
	int direction;
	SDL_Point point = checkPosition(data.activePiece);

	// Determine Move Direction
	if (data.activePlayer == Team::White) direction = -1;
	else direction = 1;

	// Check Move
	SDL_Point checkPoint = { point.x, point.y + direction };

	if (validateMovePawn(checkPoint)) {
		addValidMove(checkPoint);

		checkPoint = { point.x, point.y + direction * 2 };
		if (hasMoved(data.activePiece) == false &&
			validateMovePawn(checkPoint))
			addValidMove(checkPoint);
	}

	// Check Attack
	checkPoint = { point.x + 1, point.y + direction };
	if (validatePawnAttack(checkPoint))
		addValidMove(checkPoint);

	checkPoint = { point.x - 1, point.y + direction };
	if (validatePawnAttack(checkPoint))
		addValidMove(checkPoint);
}

void checkStraightLines(SDL_Point origin) {
	//check left
	for (int i = origin.x - 1; i >= 0; --i) {
		if (!validateMove({ i, origin.y }))
			break;
	}

	//check right
	for (int i = origin.x + 1; i <= 7; ++i) {
		if (!validateMove({ i, origin.y }))
			break;
	}

	//check up
	for (int i = origin.y - 1; i >= 0; --i) {
		if (!validateMove({ origin.x, i }))
			break;
	}

	//check down
	for (int i = origin.y + 1; i <= 7; ++i) {
		if (!validateMove({ origin.x, i }))
			break;
	}
}

void rookMoves() {
	checkStraightLines(checkPosition(data.activePiece));
}

void knightMoves() {
	SDL_Point origin = checkPosition(data.activePiece);

	validateMove({ origin.x + 2, origin.y + 1 });
	validateMove({ origin.x + 2, origin.y - 1 });
	validateMove({ origin.x - 2, origin.y + 1 });
	validateMove({ origin.x - 2, origin.y - 1 });

	validateMove({ origin.x + 1, origin.y - 2 });
	validateMove({ origin.x - 1, origin.y - 2 });
	validateMove({ origin.x + 1, origin.y + 2 });
	validateMove({ origin.x - 1, origin.y + 2 });
}

void checkDiagonalLines(SDL_Point origin) {
	int i, j;
	//check up left

	i = origin.x - 1;
	j = origin.y - 1;
	for (; i >= 0 && j >= 0;
		--i, --j) {
		if (!validateMove({ i, j }))
			break;
	}

	//check up right
	i = origin.x + 1;
	j = origin.y - 1;
	for (; i <= 7 && j >= 0;
		++i, --j) {
		if (!validateMove({ i, j }))
			break;
	}

	//check down left
	i = origin.x - 1;
	j = origin.y + 1;
	for (; i >= 0 && j <= 7;
		--i, ++j) {
		if (!validateMove({ i, j }))
			break;
	}

	//check down right
	i = origin.x + 1;
	j = origin.y + 1;
	for (; i <= 7 && j <= 7;
		++i, ++j) {
		if (!validateMove({ i, j }))
			break;
	}
}

void bishopMoves() {
	checkDiagonalLines(checkPosition(data.activePiece));
}

void queenMoves() {
	checkStraightLines(checkPosition(data.activePiece));
	checkDiagonalLines(checkPosition(data.activePiece));
}

void checkCastle() {

}

void kingMoves() {
	SDL_Point origin = checkPosition(data.activePiece);

	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			validateMove({ origin.x + i, origin.y + j });
		}
	}

	if (hasMoved(data.activePiece) == false) {
		checkCastle();
	}
}

void calculateValidMoves() {
	if (data.activePiece != nullptr) {
		Type pieceType = checkPieceType(data.activePiece);

		switch (pieceType) {
		case Type::Pawn:
			pawnMoves();
			break;
		case Type::Rook:
			rookMoves();
			break;
		case Type::Knight:
			knightMoves();
			break;
		case Type::Bishop:
			bishopMoves();
			break;
		case Type::Queen:
			queenMoves();
			break;
		case Type::King:
			kingMoves();
			break;
		}
	}
}

bool move(Piece* piece) {
	bool isValid = false;
	SDL_Point dest = { 0, 0 };

	// check if move is valid
	for (auto p : data.validMoves) {
		if (mouseInCell(p)) {
			isValid = true;
			dest = p;
			break;
		}
	}

	if (isValid == false)
		return false;

	// check if a piece is taken
	// if pawn, check for promotion
	// move piece
	movePiece(piece, dest);
	setHasMoved(piece);

	// add move to move stack, to be saved for replay

	return true;
}

void update() {
	if (data.activePiece == nullptr) {
		if (mouseClick(SDL_BUTTON_LEFT) == MouseState::Down &&
			checkIfMouseClickedOnCell() != nullptr) {
			if (checkPieceTeam(checkIfMouseClickedOnCell()) == data.activePlayer) {
				data.activePiece = checkIfMouseClickedOnCell();
				calculateValidMoves();
			}
		}
	}

	else if (data.activePiece != nullptr && mouseClick(SDL_BUTTON_LEFT) == MouseState::Up) {
		if (move(data.activePiece)) {
			switchTurn();
		}
		data.activePiece = nullptr;
		data.validMoves.clear();
	}
}

Team activePlayer() {
	return data.activePlayer;
}

Piece* activePiece() {
	return data.activePiece;
}

void renderValidMoves() {
	for (auto p : data.validMoves)
		renderValidMoveSquare(p);
}