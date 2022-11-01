struct DSU_rb
{

    struct operation
    {
        int v, rankV;
        int u, rankU;

        operation(int pv, int prankV, int pu, int prankU)
        {
            v = pv;
            prankV = rankV;
            u = pu;
            prankU = rankU;
        }
    };

    vector<int> rank;
    vector<int> parent;
    int components;

    stack<operation> opers;

    DSU_rb(int n)
    {
        rank.resize(n);
        parent.resize(n);
        for (int i = 0; i < n; ++i) parent[i] = i;
        components = n;
    }

    int getParent(int v)
    {
        return v == parent[v] ? v : getParent(parent[v]);
    }

    void uniteSets(int v, int u)
    {
        v = getParent(v);
        u = getParent(u);
        if (u == v)
        {
            opers.push(operation(-1, -1, -1, -1));
            return;
        }
        if (rank[v] < rank[u]) swap(u, v);
        --components;
        opers.push(operation(v, rank[v], u, rank[u]));
        parent[u] = v;
        if (rank[v] == rank[u]) ++rank[v];
    }

    void rollback()
    {
        operation op = opers.top();
        opers.pop();
        if (op.v == -1) return;
        ++components;
        rank[op.v] = op.rankV;
        rank[op.u] = op.rankU;;
        parent[op.v] = op.v;
        parent[op.u] = op.u;
    }

};
