class SparseTable
{
private:

    int amount, k;
    vector<vector<ll>> table;
    vector<int> log2;

public:

    SparseTable(vector<ll>& a) : amount((int)a.size())
    {
        int n = (int)a.size();
        log2.resize(n + 1);
        log2[1] = 0;
        for (int i = 2; i <= n; ++i) log2[i] = log2[i / 2] + 1;
        k = log2[n];
        table = vector<vector<ll>>(n, vector<ll>(k + 1));
        for (int i = 0; i < n; ++i) table[i][0] = a[i];
        for (int j = 1; j <= k; ++j) for (int i = 0; i + (1 << j) <= n; ++i) table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
    }

    ll get(int l, int r)
    {
        return min(table[l][log2[r - l + 1]], table[r - (1 << log2[r - l + 1]) + 1][log2[r - l + 1]]);
    }

};
