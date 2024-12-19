#include <iostream>
#include <queue>
#include <vector>

struct Edge {
    int start, end;
    long long weight;
};

const long long MAXIMUM = 1e18;

int n;
bool flag = true;

std::vector<long long> bellman_ford(const std::vector<Edge> &edges, int start) {
    std::vector<long long> dist(n + 1);
    int x = -1;
	for (int i = 0; i < n + 1; ++i) {
        int m = edges.size();
		for (int j = 0; j < m; ++j) {
			if (dist[edges[j].end] > (dist[edges[j].start] + edges[j].weight)) {
				dist[edges[j].end] = std::max(-MAXIMUM, dist[edges[j].start] + edges[j].weight);
				x = edges[j].end;
			}
        }   
    }
	if (x == -1) {
        flag = false;
    }

    return dist;
}

std::vector<long long> dijkstra(const std::vector<Edge> &edges, int start) {
    std::vector<long long> dist(n + 1, MAXIMUM);
    std::vector<bool> used(n + 1, false);

    dist[start] = 0;

    for (int t = 0; t < n + 1; ++t) {
        int start = -1;
        for (int j = 0; j < n + 1; ++j) {
            if (!used[j] && (dist[j] < dist[start] || start == -1)) {
                start = j;
            }
        }
        if (dist[start] == MAXIMUM) {
            break;
        }
        used[start] = true;
    
        for (int i = 0; i < edges.size(); ++i) {
            
            if (edges[i].start == start) {
                if (dist[start] + edges[i].weight < dist[edges[i].end]) {
                    dist[edges[i].end] = dist[start] + edges[i].weight; 
                }
            }
        }        
    }
    return dist;
}

int main() {
    int m;
    std::cin >> n >> m;

    std::vector<Edge> edges;

    for (int i = 0; i < m; ++i) {
        int start, end;
        long long weight;
        std::cin >> start >> end >> weight;
        edges.push_back({start, end, weight});
    }

    std::vector<long long> s = bellman_ford(edges, 1);
    if (flag) {
        std::cout << "Negative cycle\n"; 
    }
    else {
        for (int i = 0; i < n; ++i){
        edges.push_back({0, i + 1, 0});
        }

        std::vector<long long> h = bellman_ford(edges, 0);

        for (int i=0; i < edges.size(); ++i) {
            edges[i].weight = edges[i].weight + h[edges[i].start] - h[edges[i].end];
        }

        for (int i = 1; i < n + 1; ++i){
            std::vector<long long> res = dijkstra(edges,i);
            for (int j = 1; j < res.size(); ++j){
                if (res[j] == MAXIMUM) {
                    std::cout << "inf ";
                }
                else {
                    std::cout << res[j] - h[i] + h[j]  << " ";
                }
            }
            std::cout << '\n';
        }
    }
}