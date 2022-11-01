void dfsTarjan(int v, vector<bool>& used, vector<vector<int>>& adj, vector<vector<pair<int, int>>>& queries, DSU& dsu)
{
    used[v] = true;
    dsu.makeSet(v, v);
    for (int u : adj[v])
    {
        if (!used[u])
        {
            dfsTarjan(u, used, adj, queries, dsu);
            dsu.uniteSets(v, u);
            dsu.updateValue(v, v - dsu.getValue(v));
        }
    }
    for (auto& [u, ans] : queries[v]) if (used[u]) ans = dsu.getValue(u);
}

void lcaTarjan(vector<vector<int>>& adj, vector<vector<pair<int, int>>>& queries)
{
    int n = (int)adj.size() - 1;
    DSU dsu(n + 1);
    vector<bool> used(n + 1);
    dfsTarjan(1, used, adj, queries, dsu);
}
