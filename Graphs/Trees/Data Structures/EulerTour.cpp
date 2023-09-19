template <class T>
class EulerTour
{
private:

    int n;
    std::vector<int> tin, tout;
    std::vector<int> tTov;
    SegmentTree<T> st;

    void dfs(int v, int p, int &t, const std::vector<std::vector<int>> &adj)
    {
        tin[v] = t++;
        for (int u : adj[v])
            if (u != p)
                dfs(u, v, t, adj);
        tout[v] = t - 1;
    }

public:

    EulerTour(const std::vector<std::vector<int>> &adj, const std::vector<T> &values, const std::vector<int> roots = std::vector<int>{1}) : n((int)adj.size())
    {
        --n;
        tin.resize(n + 1);
        tout.resize(n + 1);
        tTov.resize(n);
        int t = 0;
        for (int i : roots) dfs(i, 0, t, adj);
        std::vector<T> help(n);
        for (int i = 1; i <= n; ++i)
        {
            help[tin[i]] = values[i];
            tTov[tin[i]] = i;
        }
        st = SegmentTree(help);
    }

    T get(int v)
    {
        return st.get(tin[v], tout[v]);
    }

    void update(int v, T val)
    {
        st.update(tin[v], tout[v], val);
    }

};
