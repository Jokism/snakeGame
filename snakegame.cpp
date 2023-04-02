#include "snakegame.h"
#include <iostream>
#include <conio.h>

snakegame::snakegame() : mMapHeight(20), mMapWidth(20)
{
	mGameOver = false;
	mPlayerDirection = eDirection::STOP;
	mScore = 0;
	mPlayerX = mMapWidth << 2;
	mPlayerY = mMapHeight << 2;
	mPelletX = rand() % mMapWidth;
	mPelletY = rand() % mMapHeight;
	mTailSize = 0;
}

void snakegame::draw()
{
	//call windows cls to clear terminal screen
	system("cls");

	//Create map
	for (int i = 0; i < mMapWidth + 2; i++) {
		std::cout << "#";
	}
	std::cout << std::endl;

	for (int i = 0; i < mMapHeight; i++) {
		for (int j = 0; j < mMapWidth; j++) {

			if (j == 0) 
				std::cout << "# ";
			
			else if (i == mPlayerY && j == mPlayerX)
				std::cout << "P";

			else if (i == mPelletY && j == mPelletX) 
				std::cout << "O";
			
			else {
					bool printedTailSegment = false;
					for (int k = 0; k < mTailSize; k++) {
						if (mTailX[k] == j && mTailY[k] == i) {
							std::cout << "p";
							printedTailSegment = true;
						}
					}
					if (!printedTailSegment) {
						std::cout << " ";
					}
			}
			if (j == mMapWidth - 1)
				std::cout << "# ";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < mMapWidth + 2; i++) {
		std::cout << "#";
	}
	std::cout << std::endl;
	std::cout << "S C O R E : " << mScore << std::endl;
	std::cout << std::endl;
}

void snakegame::input()
{
	//return non-zero number if key pressed
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			mPlayerDirection = eDirection::LEFT;
			break;

		case 'w':
			mPlayerDirection = eDirection::UP;
			break;

		case 's':
			mPlayerDirection = eDirection::DOWN;
			break;

		case 'd':
			mPlayerDirection = eDirection::RIGHT;
			break;

		case ' ':
			mPlayerDirection = eDirection::STOP;
			break;

		case 'x':
			mPlayerDirection = eDirection::STOP;
			mGameOver = true;
			break;
		default:
			break;
		}

		
	}
}

void snakegame::logic()
{
	int prevX = mTailX[0];
	int prevY = mTailY[0];
	int prevX2, prevY2;
	mTailX[0] = mPlayerX;
	mTailY[0] = mPlayerY;
	
	// used to print tail
	for (int i = 1; i < mTailSize; i++) {
		prevX2 = mTailX[i];
		prevY2 = mTailY[i];

		mTailX[i] = prevX;
		mTailY[i] = prevY;

		prevX = prevX2;
		prevY = prevY2;

	}

	switch (mPlayerDirection) {
	case eDirection::UP:
		if (validSpace(eDirection::UP))
			mPlayerY -= 1;

		break;
	case eDirection::DOWN:
		if (validSpace(eDirection::DOWN))
			mPlayerY += 1;

		break;
	case eDirection::LEFT:
		if (validSpace(eDirection::LEFT))
			mPlayerX -= 1;

		break;
	case eDirection::RIGHT:
		if (validSpace(eDirection::RIGHT))
			mPlayerX += 1;

		break;
	default:
		break;
	}

	if (mPlayerX >= mMapWidth - 1)
		mPlayerX = 0;
	else if (mPlayerX < 1)
		mPlayerX = mMapWidth - 1;

	if (mPlayerY >= mMapHeight-1)
		mPlayerY = 0;
	else if (mPlayerY <= 0)
		mPlayerY = mMapHeight - 1;

	for (int i = 0; i < mTailSize; i++) {
		if (mPlayerX == mTailX[i] && mPlayerY == mTailY[i] && mPlayerDirection != eDirection::STOP)
			mGameOver = true;
	}

	if (mPlayerX == mPelletX && mPlayerY == mPelletY) {
		mScore += 1;
		spawnPellet();
		mTailSize++;
	}

	

}

void snakegame::spawnPellet()
{
	mPelletX = rand() % mMapWidth;
	mPelletY = rand() % mMapHeight;
}

bool snakegame::getGameOver()
{
	std::cout << std::endl;

	if (!mGameOver) {
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "S C O R E : " << mScore << std::endl;
		std::cout << std::endl;
	}
	else {
		std::cout << "G A M E  O V E R !" << std::endl;
		std::cout << "Y O U R   S C O R E   I S : " << mScore << std::endl;
		std::cout << "T H A N K  Y O U  F O R  P L A Y I N G !" << std::endl;
	}
	return mGameOver;
}

bool snakegame::validSpace(eDirection playerDirection)
{
	switch (playerDirection) {
	case eDirection::LEFT:
		if (mPlayerX > 0)
			return true;
		else
			return false;
		break;

	case eDirection::RIGHT:
		if (mPlayerX < mMapWidth -1)
			return true;
		else
			return false;
		break;
	case eDirection::UP:
		if (mPlayerY > 0)
			return true;
		else
			return false;
		break;
	case eDirection::DOWN:
		if (mPlayerY < mMapHeight - 1)
			return true;
		else
			return false;
		break;
	default:
		return false;
		break;
	}

}
