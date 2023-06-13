#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(bool isWhite) : Player(isWhite)
{

}

bool HumanPlayer::movePiece(Game* game, int& sx, int& sy, int& ex, int& ey, Piece*& beginPiece)
{
	sf::RenderWindow* window = game->gameWindow;
	Board* board = game->getBoard();
	Player* currentPlayer = game->getCurrentPlayer();

	sf::Event event;


	if (sx >= 0 && sx < 8 && sy >= 0 && sy < 8)
	{
		while (window->pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				switch (event.key.code)
				{
				case sf::Mouse::Left:
					if (sx != -1 && sy != -1)
					{
						ex = (sf::Mouse::getPosition(*window).x - Settings::startX) / Settings::squareSize;
						ey = (sf::Mouse::getPosition(*window).y - Settings::startY) / Settings::squareSize;
						if (ex < 0 || ex >= 8 || ey < 0 || ey >= 8) {
							return false;
						}
						if (ex == sx && ey == sy) {
							sx = -1;
							sy = -1;
							return true;
						}
						std::vector<Move*> legalMoves = board->generateAllLegalMoves(beginPiece);
						return board->movePiece(beginPiece, board->getSquare(ex, ey), legalMoves, currentPlayer, true);

					}

					break;
				default:
					break;
				}
				break;
			default:
				break;
			}

		}
	}
	return false;
}



