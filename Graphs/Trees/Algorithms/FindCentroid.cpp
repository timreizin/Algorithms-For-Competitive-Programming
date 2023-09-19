int findCentroid(int v, int p, long long allWeight, const std::vector<long long> &weights, const std::vector<std::vector<int>> &adj)
{
    for (int u : adj[v])
        if (u != p && weights[u] > allWeight / 2)
            return findCentroid(u, v, allWeight, weights, adj);
    return v;
}
