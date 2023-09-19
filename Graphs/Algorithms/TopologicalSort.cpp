std::vector<int> topSort(const std::vector<std::vector<int>> &adj)
{
    std::vector<int> sorted;
    std::vector<int> used(adj.size());

    auto dfs = [&used, &adj, &sorted](auto self, int v) -> bool
    {
        used[v] = 1;
        for (int u : adj[v])
        {
            if (used[u] == 2)
                continue;
            if (used[u] == 1)
                return false;
            bool ret = self(self, v);
            if (!ret)
                return false;
        }
        sorted.push_back(v);
        used[v] = 2;
        return true;
    };

    bool res = true;
    for (int i = 0; i < adj.size(); ++i)
        if (used[i] == 0)
            res = res && dfs(dfs, i);
    if (!res)
        sorted.clear();
    reverse(sorted.begin(), sorted.end());
    return sorted;
}
