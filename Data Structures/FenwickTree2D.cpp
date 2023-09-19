template <class T = long long>
class FenwickTree2D
{
private:

    int amount1, amount2;
    std::vector<std::vector<T>> tree;

    T get(int pos1, int pos2)
    {
        T result = 0;
        for (int i = pos1; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = pos2; j >= 0; j = (j & (j + 1)) - 1)
                result += tree[i][j];
        return result;
    }

public:

    void update(int pos1, int pos2, T value)
    {
        for (int i = pos1; i < amount1; i |= i + 1)
            for (int j = pos2; j < amount2; j |= j + 1)
                tree[i][j] += value;
    }

    FenwickTree2D(int n, int m) : amount1(n), amount2(m)
    {
        std::vector<std::vector<T>> tree(n, std::vector<T>(m));
    }

    FenwickTree2D(const std::vector<std::vector<T>> &a)
    {
        FenwickTree2D((int)a.size(), (int)a.front().size());
        for (int i = 0; i < amount1; ++i)
            for (int j = 0; j < amount2; ++j)
                update(i, j, a[i][j]);
    }

    T get(int a1, int b1, int a2, int b2)
    {
        return get(a2, b2) - (a1 == 0 ? 0 : get(a1 - 1, b2)) - (b1 == 0 ? 0 : get(a2, b1 - 1)) + ((a1 == 0 || b1 == 0) ? 0 : get(a1 - 1, b1 - 1));
    }
};
