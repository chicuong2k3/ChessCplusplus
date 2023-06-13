#ifndef HEADER_KNIGHT_H
#define HEADER_KNIGHT_H

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

class Knight :
    public Piece
{
public:
    Knight(Vec2<int> position, bool isWhite, int owner, bool isAlive = true);
    std::vector<Move*> generatePossibleMoves(Board* board);
private:
    
};

#endif