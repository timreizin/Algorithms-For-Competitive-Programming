class DSUTree
{
private:
    
    int n;
    vector<int> rank;
    vector<int> parent;
    vector<vector<int>> adj;
    
public:
    
    int getParent(int a)
    {
        if (a == parent[a]) return a;
        return parent[a] = getParent(parent[a]);
    }
    
    DSUTree(int n) : n(n)
    {
        rank.resize(n + 1, 1);
        parent.resize(n + 1);
        adj.resize(n + 1);
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }
    
    void addEdge(int u, int v)
    {
        rank.push_back(1);
        parent.push_back((int)parent.size());
        u = getParent(u);
        v = getParent(v);
        adj.push_back(vector<int>{u});
        if (u != v) adj.back().push_back(v);
        parent[u] = parent[v] = parent.back();
        rank.back() = rank[u];
        if (v != u) rank.back() += rank[v];
    }
    
    bool isInOneSet(int a, int b)
    {
        return getParent(a) == getParent(b);
    }
    
    vector<vector<int>> operator()()
    {
        return adj;
    }
    
    int size()
    {
        return (int)parent.size();
    }
    
    vector<int> getRoots()
    {
        vector<int> roots;
        for (int i = 1; i < size(); ++i) if (getParent(i) == i) roots.push_back(i);
        return roots;
    }
};
