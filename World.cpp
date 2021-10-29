#include "World.hpp"
#include <algorithm>
#include <iostream>
#include <random>
using namespace std;


void World::initialize(int worldId) {
  mt19937 mt_rand(worldId);

  size = 10 + int(mt_rand() % 10);

  start = { int(mt_rand() % size), int(mt_rand() % size) };
  do {
    goal = { int(mt_rand() % size), int(mt_rand() % size) };
  } while(start == goal);

  int nblocks = size * size / 3;
  for (int ii = 0; ii < nblocks; ++ ii) {
    Point block = { int(mt_rand() % size), int(mt_rand() % size) };
    if (block != start && block != goal) {
      blocks.insert(block);
    }
  }
}

void World::display(const list<Point> & path) const {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (j == size-1) {
        if (start==Point{i,j}) {
        cout << "S";
        } else if (goal==Point{i,j}) {
        cout << "G";
        } else if (blocks.find(Point{i,j}) != blocks.end()) {
        cout << "X";
        } else if (find(path.begin(), path.end(), Point{i, j}) != path.end()) {
        cout << ".";
        } else {
          cout << " ";
        }
      } else {
        if (start==Point{i,j}) {
        cout << "S ";
      } else if (goal==Point{i,j}) {
        cout << "G ";
      } else if (blocks.find(Point{i,j}) != blocks.end()) {
        cout << "X ";
      } else if (find(path.begin(), path.end(), Point{i, j}) != path.end()) {
        cout << ". ";
      } else {
        cout << "  ";
      }
      }
      
    }
    cout << endl;
  }
}

void World::get_neighbors(const Point & p, set<Point> & neighbors) const {
  neighbors.clear();
  Point up;
  up.row = 0;
  up.col = 1;
  Point down;
  down.row = 0;
  down.col = -1;
  Point left;
  left.row = -1;
  left.col = 0;
  Point right;
  right.row = 1;
  right.col = 0;
  
  set<Point> increments;
  increments.insert(up); 
  increments.insert(down);
  increments.insert(left);
  increments.insert(right);

  

  for (Point neighbor : increments) {
    if(blocks.find(p) == blocks.end()) {
    if (p.row + neighbor.row < size && p.col + neighbor.col < size && p.row + neighbor.row >= 0 && p.col + neighbor.col >= 0) {
      Point next = {p.row + neighbor.row, p.col + neighbor.col};
      if (blocks.find(next) == blocks.end()) {
        if(neighbors.find(next) == neighbors.end()) {
          if(neighbors.find(p) == neighbors.end()) {
        neighbors.insert(next);
          }
        }
      }
    }
    }
  }
  // TODO: fill in neighbors
}
