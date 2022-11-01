template <class T>
map<T, int> compress(vector<T> &a)
{
    vector<T> help = a;
    sort(help.begin(), help.end());
    help.erase(unique(help.begin(), help.end()), help.end());
    map<T, int> mapper;
    for (int i = 0; i < help.size(); ++i) mapper[help[i]] = i;
    for (T &i : a) i = mapper[i];
    return mapper;
}
