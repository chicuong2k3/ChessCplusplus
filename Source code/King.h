#ifndef HEADER_KING_H
#define HEADER_KING_H

#include <vector>
#include "Piece.h"
#include "Board.h"
#include "Square.h"
#include "Move.h"
#include "Vec2.h"
#include "Utility.h"

class Piece;
class Board;
class Move;

class King :
    public Piece
{
public:
    King(Vec2<int> position, bool isWhite, int owner, bool isAlive = true);
    std::vector<Move*> generatePossibleMoves(Board* board);
};

#endif
