template <class T = ll>
struct Line
{
    using type = T;
    
    T k, b;
    
    Line(T k = 0, T b = LONGINF) : k(k), b(b)
    {}
    
    T operator()(T x)
    {
        return k * x + b;
    }
};

template <class Function>
class LiChao
{
private:
    
    using T = typename Function::type;
    
    int n;
    vector<Function> tree;
    
    void update(int a, int b, int l, int r, int v, Function func)
    {
        if (a > r || b < l) return;
        int m = (l + r) >> 1;
        if (a == l && b == r)
        {
            if (func(m) > tree[v](m)) swap(tree[v], func);
            if (func(l) <= tree[v](l) && func(r) <= tree[v](r)) return;
            if (func(l) > tree[v](l)) update(a, min(b, m), l, m, v << 1, func);
            else update(max(a, m + 1), b, m + 1, r, v << 1 | 1, func);
            return;
        }
        update(a, min(b, m), l, m, v << 1, func);
        update(max(a, m + 1), b, m + 1, r, v << 1 | 1, func);
    }
    
    T get(int p, int l, int r, int v)
    {
        if (l == r) return tree[v](p);
        int m = (l + r) >> 1;
        if (p <= m) return max(tree[v](p), get(p, l, m, v << 1));
        else return max(tree[v](p), get(p, m + 1, r, v << 1 | 1));
    }
    
public:
    
    LiChao(int n = 0) : n(n + 1)
    {
        tree.resize(4 * n + 5);
    }
    
    void update(Function func)
    {
        update(0, n - 1, 0, n - 1, 1, func);
    }
    
    void update(int a, int b, Function func)
    {
        update(a, b, 0, n - 1, 1, func);
    }
    
    T get(int p)
    {
        return get(p, 0, n - 1, 1);
    }
    
};
