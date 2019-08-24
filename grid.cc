#include <string>
#include "grid.h"
#include "block.h"

using namespace std;

Grid::Grid(bool textOnly) : grid_window{textOnly ? nullptr : new Xwindow{350, 730}} {}

Grid::~Grid() {
  delete grid_window;

  for (int i = 0; i < blocks.size(); i++) {
    if (blocks[i]) {
      delete blocks[i];
      blocks[i] = nullptr;
    }
  }
}

void Grid::init(int l, int w, int h) {
  if (w < 4) w = 4;   // needs this space for I blocks
  if (h < 7) h = 7;   // minimum height and width is important because height
  // and width can be specified by client at start of game
  // initialize values
  level = l;
  score = 0;
  highest_score = 0;
  noclearcount = 0;
  width = w;
  height = h;

  // draw the grid
  if (grid_window) {
    grid_window->drawLine(9, 89, 341, 89);
    grid_window->drawLine(9, 89, 9, 631);
    grid_window->drawLine(9, 631, 341, 631);
    grid_window->drawLine(341, 89, 341, 631);
    grid_window->drawStringFont(10, 20, "Level:", "8x16");
    grid_window->drawStringFont(10, 45, "Score:", "8x16");
    grid_window->drawStringFont(10, 70, "Highest Score:", "8x16", Xwindow::Red);
    grid_window->drawStringFont(10, 655, "Next Block:", "8x16");
    string score_str = to_string(score);
    string level_str = to_string(level);
    string highest_score_str = to_string(highest_score);
    grid_window->drawStringFont(60, 20, score_str, "8x16");
    grid_window->drawStringFont(60, 45, level_str, "8x16");
    grid_window->drawStringFont(125, 70, highest_score_str, "8x16", Xwindow::Red);
  }

  // Actually create theGrid
  for (int i = 0; i < h; i++) {
    vector<Cell> v;
    for (int j = 0; j < w; j++) {
      Cell c {j, i, grid_window};
      v.emplace_back(c);
      //   c.draw();
    }
    theGrid.emplace_back(v);
  } 
}

int Grid::checkfilled() {
    // count the number of rows that are filled
    int filled = 0;
    for (int i = 0; i < height; ++i) {
        // determine if the row is filled or not
        bool unfilled = false;
        for (int j = 0; j < width; ++j) {
            if (theGrid[i][j].get_type() == ' ') { // calls Cell::get_type() 
                unfilled = true;
                break;
            }
        }
        // if the row is filled, increment filled variable, add to score
        if (!(unfilled)) {
            ++filled;
            // loop through the cells in the row that has been completely filled
            for (int k = 0; k < width; ++k) {
                if (theGrid[i][k].get_block()) {
                    int num = (theGrid[i][k].get_block())->get_numcell(); // number of cells in the block of the current cell
                    if (num == 1) {
                        // if the current cell is the last cell in its block, update the score
                        int points = (theGrid[i][k].get_block())->get_spawnlevel() + 1;
                        int new_score = score + points * points;
                        display_score(new_score);
                        score = new_score;
                        theGrid[i][k].get_block()->set_numcell(num - 1);
                        
                    }
                    else {
                        theGrid[i][k].get_block()->set_numcell(num - 1);
                    }
                }
            }
            // clear the completed row
            for (int a = 0; a < width; ++a) {
                theGrid[i][a].undraw();
            }
            theGrid[i].clear();
            theGrid.erase(theGrid.begin() + i);
            // create a new row and push it to the back of theGrid
            vector<Cell> v;
            for (int q = 0; q < width; ++q) {
                // create a new first row
                v.emplace_back(Cell{q, 0, grid_window});
            }
            theGrid.insert(theGrid.begin(), v);
            this->refresh();  // resets every cell's coordinate 
        }
    }

    if (filled == 0) {
        ++noclearcount;
    }
    else {
        int points = level + filled;
        int new_score = score + points * points;
        display_score(new_score);
        score = new_score;
        noclearcount = 0;
    }
  // if the current score exceeds the highest score, update the highest score
    if (score > highest_score) {
        display_highest_score(score);
        highest_score = score;
    }

    return filled;
}

