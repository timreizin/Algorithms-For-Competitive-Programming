void findTriangles(const std::vector<std::vector<int>> &adj, std::vector<std::vector<int>> &triangles)
{
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < adj.size(); ++i)
        for (int v : adj[i])
            if (i < v)
                edges.emplace_back(i, v);
    std::vector<std::vector<bool>> has(adj.size());
    std::vector<bool> isHeavy(adj.size());
    for (int i = 0; i < adj.size(); ++i)
    {
        if ((long long)adj[i].size() * adj[i].size() <= edges.size())
            continue;
        isHeavy[i] = true;
        has[i] = std::vector<bool>(adj.size());
        for (int u : adj[i])
            has[i][u] = true;
    }
    std::vector<bool> has2(adj.size());
    for (int i = 0; i < adj.size(); ++i)
    {
        if (isHeavy[i])
        {
            for (auto [u, v] : edges)
                if (std::min(u, v) > i && has[i][u] && has[i][v])
                    triangles.push_back({i, std::min(u, v), std::max(u, v)});
            continue;
        }
        for (int j = 0; j < adj[i].size(); ++j)
        {
            if (adj[i][j] < i)
                continue;
            if (isHeavy[adj[i][j]])
            {
                for (int k = j + 1; k < adj[i].size(); ++k)
                    if (adj[i][k] > i && has[adj[i][j]][adj[i][k]])
                        triangles.push_back({i, std::min(adj[i][j], adj[i][k]), std::max(adj[i][j], adj[i][k])});
                continue;
            }
            for (int v : adj[adj[i][j]])
                if (v > i)
                    has2[v] = true;
            for (int k = j + 1; k < adj[i].size(); ++k)
                if (has2[adj[i][k]])
                    triangles.push_back({i, std::min(adj[i][j], adj[i][k]), std::max(adj[i][j], adj[i][k])});
            for (int v : adj[adj[i][j]])
                has2[v] = false;
        }
    }
}
