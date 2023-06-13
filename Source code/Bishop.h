#ifndef HEADER_BISHOP_H
#define HEADER_BISHOP_H

#include <vector>
#include <math.h>
#include "Piece.h"
#include "Board.h"
#include "Square.h"
#include "Move.h"
#include "Utility.h"

class Piece;
class Square;
class Board;
class Move;

class Bishop :
    public Piece
{
public:
    Bishop(Vec2<int> position, bool isWhite, int owner, bool isAlive = true);
    std::vector<Move*> generatePossibleMoves(Board* board);
};

#endif