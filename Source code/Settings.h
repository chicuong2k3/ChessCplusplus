#ifndef SETTINGS_H
#define SETTINGS_H
#include <SFML/Graphics.hpp>
#include "Vec2.h"

class Settings
{
public:
	static constexpr const char* screenTitle = "Chess Game";
	static const int screenWidth = 1350;
	static const int screenHeight = 900;
	static const int squareSize = 100;
	static const int startX = 200;
	static const int startY = (screenHeight - squareSize * 8) / 2;
	static const int pickColorBtnSize = 200;
	static const int buttonSize = 80;
	static constexpr Vec2<int> undoButtonPosition { Settings::startX + 8 * Settings::squareSize + 20, Settings::screenHeight / 2 };
	static constexpr Vec2<int> exitButtonPosition { Settings::startX + 8 * Settings::squareSize + 20, Settings::screenHeight / 2 + buttonSize + 20 };
	

	

	// Bishop image url
	static constexpr const char* blackBishopLightURL = "Resources\\Images\\blackBishopLight.png";
	static constexpr const char* whiteBishopLightURL = "Resources\\Images\\whiteBishopLight.png";
	static constexpr const char* whiteBishopDarkURL = "Resources\\Images\\whiteBishopDark.png";
	static constexpr const char* blackBishopDarkURL = "Resources\\Images\\blackBishopDark.png";

	// Knight image url
	static constexpr const char* blackKnightLightURL = "Resources\\Images\\blackKnightLight.png";
	static constexpr const char* whiteKnightLightURL = "Resources\\Images\\whiteKnightLight.png";
	static constexpr const char* blackKnightDarkURL = "Resources\\Images\\blackKnightDark.png";
	static constexpr const char* whiteKnightDarkURL = "Resources\\Images\\whiteKnightDark.png";

	// Rook image url
	static constexpr const char* blackRookLightURL = "Resources\\Images\\blackRookLight.png";
	static constexpr const char* whiteRookLightURL = "Resources\\Images\\whiteRookLight.png";
	static constexpr const char* blackRookDarkURL = "Resources\\Images\\blackRookDark.png";
	static constexpr const char* whiteRookDarkURL = "Resources\\Images\\whiteRookDark.png";

	// Queen image url
	static constexpr const char* blackQueenLightURL = "Resources\\Images\\blackQueenLight.png";
	static constexpr const char* whiteQueenLightURL = "Resources\\Images\\whiteQueenLight.png";
	static constexpr const char* blackQueenDarkURL = "Resources\\Images\\blackQueenDark.png";
	static constexpr const char* whiteQueenDarkURL = "Resources\\Images\\whiteQueenDark.png";

	// King image url
	static constexpr const char* blackKingLightURL = "Resources\\Images\\blackKingLight.png";
	static constexpr const char* whiteKingLightURL = "Resources\\Images\\whiteKingLight.png";
	static constexpr const char* blackKingDarkURL = "Resources\\Images\\blackKingDark.png";
	static constexpr const char* whiteKingDarkURL = "Resources\\Images\\whiteKingDark.png";

	// Pawn image url
	static constexpr const char* blackPawnLightURL = "Resources\\Images\\blackPawnLight.png";
	static constexpr const char* whitePawnLightURL = "Resources\\Images\\whitePawnLight.png";
	static constexpr const char* blackPawnDarkURL = "Resources\\Images\\blackPawnDark.png";
	static constexpr const char* whitePawnDarkURL = "Resources\\Images\\whitePawnDark.png";

	// Empty square image url
	static constexpr const char* emptyLightURL = "Resources\\Images\\emptyLight.png";
	static constexpr const char* emptyDarkURL = "Resources\\Images\\emptyDark.png";

	// Promotion pieces
	static constexpr const char* promoteBlackBishopURL = "Resources\\Images\\promoteBlackBishop.png";
	static constexpr const char* promoteWhiteBishopURL = "Resources\\Images\\promoteWhiteBishop.png";
	static constexpr const char* promoteBlackQueenURL = "Resources\\Images\\promoteBlackQueen.png";
	static constexpr const char* promoteWhiteQueenURL = "Resources\\Images\\promoteWhiteQueen.png";
	static constexpr const char* promoteBlackRookURL = "Resources\\Images\\promoteBlackRook.png";
	static constexpr const char* promoteWhiteRookURL = "Resources\\Images\\promoteWhiteRook.png";
	static constexpr const char* promoteBlackKnightURL = "Resources\\Images\\promoteBlackKnight.png";
	static constexpr const char* promoteWhiteKnightURL = "Resources\\Images\\promoteWhiteKnight.png";

	static constexpr const char* blackPieceURL = "Resources\\Images\\blackPiece.png";
	static constexpr const char* whitePieceURL = "Resources\\Images\\whitePiece.png";


	static constexpr const char* checkSoundURL = "Resources\\Sounds\\check.wav";
	static constexpr const char* captureSoundURL = "Resources\\Sounds\\capture.wav";
	static constexpr const char* moveSoundURL = "Resources\\\Sounds\\move.wav";
	static constexpr const char* checkmateSoundURL = "Resources\\Sounds\\checkmate.wav";
	static constexpr const char* castlingSoundURL = "Resources\\Sounds\\castling.wav";


	static constexpr const char* themeMusicURL = "Resources\\Musics\\theme.wav";
	static constexpr const char* endgameMusicURL = "Resources\\Musics\\endgame.wav";

	static constexpr const char* undoButtonURL = "Resources\\Images\\undoButton.png";
	static constexpr const char* exitButtonURL = "Resources\\Images\\exitButton.png";
	static constexpr const char* replayButtonURL = "Resources\\Images\\replayButton.png";
	static constexpr const char* boardBackgroundURL = "Resources\\Images\\boardBackground.jpg";
	static constexpr const char* menuBackgroundURL = "Resources\\Images\\menuBackground.png";
	static constexpr const char* menuItem1 = "Resources\\Images\\menu1.png";
	static constexpr const char* menuItem2 = "Resources\\Images\\menu2.png";
	static constexpr const char* menuItem3 = "Resources\\Images\\menu3.png";
	
	static constexpr const char* fontURL = "Resources\\Fonts\\Roboto.ttf";
};

#endif //