int kuhnMinWeight(const std::vector<std::vector<int>> &adj, std::vector<int> &matching, std::vector<std::pair<int, int>> part1)
{
    matching = std::vector<int>(adj.size(), -1);
    std::sort(part1.begin(), part1.end());
    std::vector<bool> used(adj.size());
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
        for (auto [w, v] : part1)
            if (matching[v] == -1 && dfs(dfs, v))
                isFull = true;
    }
    int counter = 0;
    for (auto [w, v] : part1)
        counter += (matching[v] != -1);
    return counter;
}
