void dfsArticulationPoints(int v, int p, int& timer, vector<vector<int>>& adj, vector<bool>& used, vector<int>& tin, vector<int>& fup, vector<int>& articulationPoints)
{
    used[v] = true;
    tin[v] = fup[v] = timer++;
    bool isArticulationPoint = false;
    int counter = 0;
    for (int u : adj[v])
    {
        if (u == p) continue;
        if (!used[u])
        {
            dfsArticulationPoints(u, v, timer, adj, used, tin, fup, articulationPoints);
            fup[v] = min(fup[v], fup[u]);
            isArticulationPoint = isArticulationPoint || tin[v] <= fup[u];
            ++counter;
        }
        else fup[v] = min(fup[v], tin[u]);
    }
    isArticulationPoint = isArticulationPoint && p != 0;
    if ((isArticulationPoint && adj[v].size() != 1) || (p == 0 && counter > 1)) articulationPoints.push_back(v);
}

void findArticulationPoints(vector<vector<int>>& adj, vector<int>& articulationPoints)
{
    int n = (int)adj.size() - 1;
    vector<bool> used(n + 1);
    vector<int> tin(n + 1), fup(n + 1);
    int timer = 0;
    for (int i = 1; i <= n; ++i) if (!used[i]) dfsArticulationPoints(i, 0, timer, adj, used, tin, fup, articulationPoints);
}
