#include "Board.h"
#include <SFML/Audio.hpp>
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Rook.h"
#include "Queen.h"
#include "ComputerPlayer.h"


Board::Board(bool isPlayerWhite)
{
	squares.resize(8);
	for (int i = 0; i < 8; i++)
	{
		squares[i].resize(8);
	}

	squares[0][0] = new Square(new Rook({ 0, 0 }, !isPlayerWhite, 1), 0, 0);
	squares[0][1] = new Square(new Knight({ 1, 0 }, !isPlayerWhite, 1), 1, 0);
	squares[0][2] = new Square(new Bishop({ 2, 0 }, !isPlayerWhite, 1), 2, 0);
	squares[0][3] = new Square(new Queen({ 3, 0 }, !isPlayerWhite, 1), 3, 0);
	squares[0][4] = new Square(new King({ 4, 0 }, !isPlayerWhite, 1), 4, 0);
	squares[0][5] = new Square(new Bishop({ 5, 0 }, !isPlayerWhite, 1), 5, 0);
	squares[0][6] = new Square(new Knight({ 6, 0 }, !isPlayerWhite, 1), 6, 0);
	squares[0][7] = new Square(new Rook({ 7, 0 }, !isPlayerWhite, 1), 7, 0);
	for (int i = 0; i < 8; i++)
	{
		squares[1][i] = new Square(new Pawn({ i, 1 }, !isPlayerWhite, 1), i, 1);
	}

	squares[7][0] = new Square(new Rook({ 0, 7 }, isPlayerWhite, 0), 0, 7);
	squares[7][1] = new Square(new Knight({ 1, 7 }, isPlayerWhite, 0), 1, 7);
	squares[7][2] = new Square(new Bishop({ 2, 7 }, isPlayerWhite, 0), 2, 7);
	squares[7][3] = new Square(new Queen({ 3, 7 }, isPlayerWhite, 0), 3, 7);

	squares[7][4] = new Square(new King({ 4, 7 }, isPlayerWhite, 0), 4, 7);
	squares[7][5] = new Square(new Bishop({ 5, 7 }, isPlayerWhite, 0), 5, 7);
	squares[7][6] = new Square(new Knight({ 6, 7 }, isPlayerWhite, 0), 6, 7);
	squares[7][7] = new Square(new Rook({ 7, 7 }, isPlayerWhite, 0), 7, 7);
	for (int i = 0; i < 8; i++)
	{
		squares[6][i] = new Square(new Pawn({ i, 6 }, isPlayerWhite, 0), i, 6);
	}

	for (int i = 2; i <= 5; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			squares[i][j] = new Square(j, i);
		}

	}
}

Board::~Board()
{
	for (int i = 0; i < squares.size(); i++)
	{
		for (int j = 0; j < squares[i].size(); j++)
		{
			delete squares[i][j];
		}
	}
}

Square* Board::getSquare(int x, int y) const
{
    return squares[y][x];
}

Square* Board::getSquare(const Vec2<int>& position) const
{
	return squares[position.getY()][position.getX()];
}

std::vector<Move*> Board::getMadeMoves() const
{
	return madeMoves;
}

bool Board::isContains(std::vector<Square*> squares, Square* square) const
{
	for (int i = 0; i < squares.size(); i++)
	{
		if (square->getPosition().getX() == squares[i]->getPosition().getX() 
			&& square->getPosition().getY() == squares[i]->getPosition().getY()) return true;
	}
	return false;
}

std::vector<Square*> Board::showLegalMoves(const Vec2<int>& position)
{
	std::vector<Square*> canMoveSquare;
	Piece* beginPiece = getSquare(position.getX(), position.getY())->getPiece();
	std::vector<Move*> moves = generateAllLegalMoves(beginPiece);

	for (int i = 0; i < moves.size(); i++)
	{
		Square* destSquare = moves[i]->getEndSquare();
		canMoveSquare.push_back(destSquare);
	}
	return canMoveSquare;
}

