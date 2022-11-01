void dfsBridges(int v, int p, int& timer, vector<vector<int>>& adj, vector<bool>& used, vector<int>& tin, vector<int>& fup, vector<pair<int, int>>& bridges)
{
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (int u : adj[v])
    {
        if (u == p) continue;
        if (!used[u])
        {
            dfsBridges(u, v, timer, adj, used, tin, fup, bridges);
            fup[v] = min(fup[v], fup[u]);
            if (tin[v] < fup[u]) bridges.push_back({v, u});
        }
        else fup[v] = min(fup[v], tin[u]);
    }
}

void findBridges(vector<vector<int>>& adj, vector<pair<int, int>>& bridges)
{
    int n = (int)adj.size() - 1;
    vector<bool> used(n + 1);
    vector<int> tin(n + 1), fup(n + 1);
    int timer = 0;
    for (int i = 1; i <= n; ++i) if (!used[i]) dfsBridges(i, -1, timer, adj, used, tin, fup, bridges);
}