string Grid::printRow(int i) {
  string s = "";
  for (int j = 0; j < width; ++j) {
    if (i >= 0 && i < height){
      char c = typeAt(j, i);
      s += c;
    }
    else s += '-';
  }
  return s;
}

int Grid::getHeight() {
  return height;
}

int Grid::getWidth() {
  return width;
}

void Grid::refresh() {
  for (int i = height - 1; i > 0 ; --i) {
    for (int j = 0; j < width; ++j) {
      theGrid[i][j].undraw();
      theGrid[i][j].set_x(j);
      theGrid[i][j].set_y(i);
      theGrid[i][j].draw();
    }
  }
}

char Grid::typeAt(int x, int y) {
  return theGrid[y][x].get_type();
}

void Grid::setAt(int x, int y, char type) {
  theGrid[y][x].set_type(type);
}

void Grid::updatescore(int s) {
  score = s;
}

int Grid::getscore() {
  return score;
}

int Grid::getnoclearcount() {
  return noclearcount;
}

void Grid::setlevel(int l) {
  level = l;
}

int Grid::getlevel() {
  return level;
}

Cell *Grid::get_cell(int x, int y) {
  return &(theGrid[y][x]);
}

int Grid::get_highest_score() {
  return highest_score;
}

void Grid::display_score(int s) {
  if (grid_window) {
    string score_str = to_string(score);
    string new_score_str = to_string(s);
    grid_window->drawStringFont(60, 45, score_str, "8x16", Xwindow::White);
    grid_window->drawStringFont(60, 45, new_score_str, "8x16");
  }
}

void Grid::display_level(int lvl) {
  if (grid_window) {
    string level_str = to_string(level);
    string new_level_str = to_string(lvl);
    grid_window->drawStringFont(60, 20, level_str, "8x16", Xwindow::White);
    grid_window->drawStringFont(60, 20, new_level_str, "8x16");
  }
}

void Grid::display_highest_score(int hs) {
  if (grid_window) {
    string hs_str = to_string(highest_score);
    string new_hs_str = to_string(hs);
    grid_window->drawStringFont(125, 70, hs_str, "8x16", Xwindow::White);
    grid_window->drawStringFont(125, 70, new_hs_str, "8x16", Xwindow::Red);
  }
}

void Grid::display_next(char c) { 
  if (grid_window) {
    if (c == 'I') {
      grid_window->fillRectangle(150, 638, 30, 30, Xwindow::Red);
      grid_window->fillRectangle(180, 638, 30, 30, Xwindow::Red);
      grid_window->fillRectangle(210, 638, 30, 30, Xwindow::Red);
      grid_window->fillRectangle(240, 638, 30, 30, Xwindow::Red);
    }
    else if (c == 'L') {
      grid_window->fillRectangle(210, 638, 30, 30, Xwindow::Green);
      grid_window->fillRectangle(150, 668, 30, 30, Xwindow::Green);
      grid_window->fillRectangle(180, 668, 30, 30, Xwindow::Green);
      grid_window->fillRectangle(210, 668, 30, 30, Xwindow::Green);
    }
    else if (c == 'Z') {
      grid_window->fillRectangle(150, 638, 30, 30, Xwindow::Blue);
      grid_window->fillRectangle(180, 638, 30, 30, Xwindow::Blue);
      grid_window->fillRectangle(180, 668, 30, 30, Xwindow::Blue);
      grid_window->fillRectangle(210, 668, 30, 30, Xwindow::Blue);
    }
    else if (c == 'S') {
      grid_window->fillRectangle(180, 638, 30, 30, Xwindow::Yellow);
      grid_window->fillRectangle(210, 638, 30, 30, Xwindow::Yellow);
      grid_window->fillRectangle(150, 668, 30, 30, Xwindow::Yellow);
      grid_window->fillRectangle(180, 668, 30, 30, Xwindow::Yellow);
    }
    else if (c == 'O') {
      grid_window->fillRectangle(150, 638, 30, 30, Xwindow::Magenta);
      grid_window->fillRectangle(180, 638, 30, 30, Xwindow::Magenta);
      grid_window->fillRectangle(150, 668, 30, 30, Xwindow::Magenta);
      grid_window->fillRectangle(180, 668, 30, 30, Xwindow::Magenta);
    }
    else if (c == 'T') {
      grid_window->fillRectangle(150, 638, 30, 30, Xwindow::Cyan);
      grid_window->fillRectangle(180, 638, 30, 30, Xwindow::Cyan);
      grid_window->fillRectangle(210, 638, 30, 30, Xwindow::Cyan);
      grid_window->fillRectangle(180, 668, 30, 30, Xwindow::Cyan);
    }
    else if (c == 'J') {
      grid_window->fillRectangle(150, 638, 30, 30, Xwindow::Orange);
      grid_window->fillRectangle(150, 668, 30, 30, Xwindow::Orange);
      grid_window->fillRectangle(180, 668, 30, 30, Xwindow::Orange);
      grid_window->fillRectangle(210, 668, 30, 30, Xwindow::Orange);
    }
  }
}

