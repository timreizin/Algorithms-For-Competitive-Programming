class DSU
{
private:

    std::vector<int> rank;
    std::vector<int> parent;
    std::vector<int> value;

    int components;

    int getParent(int a)
    {
        if (a == parent[a])
            return a;
        return parent[a] = getParent(parent[a]);
    }

public:

    DSU(int n)
    {
        rank.resize(n);
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
        value.resize(n);
        components = n;
    }

    DSU(const std::vector<int> &a)
    {
        DSU((int)a.size());
        value = a;
    }

    void makeSet(int a, int val)
    {
        rank[a] = 0;
        parent[a] = a;
        value[a] = val;
        ++components;
    }

    void uniteSets(int a, int b)
    {
        a = getParent(a);
        b = getParent(b);
        if (a == b)
            return;
        --components;
        if (rank[a] < rank[b])
            std::swap(a, b);
        parent[b] = a;
        value[a] += value[b];
        if (rank[a] == rank[b])
            ++rank[a];
    }

    int getValue(int a)
    {
        return value[getParent(a)];
    }

    void updateValue(int a, int val)
    {
        value[getParent(a)] += val;
    }

    bool isInOneSet(int a, int b)
    {
        return getParent(a) == getParent(b);
    }

    int getComponents()
    {
        return components;
    }
};
