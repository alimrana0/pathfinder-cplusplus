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
  // TODO: display world
}

void World::get_neighbors(const Point & p, set<Point> & neighbors) const {
  neighbors.clear();

  // TODO: fill in neighbors
}
