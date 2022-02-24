#include "Actor.h"
#include "StudentWorld.h"

Actor::Actor(StudentWorld* world, int imageID, int x, int y, int dir, int depth, double size)
:GraphObject(imageID, x, y, dir, depth, size) {
	m_alive = true;
	m_world = world;
};

Actor::~Actor() {};

void Actor::doSomething() {
	return;
}

void Actor::bonk() {
	return;
}

Peach::Peach(StudentWorld* world, int x, int y) : Actor(world, IID_PEACH, x, y) {
	m_hp = 1;
	m_shootPower = m_jumpPower = false;
	m_remainingJumpDistance = 0;
	m_remainingStarInvincibilityTicks = 0;
	m_remainingTempInvincibilityTicks = 0;
	m_remainingRechargeTime = 0;
}

Peach::~Peach() {

}

void Peach::doSomething() {
	if (!alive()) { // peach died
		return; 
	}

	// temporary effects
	if (m_remainingStarInvincibilityTicks > 0) m_remainingStarInvincibilityTicks--;
	if (m_remainingTempInvincibilityTicks > 0) m_remainingTempInvincibilityTicks--;
	if (m_remainingRechargeTime > 0) m_remainingRechargeTime--;

	if (m_remainingJumpDistance > 0) {
		Actor* upObj = getWorld()->objectAt(getX(), getY() + 4);
		if (upObj != nullptr && upObj->blocking()) {
			getWorld()->objectAt(getX(), getY() + 4)->bonk();
			m_remainingJumpDistance = 0;
		}
		else {
			moveTo(getX(), getY() + 4);
			m_remainingJumpDistance--;
		}
	}
	else if (getWorld()->objectAt(getX(), getY() - 3) == nullptr || 
			 !(getWorld()->objectAt(getX(), getY() - 3)->blocking())) {
		moveTo(getX(), getY() - 4);
	}

	int key;
	if (!getWorld()->getKey(key)) {
		return;
	}

	if (key == KEY_PRESS_LEFT) {
		Actor* leftObj = getWorld()->objectAt(getX() - 4, getY());
		if(leftObj == nullptr || !leftObj->blocking()) { // move left
			setDirection(180);
			moveTo(getX() - 4, getY());
		}
		else if(leftObj != nullptr) {
			leftObj->bonk();
		}
	}
	else if (key == KEY_PRESS_RIGHT) {
		Actor* rightObj = getWorld()->objectAt(getX() + 4, getY());
		if (rightObj == nullptr || !rightObj->blocking()) { // move right
			setDirection(0);
			moveTo(getX() + 4, getY());
		}
		else if (rightObj != nullptr) {
			rightObj->bonk();
		}
	}
	else if (key == KEY_PRESS_UP) {
		Actor* underObj = getWorld()->objectAt(getX(), getY() - 1);
		if (underObj != nullptr && underObj->blocking()) {
			getWorld()->playSound(SOUND_PLAYER_JUMP);
			if (m_jumpPower) {
				m_remainingJumpDistance = 12;
			}
			else {
				m_remainingJumpDistance = 8;
			}
		}
	}
	else if (key == KEY_PRESS_SPACE) {
		if (m_shootPower) {
			getWorld()->playSound(SOUND_PLAYER_FIRE);
			m_remainingRechargeTime = 8;
			int fireballx = getDirection() == 0 ? getX() + 4 : getX() - 4;
			getWorld()->addActor(new PeachFireball(getWorld(), fireballx, getY(), getDirection()));
		}
	}
}

void Peach::bonk() {
	if (m_remainingTempInvincibilityTicks == 0 && m_remainingStarInvincibilityTicks == 0) {
		m_hp--;
		m_remainingTempInvincibilityTicks = 10;
		m_shootPower = m_jumpPower = false;
		if (m_hp > 0) {
			getWorld()->playSound(SOUND_PLAYER_HURT);
		}
		else {
			kill();
		}
	}
}

void Peach::giveStarPower(int n) {
	m_remainingStarInvincibilityTicks = n;
}

void Peach::giveJumpPower() {
	m_jumpPower = true;
}

void Peach::giveShootPower() {
	m_shootPower = true;
}

void Peach::increaseHP() {
	m_hp++;
}

Block::Block(StudentWorld* world, int x, int y, char goodie) : Actor(world, IID_BLOCK, x, y, 0, 2, 1) {
	m_goodie = goodie;
	m_released = false;
}

Block::~Block() {

}

void Block::Bonk() {
	if (m_goodie == 'n' || m_released) {
		getWorld()->playSound(SOUND_PLAYER_BONK);
	}
	else if (m_goodie != 'n' && !m_released) {
		m_released = true;
		getWorld()->playSound(SOUND_POWERUP_APPEARS);
		if (m_goodie == '^') {
			getWorld()->addActor(new Mushroom(getWorld(), getX(), getY() + 8));
		} 
		else if (m_goodie == '*') {
			getWorld()->addActor(new Star(getWorld(), getX(), getY() + 8));
		}
		else if (m_goodie == '%') {
			getWorld()->addActor(new Flower(getWorld(), getX(), getY() + 8));
		}
	}
}

Pipe::Pipe(StudentWorld* world, int x, int y) : Actor(world, IID_PIPE, x, y, 0, 2, 1) {}

Pipe::~Pipe() {

}

Flag::Flag(StudentWorld* world, int x, int y) : Actor(world, IID_FLAG, x, y, 0, 1) {}

Flag::~Flag() {

}

void Flag::doSomething() {
	if (alive()) {
		if (getWorld()->isPeachAt(getX(), getY())) {
			getWorld()->increaseScore(1000);
			kill();
			getWorld()->finishedLevel();
		}
	}
}

Mario::Mario(StudentWorld* world, int x, int y) : Actor(world, IID_MARIO, x, y, 0, 1) {}

Mario::~Mario() {

}

void Mario::doSomething() {
	if (alive()) {
		if (getWorld()->isPeachAt(getX(), getY())) {
			getWorld()->increaseScore(1000);
			kill();
			getWorld()->wonGame();
		}
	}
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