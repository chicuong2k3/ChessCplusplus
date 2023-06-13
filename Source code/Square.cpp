#include "Square.h"

Square::Square(int x, int y)
{
	position.setX(x);
	position.setY(y);
	piece = nullptr;
}

Square::Square(Piece* piece, int x, int y)
{
	position.setX(x);
	position.setY(y);
	this->piece = piece;
}

Square::~Square()
{
	delete piece;
}

bool Square::isOccupied() const
{
	return piece != nullptr;
}

Piece* Square::getPiece() const
{
	return piece;
}

void Square::setPiece(Piece* piece)
{
	this->piece = piece;
}

Vec2<int> Square::getPosition() const
{
	return position;
}

void Square::setPosition(Vec2<int> position)
{
	this->position = position;
}

