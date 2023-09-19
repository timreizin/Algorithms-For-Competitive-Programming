void findBridges(const std::vector<std::vector<int>>& adj, std::vector<std::pair<int, int>>& bridges)
{
    int n = (int)adj.size() - 1;
    std::vector<bool> used(n + 1);
    std::vector<int> tin(n + 1), fup(n + 1);
    int timer = 0;
    auto dfs = [&timer, &adj, &used, &tin, &fup, &bridges](auto self, int v, int p) -> void
    {
        used[v] = true;
        tin[v] = fup[v] = timer++;
        for (int u : adj[v])
        {
            if (u == p)
                continue;
            if (!used[u])
            {
                self(self, u, v);
                fup[v] = std::min(fup[v], fup[u]);
                if (tin[v] < fup[u]) bridges.push_back({v, u});
            }
            else
                fup[v] = std::min(fup[v], tin[u]);
        }
    };
    for (int i = 1; i <= n; ++i)
        if (!used[i])
            dfs(dfs, i, -1);
}
