template <class T, class Structure>
class HeavyLightDecomposition
{
private:

    int n;

    Structure structure;
    std::vector<int> depth;
    std::vector<int> head;
    std::vector<int> pos;
    std::vector<int> parent;

    int findHeavies(int v, std::vector<std::vector<int>> &adj)
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
                    std::swap(adj[v].front(), u);
                }
            }
        }
        return size;
    }

    void decompose(int v, int h, int &curPos, std::vector<std::vector<int>> &adj)
    {
        head[v] = h;
        pos[v] = curPos++;
        if (!adj[v].empty() && adj[v].front() != parent[v])
            decompose(adj[v].front(), h, curPos, adj);
        for (int u : adj[v])
            if (u != adj[v].front() && u != parent[v])
                decompose(u, u, curPos, adj);
    }

public:

    HeavyLightDecomposition(std::vector<std::vector<int>> adj, std::vector<T> a = std::vector<T>()) : n((int)adj.size())
    {
        depth.resize(n);
        head.resize(n);
        pos.resize(n);
        parent.resize(n);
        findHeavies(1, adj);
        int curPos = 0;
        decompose(1, 1, curPos, adj);
        if (a.empty()) a.resize(n - 1, T(0));
        std::vector<T> help(n - 1);
        for (int i = 0; i < n - 1; ++i)
            help[pos[i + 1]] = a[i];
        structure = Structure(help);
    }

    T get(int a, int b)
    {
        T res = 0;
        for (; head[a] != head[b]; b = parent[head[b]])
        {
            if (depth[head[a]] > depth[head[b]])
                std::swap(a, b);
            res += structure.get(pos[head[b]], pos[b]);
        }
        return res + structure.get(std::min(pos[a], pos[b]), std::max(pos[a], pos[b]));
    }

    void update(int a, T x)
    {
        structure.update(pos[a], pos[a], x);
    }

};
