class EulerTour
{
private:
    
    int n;
    vector<int> tin, tout;
    vector<int> tTov;
    SegmentTree st;
    
    void dfs(int v, int p, int &t, vector<vector<int>> &adj)
    {
        tin[v] = t++;
        for (int u : adj[v]) if (u != p) dfs(u, v, t, adj);
        tout[v] = t - 1;
    }
    
public:
    
    EulerTour(vector<vector<int>> &adj, vector<ll> &values, vector<int> roots = vector<int>{1}) : n((int)adj.size())
    {
        --n;
        tin.resize(n + 1);
        tout.resize(n + 1);
        tTov.resize(n);
        int t = 0;
        for (int i : roots) dfs(i, 0, t, adj);
        vector<ll> help(n);
        for (int i = 1; i <= n; ++i)
        {
            help[tin[i]] = values[i];
            tTov[tin[i]] = i;
        }
        st = SegmentTree(help);
    }
    
    ll get(int v)
    {
        return st.get(tin[v], tout[v]);
    }
    
    void update(int v, ll val)
    {
        st.update(tin[v], tout[v], val);
    }
    
};
