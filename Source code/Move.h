#ifndef HEADER_MOVE_H
#define HEADER_MOVE_H

#include "Piece.h"
#include "Square.h"
#include "Player.h"

class Piece;
class Square;
class Player;


class Move
{
public:
	Move(Square* begin, Square* end, bool isWhite);
	~Move();
	Square* getBeginSquare();
	Square* getEndSquare();
	Piece* getKilledPiece();
	void setKilledPiece(Piece* killedPiece);
	Piece* getMovedPiece();
	enum class MoveType {
		NORMAL,
		PROMOTION,
		SHORT_CASTLING,
		LONG_CASTLING,
		ENPASSANT
	};
	void setType(MoveType moveType);
	MoveType getType() const;
	bool isWhite;
private:
	
	Square* begin;
	Square* end;
	Piece* movedPiece;
	Piece* killedPiece;
	MoveType type;
};

#endif