void Grid::erase_next(char c) {
  if (grid_window) {
    if (c == 'I') {
      grid_window->fillRectangle(150, 638, 30, 30, Xwindow::White);
      grid_window->fillRectangle(180, 638, 30, 30, Xwindow::White);
      grid_window->fillRectangle(210, 638, 30, 30, Xwindow::White);
      grid_window->fillRectangle(240, 638, 30, 30, Xwindow::White);
    }
    else if (c == 'L') {
      grid_window->fillRectangle(210, 638, 30, 30, Xwindow::White);
      grid_window->fillRectangle(150, 668, 30, 30, Xwindow::White);
      grid_window->fillRectangle(180, 668, 30, 30, Xwindow::White);
      grid_window->fillRectangle(210, 668, 30, 30, Xwindow::White);
    }
    else if (c == 'Z') {
      grid_window->fillRectangle(150, 638, 30, 30, Xwindow::White);
      grid_window->fillRectangle(180, 638, 30, 30, Xwindow::White);
      grid_window->fillRectangle(180, 668, 30, 30, Xwindow::White);
      grid_window->fillRectangle(210, 668, 30, 30, Xwindow::White);
    }
    else if (c == 'S') {
      grid_window->fillRectangle(180, 638, 30, 30, Xwindow::White);
      grid_window->fillRectangle(210, 638, 30, 30, Xwindow::White);
      grid_window->fillRectangle(150, 668, 30, 30, Xwindow::White);
      grid_window->fillRectangle(180, 668, 30, 30, Xwindow::White);
    }
    else if (c == 'O') {
      grid_window->fillRectangle(150, 638, 30, 30, Xwindow::White);
      grid_window->fillRectangle(180, 638, 30, 30, Xwindow::White);
      grid_window->fillRectangle(150, 668, 30, 30, Xwindow::White);
      grid_window->fillRectangle(180, 668, 30, 30, Xwindow::White);
    }
    else if (c == 'T') {
      grid_window->fillRectangle(150, 638, 30, 30, Xwindow::White);
      grid_window->fillRectangle(180, 638, 30, 30, Xwindow::White);
      grid_window->fillRectangle(210, 638, 30, 30, Xwindow::White);
      grid_window->fillRectangle(180, 668, 30, 30, Xwindow::White);
    }
    else if (c == 'J') {
      grid_window->fillRectangle(150, 638, 30, 30, Xwindow::White);
      grid_window->fillRectangle(150, 668, 30, 30, Xwindow::White);
      grid_window->fillRectangle(180, 668, 30, 30, Xwindow::White);
      grid_window->fillRectangle(210, 668, 30, 30, Xwindow::White);
    }
  }
}

void Grid::blind() {
  if (grid_window)
    grid_window->fillRectangle(70, 210, 210, 270, Xwindow::Black);
}

void Grid::addBlock(Block &b) {
  blocks.emplace_back(&b);
}

void Grid::unblind() {
  if (grid_window) {
    for (int i = 4; i < 13; ++i) {
        for (int j = 2; j < 9; ++j) {
            if (theGrid[i][j].get_type() == ' ') {
                theGrid[i][j].undraw();
            }
            else {
                theGrid[i][j].draw();
            }
        }
    }
  }
}


void Grid::set_highest_score(int s) {
    display_highest_score(s);
    highest_score = s;
}
