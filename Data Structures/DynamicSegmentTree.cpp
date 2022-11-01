class DynamicSegmentTree
{
private:
    
    int index;
    ll minValue, maxValue;
    vector<ll> tree;
    vector<pair<int, int>> child;
    
    ll get(ll a, ll b, ll l, ll r, int v)
    {
        if (v == -1 || a > r || b < l) return 0ll;
        if (a <= l && b >= r) return tree[v];
        ll m = l + (r - l) / 2;
        return get(a, min(b, m), l, m, child[v].first) + get(max(a, m + 1), b, m + 1, r, child[v].second);
    }
    
    void update(ll pos, ll l, ll r, int v, ll value)
    {
        if (l > r) return;
        if (l == r)
        {
            tree[v] += value;
            return;
        }
        ll m = l + (r - l) / 2;
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
    
    DynamicSegmentTree(ll maxVal) : index(1), minValue(0), maxValue(maxVal)
    {
        tree.push_back(0);
        child.push_back({-1, -1});
    }
    
    DynamicSegmentTree(ll minVal, ll maxVal) : index(1), minValue(minVal), maxValue(maxVal)
    {
        tree.push_back(0);
        child.push_back({-1, -1});
    }
    
    ll get(ll a, ll b)
    {
        return get(a, b, minValue, maxValue, 0);
    }
    
    void update(ll pos, ll value)
    {
        update(pos, minValue, maxValue, 0, value);
    }
};
