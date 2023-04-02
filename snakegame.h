#pragma once
class snakegame
{
public:
	enum class eDirection {
		STOP = 0,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	snakegame();
	void draw();
	void input();
	void logic();
	void spawnPellet();
	bool getGameOver();
	bool validSpace(eDirection playerDirection);

	
private:
	bool mGameOver;
	int mScore;
	int mPlayerX, mPlayerY;
	int mTailX[100], mTailY[100];
	int mTailSize;
	int mPelletX, mPelletY;
	eDirection mPlayerDirection;
	const int mMapWidth, mMapHeight;
};

