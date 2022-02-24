#include "Actor.h"
#include "StudentWorld.h"

Actor::Actor(StudentWorld* world, int imageID, int x, int y, int dir, int depth, double size, bool blocking)
:GraphObject(imageID, x, y, dir, depth, size) {
	m_alive = true;
	m_blocking = blocking;
	m_world = world;
};

Actor::~Actor() {};

void Actor::doSomething() {
	return;
}

Peach::Peach(StudentWorld* world, int x, int y) : Actor(world, IID_PEACH, x, y) {
	hp = 1;
	m_invincible = m_starPower = m_shootPower = m_jumpPower = false;
}

Peach::~Peach() {

}

void Peach::setKey(int key) {
	m_key = key;
}

void bonk(Actor* bonked) {
	return;
}

void Peach::doSomething() {
	if (!alive()) { // peach died
		return; 
	}	

	if (!getWorld()->getKey(m_key)) {
		return;
	}

	if (m_key == KEY_PRESS_LEFT && !(getWorld()->isBlockingObjectAt(getX() - 4, getY()))) { // move left
		setDirection(180);
		moveTo(getX() - 4, getY());
	}

	if (m_key == KEY_PRESS_RIGHT && !(getWorld()->isBlockingObjectAt(getX() + 4, getY()))) { // move right
		setDirection(0);
		moveTo(getX() + 4, getY());
	}
}

Block::Block(StudentWorld* world, int x, int y, char goodie) : Actor(world, IID_BLOCK, x, y, 0, 2, 1, true) {
	m_goodie = goodie;
	m_released = false;
}

Block::~Block() {

}

Pipe::Pipe(StudentWorld* world, int x, int y) : Actor(world, IID_PIPE, x, y, 0, 2, 1, true) {}

Pipe::~Pipe() {

}

Flag::Flag(StudentWorld* world, int x, int y) : Actor(world, IID_FLAG, x, y, 0, 1) {}

Flag::~Flag() {

}

void Flag::doSomething() {

}

Mario::Mario(StudentWorld* world, int x, int y) : Actor(world, IID_MARIO, x, y, 0, 1) {}

Mario::~Mario() {

}

void Mario::doSomething() {
	return;
}

Flower::Flower(StudentWorld* world, int x, int y) : Actor(world, IID_FLOWER, x, y, 0, 1) {

}

Flower::~Flower() {

}

void Flower::doSomething() {

}

Mushroom::Mushroom(StudentWorld* world, int x, int y) : Actor(world, IID_MUSHROOM, x, y, 0, 1) {

}

Mushroom::~Mushroom() {

}

void Mushroom::doSomething() {

}

Star::Star(StudentWorld* world, int x, int y) : Actor(world, IID_STAR, x, y, 0, 1) {

}

Star::~Star() {

}

void Star::doSomething() {

}

PiranhaFireball::PiranhaFireball(StudentWorld* world, int x, int y, int dir) : Actor(world, IID_PIRANHA_FIRE, x, y, dir, 1) {

}

PiranhaFireball::~PiranhaFireball() {

}

void PiranhaFireball::doSomething() {

}

PeachFireball::PeachFireball(StudentWorld* world, int x, int y, int dir) : Actor(world, IID_PEACH_FIRE, x, y, dir, 1) {

}

PeachFireball::~PeachFireball() {

}

void PeachFireball::doSomething() {

}

Shell::Shell(StudentWorld* world, int x, int y, int dir) : Actor(world, IID_SHELL, x, y, dir, 1) {

}

Shell::~Shell() {

}

void Shell::doSomething() {

}

Goomba::Goomba(StudentWorld* world, int x, int y) : Actor(world, IID_GOOMBA, x, y, rand() % 2 == 0 ? 0 : 180) { // 0 degrees if rand returns even number, 180 if odd

}

Goomba::~Goomba() {

}

void Goomba::doSomething() {

}

Koopa::Koopa(StudentWorld* world, int x, int y) : Actor(world, IID_KOOPA, x, y, rand() % 2 == 0 ? 0 : 180) {

}

Koopa::~Koopa() {

}

void Koopa::doSomething() {

}

Piranha::Piranha(StudentWorld* world, int x, int y) : Actor(world, IID_PIRANHA, x, y, rand() % 2 == 0 ? 0 : 180) {
	m_delay = 0;
}

Piranha::~Piranha() {

}

void Piranha::doSomething() {

}