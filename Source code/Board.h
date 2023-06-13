#ifndef HEADER_BOARD_H
#define HEADER_BOARD_H

#include <vector>
#include "Piece.h"
#include "Square.h"
#include "Move.h"
#include "Player.h"
#include "Vec2.h"
#include "Settings.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Piece;
class Square;
class Move;
class King;

class Board
{
private:
	std::vector<std::vector<Square*>> squares;
	std::vector<Move*> madeMoves;
	
	void promotePawn(Square* originalSquare, Player* currentPlayer);
	
public:
	Board(bool isPlayerWhite);
	~Board();
	Square* getSquare(int x, int y) const;
	Square* getSquare(const Vec2<int>& position) const;
	bool isContains(std::vector<Square*> squares, Square* square) const;
	bool movePiece(Piece* beginPiece, Square* end, std::vector<Move*> legalMoves, Player* curPlayer, bool playSound);
	void undoMove();
	std::vector<Move*> getMadeMoves() const;
	std::vector<Move*> generateAllLegalMoves(Piece* piece);
	bool isChecked(bool isWhite);
	bool isNearbyAttacked(Vec2<int> offs, bool isWhite);
	std::vector<Square*> showLegalMoves(const Vec2<int>& position);
	

};

#endif