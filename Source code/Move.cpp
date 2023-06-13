#include "Move.h"

Move::Move(Square* begin, Square* end, bool isWhite)
	: begin(begin), end(end), isWhite(isWhite)
{
	movedPiece = begin->getPiece();
	killedPiece = nullptr;
	type = MoveType::NORMAL;
}

Move::~Move()
{
	delete begin;
	delete end;
	delete movedPiece;
	delete killedPiece;
}

Square* Move::getBeginSquare()
{
	return begin;
}

Square* Move::getEndSquare()
{
	return end;
}

Piece* Move::getKilledPiece()
{
	return killedPiece;
}

void Move::setKilledPiece(Piece* killedPiece)
{
	this->killedPiece = killedPiece;
}

Piece* Move::getMovedPiece()
{
	return movedPiece;
}

void Move::setType(MoveType moveType)
{
	this->type = moveType;
}

Move::MoveType Move::getType() const
{
	return type;
}
