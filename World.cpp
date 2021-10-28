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
        cout << "s";
        } else if (goal==Point{i,j}) {
        cout << "g";
        } else if (blocks.find(Point{i,j}) != blocks.end()) {
        cout << "X";
        } else if (find(path.begin(), path.end(), Point{i, j}) != path.end()) {
        cout << ".";
        } else {
          cout << " ";
        }
      } else {
        if (start==Point{i,j}) {
        cout << "s ";
      } else if (goal==Point{i,j}) {
        cout << "g ";
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
  Point up = {0,1};
  Point down  = {0,-1};
  Point left = {-1, 0};
  Point right = {1, 0};
  
  set<Point> increments;
  increments.insert(up); 
  increments.insert(down);
  increments.insert(left);
  increments.insert(right);

  for (Point neighbor : increments) {
    if (p.row + neighbor.row < size && p.col + neighbor.col < size) {
      Point next = {p.row + neighbor.row, p.col + neighbor.col};
      if (!(blocks.find(next) != blocks.end())) {
        neighbors.insert(next);
      }
    }
  }
  // TODO: fill in neighbors
}
