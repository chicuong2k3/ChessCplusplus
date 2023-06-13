#include "Player.h"
#include "King.h"
#include "Bishop.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Pawn.h"


Player::Player(bool isWhite) : isWhite(isWhite)
{
}

bool Player::isWhiteSide() const
{
	return isWhite;
}

void Player::setWhiteSide(bool isWhite)
{
	this->isWhite = isWhite;
}

void Player::addPiece(Piece* piece)
{
	pieces.push_back(piece);
}


bool Player::hasPossibleMoves(Board* board)
{
	for (Piece* piece : pieces)
	{
		if (piece->IsAlive()) {
			std::vector<Move*> legalMoves = board->generateAllLegalMoves(piece);
			if (legalMoves.size() > 0) return true;
		}	
	}

	return false;
}

std::vector<Piece*> Player::getPieces() const
{
	return pieces;
}
