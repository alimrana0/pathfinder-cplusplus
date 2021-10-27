#include "Pathfinding.hpp"
#include "Point.hpp"
#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <vector>
using namespace std;



// utility function to compute a path from start to goal given the came_from information
void came_from_to_path(const map<Point, Point> & came_from, const Point & start, const Point & goal, list<Point> & path) {
  // TODO: reconstruct path
    Point currPoint = start;
    while (currPoint != goal) {
    path.push_back(currPoint);
    currPoint = came_from.at(currPoint);
  }
}


void pathfind_bfs(const World & w, list<Point> & path) {
  path.clear();

  deque<Point> frontier;
  map<Point, Point> came_from;
  Point up = {0,1};
  Point down  = {0,-1};
  Point left = {-1, 0};
  Point right = {1, 0};

    vector<Point> increments;
    increments.push_back(up); 
    increments.push_back(down);
    increments.push_back(left);
    increments.push_back(right);

  frontier.push_back(w.start);

for (int i = 0; i < w.size; i++) {
    for (int j = 0; j < w.size; j++) {
  for (Point neighbor : increments) {
      Point next{i + increments.row, j + increments.column};
      if (i < w.size-1 && j < w.size -1) {
        frontier.push_back(next);
      }
    }

    //use get neighbors


  // TODO: implement BFS using frontier and came_from

  came_from_to_path(came_from, w.start, w.goal, path);
}



// point for heap
struct PriorityPoint {
  double priority;
  Point point;
};

// comparison for heap - lowest first!
bool operator<(const PriorityPoint & lhs, const PriorityPoint & rhs) {
  return lhs.priority > rhs.priority;
}

// heuristic for A*
double heuristic(const Point & a, const Point & b) {
  return abs(a.row - b.row) + abs(a.col - b.col);
}

// assume cost of moving is always 1
const double move_cost = 1.0;



void pathfind_astar(const World & w, list<Point> & path) {
  path.clear();

  vector<PriorityPoint> frontier;
  map<Point, Point> came_from;
  map<Point, double> cost_so_far;

  // TODO: implement A* using frontier, came_from and cost_so_far

  came_from_to_path(came_from, w.start, w.goal, path);
}
