class SegmentTreeBeats
{
private:

    struct node
    {
        ll sum;
        ll lazy;
        ll max1;
        ll max2;
        ll maxc;
        ll min1;
        ll min2;
        ll minc;
    };

    int amount;
    vector<node> tree;

    node merge(node a, node b)
    {
        node result;
        result.sum = a.sum + b.sum;
        result.lazy = 0;
        if (a.max1 == b.max1)
        {
            result.max1 = a.max1;
            result.maxc = a.maxc + b.maxc;
            result.max2 = max(a.max2, b.max2);
        }
        else if (a.max1 > b.max1)
        {
            result.max1 = a.max1;
            result.maxc = a.maxc;
            result.max2 = max(a.max2, b.max1);
        }
        else
        {
            result.max1 = b.max1;
            result.maxc = b.maxc;
            result.max2 = max(a.max1, b.max2);
        }
        if (a.min1 == b.min1)
        {
            result.min1 = a.min1;
            result.minc = a.minc + b.minc;
            result.min2 = min(a.min2, b.min2);
        }
        else if (a.min1 < b.min1)
        {
            result.min1 = a.min1;
            result.minc = a.minc;
            result.min2 = min(a.min2, b.min1);
        }
        else
        {
            result.min1 = b.min1;
            result.minc = b.minc;
            result.min2 = min(a.min1, b.min2);
        }
        return result;
    }

    void pushMax(int v, ll value)
    {
        if (value >= tree[v].max1) return;
        tree[v].sum -= tree[v].max1 * tree[v].maxc;
        tree[v].max1 = value;
        tree[v].sum += tree[v].max1 * tree[v].maxc;
        if (tree[v].min1 > value) tree[v].min1 = value;
        else if (tree[v].min2 > value) tree[v].min2 = value;
    }

    void pushMin(int v, ll value)
    {
        if (value <= tree[v].min1) return;
        tree[v].sum -= tree[v].min1 * tree[v].minc;
        tree[v].min1 = value;
        tree[v].sum += tree[v].min1 * tree[v].minc;
        if (tree[v].max1 < value) tree[v].max1 = value;
        else if (tree[v].max2 < value) tree[v].max2 = value;
    }

    void pushAdd(int v, int l, int r, ll value)
    {
        if (value == 0) return;
        tree[v].sum += value * (r - l + 1);
        tree[v].lazy += value;
        tree[v].max1 += value;
        if (tree[v].max2 != -LONGINF) tree[v].max2 += value;
        tree[v].min1 += value;
        if (tree[v].min2 != LONGINF) tree[v].min2 += value;
    }

    void push(int v, int l, int r)
    {
        int m = (l + r) >> 1;
        pushAdd(v << 1, l, m, tree[v].lazy);
        pushAdd(v << 1 | 1, m + 1, r, tree[v].lazy);
        tree[v].lazy = 0;
        pushMax(v << 1, tree[v].max1);
        pushMax(v << 1 | 1, tree[v].max1);
        pushMin(v << 1, tree[v].min1);
        pushMin(v << 1 | 1, tree[v].min1);
    }

    void build(int l, int r, int v, vector<ll> &a)
    {
        if (l > r) return;
        if (l == r)
        {
            tree[v].sum = tree[v].max1 = tree[v].min1 = a[l];
            tree[v].maxc = tree[v].minc = 1;
            tree[v].max2 = -LONGINF;
            tree[v].min2 = LONGINF;
            tree[v].lazy = 0;
            return;
        }
        int m = (l + r) >> 1;
        build(l, m, v << 1, a);
        build(m + 1, r, v << 1 | 1, a);
        tree[v] = merge(tree[v << 1], tree[v << 1 | 1]);
    }

    void updateMin(int a, int b, ll value, int l, int r, int v = 1)
    {
        if (a > r || b < l || tree[v].max1 <= value) return;
        if (a == l && b == r && tree[v].max2 < value)
        {
            pushMax(v, value);
            return;
        }
        push(v, l, r);
        int m = (l + r) >> 1;
        updateMin(a, min(b, m), value, l, m, v << 1);
        updateMin(max(a, m + 1), b, value, m + 1, r, v << 1 | 1);
        tree[v] = merge(tree[v << 1], tree[v << 1 | 1]);
    }

    void updateMax(int a, int b, ll value, int l, int r, int v = 1)
    {
        if (a > r || b < l || tree[v].min1 >= value) return;
        if (a == l && b == r && tree[v].min2 > value)
        {
            pushMin(v, value);
            return;
        }
        push(v, l, r);
        int m = (l + r) >> 1;
        updateMax(a, min(b, m), value, l, m, v << 1);
        updateMax(max(a, m + 1), b, value, m + 1, r, v << 1 | 1);
        tree[v] = merge(tree[v << 1], tree[v << 1 | 1]);
    }

    void updateAdd(int a, int b, ll value, int l, int r, int v = 1)
    {
        if (a > r || b < l) return;
        if (a == l && b == r)
        {
            pushAdd(v, l, r, value);
            return;
        }
        push(v, l, r);
        int m = (l + r) >> 1;
        updateAdd(a, min(b, m), value, l, m, v << 1);
        updateAdd(max(a, m + 1), b, value, m + 1, r, v << 1 | 1);
        tree[v] = merge(tree[v << 1], tree[v << 1 | 1]);
    }

    ll getSum(int a, int b, int l, int r, int v = 1)
    {
        if (a > r || b < l) return 0ll;
        if (a == l && b == r) return tree[v].sum;
        push(v, l, r);
        int m = (l + r) >> 1;
        return getSum(a, min(b, m), l, m, v << 1) + getSum(max(a, m + 1), b, m + 1, r, v << 1 | 1);
    }

public:

    SegmentTreeBeats(int n) : amount(n)
    {
        tree.resize(amount * 4);
        vector<ll> a(n, 0);
        build(0, amount - 1, 1, a);
    }

    SegmentTreeBeats(vector<ll> &a) : amount((int)a.size())
    {
        tree.resize(amount * 4);
        build(0, amount - 1, 1, a);
    }

    void updateMin(int a, int b, ll value)
    {
        updateMin(a, b, value, 0, amount - 1);
    }

    void updateMax(int a, int b, ll value)
    {
        updateMax(a, b, value, 0, amount - 1);
    }

    void updateAdd(int a, int b, ll value)
    {
        updateAdd(a, b, value, 0, amount - 1);
    }

    ll getSum(int a, int b)
    {
        return getSum(a, b, 0, amount - 1);
    }

};
