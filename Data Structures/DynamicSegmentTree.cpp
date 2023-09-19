template <class T>
class DynamicSegmentTree
{
private:

    int index;
    long long minValue, maxValue;
    std::vector<T> tree;
    std::vector<std::pair<int, int>> child;

    T get(long long a, long long b, long l, long r, int v)
    {
        if (v == -1 || a > r || b < l)
            return T(0);
        if (a <= l && b >= r)
            return tree[v];
        long long m = l + (r - l) / 2;
        return get(a, std::min(b, m), l, m, child[v].first) + get(std::max(a, m + 1), b, m + 1, r, child[v].second);
    }

    void update(long long pos, long long l, long long r, int v, T value)
    {
        if (l > r)
            return;
        if (l == r)
        {
            tree[v] += value;
            return;
        }
        long long m = l + (r - l) / 2;
        if (pos <= m)
        {
            if (child[v].first == -1)
            {
                child[v].first = index++;
                tree.push_back(0);
                child.push_back({-1, -1});
            }
            update(pos, l, m, child[v].first, value);
        }
        else
        {
            if (child[v].second == -1)
            {
                child[v].second = index++;
                tree.push_back(0);
                child.push_back({-1, -1});
            }
            update(pos, m + 1, r, child[v].second, value);
        }
        tree[v] = (child[v].first == -1 ? 0 : tree[child[v].first]) + (child[v].second == -1 ? 0 : tree[child[v].second]);
    }

public:

    DynamicSegmentTree(long long maxVal) : index(1), minValue(0), maxValue(maxVal)
    {
        tree.push_back(0);
        child.push_back({-1, -1});
    }

    DynamicSegmentTree(long long minVal, long long maxVal) : index(1), minValue(minVal), maxValue(maxVal)
    {
        tree.push_back(0);
        child.push_back({-1, -1});
    }

    T get(long long a, long long b)
    {
        return get(a, b, minValue, maxValue, 0);
    }

    void update(long long pos, long long value)
    {
        update(pos, minValue, maxValue, 0, value);
    }
};
