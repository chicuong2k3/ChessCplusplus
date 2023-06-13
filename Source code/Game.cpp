#include "Game.h"
#include "Settings.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "Pawn.h"
#include "King.h"
#include <SFML/Audio.hpp>
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <iostream>


Game::Game(sf::RenderWindow* window, int choice)
{
	this->gameWindow = window;
	if (choice == 1) {
		playWithComputer = false;
	}
	else if (choice == 2) {
		playWithComputer = true;
	}
}

Game::~Game()
{
	delete player[0];
	delete player[1];
}

void Game::setStatus(GameStatus status)
{
	gameStatus = status;
}

Game::GameStatus Game::getStatus() const
{
	return gameStatus;
}

Board* Game::getBoard()
{
	return board;
}

Player* Game::getCurrentPlayer()
{
	return currentPlayer;
}

bool Game::play()
{

	int res = 1;
	while (res == 1)
	{
		
		res = 0;
		initGame();
		playerChoice = choosePlayer();
		

		if (playWithComputer) {
			if (playerChoice == 0) {
				player[0] = new HumanPlayer(true);
				player[1] = new ComputerPlayer(false);
				board = new Board(true);
			}
			else {
				player[0] = new HumanPlayer(false);
				player[1] = new ComputerPlayer(true);
				board = new Board(false);
			}
		}
		else {
			if (playerChoice == 0) {
				player[0] = new HumanPlayer(true);
				player[1] = new HumanPlayer(false);
				board = new Board(true);
			}
			else {
				player[0] = new HumanPlayer(false);
				player[1] = new HumanPlayer(true);
				board = new Board(false);
			}
		}


		currentPlayer = player[0]->isWhiteSide() ? player[0] : player[1];


		for (int y = 0; y < 8; y++)
		{
			if (y == 0 || y == 1 || y == 6 || y == 7) {
				for (int x = 0; x < 8; x++)
				{
					Piece* piece = board->getSquare(x, y)->getPiece();
					if (piece != nullptr && piece->IsWhite() == player[0]->isWhiteSide()) {
						player[0]->addPiece(piece);
					}
					else if (piece != nullptr && piece->IsWhite() == player[1]->isWhiteSide()) {
						player[1]->addPiece(piece);
					}
				}
			}
		}

		int sx = -1;
		int sy = -1;
		int ex = -1, ey = -1;
		int x, y;
		Piece* beginPiece = nullptr;
		sf::Event event;
	
		

		
		

		while (gameWindow->isOpen())
		{
			
			while (gameStatus == GameStatus::ACTIVE)
			{
				
				if (sx == -1 && sy == -1) {
					while (gameWindow->pollEvent(event))
					{
						if (event.type == sf::Event::Closed)
						{
							gameWindow->close();
						}

						if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
						{
							x = sf::Mouse::getPosition(*gameWindow).x;
							y = sf::Mouse::getPosition(*gameWindow).y;
							sx = (sf::Mouse::getPosition(*gameWindow).x - Settings::startX) / Settings::squareSize;
							sy = (sf::Mouse::getPosition(*gameWindow).y - Settings::startY) / Settings::squareSize;

							// Click on a piece 
							if (sx >= 0 && sx < 8 && sy >= 0 && sy < 8)
							{
								beginPiece = board->getSquare(sx, sy)->getPiece();
								if (beginPiece == nullptr || beginPiece->IsWhite() != currentPlayer->isWhiteSide() || board->generateAllLegalMoves(beginPiece).size() == 0)
								{
									sx = -1;
									sy = -1;
								}
							}

							// Click on the undo button
							sf::FloatRect undoButtonBounds = sf::FloatRect(Settings::undoButtonPosition.getX(), Settings::undoButtonPosition.getY(), Settings::buttonSize, Settings::buttonSize);
							if (undoButtonBounds.contains(static_cast<float>(x), static_cast<float>(y)))
							{
								if (dynamic_cast<ComputerPlayer*>(player[1]) && board->getMadeMoves().size() >= 2)
								{
									board->undoMove();
									board->undoMove();
								}
								else if (dynamic_cast<ComputerPlayer*>(player[1]) && board->getMadeMoves().size() == 1)
								{
									board->undoMove();
									currentPlayer = currentPlayer == player[0] ? player[1] : player[0];
								}
								else if (dynamic_cast<HumanPlayer*>(player[1]) && board->getMadeMoves().size() >= 1)
								{
									board->undoMove();
									currentPlayer = currentPlayer == player[0] ? player[1] : player[0];
								}
							}

						}
					}

				}
				bool moveResult = false;
				if (dynamic_cast<HumanPlayer*>(currentPlayer)) {
					moveResult = ((HumanPlayer*)currentPlayer)->movePiece(this, sx, sy, ex, ey, beginPiece);

				}
				else {
					moveResult = ((ComputerPlayer*)currentPlayer)->movePiece(this, sx, sy, ex, ey, beginPiece);

				}

				if (moveResult) {

					if (sx != -1 && sy != -1) currentPlayer = currentPlayer == player[0] ? player[1] : player[0];
					if (board->isChecked(currentPlayer->isWhiteSide())) {
						if (currentPlayer->hasPossibleMoves(board)) {
							Utility::playSound(Settings::checkSoundURL);
						}
					}
					if (!currentPlayer->hasPossibleMoves(board)) {
						Utility::playSound(Settings::checkmateSoundURL);
						gameStatus = currentPlayer->isWhiteSide() ? GameStatus::BLACK_WIN : GameStatus::WHITE_WIN;
					}
					sx = -1;
					sy = -1;

					break;
				}

				gameWindow->clear(sf::Color::White);

				displayBackground();
				drawButton(Settings::undoButtonURL, Settings::buttonSize, Settings::undoButtonPosition.getX(), Settings::undoButtonPosition.getY());
				if (!(sx >= 0 && sx < 8 && sy >= 0 && sy < 8)) {
					sx = -1;
					sy = -1;
				}
				drawBoard({ sx, sy }, { ex, ey });
				gameWindow->display();
				
			}
			
			if (gameStatus == GameStatus::WHITE_WIN || gameStatus == GameStatus::BLACK_WIN) {
				if (dynamic_cast<ComputerPlayer*>(player[1])) {
					if (gameStatus == GameStatus::WHITE_WIN) {
						{
							if (player[0]->isWhiteSide())
							{
								res = displayMessageBox("YOU WIN", 500, 340, 120, 150);
							}
							else {
								res = displayMessageBox("YOU LOSE", 500, 340, 120, 150);
							}
						}

					}
					else if (gameStatus == GameStatus::BLACK_WIN) {
						if (player[0]->isWhiteSide())
						{
							res = displayMessageBox("YOU LOSE", 500, 340, 120, 150);
						}
						else {
							res = displayMessageBox("YOU WIN", 500, 340, 120, 150);
						}
					}
				}
				else {
					if (gameStatus == GameStatus::WHITE_WIN) {
						res = displayMessageBox("WHITE WIN", 500, 340, 120, 150);
					}
					else if (gameStatus == GameStatus::BLACK_WIN) {
						res = displayMessageBox("BLACK WIN", 500, 340, 120, 150);
					}
				}

				if (res == 1 || res == 2) {
					if (res == 2) return true;
					break;
				}
			}
			
		}
		
	}
}

