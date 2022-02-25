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

AutoActor::AutoActor(StudentWorld* world, int x, int y, int imageID, int dir) : Actor(world, imageID, x, y, dir, 1) {}

AutoActor::~AutoActor() {

}

void AutoActor::move() {
	if (getWorld()->objectOverlaps(getX(), getY() - 2) == nullptr || !(getWorld()->objectOverlaps(getX(), getY() - 2)->blocking())) { // nothing blocking right side of fireball
		if (getWorld()->objectOverlaps(getX() + SPRITE_WIDTH - 1, getY() - 2) == nullptr || !(getWorld()->objectOverlaps(getX() + SPRITE_WIDTH - 1, getY() - 2)->blocking())) {
			moveTo(getX(), getY() - 2);
		}
	}
	if (getDirection() == 0) {
		if (getWorld()->objectOverlaps(getX() + SPRITE_WIDTH + 1, getY()) == nullptr || !(getWorld()->objectOverlaps(getX() + SPRITE_WIDTH + 1, getY())->blocking())) {
			moveTo(getX() + 2, getY());
		}
		else {
			setDirection(180);
		}
	}
	else if (getDirection() == 180) {
		if (getWorld()->objectOverlaps(getX() - 2, getY()) == nullptr || !(getWorld()->objectOverlaps(getX() - 2, getY())->blocking())) {
			moveTo(getX() - 2, getY());
		}
		else {
			setDirection(0);
		}
	}
}

Fireball::Fireball(StudentWorld* world, int x, int y, int imageID, int dir) : AutoActor(world, x, y, imageID, dir) {}

Fireball::~Fireball() {

}

void Fireball::move() {
	if (getWorld()->objectOverlaps(getX(), getY() - 2) == nullptr || !(getWorld()->objectOverlaps(getX(), getY() - 2)->blocking())) { // nothing blocking right side of fireball
		if (getWorld()->objectOverlaps(getX() + SPRITE_WIDTH - 1, getY() - 2) == nullptr || !(getWorld()->objectOverlaps(getX() + SPRITE_WIDTH - 1, getY() - 2)->blocking())) {
			moveTo(getX(), getY() - 2);
		}
	}
	if (getDirection() == 0) {
		if (getWorld()->objectOverlaps(getX() + SPRITE_WIDTH + 1, getY()) == nullptr || !(getWorld()->objectOverlaps(getX() + SPRITE_WIDTH + 1, getY())->blocking())) {
			moveTo(getX() + 2, getY());
		}
		else {
			kill();
		}
	}
	else if (getDirection() == 180) {
		if (getWorld()->objectOverlaps(getX() - 2, getY()) == nullptr || !(getWorld()->objectOverlaps(getX() - 2, getY())->blocking())) {
			moveTo(getX() - 2, getY());
		}
		else {
			kill();
		}
	}
}

Enemy::Enemy(StudentWorld* world, int imageID, int x, int y) : Actor(world, imageID, x, y, rand() % 2 == 0 ? 0 : 180) {}

Enemy::~Enemy() {}

void Enemy::doSomething() {
	if (alive()) {
		if (getWorld()->isPeachAt(getX(), getY())) {
			getWorld()->getPeach()->bonk();
			return;
		}

		if (getDirection() == 0) {
			if (getWorld()->objectOverlaps(getX() + SPRITE_WIDTH, getY()) != nullptr && getWorld()->objectOverlaps(getX() + SPRITE_WIDTH, getY())->blocking()) {
				setDirection(180);

			}
			else if (getWorld()->objectAt(getX() + SPRITE_WIDTH, getY() - 3) == nullptr || !(getWorld()->objectAt(getX() + SPRITE_WIDTH, getY() - 3)->blocking())) {
				setDirection(180);
			}
			else {
				moveTo(getX() + 1, getY());
			}

		} else if (getDirection() == 180) {
			if (getWorld()->objectOverlaps(getX() - 1, getY()) != nullptr && getWorld()->objectOverlaps(getX() - 1, getY())->blocking()) {
				setDirection(0);
			}
			else if (getWorld()->objectAt(getX() - 1, getY() - 3) == nullptr || !(getWorld()->objectAt(getX() - 1, getY() - 3)->blocking())) {
				setDirection(0);
			}
			else {
				moveTo(getX() - 1, getY());
			}
		}

	}

}

void Enemy::bonk() { // only peach will call this method
	if (getWorld()->getPeach()->hasStarPower()) {

		getWorld()->playSound(SOUND_PLAYER_KICK);
		getWorld()->increaseScore(100);
		kill();
	}
}

void Enemy::damage() {
	getWorld()->increaseScore(100);
	kill();
}

