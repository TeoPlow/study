#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <iomanip>


struct Point {
    float x, y;
};

struct Edge {
    int start, end;
    float weight;
};

int n, m, q;
const long long MAXIMUM = 1e9;
std::vector<Point> vertices;
std::vector<std::vector<Edge>> edges;

float euclideanDistance(const Point& a, const Point& b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

std::vector<float> dijkstra(const std::vector<std::vector<Edge>>& edges, int start) {
    std::vector<float> dist(n + 1, MAXIMUM);
    std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<>> pq;

    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [currentDist, current] = pq.top();
        pq.pop();

        if (currentDist > dist[current]) {
            continue;
        }

        for (const auto& edge : edges[current]) {
            if (dist[current] + edge.weight < dist[edge.end]) {
                dist[edge.end] = dist[current] + edge.weight;
                pq.emplace(dist[edge.end], edge.end);
            }
        }
    }

    return dist;
}

int main() {
    std::cin >> n >> m;
    vertices.resize(n + 1);
    edges.resize(n + 1);

    for (int i = 1; i <= n; ++i) {
        std::cin >> vertices[i].x >> vertices[i].y;
    }
    
    for (int i = 0; i < m; ++i) {
        int start, end;
        std::cin >> start >> end;

        float weight = euclideanDistance(vertices[start], vertices[end]);
        edges[start].push_back({start, end, weight});
        edges[end].push_back({end, start, weight});
    }

    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int from, to;
        std::cin >> from >> to;

        std::vector<float> dist = dijkstra(edges, from);

        if (dist[to] == MAXIMUM) {
            std::cout << -1 << "\n";
        } else {
            std::cout << std::fixed << std::setprecision(6) << dist[to] << "\n";
        }
    }

    return 0;
}
