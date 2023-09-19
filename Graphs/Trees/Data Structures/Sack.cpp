class Sack
{
private:

    struct Answer
    {
        int maxim = 0;
        int sum = 0;
        std::vector<int> counter;

        void update(int v, int x, bool del = false)
        {
            counter[v] += x;
            if (!del)
            {
                if (counter[v] > maxim)
                {
                    sum = 0;
                    maxim = counter[v];
                }
                if (counter[v] == maxim)
                    sum += v;
            }
        }

        int operator()()
        {
            return sum;
        }

        void clear()
        {
            sum = 0;
            maxim = 0;
        }
    };

    std::vector<std::vector<int>> adj;
    std::vector<int> tin, tout, tTov;
    std::vector<int> values;
    std::vector<int> result;
    std::vector<int> sizes;
    Answer answer;

    int calculate(int v, int p, int &t)
    {
        tTov.push_back(v);
        tin[v] = t++;
        sizes[v] = 1;
        for (int u : adj[v])
            if (u != p)
                sizes[v] += calculate(u, v, t);
        tout[v] = t - 1;
        return sizes[v];
    }

    int findHeavy(int v, int p)
    {
        int maxim = 0, heavy = -1;
        for (int u : adj[v])
        {
            if (u != p && sizes[u] > maxim)
            {
                maxim = sizes[u];
                heavy = u;
            }
        }
        return heavy;
    }

    void dfs(int v, int p, bool isHeavy = false)
    {
        int heavy = findHeavy(v, p);
        for (int u : adj[v])
            if (u != p && u != heavy)
                dfs(u, v);
        if (heavy != -1)
            dfs(heavy, v, 1);
        for (int i = tin[v]; i <= tout[v]; ++i)
        {
            if (i == tin[heavy])
            {
                i = tout[heavy];
                continue;
            }
            answer.update(values[tTov[i]], 1);
        }
        result[v] = answer();
        if (!isHeavy)
        {
            for (int i = tin[v]; i <= tout[v]; ++i)
                answer.update(values[tTov[i]], -1, 1);
            answer.clear();
        }
    }

public:

    Sack(std::vector<std::vector<int>> adj, std::vector<int> values) : adj(adj), values(values)
    {
        result.resize(adj.size());
        sizes.resize(adj.size());
        tin.resize(adj.size());
        tout.resize(adj.size());
        tTov.reserve(adj.size());
        answer.counter.resize(adj.size());
        int t = 0;
        calculate(1, 0, t);
        dfs(1, 0);
    }

    std::vector<int> operator()()
    {
        return result;
    }

};
