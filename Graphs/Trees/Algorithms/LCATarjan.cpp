void lcaTarjan(const std::vector<std::vector<int>> &adj, std::vector<std::vector<std::pair<int, int>>> &queries)
{
    int n = (int)adj.size() - 1;
    DSU dsu(n + 1);
    std::vector<bool> used(n + 1);
    auto dfs = [&used, &adj, &queries, &dsu](auto self, int v) -> void
    {
        used[v] = true;
        dsu.makeSet(v, v);
        for (int u : adj[v])
        {
            if (!used[u])
            {
                self(self, u);
                dsu.uniteSets(v, u);
                dsu.updateValue(v, v - dsu.getValue(v));
            }
        }
        for (auto& [u, ans] : queries[v])
            if (used[u])
                ans = dsu.getValue(u);
    };
    dfs(dfs, 1);
}
