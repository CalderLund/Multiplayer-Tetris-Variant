#include "level5.h"
#include "levelheavy.h"
#include "lock.h"
#include <cstdlib>
#include "cell.h"
#include "normal.h"
#include <iostream>
#include <time.h>

using namespace std;

char Level5::generatenext(int seed) {
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

Action *Level5::generateaction() {
    Action *a = new Lock(new LevelHeavy(new Normal));
    return a;
}

void Level5::nocleareffect(Grid *g) {
  int count = g->getnoclearcount();
    if (count != 0 && count  % 5 == 0) {
        int center = g->getWidth() / 2; // for example, grid width is 11
                                        // center = 5, 0.1.2.3.4  5  6.7.8.9.10
        int height = g->getHeight();
        
        for (int i = 0; i < height; i++) {
            if (g->typeAt(center, i) == ' ' &&     // if empty and next exists
                ((g->typeAt(center, i < height - 1 ? i+1 : i) != ' ' && // and next is something or i might be height - 1 (in which case i + 1 segfaults) or
                  i+1 < height) ||                 // next doesn't exist
                 (i+1 == height))) {
                g->setAt(center, i, '*');
                g->get_cell(center, i)->draw();
                break;
            }
        }
    }
}
