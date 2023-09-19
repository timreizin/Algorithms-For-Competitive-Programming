long long kruskal(const std::vector<std::vector<std::pair<int, long long>>> &adj, std::vector<std::pair<std::pair<int, int>, long long>> &mst)
{
    std::vector<std::pair<long long, std::pair<int, int>>> edges;
    int n = (int)adj.size() - 1;
    DSU dsu(n);
    for (int i = 1; i <= n; ++i)
        for (auto [u, w] : adj[i])
            edges.emplace_back(w, std::pair(i, u));
    std::sort(edges.begin(), edges.end());
    long long minCost = 0;
    int countEdges = 0;
    for (auto [w, e] : edges)
    {
        if (dsu.isInOneSet(e.first, e.second))
            continue;
        dsu.uniteSets(e.first, e.second);
        minCost += w;
        mst.emplace_back(e, w);
        ++countEdges;
        if (countEdges == n - 1)
            break;
    }
    return minCost;
}
