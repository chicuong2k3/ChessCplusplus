#ifndef HEADER_SQUARE_H
#define HEADER_SQUARE_H

#include "Piece.h"
#include "Vec2.h"

class Piece;

class Square
{
public:
	
	Square(int x = 0, int y = 0);
	Square(Piece* piece, int x = 0, int y = 0);
	~Square();
	Piece* getPiece() const;
	void setPiece(Piece* piece);
	Vec2<int> getPosition() const;
	void setPosition(Vec2<int> position);
	bool isOccupied() const;

	
private:
	Vec2<int> position;
	Piece* piece;

};

#endif