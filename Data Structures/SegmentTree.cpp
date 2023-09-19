template <class T = long long>
class SegmentTree
{
private:

    int amount;
    std::vector<T> tree;
    std::vector<T> mod;

    void push(int l, int r, int v)
    {
        if (mod[v] != 0)
        {
            mod[v << 1] += mod[v];
            mod[v << 1 | 1] += mod[v];
            int m = (l + r) >> 1;
            tree[v << 1] += (m - l + 1) * mod[v];
            tree[v << 1 | 1] += (r - m) * mod[v];
            mod[v] = 0;
        }
    }

    void buildTree(int l, int r, int v, const std::vector<T> &a)
    {
        if (l > r)
            return;
        if (l == r)
        {
            tree[v] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        buildTree(l, m, v << 1, a);
        buildTree(m + 1, r, v << 1 | 1, a);
        tree[v] = tree[v << 1] + tree[v << 1 | 1];
    }

    T get(int a, int b, int l, int r, int v)
    {
        if (a > r || b < l)
            return 0ll;
        if (a == l && b == r)
            return tree[v];
        push(l, r, v);
        int m = (l + r) >> 1;
        return get(a, std::min(b, m), l, m, v << 1) + get(std::max(a, m + 1), b, m + 1, r, v << 1 | 1);
    }

    void update(int a, int b, int l, int r, int v, T value)
    {
        if (a > r || b < l)
            return;
        if (a == l && b == r)
        {
            mod[v] += value;
            tree[v] += (r - l + 1) * value;
            return;
        }
        push(l, r, v);
        int m = (l + r) >> 1;
        update(a, std::min(b, m), l, m, v << 1, value);
        update(std::max(a, m + 1), b, m + 1, r, v << 1 | 1, value);
        tree[v] = tree[v << 1] + tree[v << 1 | 1];
    }

public:

    SegmentTree(int n = 0) : amount(n)
    {
        tree.resize(4 * amount + 5);
        mod.resize(4 * amount + 5);
    }

    SegmentTree(const std::vector<T> &a)
    {
        SegmentTree((int)a.size());
        buildTree(0, amount - 1, 1, a);
    }

    T get(int a, int b)
    {
        return get(a, b, 0, amount - 1, 1);
    }

    void update(int a, int b, T value)
    {
        update(a, b, 0, amount - 1, 1, value);
    }
};
