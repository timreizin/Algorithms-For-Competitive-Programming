ll countInversions(vector<int> &p, int l, int r)
{
    if (l >= r) return 0;
    int m = (l + r) >> 1;
    ll res = countInversions(p, l, m) + countInversions(p, m + 1, r);
    vector<int> help;
    for (int i = l, j = m + 1; i <= m || j <= r;)
    {
        if (i > m) help.push_back(p[j++]);
        else if (j > r) help.push_back(p[i++]);
        else if (p[i] < p[j]) help.push_back(p[i++]);
        else
        {
            res += (ll)(m - i + 1);
            help.push_back(p[j++]);
        }
    }
    for (int i = l; i <= r; ++i) p[i] = help[i - l];
    return res;
}
