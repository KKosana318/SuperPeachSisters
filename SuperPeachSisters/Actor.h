#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

using namespace std;

class StudentWorld;

class Actor : public GraphObject {
public:
	Actor::Actor(StudentWorld* world,
				 int imageID, 
				 int x, 
				 int y, 
				 int dir = 0, 
				 int depth = 0,
				 double size = 1.0);

	virtual ~Actor() = 0;
	StudentWorld* getWorld() { return m_world; }
	virtual void doSomething();
	virtual void bonk();
	bool alive() { return m_alive; }
	void kill() { m_alive = false; }
	virtual bool blocking() { return false; }
	virtual bool damageable() { return false; }

private:
	bool m_alive;
	StudentWorld* m_world;
};

class Peach : public Actor {
public:
	Peach(StudentWorld* world, int x, int y);
	~Peach();
	void doSomething();
	void bonk();
	bool damageable() { return true; }
	void giveStarPower(int n);
	void giveJumpPower();
	void giveShootPower();
	void increaseHP();

private:
	int m_hp;
	bool m_shootPower;
	bool m_jumpPower;
	int m_remainingJumpDistance;
	int m_remainingStarInvincibilityTicks;
	int m_remainingTempInvincibilityTicks;
	int m_remainingRechargeTime;
};

class Block : public Actor {
public:
	Block(StudentWorld* world, int x, int y, char goodie = 'n');
	~Block();
	void Bonk();
	bool blocking() { return true; }
private:
	char m_goodie; // n=none, ^ = mushroom, % = flower, * = star
	bool m_released;
};

class Pipe : public Actor {
public:
	Pipe(StudentWorld* world, int x, int y);
	~Pipe();
	bool blocking() { return true; }
};

class Flag : public Actor {
public:
	Flag(StudentWorld* world, int x, int y);
	~Flag();
	void doSomething();
};

class Mario : public Actor {
public:
	Mario(StudentWorld* world, int x, int y);
	~Mario();
	void doSomething();

};

class Flower : public Actor {
public:
	Flower(StudentWorld* world, int x, int y);
	~Flower();
	void doSomething();
};

class Mushroom : public Actor {
public:
	Mushroom(StudentWorld* world, int x, int y);
	~Mushroom();
	void doSomething();
};

class Star : public Actor {
public:
	Star(StudentWorld* world, int x, int y);
	~Star();
	void doSomething();
};

class PiranhaFireball : public Actor {
public:
	PiranhaFireball(StudentWorld* world, int x, int y, int dir);
	~PiranhaFireball();
	void doSomething();
};

class PeachFireball : public Actor {
public:
	PeachFireball(StudentWorld* world, int x, int y, int dir);
	~PeachFireball();
	void doSomething();
};

class Shell : public Actor {
public:
	Shell(StudentWorld* world, int x, int y, int dir);
	~Shell();
	void doSomething();
};

class Goomba : public Actor {
public:
	Goomba(StudentWorld* world, int x, int y);
	~Goomba();
	void doSomething();
};

class Koopa : public Actor {
public:
	Koopa(StudentWorld* world, int x, int y);
	~Koopa();
	void doSomething();
};

class Piranha : public Actor {
public:
	Piranha(StudentWorld* world, int x, int y);
	~Piranha();
	void doSomething();
private:
	int m_delay;
};

#endif // ACTOR_H_
