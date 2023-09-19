template <class T>
long long countInversions(std::vector<T> &p, int l, int r)
{
    if (l >= r)
        return 0;
    int m = (l + r) >> 1;
    long long res = countInversions(p, l, m) + countInversions(p, m + 1, r);
    std::vector<int> help;
    for (int i = l, j = m + 1; i <= m || j <= r;)
    {
        if (i > m)
            help.push_back(p[j++]);
        else if (j > r)
            help.push_back(p[i++]);
        else if (p[i] < p[j])
            help.push_back(p[i++]);
        else
        {
            res += (long long)(m - i + 1);
            help.push_back(p[j++]);
        }
    }
    for (int i = l; i <= r; ++i)
        p[i] = help[i - l];
    return res;
}
