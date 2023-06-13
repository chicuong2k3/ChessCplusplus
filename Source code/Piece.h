#ifndef HEADER_PIECE_H
#define HEADER_PIECE_H

#include "Board.h"
#include "Square.h"
#include "Move.h"

class Board;
class Square;

class Piece
{
public:
	Piece(Vec2<int> position, bool isWhite, int owner, bool isAlive = true);
	virtual ~Piece();
	void setPosition(Vec2<int> position);
	Vec2<int> getPosition() const;
	bool IsWhite() const;
	bool IsAlive() const;
	void setAlive(bool isAlive);
	void increaseNumberOfMoves();
	void decreaseNumberOfMoves();
	int getNumOfMoves() const;
	bool HasMoved() const;
	void setOwner(int ownerNumber);
	int getOwner() const;
	virtual std::vector<Move*> generatePossibleMoves(Board* board) = 0;
protected:
	bool isWhite;
	bool isAlive;
	Vec2<int> position;
	int numOfMoves;
	int owner;
};

#endif