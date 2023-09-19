class CentroidDecomposition
{
private:

    std::vector<std::vector<std::pair<int, int>>> parents;
    std::vector<int> info;

    int findCentroid(int v, int p, int size, const std::vector<int> &sizes, const std::vector<bool> &used, const std::vector<std::vector<int>> &adj)
    {
        for (int u : adj[v])
            if (u != p && !used[u] && sizes[u] > size / 2)
                return findCentroid(u, v, size, sizes, used, adj);
        return v;
    }

    int calculateSizes(int v, int p, std::vector<int> &sizes, const std::vector<bool> &used, const std::vector<std::vector<int>> &adj)
    {
        sizes[v] = 1;
        for (int u : adj[v])
            if (u != p && !used[u])
                sizes[v] += calculateSizes(u, v, sizes, used, adj);
        return sizes[v];
    }

    void setParents(int v, int p, int parent, int distance, const std::vector<bool> &used, const std::vector<std::vector<int>> &adj)
    {
        if (v != parent)
            parents[v].emplace_back(parent, distance);
        for (int u : adj[v])
            if (u != p && !used[u])
                setParents(u, v, parent, distance + 1, used, adj);
    }

    void build(int v, std::vector<int> &sizes, std::vector<bool> &used, const std::vector<std::vector<int>> &adj)
    {
        int size = calculateSizes(v, -1, sizes, used, adj);
        int centroid = findCentroid(v, -1, size, sizes, used, adj);
        setParents(centroid, -1, centroid, 0, used, adj);
        used[centroid] = true;
        info[centroid] = 1e9;
        for (int u : adj[centroid])
            if (!used[u])
                build(u, sizes, used, adj);
    }

public:

    CentroidDecomposition(const std::vector<std::vector<int>> &adj)
    {
        parents.resize(adj.size());
        info.resize(adj.size());
        std::vector<int> sizes(adj.size());
        std::vector<bool> used(adj.size());
        build(0, sizes, used, adj);
    }

    void update(int v)
    {
        info[v] = 0;
        for (auto [u, d] : parents[v])
            info[u] = std::min(info[u], d);
    }

    int get(int v)
    {
        int result = info[v];
        for (auto [u, d] : parents[v])
            result = std::min(result, info[u] + d);
        return result;
    }
};
