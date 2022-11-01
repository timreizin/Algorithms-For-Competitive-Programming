ll kruskal(vector<vector<pair<int, ll>>>& adj, vector<pair<pair<int, int>, ll>>& mst)
{
    vector<pair<ll, pair<int, int>>> edges;
    int n = (int)adj.size() - 1;
    DSU dsu(n);
    for (int i = 1; i <= n; ++i) for (auto [u, w] : adj[i]) edges.emplace_back(w, make_pair(i, u));
    sort(edges.begin(), edges.end());
    ll minCost = 0;
    int countEdges = 0;
    for (auto [w, e] : edges)
    {
        if (dsu.isInOneSet(e.first, e.second)) continue;
        dsu.uniteSets(e.first, e.second);
        minCost += w;
        mst.emplace_back(e, w);
        ++countEdges;
        if (countEdges == n - 1) break;
    }
    return minCost;
}