void Game::displayBackground() {
	sf::Texture background;
	background.loadFromFile(Settings::boardBackgroundURL);
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(background);
	backgroundSprite.setScale((float)gameWindow->getSize().x / background.getSize().x, (float)gameWindow->getSize().y / background.getSize().y);
	gameWindow->draw(backgroundSprite);
}

void Game::drawButton(const char* url, int size, int x, int y)
{
	sf::Texture undoBtn;
	undoBtn.loadFromFile(url);
	sf::Sprite undoBtnSprite;
	undoBtnSprite.setTexture(undoBtn);
	undoBtnSprite.setScale((float)size / undoBtn.getSize().x, (float)size / undoBtn.getSize().y);
	undoBtnSprite.setPosition(x, y);
	gameWindow->draw(undoBtnSprite);
}

void Game::loadResources()
{
	blackBishopLightTexture.loadFromFile(Settings::blackBishopLightURL);
	whiteBishopLightTexture.loadFromFile(Settings::whiteBishopLightURL);
	blackBishopDarkTexture.loadFromFile(Settings::blackBishopDarkURL);
	whiteBishopDarkTexture.loadFromFile(Settings::whiteBishopDarkURL);

	blackKnightLightTexture.loadFromFile(Settings::blackKnightLightURL);
	whiteKnightLightTexture.loadFromFile(Settings::whiteKnightLightURL);
	blackKnightDarkTexture.loadFromFile(Settings::blackKnightDarkURL);
	whiteKnightDarkTexture.loadFromFile(Settings::whiteKnightDarkURL);

	blackRookLightTexture.loadFromFile(Settings::blackRookLightURL);
	whiteRookLightTexture.loadFromFile(Settings::whiteRookLightURL);
	blackRookDarkTexture.loadFromFile(Settings::blackRookDarkURL);
	whiteRookDarkTexture.loadFromFile(Settings::whiteRookDarkURL);

	blackQueenLightTexture.loadFromFile(Settings::blackQueenLightURL);
	whiteQueenLightTexture.loadFromFile(Settings::whiteQueenLightURL);
	blackQueenDarkTexture.loadFromFile(Settings::blackQueenDarkURL);
	whiteQueenDarkTexture.loadFromFile(Settings::whiteQueenDarkURL);

	blackKingLightTexture.loadFromFile(Settings::blackKingLightURL);
	whiteKingLightTexture.loadFromFile(Settings::whiteKingLightURL);
	blackKingDarkTexture.loadFromFile(Settings::blackKingDarkURL);
	whiteKingDarkTexture.loadFromFile(Settings::whiteKingDarkURL);

	blackPawnLightTexture.loadFromFile(Settings::blackPawnLightURL);
	whitePawnLightTexture.loadFromFile(Settings::whitePawnLightURL);
	blackPawnDarkTexture.loadFromFile(Settings::blackPawnDarkURL);
	whitePawnDarkTexture.loadFromFile(Settings::whitePawnDarkURL);

	emptyLightTexture.loadFromFile(Settings::emptyLightURL);
	emptyDarkTexture.loadFromFile(Settings::emptyDarkURL);

}

