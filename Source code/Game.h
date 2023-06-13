#ifndef HEADER_GAME_H
#define HEADER_GAME_H

#include "Board.h"
#include "Player.h"
#include "Move.h"

#include <SFML/Audio.hpp>
#include "SFML/Graphics.hpp"
#include <fstream>

class Move;
class Board;
class Player;
class Square;

class Game
{
public:
	enum class GameStatus {
        ACTIVE,
        BLACK_WIN,
        WHITE_WIN,
        EXIT
	};
	sf::RenderWindow *gameWindow;
	int playerChoice;
	GameStatus gameStatus;
	Game(sf::RenderWindow* window, int choice);
    ~Game();
    void setStatus(GameStatus status);
    GameStatus getStatus() const;
    Board* getBoard();
    Player* getCurrentPlayer();
    bool play();
private:
    Player* player[2];
    Player* currentPlayer;
	Board* board;

	bool playWithComputer;
	sf::Sound checkSound;
    void loadResources();
    void initGame(); 
    int choosePlayer();
    void displayBackground();
	void drawButton(const char* url, int size, int x, int y);
	void drawBoard(Vec2<int> position, Vec2<int> destination);
	int displayMessageBox(const char* message, int width, int height, int buttonWidth, int buttonHeight);

	sf::Texture getTexture(Square* square) const;
	sf::Texture blackBishopLightTexture;
	sf::Texture whiteBishopLightTexture;
	sf::Texture blackBishopDarkTexture;
	sf::Texture whiteBishopDarkTexture;

	sf::Texture blackKnightLightTexture;
	sf::Texture whiteKnightLightTexture;
	sf::Texture blackKnightDarkTexture;
	sf::Texture whiteKnightDarkTexture;

	sf::Texture blackRookLightTexture;
	sf::Texture whiteRookLightTexture;
	sf::Texture blackRookDarkTexture;
	sf::Texture whiteRookDarkTexture;

	sf::Texture blackQueenLightTexture;
	sf::Texture whiteQueenLightTexture;
	sf::Texture blackQueenDarkTexture;
	sf::Texture whiteQueenDarkTexture;

	sf::Texture blackKingLightTexture;
	sf::Texture whiteKingLightTexture;
	sf::Texture blackKingDarkTexture;
	sf::Texture whiteKingDarkTexture;

	sf::Texture blackPawnLightTexture;
	sf::Texture whitePawnLightTexture;
	sf::Texture blackPawnDarkTexture;
	sf::Texture whitePawnDarkTexture;

	sf::Texture emptyLightTexture;
	sf::Texture emptyDarkTexture;

};

#endif
