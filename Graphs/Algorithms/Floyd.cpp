std::pair<int, int> floyd(int s, std::vector<int> &next)
{
    int a, b;
    a = b = s;
    while (a != b)
    {
        a = next[a];
        b = next[next[b]];
    }
    a = s;
    while (a != b)
    {
        a = next[a];
        b = next[b];
    }
    int len = 0;
    do
    {
        ++len;
        b = next[b];
    } while (b != a);
    return {a, len};
}
