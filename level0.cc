#include "level0.h"
#include "action.h"
#include "normal.h"
using namespace std;

Level0::Level0(string file): blocks {ifstream (file)} {}

char Level0::generatenext(int seed) {
    char c;
    blocks >> c;
    return c;
}

Action *Level0::generateaction() {
    Action *a = new Normal();
    return a;
}

void Level0::nocleareffect(Grid *) {}

Level0::~Level0() {}
