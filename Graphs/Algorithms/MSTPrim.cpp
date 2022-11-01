ll prim(vector<vector<pair<int, ll>>>& adj, vector<pair<pair<int, int>, ll>>& mst)
{
    int n = (int)adj.size() - 1;
    vector<bool> used(n + 1);
    vector<pair<ll, int>> minEdges(n + 1, {INF, -1});
    minEdges[1].first = 0;
    ll minCost = 0;
    for (int i = 0; i < n; ++i)
    {
        int v = -1;
        for (int j = 1; j <= n; ++j) if (!used[j] && (v == -1 || minEdges[j].first < minEdges[v].first)) v = j;
        used[v] = true;
        minCost += minEdges[v].first;
        if (minEdges[v].second != -1) mst.emplace_back(make_pair(v, minEdges[v].second), minEdges[v].first);
        for (auto [u, w] : adj[v]) if (w < minEdges[u].first) minEdges[u] = {w, v};
    }
    return minCost;
}
