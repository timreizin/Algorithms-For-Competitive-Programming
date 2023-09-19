void dfs2SAT1(int v, std::vector<int> &order, std::vector<bool> &used, const std::vector<std::vector<int>> &adj)
{
    used[v] = true;
    for (int u : adj[v])
        if (!used[u])
            dfs2SAT1(u, order, used, adj);
    order.push_back(v);
}

void dfs2SAT2(int v, int t, const std::vector<std::vector<int>> &adj, std::vector<int> &comp)
{
    comp[v] = t;
    for (int u : adj[v])
        if (comp[u] == 0)
            dfs2SAT2(u, t, adj, comp);
}

bool SAT2(const std::vector<std::vector<int>> &adj, std::vector<bool> &result)
{
    std::vector<int> order;
    std::vector<bool> used(adj.size());
    for (int i = 0; i < adj.size(); ++i)
        if (!used[i])
            dfs2SAT1(i, order, used, adj);
    reverse(order.begin(), order.end());
    std::vector<int> comp(adj.size());
    std::vector<std::vector<int>> adjT(adj.size());
    for (int i = 0; i < adj.size(); ++i)
        for (int u : adj[i])
            adjT[u].push_back(i);
    for (int i = 0, j = 1; i < order.size(); ++i)
        if (comp[order[i]] == 0)
            dfs2SAT2(order[i], j++, adjT, comp);
    for (int i = 0; i < adj.size(); i += 2)
    {
        if (comp[i] == comp[i + 1])
        {
            result.clear();
            return false;
        }
        result.push_back(comp[i] > comp[i + 1]);
    }
    return true;
}
