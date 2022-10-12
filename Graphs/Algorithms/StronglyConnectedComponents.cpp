#include <vector>

std::vector<int> SCC(const std::vector<std::vector<int>> &adj)
{
    std::vector<int> sorted;
    std::vector<bool> used(adj.size());
    
    auto dfsSort = [&](auto self, int v) -> void
    {
        used[v] = true;
        for (int u : adj[v])
            if (!used[u])
                self(self, u);
        sorted.push_back(v);
    };
    
    for (int i = 0; i < adj.size(); ++i)
        if (!used[i])
            dfsSort(dfsSort, i);
    reverse(sorted.begin(), sorted.end());
    std::vector<std::vector<int>> adjT(adj.size());
    for (int v = 0; v < adj.size(); ++v)
        for (int u : adj[v])
            adjT[u].push_back(v);
    used = std::vector<bool>(adj.size());
    std::vector<int> component(adj.size());
    
    auto dfs = [&](auto self, int v, int comp) -> void
    {
        used[v] = true;
        component[v] = comp;
        for (int u : adj[v]) if (!used[u]) self(self, u, comp);
    };
    
    int counter = 0;
    for (int v : sorted)
        if (!used[v])
            dfs(dfs, v, counter);
    return component;
}
