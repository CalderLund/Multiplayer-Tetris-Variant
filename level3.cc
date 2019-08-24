#include "level3.h"
#include "levelheavy.h"
#include <cstdlib>
#include "normal.h"
#include <time.h>

Level3::Level3() {}

char Level3::generatenext(int seed) {
    char c;
    srand(time(nullptr));
    int n = rand() % 9;
    if (n == 0 || n == 1) c = 'S';      // 2/9 prob
    if (n == 2 || n == 3) c = 'Z';           
    if (n == 4) c = 'T';                // 1/9 prob
    if (n == 5) c = 'L';
    if (n == 6) c = 'J';
    if (n == 7) c = 'O';
    if (n == 8) c = 'I';
    return c;
}

Action *Level3::generateaction() {
    Action *a = new LevelHeavy(new Normal);
    return a;
}

void Level3::nocleareffect(Grid *) {}
