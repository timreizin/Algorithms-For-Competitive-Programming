struct Edge
{
    int v;
    ll capacity;
    ll flow;
    int indexOfReversed;
};

ll dfsDinic(int u, ll flow, int t, vector<int> &startIndex, vector<int> &level, vector<vector<Edge>> &adj)
{
    if (u == t) return flow;
    for (; startIndex[u] < adj[u].size(); ++startIndex[u])
    {
        Edge &edge = adj[u][startIndex[u]];
        if (level[edge.v] == level[u] + 1 && edge.flow < edge.capacity)
        {
            ll newFlow = dfsDinic(edge.v, min(flow, edge.capacity - edge.flow), t, startIndex, level, adj);
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

bool bfsDinic(int s, int t, vector<int> &level, vector<vector<Edge>> &adj)
{
    level = vector<int>(adj.size(), -1);
    level[s] = 0;
    queue<int> q;
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

ll maxFlowDinic(int s, int t, vector<vector<pair<int, ll>>> &adj)
{
    vector<vector<Edge>> adjFlow(adj.size());
    for (int i = 0; i < adj.size(); ++i)
    {
        for (auto [v, c] : adj[i])
        {
            adjFlow[i].push_back({v, c, 0, (int)adjFlow[v].size()});
            adjFlow[v].push_back({i, 0, 0, (int)adjFlow[i].size() - 1});
        }
    }
    vector<int> level(adj.size());
    ll flow = 0;
    while (bfsDinic(s, t, level, adjFlow))
    {
        vector<int> startIndex(adj.size());
        while (ll newFlow = dfsDinic(s, 1e9, t, startIndex, level, adjFlow))
        {
            flow += newFlow;
        }
    }
    return flow;
}
