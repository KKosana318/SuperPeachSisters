#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h> 
#include <iterator>
using namespace std;

GameWorld* createStudentWorld(string assetPath) {
	return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath) : GameWorld(assetPath) {
    peach = nullptr;
    m_finishedLevel = m_wonGame = false;
}

StudentWorld::~StudentWorld() {
    cleanUp();
}

int StudentWorld::init() {
    Level lev(assetPath());

    m_finishedLevel = false;

    ostringstream oss;
    oss << "level";
    if (getLevel() < 10) {
        oss << 0;
    }
    oss << getLevel() << ".txt";
    cout << oss.str() << endl;

    string level_file = oss.str();
    Level::LoadResult result = lev.loadLevel(level_file);

    if (result == Level::load_fail_file_not_found || result == Level::load_fail_bad_format) {
        cerr << "Could not find level01.txt data file" << endl;
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level::load_success) {
        for (int i = 0; i < GRID_WIDTH; i++) {
            for (int j = 0; j < GRID_HEIGHT; j++) {
                int width = i * SPRITE_WIDTH;
                int height = j * SPRITE_HEIGHT;
                Level::GridEntry ge = lev.getContentsOf(i, j);

                switch (ge) {
                case Level::empty:
                    break;
                case Level::peach:
                    peach = new Peach(this, width, height);
                    break;
                case Level::block:
                    actors.push_back(new Block(this, width, height));
                    break;
                case Level::star_goodie_block:
                    actors.push_back(new Block(this, width, height, '*'));
                    break;
                case Level::mushroom_goodie_block:
                    actors.push_back(new Block(this, width, height, '^'));
                    break;
                case Level::flower_goodie_block:
                    actors.push_back(new Block(this, width, height, '%'));
                    break;
                case Level::pipe:
                    actors.push_back(new Pipe(this, width, height));
                    break;
                case Level::flag:
                    actors.push_back(new Flag(this, width, height));
                    break;
                case Level::mario:
                    actors.push_back(new Mario(this, width, height));
                case Level::goomba:
                    actors.push_back(new Goomba(this, width, height));
                    break;
                case Level::koopa:
                    actors.push_back(new Koopa(this, width, height));
                    break;
                case Level::piranha:
                    actors.push_back(new Piranha(this, width, height));
                    break;
                }
            }
        }
    }

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {
    peach->doSomething();

    for (auto const& actor : actors) {
        actor->doSomething();
        if (!peach->alive()) {
            playSound(SOUND_PLAYER_DIE);
            return GWSTATUS_PLAYER_DIED;
        }
        if (m_wonGame) {
            playSound(SOUND_GAME_OVER);
            return GWSTATUS_PLAYER_WON;
        }
        if (m_finishedLevel) {
            playSound(SOUND_FINISHED_LEVEL);
            return GWSTATUS_FINISHED_LEVEL;
        }
    }


    // remove dead objects
    vector<Actor*>::iterator i = actors.begin();
    while (i != actors.end()) {
        if (!(*i)->alive()) {
            delete* i;
            i = actors.erase(i);
        }
        else {
            i++;
        }
    }

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() {
    for (vector<Actor*>::iterator i = actors.begin(); i != actors.end(); i++) {
        delete* i;
    }

    while (!actors.empty()) {
        actors.erase(actors.begin());
    }

    delete peach;
}

// returns first non-peach object in vector at x, y or nullptr if no such object
Actor* StudentWorld::objectAt(int x, int y) { 
    for (vector<Actor*>::iterator i = actors.begin(); i != actors.end(); i++) {
        int firstX = (*i)->getX(); // 80
        int secondX = x; // 108
        int firstY = (*i)->getY(); // 32
        int secondY = y; // 38
        if (abs(firstX - secondX) < SPRITE_WIDTH && abs(firstY - secondY) < SPRITE_HEIGHT && firstX <= secondX && firstY <= secondY) {
            return *i;
        }
    }

    return nullptr;
}

// returns first non-peach object that overlaps with the object starting at x,y or nullptr if no such object
Actor* StudentWorld::objectOverlaps(int x, int y) {
    for (vector<Actor*>::iterator i = actors.begin(); i != actors.end(); i++) {
        int firstX = (*i)->getX();
        int secondX = x;
        int firstY = (*i)->getY();
        int secondY = y;
        if (abs(firstX - secondX) < SPRITE_WIDTH && abs(firstY - secondY) < SPRITE_HEIGHT && firstX <= secondX && firstY <= secondY) {
            return *i;
        }
    }

    return nullptr;
}



bool StudentWorld::isPeachAt(int x, int y) {
    return (abs(peach->getX() - x) < SPRITE_WIDTH && abs(peach->getY() - y) < SPRITE_HEIGHT);
}

void StudentWorld::addActor(Actor* actor) {
    actors.push_back(actor);
}

bool StudentWorld::isPeach(Actor* actor) {
    return actor == peach;
}

Peach* StudentWorld::getPeach() {
    return peach;
}

void StudentWorld::finishedLevel() {
    m_finishedLevel = true;
}

void StudentWorld::wonGame() {
    m_wonGame = true;
}

