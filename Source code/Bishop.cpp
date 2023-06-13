#include "Bishop.h"

Bishop::Bishop(Vec2<int> position, bool isWhite, int owner, bool isAlive) : Piece(position, isWhite, owner, isAlive)
{
}

std::vector<Move*> Bishop::generatePossibleMoves(Board* board)
{
	std::vector<Move*> possibleMoves;
	std::vector<Vec2<int>> offsets = {
		{1, 1}, {-1, 1}, {1, -1}, {-1, -1}
	};
	

    for (Vec2<int> offset : offsets)
    {
        Square* beginSquare = board->getSquare(this->position);
        while (true)
        {
            Vec2<int> dest = beginSquare->getPosition() + offset;
            if (!Utility::isOnBoard(dest)) break;
            Square* destSquare = board->getSquare(dest);
            if (destSquare->isOccupied())
            {
                if (destSquare->getPiece()->IsWhite() != board->getSquare(this->position)->getPiece()->IsWhite()) {
                    possibleMoves.push_back(new Move(board->getSquare(this->position), destSquare, isWhite));
                }
                break;
            }
            else {
                possibleMoves.push_back(new Move(board->getSquare(this->position), destSquare, isWhite));
                beginSquare = destSquare;
            }
        }
    }
	return possibleMoves;
}