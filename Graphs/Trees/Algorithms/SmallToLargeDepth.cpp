class SmallToLargeDepth
{
private:
    
    struct DS
    {
        vector<int> values;
        pair<int, int> best{0, 0};
        
        void insert(int d, int value)
        {
            values[(int)values.size() - d - 1] += value;
            best = max(best, pair(values[(int)values.size() - d - 1], -d));
        }
        
        void shift()
        {
            values.push_back(0);
            --best.second;
        }
        
        int operator()()
        {
            return -best.second;
        }
        
        int operator[](int i)
        {
            return values[(int)values.size() - i - 1];
        }
        
        int size()
        {
            return (int)values.size();
        }
        
    };
    
    vector<vector<int>> adj;
    vector<int> result;
    
    void dfs(int v, int p, DS &ds)
    {
        for (int u : adj[v])
        {
            if (u != p)
            {
                DS child;
                dfs(u, v, child);
                if (child.size() > ds.size()) swap(child, ds);
                for (int i = 0; i < child.size(); ++i) ds.insert(i, child[i]);
            }
        }
        ds.shift();
        ds.insert(0, 1);
        result[v] = ds();
    }
    
public:
    
    SmallToLargeDepth(vector<vector<int>> &adj) : adj(adj)
    {
        result.resize(adj.size());
        DS ds;
        dfs(1, 0, ds);
    }
    
    vector<int> operator()()
    {
        return result;
    }
};
