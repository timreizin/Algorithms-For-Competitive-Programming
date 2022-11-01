template <class T>
struct Pref2D
{
    
    int n, m;
    vector<vector<T>> pref;
    
    Pref2D(vector<vector<T>> a) : n(int(a.size())), m(int(a.front().size()))
    {
        pref = a;
        for (int i = 1; i < n; ++i) for (int j = 0; j < m; ++j) pref[i][j] += pref[i - 1][j];
        for (int i = 0; i < n; ++i) for (int j = 1; j < m; ++j) pref[i][j] += pref[i][j - 1];
    }
    
    T get(int x1, int x2, int y1, int y2)
    {
        if (x1 > x2 || y1 > y2) return 0;
        T res = pref[x2][y2];
        if (x1 > 0) res -= pref[x1 - 1][y2];
        if (y1 > 0) res -= pref[x2][y1 - 1];
        if (x1 > 0 && y1 > 0) res += pref[x1 - 1][y1 - 1];
        return res;
    }
    
};
