#include "Pathfinding.hpp"
#include "Point.hpp"
#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

// utility function to compute a path from start to goal given the came_from information
void came_from_to_path(const map<Point, Point> &came_from, const Point &start, const Point &goal, list<Point> &path)
{
  Point currPoint = goal;

  while (currPoint != start)
  {
    path.push_front(currPoint);
    currPoint = came_from.at(currPoint);
  }

  path.push_front(start);
}

void pathfind_bfs(const World &w, list<Point> &path)
{
  path.clear();

  deque<Point> frontier;
  map<Point, Point> came_from;

  set<Point> neighbors;

  frontier.push_back(w.start);

  while (!frontier.empty())
  {
    Point current = frontier.front();
    if (current == w.goal)
    {
      came_from_to_path(came_from, w.start, w.goal, path);
      break;
    }
    frontier.pop_front();

    //use get neighbors
    w.get_neighbors(current, neighbors);

    for (Point neighbor : neighbors)
    {
      if (came_from.find(neighbor) == came_from.end())
      {
        frontier.push_back(neighbor);
        came_from.insert(make_pair(neighbor, current));
      }
    }
  }
  // TODO: implement BFS using frontier and came_from
}

// point for heap
struct PriorityPoint
{
  double priority;
  Point point;
};

// comparison for heap - lowest first!
bool operator<(const PriorityPoint &lhs, const PriorityPoint &rhs)
{
  return lhs.priority > rhs.priority;
}

// heuristic for A*
double heuristic(const Point &a, const Point &b)
{
  return abs(a.row - b.row) + abs(a.col - b.col);
}

// assume cost of moving is always 1
const double move_cost = 1.0;

bool operator==(const PriorityPoint &lhs, const PriorityPoint &rhs)
{
  return !(lhs.point < rhs.point) && !(rhs.point < lhs.point);
}

void pathfind_astar(const World &w, list<Point> &path)
{
  path.clear();

  vector<PriorityPoint> frontier;
  map<Point, Point> came_from;
  map<Point, double> cost_so_far;

  set<Point> neighbors;

  make_heap(frontier.begin(), frontier.end());
  frontier.push_back(PriorityPoint{0, w.start});
  push_heap(frontier.begin(), frontier.end());
  cost_so_far.insert(make_pair(w.start, 0.0));

  while (!frontier.empty())
  {
    pop_heap(frontier.begin(), frontier.end());
    PriorityPoint current = frontier.back();
    frontier.pop_back();

    if (current.point == w.goal)
    {
      came_from_to_path(came_from, w.start, w.goal, path);
      break;
    }

    w.get_neighbors(current.point, neighbors);

    for (Point neighbor : neighbors)
    {
      double new_cost = cost_so_far.find(current.point)->second + move_cost;
      if (cost_so_far.find(neighbor) == cost_so_far.end() || new_cost < cost_so_far.find(current.point)->second)
      {
        double newPriority = new_cost + heuristic(current.point, neighbor);
        frontier.push_back(PriorityPoint{newPriority, neighbor});
        push_heap(frontier.begin(), frontier.end());
        came_from.insert(make_pair(neighbor, current.point));
        cost_so_far.insert(make_pair(neighbor, new_cost));
      }
    }
  }

  // TODO: implement A* using frontier, came_from and cost_so_far
}