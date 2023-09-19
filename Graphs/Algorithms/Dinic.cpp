struct Edge
{
    int v;
    long long capacity;
    long long flow;
    int indexOfReversed;
};

long long dfsDinic(int u, long long flow, int t, std::vector<int> &startIndex, const std::vector<int> &level, std::vector<std::vector<Edge>> &adj)
{
    if (u == t) return flow;
    for (; startIndex[u] < adj[u].size(); ++startIndex[u])
    {
        Edge &edge = adj[u][startIndex[u]];
        if (level[edge.v] == level[u] + 1 && edge.flow < edge.capacity)
        {
            long long newFlow = dfsDinic(edge.v, std::min(flow, edge.capacity - edge.flow), t, startIndex, level, adj);
            if (newFlow > 0)
            {
                edge.flow += newFlow;
                adj[edge.v][edge.indexOfReversed].flow -= newFlow;
                return newFlow;
            }
        }
    }
    return 0;
}

bool bfsDinic(int s, int t, std::vector<int> &level, const std::vector<std::vector<Edge>> &adj)
{
    level = std::vector<int>(adj.size(), -1);
    level[s] = 0;
    std::queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (Edge edge : adj[u])
        {
            if (level[edge.v] == -1 && edge.flow < edge.capacity)
            {
                level[edge.v] = level[u] + 1;
                q.push(edge.v);
            }
        }
    }
    return level[t] != -1;
}

long long maxFlowDinic(int s, int t, std::vector<std::vector<std::pair<int, long long>>> &adj)
{
    std::vector<std::vector<Edge>> adjFlow(adj.size());
    for (int i = 0; i < adj.size(); ++i)
    {
        for (auto [v, c] : adj[i])
        {
            adjFlow[i].push_back({v, c, 0, (int)adjFlow[v].size()});
            adjFlow[v].push_back({i, 0, 0, (int)adjFlow[i].size() - 1});
        }
    }
    std::vector<int> level(adj.size());
    long long flow = 0;
    while (bfsDinic(s, t, level, adjFlow))
    {
        std::vector<int> startIndex(adj.size());
        while (long long newFlow = dfsDinic(s, 1e9, t, startIndex, level, adjFlow))
            flow += newFlow;
    }
    return flow;
}
