void findArticulationPoints(const std::vector<std::vector<int>>& adj, std::vector<int>& articulationPoints)
{
    int n = (int)adj.size() - 1;
    std::vector<bool> used(n + 1);
    std::vector<int> tin(n + 1), fup(n + 1);
    int timer = 0;
    auto dfs = [&timer, &adj, &used, &tin, &fup, &articulationPoints](auto self, int v, int p) -> void
    {
        used[v] = true;
        tin[v] = fup[v] = timer++;
        bool isArticulationPoint = false;
        int counter = 0;
        for (int u : adj[v])
        {
            if (u == p)
                continue;
            if (!used[u])
            {
                self(self, u, v);
                fup[v] = std::min(fup[v], fup[u]);
                isArticulationPoint = isArticulationPoint || tin[v] <= fup[u];
                ++counter;
            }
            else
                fup[v] = std::min(fup[v], tin[u]);
        }
        isArticulationPoint = isArticulationPoint && p != 0;
        if ((isArticulationPoint && adj[v].size() != 1) || (p == 0 && counter > 1))
            articulationPoints.push_back(v);
    };
    for (int i = 1; i <= n; ++i)
        if (!used[i])
            dfs(dfs, i, 0);
}
