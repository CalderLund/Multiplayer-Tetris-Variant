#include "level1.h"
#include "normal.h"
#include <cstdlib>
#include <time.h>

Level1::Level1() {}

char Level1::generatenext(int seed) {
    char c;

    srand(time(nullptr));
    int n = rand() % 12;
    if (n == 0) c = 'S';           // 1/12 prob
    if (n == 1) c = 'Z';           
    if (n == 2 || n == 3) c = 'T'; // 1/6 prob
    if (n == 4 || n == 5) c = 'L';
    if (n == 6 || n == 7) c = 'J';
    if (n == 8 || n == 9) c = 'O';
    if (n == 10 || n == 11) c = 'I';
    return c;
}

Action *Level1::generateaction() {
    Action *a = new Normal();
    return a;
}

void Level1::nocleareffect(Grid *) {}
