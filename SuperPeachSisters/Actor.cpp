#include "Actor.h"
#include "StudentWorld.h"

Actor::Actor(int imageID, int x, int y, int dir, int depth, double size)
:GraphObject(imageID, x, y, dir, depth, size) {
	m_alive = true;
};

Actor::~Actor() {};

void Actor::doSomething() {
	return;
}

Peach::Peach(int x, int y) :Actor(IID_PEACH, x, y) {
	hp = 1;
	m_invincible = m_starPower = m_shootPower = m_jumpPower = false;
}

Peach::~Peach() {

}

void Peach::setKey(int key) {
	m_key = key;
}

void Peach::doSomething() {
	if (!alive()) {
		return; 
	}

	if (m_key == KEY_PRESS_LEFT) {
		setDirection(180);
		moveTo(getX() - 4, getY());
	}

	if (m_key == KEY_PRESS_RIGHT) {
		setDirection(0);
		moveTo(getX() + 4, getY());
	}
}

Block::Block(int x, int y, char goodie) :Actor(IID_BLOCK, x, y, 0, 2) {
	m_goodie = goodie;
	m_released = false;
}

Block::~Block() {

}

Pipe::Pipe(int x, int y) :Actor(IID_PIPE, x, y, 0, 2) {}

Pipe::~Pipe() {

}

Flag::Flag(int x, int y) :Actor(IID_FLAG, x, y, 0, 1) {}

Flag::~Flag() {

}

void Flag::doSomething() {

}

Mario::Mario(int x, int y) :Actor(IID_MARIO, x, y, 0, 1) {}

Mario::~Mario() {

}

void Mario::doSomething() {
	return;
}

Flower::Flower(int x, int y) :Actor(IID_FLOWER, x, y, 0, 1) {

}

Flower::~Flower() {

}

void Flower::doSomething() {

}

Mushroom::Mushroom(int x, int y) :Actor(IID_MUSHROOM, x, y, 0, 1) {

}

Mushroom::~Mushroom() {

}

void Mushroom::doSomething() {

}

Star::Star(int x, int y) :Actor(IID_STAR, x, y, 0, 1) {

}

Star::~Star() {

}

void Star::doSomething() {

}

PiranhaFireball::PiranhaFireball(int x, int y, int dir) :Actor(IID_PIRANHA_FIRE, x, y, dir, 1) {

}

PiranhaFireball::~PiranhaFireball() {

}

void PiranhaFireball::doSomething() {

}

PeachFireball::PeachFireball(int x, int y, int dir) :Actor(IID_PEACH_FIRE, x, y, dir, 1) {

}

PeachFireball::~PeachFireball() {

}

void PeachFireball::doSomething() {

}

Shell::Shell(int x, int y, int dir) :Actor(IID_SHELL, x, y, dir, 1) {

}

Shell::~Shell() {

}

void Shell::doSomething() {

}

Goomba::Goomba(int x, int y) :Actor(IID_GOOMBA, x, y, rand() % 2 == 0 ? 0 : 180) { // 0 degrees if rand returns even number, 180 if odd

}

Goomba::~Goomba() {

}

void Goomba::doSomething() {

}

Koopa::Koopa(int x, int y) :Actor(IID_KOOPA, x, y, rand() % 2 == 0 ? 0 : 180) {

}

Koopa::~Koopa() {

}

void Koopa::doSomething() {

}

Piranha::Piranha(int x, int y) :Actor(IID_PIRANHA, x, y, rand() % 2 == 0 ? 0 : 180) {
	m_delay = 0;
}

Piranha::~Piranha() {

}

void Piranha::doSomething() {

}