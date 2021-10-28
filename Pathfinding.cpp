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

  set<Point> neighbors;

  frontier.push_back(w.start);

  while (!frontier.empty()) {
    Point current = frontier.front();
    if (current == w.goal) {
        break;
    }
    frontier.pop_front();

    //use get neighbors
    w.get_neighbors(current, neighbors);

    for (Point neighbor : neighbors) {
      if (came_from.find(neighbor) == came_from.end()) {
        frontier.push_back(neighbor);
        came_from.insert(neighbor, current);
      }
    }
  }
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

  set<Point> neighbors;

  frontier.push_back(PriorityPoint{0, w.start});
  cost_so_far.insert(pair<Point, double> (w.start, 0.0));

  while (!frontier.empty())
  {
    PriorityPoint current = frontier.front();
    if (current.point == w.goal) {
        break;
    }
    remove(frontier.begin(), frontier.begin() + 1, current);

    w.get_neighbors(current.point, neighbors);

    for (Point neighbor : neighbors) {
      double new_cost = cost_so_far.find(current.point)->second + move_cost;
      if (came_from.find(neighbor) == came_from.end() || new_cost < cost_so_far.find(current.point)->second) {
        double newPriority = new_cost + heuristic(current.point, neighbor);
        frontier.push_back(PriorityPoint{newPriority, neighbor});
        came_from.insert(neighbor, current.point);
        cost_so_far.insert(pair<Point, double> (neighbor, new_cost));
      }
    }
  }
  

  

  // TODO: implement A* using frontier, came_from and cost_so_far

  came_from_to_path(came_from, w.start, w.goal, path);
}