bool Board::movePiece(Piece* beginPiece, Square* end, std::vector<Move*> legalMoves, Player* curPlayer, bool playSound)
{
	Move* requiredMove = nullptr;
	for (Move* move: legalMoves)
	{
		if (move->getEndSquare()->getPosition() == end->getPosition()) {
			requiredMove = move;
			break;
		}
	}
	if (requiredMove == nullptr) return false;
	
	// process for Enpassant


	/*if (requiredMove->getType() == Move::MoveType::ENPASSANT) {
		madeMoves.push_back(requiredMove);
		Vec2<int> dir;
		if (beginPiece->getOwner() == 0) dir = {0, -1};
		else dir = {0, 1};
		Square* square = getSquare(end->getPosition() - dir);
		Piece* endPiece = square->getPiece();
		square->setPiece(nullptr);
		endPiece->setKilled(false);
		requiredMove->setKilledPiece(endPiece);
		end->setPiece(beginPiece);
		beginPiece->setPosition(end->getPosition());
		requiredMove->getBeginSquare()->setPiece(nullptr);
		requiredMove->getMovedPiece()->increaseNumberOfMoves();
		if (playSound) {
			sf::Sound captureSound;
			captureSound.setBuffer(captureBuffer);
			captureSound.play();
			while (captureSound.getStatus() == sf::Sound::Playing)
			{

			}
		}
		return true;
	}*/


	// capture the piece at the destination if possible
	
	Piece* endPiece = end->getPiece();

	if (endPiece != nullptr) {
		endPiece->setAlive(false);
		requiredMove->setKilledPiece(endPiece);
	}
	
	madeMoves.push_back(requiredMove);
	Square* originalSquare = requiredMove->getBeginSquare();
	if (playSound) {
		if (requiredMove->getType() == Move::MoveType::NORMAL) {
			if (endPiece != nullptr) {
				Utility::playSound(Settings::captureSoundURL);
			}
			else {
				Utility::playSound(Settings::moveSoundURL);
			}
		}
		else if (requiredMove->getType() == Move::MoveType::PROMOTION) {

		}
		else if (requiredMove->getType() == Move::MoveType::SHORT_CASTLING || requiredMove->getType() == Move::MoveType::LONG_CASTLING) {
			Utility::playSound(Settings::castlingSoundURL);
		}
	}
	// the pawn promotion, short and long castling
	int y;
	if (beginPiece->getOwner() == 0) y = 7;
	else y = 0;
	if (requiredMove->getType() == Move::MoveType::PROMOTION) {
		beginPiece->setAlive(false);
		if (curPlayer != nullptr) {
			promotePawn(originalSquare, curPlayer);
		}
	}
	else if (requiredMove->getType() == Move::MoveType::SHORT_CASTLING) {
		getSquare(5, y)->setPiece(getSquare(7, y)->getPiece());
		getSquare(7, y)->getPiece()->increaseNumberOfMoves();
		getSquare(7, y)->setPiece(nullptr);
		getSquare(5, y)->getPiece()->setPosition({ 5, y });
	}
	else if (requiredMove->getType() == Move::MoveType::LONG_CASTLING) {
		getSquare(3, y)->setPiece(getSquare(0, y)->getPiece());
		getSquare(0, y)->getPiece()->increaseNumberOfMoves();
		getSquare(0, y)->setPiece(nullptr);
		getSquare(3, y)->getPiece()->setPosition({ 3, y });
	}
	
	Piece* originalPiece = originalSquare->getPiece();

	end->setPiece(originalPiece); // move the piece to the destination
	originalPiece->setPosition(end->getPosition()); // update the position of the piece
	originalSquare->setPiece(nullptr); // remove the piece from the original square
	requiredMove->getMovedPiece()->increaseNumberOfMoves();
	return true;
}

