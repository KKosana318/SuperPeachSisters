#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

GameWorld* createStudentWorld(string assetPath) {
	return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath) : GameWorld(assetPath) {
}

int StudentWorld::init() {
    Level lev(assetPath());

    ostringstream oss;
    oss << "level" << (getLevel() < 10 ? 0 : "") << getLevel() << ".txt";

    string level_file = oss.str();
    Level::LoadResult result = lev.loadLevel(level_file);

    if (result == Level::load_fail_file_not_found) {
        cerr << "Could not find level01.txt data file" << endl;
    }
    else if (result == Level::load_fail_bad_format) {
        cerr << "level01.txt is improperly formatted" << endl;
    }
    else if (result == Level::load_success) {

    }

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {
    decLives();
    return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp() {

}
