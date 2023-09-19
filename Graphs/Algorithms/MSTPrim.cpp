long long prim(std::vector<std::vector<std::pair<int, long long>>> &adj, std::vector<std::pair<std::pair<int, int>, long long>> &mst)
{
    constexpr long long INF = 1e18;
    int n = (int)adj.size() - 1;
    std::vector<bool> used(n + 1);
    std::vector<std::pair<long long, int>> minEdges(n + 1, {INF, -1});
    minEdges[1].first = 0;
    long long minCost = 0;
    for (int i = 0; i < n; ++i)
    {
        int v = -1;
        for (int j = 1; j <= n; ++j) 
            if (!used[j] && (v == -1 || minEdges[j].first < minEdges[v].first))
                v = j;
        used[v] = true;
        minCost += minEdges[v].first;
        if (minEdges[v].second != -1)
            mst.emplace_back(std::pair(v, minEdges[v].second), minEdges[v].first);
        for (auto [u, w] : adj[v])
            if (w < minEdges[u].first)
                minEdges[u] = {w, v};
    }
    return minCost;
}
