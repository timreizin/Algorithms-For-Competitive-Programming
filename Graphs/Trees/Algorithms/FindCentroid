int findCentroid(int v, int p, ll allWeight, vector<ll>& weights, vector<vector<int>>& adj)
{
    for (int u : adj[v])
        if (u != p && weights[u] > allWeight / 2)
            return findCentroid(u, v, allWeight, weights, adj);
    return v;
}
