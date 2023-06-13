#include "Pawn.h"


Pawn::Pawn(Vec2<int> position, bool isWhite, int owner, bool isAlive) : Piece(position, isWhite, owner, isAlive)
{
	isValidForEnpassent = true;
}

std::vector<Move*> Pawn::generatePossibleMoves(Board* board)
{
	std::vector<Move*> possibleMoves;
	Square* beginSquare = board->getSquare(this->position);

	Vec2<int> direction;
	if (owner == 0) {
		direction = {0, -1};
	}
	else direction = {0, 1};

	const Vec2<int> newPosition = this->position + direction;
	if (!Utility::isOnBoard(newPosition)) return possibleMoves;

	int doubleStepY;
	if (owner == 0) doubleStepY = 6;
	else doubleStepY = 1;

	
	// check for Pawn promotion
	Move::MoveType moveType = Move::MoveType::NORMAL;
	if (owner == 0 && newPosition.getY() == 0 || owner == 1 && newPosition.getY() == 7) {
		moveType = Move::MoveType::PROMOTION;
	}


	std::vector<Vec2<int>> offsets = {
		{1, 0}, {-1, 0}
	};

	for (Vec2<int> offset : offsets)
	{
		Vec2<int> dest = newPosition + offset;
		if (Utility::isOnBoard(dest)) {
			Square* destSquare = board->getSquare(dest);
			if (destSquare->isOccupied())
			{
				if (destSquare->getPiece()->IsWhite() != beginSquare->getPiece()->IsWhite()) {
					Move* move = new Move(beginSquare, destSquare, isWhite);
					move->setType(moveType);
					possibleMoves.push_back(move);
				}
			}
		}
	}

	// check for Pawn Enpassant
	/*if (isValidForEnpassent) {
		
		if ((owner == 0 && newPosition.getY() == 2) || (owner == 1 && newPosition.getY() == 5)) {
			
			
			if (Utility::isOnBoard(this->position + Vec2<int>{-1, 0})) {
				Square* leftSquare = board->getSquare(this->position + Vec2<int>{-1, 0});
				Piece* leftPiece = leftSquare->getPiece();
				bool leftHasPawn = leftSquare->isOccupied() && dynamic_cast<Pawn*>(leftPiece);
				if (leftHasPawn && leftPiece->IsWhite() != this->IsWhite() && leftPiece->getNumOfMoves() == 1 && ((Pawn*)leftPiece)->isValidForEnpassent) {
					Square* destSquare = board->getSquare(newPosition + Vec2<int>{-1, 0});
					if (!destSquare->isOccupied()) {
						Move* move = new Move(beginSquare, destSquare, isWhite);
						move->setType(Move::MoveType::ENPASSANT);
						possibleMoves.push_back(move);
					}
				}
			}
			
			if (Utility::isOnBoard(this->position + Vec2<int>{1, 0})) {
				Square* rightSquare = board->getSquare(this->position + Vec2<int>{1, 0});
				Piece* rightPiece = rightSquare->getPiece();
				bool rightHasPawn = rightSquare->isOccupied() && dynamic_cast<Pawn*>(rightPiece);
				if (rightHasPawn && rightPiece->IsWhite() != this->IsWhite() && rightPiece->getNumOfMoves() == 1 && ((Pawn*)rightPiece)->isValidForEnpassent) {
					Square* destSquare = board->getSquare(newPosition + Vec2<int>{1, 0});
					if (!destSquare->isOccupied()) {
						Move* move = new Move(beginSquare, destSquare, isWhite);
						move->setType(Move::MoveType::ENPASSANT);
						possibleMoves.push_back(move);
					}
				}
			}
			
		}
	}*/


	if (!board->getSquare(newPosition)->isOccupied()) {
		Move* move = new Move(beginSquare, board->getSquare(newPosition), isWhite);
		move->setType(moveType);
		possibleMoves.push_back(move);
	}
	else return possibleMoves;

	if (this->position.getY() != doubleStepY 
		|| board->getSquare(newPosition + direction)->isOccupied()) return possibleMoves;

	possibleMoves.push_back(new Move(beginSquare, board->getSquare(newPosition + direction), isWhite));

	return possibleMoves;
}
