#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(bool isWhite)
	: Player(isWhite)
{
}

bool ComputerPlayer::movePiece(Game* game, int& sx, int& sy, int& ex, int& ey, Piece*& beginPiece)
{

	Board* board = game->getBoard();
	Player* currentPlayer = game->getCurrentPlayer();
	srand(time(0));
	if (sx == -1 && sy == -1) {
		do
		{
			do
			{
				beginPiece = pieces[rand() % (pieces.size())];
			} while (!beginPiece->IsAlive());

		} while (board->generateAllLegalMoves(beginPiece).size() == 0);
		sx = beginPiece->getPosition().getX();
		sy = beginPiece->getPosition().getY();
	}
	if (sx >= 0 && sx < 8 && sy >= 0 && sy < 8) {
		std::vector<Move*> legalMoves = board->generateAllLegalMoves(beginPiece);
		Move* randomMove = legalMoves[rand() % legalMoves.size()];
		ex = randomMove->getEndSquare()->getPosition().getX();
		ey = randomMove->getEndSquare()->getPosition().getY();
		return board->movePiece(beginPiece, randomMove->getEndSquare(), legalMoves, currentPlayer, true);
	}
	return false;
}

