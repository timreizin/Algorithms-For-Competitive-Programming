class LCA
{
private:

    std::vector<int> tin;
    std::vector<int> tout;
    std::vector<std::vector<int>> up;
    int log2;

    void dfs(int v, int p, int &timer, std::vector<std::vector<int>> &adj)
    {
        tin[v] = timer++;
        up[v][0] = p;
        for (int i = 1; i <= log2; ++i)
            up[v][i] = up[up[v][i - 1]][i - 1];
        for (int u : adj[v])
            if (u != p)
                dfs(u, v, timer, adj);
        tout[v] = timer - 1;
    }

    bool isAncestor(int v, int u)
    {
        return tin[v] <= tin[u] && tout[v] >= tout[u];
    }

public:

    LCA(std::vector<std::vector<int>> &adj, std::vector<int> roots = std::vector<int>{1}) : log2(0)
    {
        tin.resize(adj.size());
        tout.resize(adj.size());
        int n = (int)adj.size();
        while (n > 1)
        {
            n = (n + 1) / 2;
            ++log2;
        }
        up = std::vector<std::vector<int>>(adj.size(), std::vector<int>(log2 + 1));
        int timer = 0;
        for (int i : roots)
            dfs(i, i, timer, adj);
    }

    int get(int v, int u)
    {
        if (up[v].back() != up[u].back())
            return -1;
        if (isAncestor(v, u))
            return v;
        if (isAncestor(u, v))
            return u;
        for (int i = log2; i >= 0; --i)
            if (!isAncestor(up[v][i], u))
                v = up[v][i];
        return up[v][0];
    }

};