Peach::Peach(StudentWorld* world, int x, int y) : Actor(world, IID_PEACH, x, y) {
	m_hp = 1;
	m_shootPower = m_jumpPower = true;
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
		Actor* upObjLeft = getWorld()->objectOverlaps(getX(), getY() + SPRITE_HEIGHT + 3);
		Actor* upObjRight = getWorld()->objectOverlaps(getX() + 4, getY() + SPRITE_HEIGHT + 3);
		if (upObjLeft != nullptr && upObjLeft->blocking()) {
			getWorld()->objectOverlaps(upObjLeft->getX(), upObjLeft->getY())->bonk();
			m_remainingJumpDistance = 0;
		}
		else if (upObjRight != nullptr && upObjRight->blocking()) {
			getWorld()->objectOverlaps(upObjRight->getX(), upObjRight->getY())->bonk();
			m_remainingJumpDistance = 0;
		}
		else {
			moveTo(getX(), getY() + 4);
			m_remainingJumpDistance--;
		}
	}
	else if (getWorld()->objectOverlaps(getX(), getY() - 3) == nullptr || !(getWorld()->objectOverlaps(getX(), getY() - 3)->blocking())) {
		if (getWorld()->objectOverlaps(getX() + 4, getY() - 3) == nullptr || !(getWorld()->objectOverlaps(getX() + 4, getY() - 3)->blocking())) {
			moveTo(getX(), getY() - 4);
		}
	}

	int key;
	if (!getWorld()->getKey(key)) {
		return;
	}

	if (key == KEY_PRESS_LEFT) {
		Actor* leftObj = getWorld()->objectOverlaps(getX() - 4, getY());
		if(leftObj == nullptr || !leftObj->blocking()) { // move left
			setDirection(180);
			moveTo(getX() - 4, getY());
		}
		else if(leftObj != nullptr) {
			leftObj->bonk();
		}
	}
	else if (key == KEY_PRESS_RIGHT) {
		Actor* rightObj = getWorld()->objectAt(getX() + SPRITE_WIDTH, getY());
		if (rightObj == nullptr || !rightObj->blocking()) { // move right
			setDirection(0);
			moveTo(getX() + 4, getY());
		}
		else if (rightObj != nullptr) {
			rightObj->bonk();
		}
	}
	else if (key == KEY_PRESS_UP) {
		Actor* underObj = getWorld()->objectOverlaps(getX(), getY() - 1);
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
			if (m_remainingRechargeTime == 0) {
				int fireballx = getDirection() == 0 ? getX() + 4 : getX() - 4;
				getWorld()->addActor(new PeachFireball(getWorld(), fireballx, getY(), getDirection()));
				m_remainingRechargeTime = 8;
			}
			
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

void Peach::setHP(int hp) {
	m_hp = hp;
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

Flower::Flower(StudentWorld* world, int x, int y) : AutoActor(world, x, y, IID_FLOWER) {}

Flower::~Flower() {

}

void Flower::doSomething() {
	if (getWorld()->isPeachAt(getX(), getY())) {
		getWorld()->increaseScore(50);
		getWorld()->getPeach()->giveShootPower();
		getWorld()->getPeach()->setHP(2);
		kill();
		getWorld()->playSound(SOUND_PLAYER_POWERUP);
		return;
	}

	move();
}

Mushroom::Mushroom(StudentWorld* world, int x, int y) : AutoActor(world, x, y, IID_MUSHROOM) {}

Mushroom::~Mushroom() {

}

void Mushroom::doSomething() {
	if (getWorld()->isPeachAt(getX(), getY())) {
		getWorld()->increaseScore(75);
		getWorld()->getPeach()->giveJumpPower();
		getWorld()->getPeach()->setHP(2);
		kill();
		getWorld()->playSound(SOUND_PLAYER_POWERUP);
		return;
	}

	move();
}

Star::Star(StudentWorld* world, int x, int y) : AutoActor(world, x, y, IID_STAR) {}

Star::~Star() {

}

void Star::doSomething() {
	if (getWorld()->isPeachAt(getX(), getY())) {
		getWorld()->increaseScore(100);
		getWorld()->getPeach()->giveStarPower(150);
		getWorld()->getPeach()->setHP(2);
		kill();
		getWorld()->playSound(SOUND_PLAYER_POWERUP);
		return;
	}

	move();
}

PiranhaFireball::PiranhaFireball(StudentWorld* world, int x, int y, int dir) : Fireball(world, x, y, IID_PIRANHA_FIRE, dir) {

}

PiranhaFireball::~PiranhaFireball() {

}

void PiranhaFireball::doSomething() {
	if (getWorld()->isPeachAt(getX(), getY())) {
		getWorld()->getPeach()->bonk();
		kill();
		return;
	}

	move();
}

PeachFireball::PeachFireball(StudentWorld* world, int x, int y, int dir) : Fireball(world, x, y, IID_PEACH_FIRE, dir) {}

PeachFireball::~PeachFireball() {

}

void PeachFireball::doSomething() {
	cout << "Fireball: " << endl << getX() << endl << getY() << endl << endl;
	if (getWorld()->objectOverlaps(getX(), getY()) != nullptr &&
		getWorld()->objectOverlaps(getX(), getY())->damageable() &&
		!getWorld()->isPeachAt(getX(), getY())) {
		getWorld()->objectOverlaps(getX(), getY())->damage();
		kill();
		return;
	}

	move();
}

Shell::Shell(StudentWorld* world, int x, int y, int dir) : AutoActor(world, x, y, IID_SHELL, dir) {}

Shell::~Shell() {

}

void Shell::doSomething() {
	if (getWorld()->objectOverlaps(getX(), getY()) != nullptr &&
		getWorld()->objectOverlaps(getX(), getY())->damageable() &&
		!getWorld()->isPeachAt(getX(), getY())) {
		getWorld()->objectOverlaps(getX(), getY())->damage();
		kill();
		return;
	}

	move();
}

Goomba::Goomba(StudentWorld* world, int x, int y) : Enemy(world, IID_GOOMBA, x, y) { // 0 degrees if rand returns even number, 180 if odd

}

Goomba::~Goomba() {

}

Koopa::Koopa(StudentWorld* world, int x, int y) : Enemy(world, IID_KOOPA, x, y) {

}

Koopa::~Koopa() {

}

void Koopa::bonk() {
	Enemy::bonk();
	getWorld()->addActor(new Shell(getWorld(), getX(), getY(), getDirection()));
}

void Koopa::damage() {
	Enemy::damage();
	getWorld()->addActor(new Shell(getWorld(), getX(), getY(), getDirection()));
}

Piranha::Piranha(StudentWorld* world, int x, int y) : Actor(world, IID_PIRANHA, x, y, rand() % 2 == 0 ? 0 : 180) {
	m_delay = 0;
}

Piranha::~Piranha() {

}

void Piranha::doSomething() {

}