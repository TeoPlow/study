#include <bits/stdc++.h>

// #define ARTEM_DEBUG
#ifdef ARTEM_DEBUG
#define debug(x) cout << #x << " = " << (x) << endl;
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec) { out << "["; for (int i = 0; i < (int)vec.size() - 1; ++i) out << vec[i] << ", "; out << vec[vec.size() - 1] << ']'; return out; }
template <typename F, typename S>
std::ostream& operator<<(std::ostream& out, const std::pair<F, S>& p) { out << "(" << p.first << ", " << p.second << ')'; return out; }
template <typename F, typename S>
std::ostream& operator<<(std::ostream& out, const std::map<F, S>& mp) { out << "{ "; for (auto & elem : mp) out << "{" << elem.first << ", " << elem.second << "} "; out << " }"; return out; }
#endif

#define all(x) x.begin(), x.end()
using ll = int64_t;
using pii = std::pair<int, int>;
const int M(1e9 + 7);
const int M2(1e9 + 123);
const int inf(1e9);
const ll INF(1e18);
using namespace std;

using graph = vector<vector<int>>;

struct Point {
    double x, y;
};

struct items {
    int index;
    double d; // расстояние от вершины до финиша
    double p; // расстояние от старта до вершины

    items(int index_, double d_, double p_) : index(index_), d(d_), p(p_) {}
};

double get_distance(const Point & a, const Point & b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double a_star(const graph & g, int u, int finish, const vector<Point> & points) {
    int n = (int)g.size();
    vector<double> dist(n, -1);
    auto items_less = [&](items & i1, items & i2) -> bool {
        if (i1.d + i1.p != i2.d + i2.p) {
            return i1.d + i1.p > i2.d + i2.p;
        }
        return i1.index < i2.index;
    };
    priority_queue<items, vector<items>, decltype(items_less)> q(items_less);
    dist[u] = 0;
    q.push({u, get_distance(points[u], points[finish]), 0});
    while (!q.empty()) {
        items elem = q.top();
        int u = elem.index;
        q.pop();
        if (u == finish) {
            break;
        }
        for (auto & v : g[u]) {
            if (dist[v] < 0 || dist[v] > dist[u] + get_distance(points[u], points[v])) {
                dist[v] = dist[u] + get_distance(points[u], points[v]);
                q.push({v, dist[v], get_distance(points[v], points[finish])});
            }
        }
    }
    return dist[finish];
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Point> points(n);
    for (auto & elem : points) {
        cin >> elem.x >> elem.y;
    }

    graph g(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int s, f;
        cin >> s >> f;
        s--; f--;
        cout.precision(6);
        cout << fixed << a_star(g, s, f, points) << '\n';
    }
}