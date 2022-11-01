void SPFA(int s, vector<vector<pair<int, ll>>> &adj, vector<ll> &d)
{
    //if vertex has been used more than n - 1 time, there is a cycle of negative weight
    //to get cycle use array of parents
    d = vector<ll>(adj.size(), 1e18);
    d[s] = 0;
    vector<bool> inQueue(adj.size(), false);
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        inQueue[v] = false;
        for (auto [u, w] : adj[v])
        {
            if (d[v] + w < d[u])
            {
                d[u] = d[v] + w;
                if (!inQueue[u])
                {
                    q.push(u);
                    inQueue[u] = true;
                }
            }
        }
    }
}
