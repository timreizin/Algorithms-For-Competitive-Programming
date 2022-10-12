#include <vector>
#include <queue>
#include <functional>

std::pair<std::vector<long long>, std::vector<int>> dijkstra(const std::vector<int> starts, const int n, const std::vector<std::vector<std::pair<int, long long>>> &adj)
{
    std::vector<long long> distances;
    std::vector<int> parents;
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<>> pq;
    std::vector<bool> used(n + 1, false);
    for (const int v : starts)
    {
        distances[v] = 0;
        pq.push({0, v});
    }
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (used[u]) continue;
        used[u] = true;
        for (auto [v, w] : adj[u])
        {
            if (distances[v] > distances[u] + w)
            {
                distances[v] = distances[u] + w;
                parents[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    return {distances, parents};
}
