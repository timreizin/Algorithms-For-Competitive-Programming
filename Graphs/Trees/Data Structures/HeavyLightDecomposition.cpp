template <class Structure, ll zero = 0>
class HeavyLightDecomposition
{
private:
    
    int n;
    
    Structure structure;
    vector<int> depth;
    vector<int> head;
    vector<int> pos;
    vector<int> parent;
    
    int findHeavies(int v, vector<vector<int>> &adj)
    {
        int size = 1, maxSize = 0;
        for (int &u : adj[v])
        {
            if (u != parent[v])
            {
                parent[u] = v;
                depth[u] = depth[v] + 1;
                int childSize = findHeavies(u, adj);
                size += childSize;
                if (childSize > maxSize)
                {
                    maxSize = childSize;
                    swap(adj[v].front(), u);
                }
            }
        }
        return size;
    }
    
    void decompose(int v, int h, int &curPos, vector<vector<int>> &adj)
    {
        head[v] = h;
        pos[v] = curPos++;
        if (!adj[v].empty() && adj[v].front() != parent[v]) decompose(adj[v].front(), h, curPos, adj);
        for (int u : adj[v]) if (u != adj[v].front() && u != parent[v]) decompose(u, u, curPos, adj);
    }
    
public:
    
    HeavyLightDecomposition(vector<vector<int>> adj, vector<ll> a = vector<ll>()) : n((int)adj.size())
    {
        depth.resize(n);
        head.resize(n);
        pos.resize(n);
        parent.resize(n);
        findHeavies(1, adj);
        int curPos = 0;
        decompose(1, 1, curPos, adj);
        if (a.empty()) a.resize(n - 1, zero);
        vector<ll> help(n - 1);
        for (int i = 0; i < n - 1; ++i) help[pos[i + 1]] = a[i];
        structure = Structure(help);
    }
    
    ll get(int a, int b)
    {
        ll res = 0;
        for (; head[a] != head[b]; b = parent[head[b]])
        {
            if (depth[head[a]] > depth[head[b]]) swap(a, b);
            res += structure.get(pos[head[b]], pos[b]);
        }
        return res + structure.get(min(pos[a], pos[b]), max(pos[a], pos[b]));
    }
    
    void update(int a, ll x)
    {
        structure.update(pos[a], pos[a], x);
    }
    
};
