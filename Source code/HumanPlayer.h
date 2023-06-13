#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H


#include "Player.h"
class HumanPlayer :
    public Player
{
public:
	HumanPlayer(bool isWhite);
	bool movePiece(Game* game, int& sx, int& sy, int& ex, int& ey, Piece*& beginPiece);
};

#endif // !HUMAN_PLAYER_H