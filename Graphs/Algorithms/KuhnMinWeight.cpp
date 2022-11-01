bool dfsKuhn(int v, vector<bool>& used, vector<int>& matching, vector<vector<int>>& adj)
{
    if (used[v]) return false;
    used[v] = true;
    for (int u : adj[v])
    {
        if (matching[u] == -1 || dfsKuhn(matching[u], used, matching, adj))
        {
            matching[u] = v;
            matching[v] = u;
            return true;
        }
    }
    return false;
}

int kuhnMinWeight(vector<vector<int>> &adj, vector<int> &matching, vector<pair<int, int>> part1)
{
    matching = vector<int>(adj.size(), -1);
    sort(part1.begin(), part1.end());
    vector<bool> used(adj.size());
    for (bool isFull = true; isFull;)
    {
        isFull = false;
        used = vector<bool>(adj.size(), false);
        for (auto [w, v] : part1)
            if (matching[v] == -1 && dfsKuhn(v, used, matching, adj))
                isFull = true;
    }
    int counter = 0;
    for (auto [w, v] : part1) counter += (matching[v] != -1);
    return counter;
}
