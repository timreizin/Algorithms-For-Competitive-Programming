void dfsBipartite(int v, bool part, vector<int>& part1, vector<int>& part2, vector<bool>& used, vector<vector<int>>& adj)
{
    used[v] = true;
    if (part) part1.push_back(v);
    else part2.push_back(v);
    for (int u : adj[v])
        if (!used[u])
            dfsBipartite(u, !part, part1, part2, used, adj);
}

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

int kuhn(vector<vector<int>> &adj, vector<int> &matching, vector<int> part1 = vector<int>())
{
    matching = vector<int>(adj.size(), -1);
    vector<bool> used(adj.size());
    if (part1.empty())
    {
        vector<int> part2;
        for (int i = 0; i < adj.size(); ++i) if (!used[i]) dfsBipartite(i, true, part1, part2, used, adj);
        if (part1.size() > part2.size()) part1.swap(part2);
    }
    for (bool isFull = true; isFull;)
    {
        isFull = false;
        used = vector<bool>(adj.size(), false);
        for (int v : part1)
            if (matching[v] == -1 && dfsKuhn(v, used, matching, adj))
                isFull = true;
    }
    int counter = 0;
    for (int v : part1) counter += (matching[v] != -1);
    return counter;
}
