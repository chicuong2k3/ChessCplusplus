#ifndef HEADER_PLAYER_H
#define HEADER_PLAYER_H

#include <vector>
#include "Piece.h"
#include "Board.h"
#include "Move.h"
#include "Vec2.h"
#include "Game.h"
#include "SFML/Graphics.hpp"

class Piece;
class Board;
class Move;
class Game;

class Player
{
public:
	Player();
	Player(bool isWhite);
	bool isWhiteSide() const;
	void setWhiteSide(bool isWhite);
	void addPiece(Piece* piece);
	bool hasPossibleMoves(Board* board);
	std::vector<Piece*> getPieces() const;
	virtual bool movePiece(Game* game, int& sx, int& sy, int& ex, int& ey, Piece*& beginPiece) = 0;
protected:
	bool isWhite;
	std::vector<Piece*> pieces;
};

#endif