ll countMoves(string &s1, string &s2)
{
    int n = (int)s1.size();
    vector<int> p(n);
    array<vector<int>, 26> sI1, sI2;
    for (int i = 0; i < n; ++i)
    {
        sI1[s1[i] - 'a'].push_back(i);
        sI2[s2[i] - 'a'].push_back(i);
    }
    for (int i = 0; i < 26; ++i)
    {
        for (int j = 0; j < sI1[i].size(); ++j)
        {
            p[sI1[i][j]] = sI2[i][j];
        }
    }
    return countInversions(p, 0, n - 1);
}
