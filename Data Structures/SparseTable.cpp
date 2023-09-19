class SparseTable
{
private:

    int amount, k;
    std::vector<std::vector<long long>> table;
    std::vector<int> log2;

public:

    SparseTable(std::vector<long long> &a) : amount((int)a.size())
    {
        int n = (int)a.size();
        log2.resize(n + 1);
        log2[1] = 0;
        for (int i = 2; i <= n; ++i)
            log2[i] = log2[i / 2] + 1;
        k = log2[n];
        table = std::vector<std::vector<long long>>(n, std::vector<long long>(k + 1));
        for (int i = 0; i < n; ++i)
            table[i][0] = a[i];
        for (int j = 1; j <= k; ++j)
            for (int i = 0; i + (1 << j) <= n; ++i)
                table[i][j] = std::min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
    }

    long long get(int l, int r)
    {
        return std::min(table[l][log2[r - l + 1]], table[r - (1 << log2[r - l + 1]) + 1][log2[r - l + 1]]);
    }

};
