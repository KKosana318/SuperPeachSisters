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
	Actor* objectAt(int x, int y);
	bool isPeachAt(int x, int y);
	void addActor(Actor* actor);
	bool isPeach(Actor* actor);
	Peach* getPeach();
	void finishedLevel();
	void wonGame();

private:
	 vector<Actor*> actors;
	 Peach* peach;
	 bool m_finishedLevel;
	 bool m_wonGame;
};

#endif // STUDENTWORLD_H_
