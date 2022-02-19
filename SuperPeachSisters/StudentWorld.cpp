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
}

StudentWorld::~StudentWorld() {
    cleanUp();
}

int StudentWorld::init() {
    Level lev(assetPath());

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
                    peach = new Peach(width, height);
                    break;
                case Level::block:
                    actors.push_back(new Block(width, height));
                    break;
                case Level::star_goodie_block:
                    actors.push_back(new Block(width, height, '*'));
                    break;
                case Level::mushroom_goodie_block:
                    actors.push_back(new Block(width, height, '^'));
                    break;
                case Level::flower_goodie_block:
                    actors.push_back(new Block(width, height, '%'));
                    break;
                case Level::pipe:
                    actors.push_back(new Pipe(width, height));
                    break;
                case Level::flag:
                    actors.push_back(new Flag(width, height));
                    break;
                case Level::mario:
                    actors.push_back(new Mario(width, height));
                case Level::goomba:
                    actors.push_back(new Goomba(width, height));
                    break;
                case Level::koopa:
                    actors.push_back(new Koopa(width, height));
                    break;
                case Level::piranha:
                    actors.push_back(new Piranha(width, height));
                    break;
                }
            }
        }
    }

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {
    int key;
    getKey(key);
    peach->setKey(key);
    peach->doSomething();

    for (auto const& actor : actors) {
        actor->doSomething();
        if (!peach->alive()) {
            playSound(SOUND_PLAYER_DIE);
            return GWSTATUS_PLAYER_DIED;
        }
    }

    // remove dead objects
    for (vector<Actor*>::iterator i = actors.begin(); i != actors.end(); i++) {
        if ((*i)->alive()) {
            Actor* temp = *i;
            actors.erase(i);
            delete temp;
        }
    }

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() {
    for (vector<Actor*>::iterator i = actors.begin(); i != actors.end(); i++) {
        Actor* temp = *i;
        actors.erase(i);
        delete temp;
    }

    delete peach;
}

bool StudentWorld::checkOverlap(Actor* first, Actor* second) {
    int firstX = first->getX();
    int secondX = second->getX();
    int firstY = first->getY();
    int secondY = second->getY();

    return abs(firstX - secondX) < SPRITE_WIDTH && abs(firstY - secondY) < SPRITE_HEIGHT;
}
