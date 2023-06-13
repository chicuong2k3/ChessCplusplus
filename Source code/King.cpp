#include "King.h"
#include "Rook.h"

King::King(Vec2<int> position, bool isWhite, int owner, bool isAlive) : Piece(position, isWhite, owner, isAlive)
{
}

std::vector<Move*> King::generatePossibleMoves(Board* board)
{
    std::vector<Move*> possibleMoves;
    Square* beginSquare = board->getSquare(this->position);
    for (int y = position.getY() - 1; y <= position.getY() + 1; y++)
    {
        for (int x = position.getX() - 1; x <= position.getX() + 1; x++)
        {
            if ((x != position.getX() || y != position.getY()) && Utility::isOnBoard({x, y})) {
                Square* destSquare = board->getSquare(x, y);
                if (destSquare->isOccupied())
                {
                    if (destSquare->getPiece()->IsWhite() != beginSquare->getPiece()->IsWhite()) {
                        possibleMoves.push_back(new Move(beginSquare, destSquare, isWhite));
                    }
                }
                else possibleMoves.push_back(new Move(beginSquare, destSquare, isWhite));
            }
        }
    }

    // Castling check
    if (!HasMoved()) {
        // check for short castle
        Square* rookSquare1 = board->getSquare(position + Vec2<int>{3, 0}); // get the square contains the Rook
        Piece* rook1 = rookSquare1->getPiece();
        if (!board->getSquare(position + Vec2<int>{1, 0})->isOccupied()
            && !board->getSquare(position + Vec2<int>{2, 0})->isOccupied()
            && rookSquare1->isOccupied() 
            && dynamic_cast<Rook*>(rook1) 
            && !rook1->HasMoved()) {
            Square* destinationSquare1 = board->getSquare(beginSquare->getPosition() + Vec2<int>{2, 0});
            Move* shortCastleMove = new Move(beginSquare, destinationSquare1, isWhite);
            shortCastleMove->setType(Move::MoveType::SHORT_CASTLING);
            possibleMoves.push_back(shortCastleMove);
        }

        // check for long castle
        Square* rookSquare2 = board->getSquare(position + Vec2<int>{-4, 0}); // get the square contains the Rook
        Piece* rook2 = rookSquare2->getPiece();
        if (!board->getSquare(position + Vec2<int>{-1, 0})->isOccupied()
            && !board->getSquare(position + Vec2<int>{-2, 0})->isOccupied()
            && !board->getSquare(position + Vec2<int>{-3, 0})->isOccupied()
            && rookSquare2->isOccupied()
            && dynamic_cast<Rook*>(rook2)
            && !rook2->HasMoved()) {
            Square* destinationSquare2 = board->getSquare(beginSquare->getPosition() + Vec2<int>{-2, 0});
            Move* longCastleMove = new Move(beginSquare, destinationSquare2, isWhite);
            longCastleMove->setType(Move::MoveType::LONG_CASTLING);
            possibleMoves.push_back(longCastleMove);
        }
    }

    return possibleMoves;
}
