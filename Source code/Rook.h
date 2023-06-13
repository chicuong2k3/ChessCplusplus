#ifndef HEADER_ROOK_H
#define HEADER_ROOK_H

#include <vector>
#include "Piece.h"
#include "Board.h"
#include "Square.h"
#include "Move.h"
#include "Utility.h"

class Piece;
class Square;
class Board;
class Move;

class Rook :
    public Piece
{
public:
    Rook(Vec2<int> position, bool isWhite, int owner, bool isAlive = true);
    std::vector<Move*> generatePossibleMoves(Board* board);
};

#endif