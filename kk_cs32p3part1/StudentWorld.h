#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <vector>


class StudentWorld : public GameWorld {
public:
	StudentWorld(std::string assetPath);
	~StudentWorld();
	virtual int init();
	virtual int move();
	virtual void cleanUp();
	bool isBlockingObjectAt(int x, int y);

private:
	 vector<Actor*> actors;
	 Peach* peach;
};

#endif // STUDENTWORLD_H_
