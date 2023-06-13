#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H
#include "Player.h"
class ComputerPlayer :
    public Player
{
public:
    ComputerPlayer(bool isWhite);
    bool movePiece(Game* game, int& sx, int& sy, int& ex, int& ey, Piece*& beginPiece);
};

#endif
