int gaussianElimination(vector<vector<int>> a, vector<int> &res)
{
    vector<int> where((int)a.front().size() - 1, -1);
    for (int i = 0, j = 0; i < a.size() && j + 1 < a.front().size(); ++j)
    {
        int ind = i;
        for (int k = i; k < a.size(); ++k) if (a[k][j] > a[ind][j]) ind = k;
        if (a[ind][j] == 0) continue;
        swap(a[i], a[ind]);
        where[j] = i;
        int inv = binPow(a[i][j], MOD - 2);
        for (int k = j; k < a.front().size(); ++k) a[i][k] = (a[i][k] * inv) % MOD;
        for (int k = 0; k < a.size(); ++k)
        {
            if (k == i) continue;
            for (int l = (int)a.front().size() - 1; l >= j; --l)
            {
                a[k][l] -= (a[k][j] * a[i][l]) % MOD;
                if (a[k][l] < 0) a[k][l] += MOD;
            }
        }
        ++i;
    }
    res = vector<int>((int)a.front().size() - 1, 0);
    for (int i = 0; i + 1 < a.front().size(); ++i) if (where[i] != -1) res[i] = a[where[i]].back();
    for (int i = 0; i < a.size(); ++i)
    {
        int sum = 0;
        for (int j = 0; j + 1 < a.front().size(); ++j)
        {
            sum += (res[j] * a[i][j]) % MOD;
            if (sum >= MOD) sum -= MOD;
        }
        if (sum != a[i].back()) return 0;
    }
    for (int i = 0; i + 1 < a.front().size(); ++i) if (where[i] == -1) return 2;
    return 1;
}
