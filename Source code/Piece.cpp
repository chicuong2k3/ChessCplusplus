#include "Piece.h"

Piece::Piece(Vec2<int> position, bool isWhite, int owner, bool isAlive) :
	position(position), isWhite(isWhite), owner(owner), isAlive(isAlive)
{
	numOfMoves = 0;
}

Piece::~Piece()
{
	
}

void Piece::setPosition(Vec2<int> position)
{
	this->position = position;
}

Vec2<int> Piece::getPosition() const
{
	return position;
}

bool Piece::IsWhite() const
{
	return isWhite;
}

bool Piece::IsAlive() const
{
	return isAlive;
}

void Piece::setAlive(bool isAlive)
{
	this->isAlive = isAlive;
}

void Piece::increaseNumberOfMoves()
{
	numOfMoves++;
}

void Piece::decreaseNumberOfMoves()
{
	numOfMoves--;
}

int Piece::getNumOfMoves() const
{
	return numOfMoves;
}

bool Piece::HasMoved() const
{
	return numOfMoves != 0;
}

void Piece::setOwner(int ownerNumber)
{
	owner = ownerNumber;
}

int Piece::getOwner() const
{
	return owner;
}