sf::Texture Game::getTexture(Square* square) const
{
	if ((square->getPosition().getX() + square->getPosition().getY()) % 2 == 0) {
		if (square->isOccupied()) {
			Piece* piece = square->getPiece();
			if (dynamic_cast<Bishop*>(piece) && !piece->IsWhite()) {
				return blackBishopLightTexture;
			}
			else if (dynamic_cast<Bishop*>(piece) && piece->IsWhite()) {
				return whiteBishopLightTexture;
			}
			else if (dynamic_cast<Knight*>(piece) && !piece->IsWhite()) {
				return blackKnightLightTexture;
			}
			else if (dynamic_cast<Knight*>(piece) && piece->IsWhite()) {
				return whiteKnightLightTexture;
			}
			else if (dynamic_cast<Rook*>(piece) && !piece->IsWhite()) {
				return blackRookLightTexture;
			}
			else if (dynamic_cast<Rook*>(piece) && piece->IsWhite()) {
				return whiteRookLightTexture;
			}
			else if (dynamic_cast<Queen*>(piece) && !piece->IsWhite()) {
				return blackQueenLightTexture;
			}
			else if (dynamic_cast<Queen*>(piece) && piece->IsWhite()) {
				return whiteQueenLightTexture;
			}
			else if (dynamic_cast<King*>(piece) && !piece->IsWhite()) {
				return blackKingLightTexture;
			}
			else if (dynamic_cast<King*>(piece) && piece->IsWhite()) {
				return whiteKingLightTexture;
			}
			else if (dynamic_cast<Pawn*>(piece) && !piece->IsWhite()) {
				return blackPawnLightTexture;
			}
			else if (dynamic_cast<Pawn*>(piece) && piece->IsWhite()) {
				return whitePawnLightTexture;
			}
		}
		else {
			return emptyLightTexture;
		}
	}
	else {
		if (square->isOccupied()) {
			Piece* piece = square->getPiece();
			if (dynamic_cast<Bishop*>(piece) && !piece->IsWhite()) {
				return blackBishopDarkTexture;
			}
			else if (dynamic_cast<Bishop*>(piece) && piece->IsWhite()) {
				return whiteBishopDarkTexture;
			}
			else if (dynamic_cast<Knight*>(piece) && !piece->IsWhite()) {
				return blackKnightDarkTexture;
			}
			else if (dynamic_cast<Knight*>(piece) && piece->IsWhite()) {
				return whiteKnightDarkTexture;
			}
			else if (dynamic_cast<Rook*>(piece) && !piece->IsWhite()) {
				return blackRookDarkTexture;
			}
			else if (dynamic_cast<Rook*>(piece) && piece->IsWhite()) {
				return whiteRookDarkTexture;
			}
			else if (dynamic_cast<Queen*>(piece) && !piece->IsWhite()) {
				return blackQueenDarkTexture;
			}
			else if (dynamic_cast<Queen*>(piece) && piece->IsWhite()) {
				return whiteQueenDarkTexture;
			}
			else if (dynamic_cast<King*>(piece) && !piece->IsWhite()) {
				return blackKingDarkTexture;
			}
			else if (dynamic_cast<King*>(piece) && piece->IsWhite()) {
				return whiteKingDarkTexture;
			}
			else if (dynamic_cast<Pawn*>(piece) && !piece->IsWhite()) {
				return blackPawnDarkTexture;
			}
			else if (dynamic_cast<Pawn*>(piece) && piece->IsWhite()) {
				return whitePawnDarkTexture;
			}
		}
		else {
			return emptyDarkTexture;
		}
	}

}

