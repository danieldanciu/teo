#include <algorithm>// for std::min
#include <cstring>  // for memset
#include <fstream>
#include <limits>
#include <queue>
#include <vector>

const int MAX_DIM = 501;

// a very large number to signify "unreachable"; careful at overflows! In comps, prefer using just a large number such as
// 1.000.000 (signed int goes up to ~2B)
const int INF = std::numeric_limits<int>::max();

const int di[4] = {-1, +1, 0, 0};
const int dj[4] = {0, 0, -1, +1};

int n, m, T;

char labyrinth[MAX_DIM][MAX_DIM];

using IntMat = std::array<std::array<int, MAX_DIM>, MAX_DIM>;

IntMat dist_from_start;
IntMat dist_from_exit;
bool visited[MAX_DIM][MAX_DIM];

int iw = 0, jw = 0, ie = 0, je = 0;// start and end point coordinates

// A node in our implicit graph, defined by the labyrinth
struct Vertex {
  int i, j, dist;
  Vertex(int i, int j, int dist) : i(i), j(j), dist(dist) {}
};
std::vector<Vertex> portals;

void read() {
  std::ifstream fin("walle.in");
  fin >> n >> m >> T;
  fin.get();
  for (int i = 0; i < n; ++i) {
    fin.getline(labyrinth[i], MAX_DIM);
    for (int j = 0; j < m; ++j) {
      if (labyrinth[i][j] == 'P')
        portals.emplace_back(i, j, 0);
      else if (labyrinth[i][j] == 'W') {
        iw = i;
        jw = j;
      } else if (labyrinth[i][j] == 'E') {
        ie = i;
        je = j;
      }
    }
  }
}

bool is_valid(int i, int j) {
  return i >= 0 && i < n && j >= 0 && j < m;
}

void dijkstra(int i, int j, IntMat &dist) {
  std::fill(&dist[0][0], &dist[n][m], INF);
  std::memset(visited, false, n * MAX_DIM * sizeof(bool));

  auto cmp = [](Vertex a, Vertex b) { return a.dist > b.dist; };
  std::priority_queue<Vertex, std::vector<Vertex>, decltype(cmp)> q(cmp);

  dist[i][j] = 0;
  q.push({i, j, 0});
  while (!q.empty()) {
    Vertex t = q.top();
    q.pop();
    if (visited[t.i][t.j]) continue;
    visited[t.i][t.j] = 1;
    for (int k = 0; k < 4; k++) {
      auto [new_i, new_j] = std::pair<int, int>({t.i + di[k], t.j + dj[k]});
      if (!is_valid(new_i, new_j) || labyrinth[new_i][new_j] == '#') continue;
      int new_cost = t.dist + 1 + T * (labyrinth[new_i][new_j] == '+');
      if (new_cost < dist[new_i][new_j]) {
        dist[new_i][new_j] = new_cost;
        if (labyrinth[new_i][new_j] != 'P' && labyrinth[new_i][new_j] != 'E')
          q.push({new_i, new_j, dist[new_i][new_j]});
      }
    }
  }
}

std::pair<int, int> get_furthest_portals() {
  int max= 0, max2= 0;
  for (auto &[i, j, _] : portals) {
    int d_exit = dist_from_exit[i][j];
    if (d_exit >= max) {
      max2 = max;
      max = d_exit;
    } else if (d_exit > max2) {
      max2 = d_exit;
    }
  }
  return {max, max2};
}

int help_walle_out() {
  std::vector<int> left_max(portals.size());
  std::vector<int> right_max(portals.size());

  // compute the cost for each portal (it's the maximum cost of all the other portals)
  auto [max, max2] = get_furthest_portals();

  for (const auto &[i, j, _] : portals) {

    int dist_via_portal = dist_from_exit[i][j]==max ? max2: max;
    if (dist_via_portal == INF) {
      continue;
    }

    bool has_free_cell = false;
    bool has_time_delay = false;

    for (int k = 0; k < 4; k++) {
      auto [new_i, new_j] = std::pair<int, int>(i + di[k], j + dj[k]);
      if (not is_valid(new_i, new_j)) continue;
      if (labyrinth[new_i][new_j] == '.')
        has_free_cell = 1;
      else if (labyrinth[new_i][new_j] == '+')
        has_time_delay = 1;
    }
    if (has_free_cell)
      dist_from_exit[i][j] = std::min(dist_from_exit[i][j], 2 + dist_via_portal);
    else if (has_time_delay)
      dist_from_exit[i][j] = std::min(dist_from_exit[i][j], T + 2 + dist_via_portal);
  }

  auto [nmax, nmax2] = get_furthest_portals();

  // shortest path NOT using portals
  int result = dist_from_start[ie][je];
  // let's check if using a portal is faster
  for (const auto &[i, j, _] : portals) {
    int dist_via_portal = dist_from_exit[i][j]==nmax ? nmax2: nmax;

    if (dist_from_start[i][j] != INF && dist_via_portal != INF) {
      result = std::min(result, dist_from_start[i][j] + dist_via_portal);
    }
  }

  return (result == INF ? -1 : result);
}

int main() {
  read();
  // compute distances from entrance to all nodes
  dijkstra(iw, jw, dist_from_start);
  // compute distances frome exit to all nodes
  dijkstra(ie, je, dist_from_exit);

  int result = help_walle_out();
  std::ofstream fout("walle.out");
  fout << result;
}