void Board::promotePawn(Square* originalSquare, Player* currentPlayer)
{
	if (dynamic_cast<ComputerPlayer*>(currentPlayer)) {
		srand(time(0));
		int x = rand() % 4;
		Piece* newPiece;
		Piece* oldPiece = originalSquare->getPiece();
		switch (x)
		{
		case 0:
			oldPiece->setAlive(false);
			newPiece = new Rook(originalSquare->getPosition(),
				originalSquare->getPiece()->IsWhite(), oldPiece->getOwner());
			originalSquare->setPiece(newPiece);
			currentPlayer->addPiece(newPiece);
			break;
		case 1:
			oldPiece->setAlive(false);
			newPiece = new Queen(originalSquare->getPosition(),
				originalSquare->getPiece()->IsWhite(), oldPiece->getOwner());
			originalSquare->setPiece(newPiece);
			currentPlayer->addPiece(newPiece);
			break;
		case 2:
			oldPiece->setAlive(false);
			newPiece = new Knight(originalSquare->getPosition(),
				originalSquare->getPiece()->IsWhite(), oldPiece->getOwner());
			originalSquare->setPiece(newPiece);
			currentPlayer->addPiece(newPiece);
			break;
		case 3:
			oldPiece->setAlive(false);
			newPiece = new Bishop(originalSquare->getPosition(),
				originalSquare->getPiece()->IsWhite(), oldPiece->getOwner());
			originalSquare->setPiece(newPiece);
			currentPlayer->addPiece(newPiece);
			break;
		}
		return;
	}


	sf::RenderWindow promotionWindow(sf::VideoMode(100 + Settings::squareSize * 4, Settings::squareSize),
		"Promotion");
	promotionWindow.clear(sf::Color::Magenta);
	sf::Texture promoteRook;
	sf::Texture promoteQueen;
	sf::Texture promoteKnight;
	sf::Texture promoteBishop;
	if (currentPlayer->isWhiteSide()) {
		promoteRook.loadFromFile(Settings::promoteWhiteRookURL);
		promoteQueen.loadFromFile(Settings::promoteWhiteQueenURL);
		promoteKnight.loadFromFile(Settings::promoteWhiteKnightURL);
		promoteBishop.loadFromFile(Settings::promoteWhiteBishopURL);
	}
	else {
		promoteRook.loadFromFile(Settings::promoteBlackRookURL);
		promoteQueen.loadFromFile(Settings::promoteBlackQueenURL);
		promoteKnight.loadFromFile(Settings::promoteBlackKnightURL);
		promoteBishop.loadFromFile(Settings::promoteBlackBishopURL);
	}
	sf::Sprite promoteRookSprite;
	sf::Sprite promoteQueenSprite;
	sf::Sprite promoteKnightSprite;
	sf::Sprite promoteBishopSprite;

	promoteRookSprite.setTexture(promoteRook);
	promoteRookSprite.setScale((float)Settings::squareSize / promoteRook.getSize().x, (float)Settings::squareSize / promoteRook.getSize().y);
	promoteRookSprite.setPosition(50 + 0 * Settings::squareSize, 0);
	promotionWindow.draw(promoteRookSprite);

	promoteQueenSprite.setTexture(promoteQueen);
	promoteQueenSprite.setScale((float)Settings::squareSize / promoteQueen.getSize().x, (float)Settings::squareSize / promoteQueen.getSize().y);
	promoteQueenSprite.setPosition(50 + 1 * Settings::squareSize, 0);
	promotionWindow.draw(promoteQueenSprite);

	promoteKnightSprite.setTexture(promoteKnight);
	promoteKnightSprite.setScale((float)Settings::squareSize / promoteKnight.getSize().x, (float)Settings::squareSize / promoteKnight.getSize().y);
	promoteKnightSprite.setPosition(50 + 2 * Settings::squareSize, 0);
	promotionWindow.draw(promoteKnightSprite);

	promoteBishopSprite.setTexture(promoteBishop);
	promoteBishopSprite.setScale((float)Settings::squareSize / promoteBishop.getSize().x, (float)Settings::squareSize / promoteBishop.getSize().y);
	promoteBishopSprite.setPosition(50 + 3 * Settings::squareSize, 0);
	promotionWindow.draw(promoteBishopSprite);

	promotionWindow.display();
	int x = -1;
	while (promotionWindow.isOpen())
	{

		sf::Event event;
		while (promotionWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				switch (event.key.code)
				{
				case sf::Mouse::Left:
					x = (sf::Mouse::getPosition(promotionWindow).x - 50) / Settings::squareSize;
					if (x >= 0 && x <= 3) promotionWindow.close();
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
	Piece* newPiece;
	Piece* oldPiece = originalSquare->getPiece();
	switch (x)
	{
	case 0:
		oldPiece->setAlive(false);
		newPiece = new Rook(originalSquare->getPosition(),
			originalSquare->getPiece()->IsWhite(), oldPiece->getOwner());
		originalSquare->setPiece(newPiece);
		currentPlayer->addPiece(newPiece);
		break;
	case 1:
		oldPiece->setAlive(false);
		newPiece = new Queen(originalSquare->getPosition(),
			originalSquare->getPiece()->IsWhite(), oldPiece->getOwner());
		originalSquare->setPiece(newPiece);
		currentPlayer->addPiece(newPiece);
		break;
	case 2:
		oldPiece->setAlive(false);
		newPiece = new Knight(originalSquare->getPosition(),
			originalSquare->getPiece()->IsWhite(), oldPiece->getOwner());
		originalSquare->setPiece(newPiece);
		currentPlayer->addPiece(newPiece);
		break;
	case 3:
		oldPiece->setAlive(false);
		newPiece = new Bishop(originalSquare->getPosition(),
			originalSquare->getPiece()->IsWhite(), oldPiece->getOwner());
		originalSquare->setPiece(newPiece);
		currentPlayer->addPiece(newPiece);
		break;
	}
}

void Board::undoMove()
{
	Move* madeMove = madeMoves[madeMoves.size() - 1];
	madeMoves.pop_back();
	Square* beginSquare = madeMove->getBeginSquare();
	Square* destSquare = madeMove->getEndSquare();

	// process for Enpassant
	/*if (madeMove->getType() == Move::MoveType::ENPASSANT) {
		Piece* beginPiece = madeMove->getMovedPiece();
		Vec2<int> dir;
		if (beginPiece->getOwner() == 0) dir = { 0, -1 };
		else dir = { 0, 1 };

		beginSquare->setPiece(beginPiece);
		beginPiece->setPosition(beginSquare->getPosition());
		beginPiece->decreaseNumberOfMoves();

		Square* square = getSquare(destSquare->getPosition() - dir);
		square->setPiece(madeMove->getKilledPiece());
		square->getPiece()->setPosition(square->getPosition());
		square->getPiece()->setKilled(true);

		destSquare->setPiece(nullptr);
		return;
	}*/



	if (madeMove->getType() == Move::MoveType::PROMOTION) {
		destSquare->getPiece()->setAlive(false);
		madeMove->getMovedPiece()->setAlive(true);
	}

	beginSquare->setPiece(madeMove->getMovedPiece()); // place the piece that has been moved into the original square
	destSquare->setPiece(madeMove->getKilledPiece()); // place the piece that has been killed into the destination square
	beginSquare->getPiece()->setPosition(beginSquare->getPosition());
	
	if (destSquare->getPiece() != nullptr) {
		destSquare->getPiece()->setPosition(destSquare->getPosition());
		destSquare->getPiece()->setAlive(true);
	}
	beginSquare->getPiece()->decreaseNumberOfMoves();


	
	if (madeMove->getType() == Move::MoveType::LONG_CASTLING) {
		int y;
		if (beginSquare->getPiece()->getOwner() == 0) y = 7;
		else y = 0;
		Piece* rook = getSquare(3, y)->getPiece();
		rook->decreaseNumberOfMoves();
		getSquare(0, y)->setPiece(rook);
		getSquare(0, y)->getPiece()->setPosition({0, y});
		getSquare(3, y)->setPiece(nullptr);
	}
	
	if (madeMove->getType() == Move::MoveType::SHORT_CASTLING) {
		int y;
		if (beginSquare->getPiece()->getOwner() == 0) y = 7;
		else y = 0;
		Piece* rook = getSquare(5, y)->getPiece();
		rook->decreaseNumberOfMoves();
		getSquare(7, y)->setPiece(rook);
		getSquare(7, y)->getPiece()->setPosition({ 7, y });
		getSquare(5, y)->setPiece(nullptr);
	}

}

std::vector<Move*> Board::generateAllLegalMoves(Piece* piece) {
	std::vector<Move*> legalMoves;
	std::vector<Move*> possibleMoves = piece->generatePossibleMoves(this);
	for (Move* move : possibleMoves) {
		
		if ((move->getType() == Move::MoveType::LONG_CASTLING || move->getType() == Move::MoveType::SHORT_CASTLING))
		{
			if (isChecked(piece->IsWhite())) continue;
			if (move->getType() == Move::MoveType::LONG_CASTLING && isNearbyAttacked({ -1, 0 }, piece->IsWhite()))
			{
				continue;
			}
					
			if (move->getType() == Move::MoveType::SHORT_CASTLING && isNearbyAttacked({ 1, 0 }, piece->IsWhite()))
			{
				continue;
			}
		}
		
		movePiece(piece, move->getEndSquare(), possibleMoves, nullptr, false);
		if (!isChecked(piece->IsWhite())) {
			legalMoves.push_back(move);
		}
		undoMove();
	}

	return legalMoves;
}

bool Board::isChecked(bool isWhite)
{
	Vec2<int> position = { -1, -1 };

	// find the position of this player's King on the board
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			Square* curSquare = getSquare(x, y);
			if (curSquare->isOccupied()) {
				Piece* piece = curSquare->getPiece();
				if (dynamic_cast<King*>(piece) && piece->IsWhite() == isWhite) {
					position = { x,y };
					break;
				}
			}
		}
	}

	// check if the King is checked by the Bishops or Queen
	std::vector<Vec2<int>> diagonalOffsets = { {1, 1}, {1, -1 }, {-1, 1}, {-1, -1} };

	for (Vec2<int> offset : diagonalOffsets) {
		Vec2<int> destination = position + offset;
		while (Utility::isOnBoard(destination))
		{
			Square* square = getSquare(destination);
			if (square->isOccupied()) {
				Piece* piece = square->getPiece();
				if ((dynamic_cast<Bishop*>(piece) || dynamic_cast<Queen*>(piece)) && piece->IsWhite() != isWhite) {
					return true;
				}
				else break;
			}
			destination += offset;
		}
	}

	// check if the King is checked by the Rooks or Queen
	std::vector<Vec2<int>> straightOffsets = { {1, 0}, { 0, 1 }, { 0, -1 }, { -1, 0 } };
	for (Vec2<int> offset : straightOffsets) {
		Vec2<int> destination = position + offset;
		while (Utility::isOnBoard(destination))
		{
			Square* square = getSquare(destination);
			if (square->isOccupied()) {
				Piece* piece = square->getPiece();
				if ((dynamic_cast<Rook*>(piece) || dynamic_cast<Queen*>(piece)) && piece->IsWhite() != isWhite) {
					return true;
				}
				else break;
			}
			destination += offset;
		}
	}

	// check if the King is checked by Knights
	std::vector<Vec2<int>> knightOffsets = {
		{2, 1}, {2, -1},
		{1, 2}, {1, -2},
		{-1, 2 }, { -1, -2 },
		{ -2, 1}, { -2, -1}
	};

	for (Vec2<int> offset : knightOffsets) {
		Vec2<int> destination = position + offset;
		if (Utility::isOnBoard(destination)) {
			Square* square = getSquare(destination);
			if (square->isOccupied()) {
				Piece* piece = square->getPiece();
				if (dynamic_cast<Knight*>(piece) && piece->IsWhite() != isWhite) {
					return true;
				}
			}
		}
	}

	//check if the King is checked by Pawns
	int direction;
	if (getSquare(position)->getPiece()->getOwner() == 0) direction = -1;
	else direction = 1;

	std::vector<Vec2<int>> pawnOffsets = { {1, direction}, {-1, direction} };
	for (Vec2<int> offset : pawnOffsets) {
		Vec2<int> destination = position + offset;
		if (Utility::isOnBoard(destination)) {
			Square* square = getSquare(destination);
			if (square->isOccupied()) {
				Piece* piece = square->getPiece();
				if (dynamic_cast<Pawn*>(piece) && piece->IsWhite() != isWhite) {
					return true;
				}
			}
		}
	}


	//check if the King is checked by the King
	std::vector<Vec2<int>> kingOffsets = {
		{-1, -1}, {0, -1},
		{1, -1}, {1, 0},
		{1, 1}, { 0, 1 },
		{-1, 1}, {-1, 0}
	};

	for (Vec2<int> offset : kingOffsets) {
		Vec2<int> destination = position + offset;
		if (Utility::isOnBoard(destination)) {
			Square* square = getSquare(destination);
			if (square->isOccupied()) {
				Piece* piece = square->getPiece();
				if (dynamic_cast<King*>(piece) && square->getPiece()->IsWhite() != isWhite) {
					return true;
				}
			}
		}
	}


	return false;
}

bool Board::isNearbyAttacked(Vec2<int> offs, bool isWhite) {
	Vec2<int> kingPos = { -1, -1 };
	// find the position of this player's King on the board
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			Square* curSquare = getSquare(x, y);
			if (curSquare->isOccupied()) {
				Piece* piece = curSquare->getPiece();
				if (dynamic_cast<King*>(piece) && piece->IsWhite() == isWhite) {
					kingPos = { x,y };
					break;
				}
			}
		}
	}

	Vec2<int> position = kingPos + offs;

	// check if the nearby of the King is checked by the Bishops or Queen
	std::vector<Vec2<int>> diagonalOffsets = { {1, 1}, {1, -1 }, {-1, 1}, {-1, -1} };

	for (Vec2<int> offset : diagonalOffsets) {
		Vec2<int> destination = position + offset;
		while (Utility::isOnBoard(destination))
		{
			Square* square = getSquare(destination);
			if (square->isOccupied()) {
				Piece* piece = square->getPiece();
				if (piece->IsWhite() != isWhite
					&& (dynamic_cast<Bishop*>(piece) || dynamic_cast<Queen*>(piece))) {
					return true;
				}
				else break;
			}
			destination += offset;
		}
	}

	// check if the nearby of the King is checked by the Rooks or Queen
	std::vector<Vec2<int>> straightOffsets = { {1, 0}, { 0, 1 }, { 0, -1 }, { -1, 0 } };
	for (Vec2<int> offset : straightOffsets) {
		Vec2<int> destination = position + offset;
		while (Utility::isOnBoard(destination))
		{
			Square* square = getSquare(destination);
			if (square->isOccupied()) {
				Piece* piece = square->getPiece();
				if (piece->IsWhite() != isWhite
					&& (dynamic_cast<Rook*>(piece) || dynamic_cast<Queen*>(piece))) {
					return true;
				}
				else break;
			}
			destination += offset;
		}
	}

	// check if the nearby of the King is checked by Knights
	std::vector<Vec2<int>> knightOffsets = {
		{2, 1}, {2, -1},
		{1, 2}, {1, -2},
		{-1, 2 }, { -1, -2 },
		{ -2, 1}, { -2, -1}
	};

	for (Vec2<int> offset : knightOffsets) {
		Vec2<int> destination = position + offset;
		if (Utility::isOnBoard(destination)) {
			Square* square = getSquare(destination);
			if (square->isOccupied()) {
				Piece* piece = square->getPiece();
				if (piece->IsWhite() != isWhite && dynamic_cast<Knight*>(piece)) {
					return true;
				}
			}
		}
	}

	//check if the nearby of the King is checked by Pawns
	int direction;
	Piece* king = getSquare(kingPos)->getPiece();

	if (king->getOwner() == 0) direction = -1;
	else direction = 1;

	std::vector<Vec2<int>> pawnOffsets = { {1, direction}, {-1, direction} };
	for (Vec2<int> offset : pawnOffsets) {
		Vec2<int> destination = position + offset;
		if (Utility::isOnBoard(destination)) {
			Square* square = getSquare(destination);
			if (square->isOccupied()) {
				Piece* piece = square->getPiece();
				if (piece->IsWhite() != isWhite && dynamic_cast<Pawn*>(piece)) {
					return true;
				}
			}
		}
	}


	//check if the nearby of the King is checked by the King
	std::vector<Vec2<int>> kingOffsets = {
		{-1, -1}, {0, -1},
		{1, -1}, {1, 0},
		{1, 1}, { 0, 1 },
		{-1, 1}, {-1, 0}
	};

	for (Vec2<int> offset : kingOffsets) {
		Vec2<int> destination = position + offset;
		if (Utility::isOnBoard(destination)) {
			Square* square = getSquare(destination);
			if (square->isOccupied()) {
				Piece* piece = square->getPiece();
				if (square->getPiece()->IsWhite() != isWhite && dynamic_cast<King*>(piece)) {
					return true;
				}
			}
		}
	}
	return false;
}