void Game::initGame()
{
	loadResources();
	gameStatus = GameStatus::ACTIVE;
}

int Game::choosePlayer() {
	sf::RenderWindow choiceWindow(sf::VideoMode(100 + Settings::pickColorBtnSize * 2, Settings::pickColorBtnSize), "Select Color");
	choiceWindow.clear(sf::Color::White);
	sf::Texture whiteTexture;
	sf::Texture blackTexture;
	whiteTexture.loadFromFile(Settings::whitePieceURL);
	blackTexture.loadFromFile(Settings::blackPieceURL);

	sf::Sprite whiteSprite;
	sf::Sprite blackSprite;

	whiteSprite.setTexture(whiteTexture);
	whiteSprite.setScale((float)Settings::pickColorBtnSize / whiteTexture.getSize().x, (float)Settings::pickColorBtnSize / whiteTexture.getSize().y);
	whiteSprite.setPosition(50 + 0 * Settings::pickColorBtnSize, 0);
	choiceWindow.draw(whiteSprite);

	blackSprite.setTexture(blackTexture);
	blackSprite.setScale((float)Settings::pickColorBtnSize / blackTexture.getSize().x, (float)Settings::pickColorBtnSize / blackTexture.getSize().y);
	blackSprite.setPosition(50 + 1 * Settings::pickColorBtnSize, 0);
	choiceWindow.draw(blackSprite);

	choiceWindow.display();
	int x = -1;
	while (choiceWindow.isOpen())
	{

		sf::Event event;
		while (choiceWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				switch (event.key.code)
				{
				case sf::Mouse::Left:
					x = (sf::Mouse::getPosition(choiceWindow).x - 50) / Settings::pickColorBtnSize;
					if (x >= 0 && x <= 1) choiceWindow.close();
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
	return x;
}

void Game::drawBoard(Vec2<int> position, Vec2<int> destination)
{
	std::vector<Square*> canMoveSquare;
	if (position.getX() >= 0 && position.getY() >= 0) {
		canMoveSquare = board->showLegalMoves(position);
	}

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			sf::Sprite sprite;
			sf::Texture texture = getTexture(board->getSquare(x, y));
			sprite.setTexture(texture);
			sf::Color color = sprite.getColor();
			color.a = 240;
			sprite.setColor(color);
			color.a = 150;
			if ((x == position.getX() && y == position.getY())) sprite.setColor(color);
			sprite.setScale((float)Settings::squareSize / texture.getSize().x, (float)Settings::squareSize / texture.getSize().y);
			sprite.setPosition(Settings::startX + x * Settings::squareSize, Settings::startY + y * Settings::squareSize);

			if (board->isContains(canMoveSquare, board->getSquare(x, y))) {
				sprite.setColor(sf::Color(255, 255, 0, 200));
				if (board->getSquare(x, y)->isOccupied()) sprite.setColor(sf::Color(255, 0, 0, 200));
			}

			gameWindow->draw(sprite);
		}
	}


}

int Game::displayMessageBox(const char* message, int width, int height, int buttonWidth, int buttonHeight)
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Message Box", sf::Style::None);

	sf::Color backgroundColor(255, 255, 255, 200);

	sf::Font font;
	font.loadFromFile(Settings::fontURL);


	sf::Text messageText;
	messageText.setFont(font);
	messageText.setString(message);
	messageText.setCharacterSize(75);
	messageText.setFillColor(sf::Color::Blue);

	sf::FloatRect textBounds = messageText.getLocalBounds();
	messageText.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	messageText.setPosition(window.getSize().x / 2, window.getSize().y / 4);

	sf::Texture buttonTexture1;
	buttonTexture1.loadFromFile(Settings::replayButtonURL);

	sf::Sprite button1;
	button1.setTexture(buttonTexture1);
	button1.setScale((float)buttonWidth / buttonTexture1.getSize().x, (float)buttonHeight / buttonTexture1.getSize().y);
	button1.setPosition(buttonWidth, textBounds.height * 2.5);

	sf::Texture buttonTexture2;
	buttonTexture2.loadFromFile(Settings::exitButtonURL);
	sf::Sprite button2;
	button2.setTexture(buttonTexture2);
	button2.setScale((float)buttonWidth / buttonTexture2.getSize().x, (float)buttonHeight / buttonTexture2.getSize().y);
	button2.setPosition(window.getSize().x - buttonWidth * 2, textBounds.height * 2.5);

	sf::Color buttonDefaultColor = sf::Color::White;
	sf::Color buttonHoverColor = sf::Color::Yellow;

	button1.setColor(buttonDefaultColor);
	button2.setColor(buttonDefaultColor);

	sf::RectangleShape borderShape(sf::Vector2f(window.getSize().x - 40.0f,
		window.getSize().y - 40.0f)); 
			borderShape.setFillColor(sf::Color::Transparent);
	borderShape.setOutlineThickness(10.0f);
	borderShape.setOutlineColor(sf::Color::Black);
	borderShape.setPosition(sf::Vector2f(20.0f, 20.0f));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

				if (button1.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
				{
					button1.setColor(buttonHoverColor);
				}
				else
				{
					button1.setColor(buttonDefaultColor);
				}

				if (button2.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
				{
					button2.setColor(buttonHoverColor);
				}
				else
				{
					button2.setColor(buttonDefaultColor);
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

				if (button1.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
				{
					window.close();
					return 1;
				}

				if (button2.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
				{
					window.close();
					return 2;
				}
			}
		}

		window.clear(backgroundColor);

		window.draw(borderShape);
		window.draw(messageText);
		window.draw(button1);
		window.draw(button2);
		window.display();
	}
}