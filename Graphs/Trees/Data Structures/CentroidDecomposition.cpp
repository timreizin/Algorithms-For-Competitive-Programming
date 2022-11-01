class CentroidDecomposition
{
private:

    vector<vector<pair<int, int>>> parents;
    vector<int> info;

    int findCentroid(int v, int p, int size, vector<int> &sizes, vector<bool> &used, vector<vector<int>> &adj)
    {
        for (int u : adj[v])
            if (u != p && !used[u] && sizes[u] > size / 2)
                return findCentroid(u, v, size, sizes, used, adj);
        return v;
    }

    int calculateSizes(int v, int p, vector<int> &sizes, vector<bool> &used, vector<vector<int>> &adj)
    {
        sizes[v] = 1;
        for (int u : adj[v]) if (u != p && !used[u]) sizes[v] += calculateSizes(u, v, sizes, used, adj);
        return sizes[v];
    }

    void setParents(int v, int p, int parent, int distance, vector<bool> &used, vector<vector<int>> &adj)
    {
        if (v != parent) parents[v].emplace_back(parent, distance);
        for (int u : adj[v]) if (u != p && !used[u]) setParents(u, v, parent, distance + 1, used, adj);
    }

    void build(int v, vector<int> &sizes, vector<bool> &used, vector<vector<int>> &adj)
    {
        int size = calculateSizes(v, -1, sizes, used, adj);
        int centroid = findCentroid(v, -1, size, sizes, used, adj);
        setParents(centroid, -1, centroid, 0, used, adj);
        used[centroid] = true;
        info[centroid] = 1e9;
        for (int u : adj[centroid]) if (!used[u]) build(u, sizes, used, adj);
    }

public:

    CentroidDecomposition(vector<vector<int>> &adj)
    {
        parents.resize(adj.size());
        info.resize(adj.size());
        vector<int> sizes(adj.size());
        vector<bool> used(adj.size());
        build(0, sizes, used, adj);
    }

    void update(int v)
    {
        info[v] = 0;
        for (auto [u, d] : parents[v]) info[u] = min(info[u], d);
    }

    int get(int v)
    {
        int result = info[v];
        for (auto [u, d] : parents[v]) result = min(result, info[u] + d);
        return result;
    }
};
