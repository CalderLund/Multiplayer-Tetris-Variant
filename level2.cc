#include "level2.h"
#include "normal.h"
#include <cstdlib>
#include <time.h>

char Level2::generatenext(int seed) {
    char c;
    srand(time(nullptr));
    int n = rand() % 7;
    if (n == 0) c = 'S';  // equal prob
    if (n == 1) c = 'Z';           
    if (n == 2) c = 'T';
    if (n == 3) c = 'L';
    if (n == 4) c = 'J';
    if (n == 5) c = 'O';
    if (n == 6) c = 'I';
    return c;
}

Action *Level2::generateaction() {
    Action *a = new Normal();
    return a;
}

void Level2::nocleareffect(Grid *) {}
