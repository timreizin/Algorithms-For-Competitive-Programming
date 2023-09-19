void suffixArray(const std::string &s, std::vector<std::vector<int>> &c)
{
    std::vector p(ceil(log2(s.size() + 1)) + 1, std::vector<int>(s.size()));
    c = p;
    std::vector<int> counter(10), temp;
    for (char i : s)
        ++counter[i - '0'];
    for (int i = 1; i < 10; ++i)
        counter[i] += counter[i - 1];
    for (int i = 0; i < s.size(); ++i)
        p[0][--counter[s[i] - '0']] = i;
    int classes = 0;
    c[0][p[0][0]] = 0;
    for (int i = 1; i < s.size(); ++i)
    {
        if (s[p[0][i]] != s[p[0][i - 1]])
            ++classes;
        c[0][p[0][i]] = classes;
    }
    ++classes;
    for (int h = 0; (1 << h) < s.size(); ++h)
    {
        for (int i = 0; i < s.size(); ++i)
        {
            p[h + 1][i] = p[h][i] - (1 << h);
            if (p[h + 1][i] < 0)
                p[h + 1][i] += (int)s.size();
        }
        counter.clear();
        counter.resize(classes);
        for (int i = 0; i < s.size(); ++i)
            ++counter[c[h][p[h + 1][i]]];
        for (int i = 1; i < classes; ++i)
            counter[i] += counter[i - 1];
        temp = p[h + 1];
        for (int i = (int)s.size() - 1; i >= 0; --i)
            p[h + 1][--counter[c[h][temp[i]]]] = temp[i];
        c[h + 1][p[h + 1][0]] = 0;
        classes = 0;
        for (int i = 1; i < s.size(); ++i)
        {
            if (c[h][p[h + 1][i]] != c[h][p[h + 1][i - 1]] ||
                c[h][(p[h + 1][i] + (1 << h)) % s.size()] != c[h][(p[h + 1][i - 1] + (1 << h)) % s.size()])
                ++classes;
            c[h + 1][p[h + 1][i]] = classes;
        }
        ++classes;
    }
}

int compare(int i, int j, int l, int k, std::vector<std::vector<int>> &c)
{
    std::pair<int, int> a{c[k][i], c[k][i + l - (1 << k)]};
    std::pair<int, int> b{c[k][j], c[k][j + l - (1 << k)]};
    return a == b ? 0 : a < b ? - 1 : 1;
}
