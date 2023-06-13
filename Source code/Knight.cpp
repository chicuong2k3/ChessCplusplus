#include "Knight.h"



Knight::Knight(Vec2<int> position, bool isWhite, int owner, bool isAlive) : Piece(position, isWhite, owner, isAlive)
{
}

std::vector<Move*> Knight::generatePossibleMoves(Board* board)
{
    std::vector<Move*> possibleMoves;
    std::vector<Vec2<int>> offsets = {
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1},
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1}
    };
    Square* beginSquare = board->getSquare(this->position);
    for (Vec2<int> offset: offsets)
    {
        Vec2<int> dest = beginSquare->getPosition() + offset;
        if (Utility::isOnBoard(dest)) {
            Square* destSquare = board->getSquare(dest);
            if (destSquare->isOccupied())
            {
                if (destSquare->getPiece()->IsWhite() != beginSquare->getPiece()->IsWhite()) {
                    possibleMoves.push_back(new Move(beginSquare, destSquare, isWhite));
                }
            } else possibleMoves.push_back(new Move(beginSquare, destSquare, isWhite));
        }
    }
    return possibleMoves;
}

