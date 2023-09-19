int kuhn(const std::vector<std::vector<int>> &adj, std::vector<int> &matching, std::vector<int> part1 = std::vector<int>())
{
    matching = std::vector<int>(adj.size(), -1);
    std::vector<bool> used(adj.size());
    if (part1.empty())
    {
        std::vector<int> part2;
        auto dfs = [&part1, &part2, &adj, &used](auto self, int v, bool part) -> void
        {
            used[v] = true;
            if (part) part1.push_back(v);
            else part2.push_back(v);
            for (int u : adj[v])
                if (!used[u])
                    self(self, u, !part);
        };
        for (int i = 0; i < adj.size(); ++i)
            if (!used[i])
                dfs(dfs, i, true);
        if (part1.size() > part2.size())
            part1.swap(part2);
    }
    auto dfs = [&used, &matching, &adj](auto self, int v) -> bool
    {
        if (used[v])
            return false;
        used[v] = true;
        for (int u : adj[v])
        {
            if (matching[u] == -1 || self(self, matching[u]))
            {
                matching[u] = v;
                matching[v] = u;
                return true;
            }
        }
        return false;
    };
    for (bool isFull = true; isFull;)
    {
        isFull = false;
        used = std::vector<bool>(adj.size(), false);
        for (int v : part1)
            if (matching[v] == -1 && dfs(dfs, v))
                isFull = true;
    }
    int counter = 0;
    for (int v : part1)
        counter += (matching[v] != -1);
    return counter;
}
