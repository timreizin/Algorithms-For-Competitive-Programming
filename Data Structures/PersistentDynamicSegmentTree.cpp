template <class T>
class PersistentDynamicSegmentTree
{
private:

    int index;
    long long maxValue;
    std::vector<T> tree;
    std::vector<int> versions;
    std::vector<std::pair<int, int>> child;

    T get(long long a, long long b, long long l, long long r, int v)
    {
        if (v == -1 || a > r || b < l)
            return T(0);
        if (a <= l && b >= r)
            return tree[v];
        long long m = l + (r - l) / 2;
        return get(a, std::min(b, m), l, m, child[v].first) + get(std::max(a, m + 1), b, m + 1, r, child[v].second);
    }

    void updateNew(long long pos, long long l, long long r, int v, T value)
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
            updateNew(pos, l, m, child[v].first, value);
        }
        else
        {
            if (child[v].second == -1)
            {
                child[v].second = index++;
                tree.push_back(0);
                child.push_back({-1, -1});
            }
            updateNew(pos, m + 1, r, child[v].second, value);
        }
        tree[v] = (child[v].first == -1 ? 0 : tree[child[v].first]) + (child[v].second == -1 ? 0 : tree[child[v].second]);
    }

    int updatePresent(long long pos, long long l, long long r, int v, T value)
    {
        if (l > r)
            return -1;
        tree.push_back(tree[v]);
        child.push_back(child[v]);
        int newV = index++;
        if (l == r)
        {
            tree[newV] += value;
            return newV;
        }
        long long m = l + (r - l) / 2;
        if (pos <= m)
        {
            if (child[v].first == -1)
            {
                child[newV].first = index++;
                tree.push_back(0);
                child.push_back({-1, -1});
                updateNew(pos, l, m, child[newV].first, value);
            }
            else
            {
                int childV = updatePresent(pos, l, m, child[v].first, value);
                child[newV].first = childV;
            }
        }
        else
        {
            if (child[v].second == -1)
            {
                child[newV].second = index++;
                tree.push_back(0);
                child.push_back({-1, -1});
                updateNew(pos, m + 1, r, child[newV].second, value);
            }
            else
            {
                int childV = updatePresent(pos, m + 1, r, child[v].second, value);
                child[newV].second = childV;
            }
        }
        tree[newV] = (child[newV].first == -1 ? 0 : tree[child[newV].first]) + (child[newV].second == -1 ? 0 : tree[child[newV].second]);
        return newV;
    }


public:

    PersistentDynamicSegmentTree(T maxValue) : index(1), maxValue(maxValue)
    {
        tree.push_back(0);
        child.push_back({-1, -1});
        versions.push_back(0);
    }

    T get(int version, long long a, long long b)
    {
        return get(a, b, 0, maxValue, versions[version]);
    }

    void update(int version, long long pos, T value)
    {
        versions.push_back(updatePresent(pos, 0, maxValue, versions[version], value));
    }

    int lastVersion()
    {
        return (int)versions.size() - 1;
    }
};
