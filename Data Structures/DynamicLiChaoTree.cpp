template <class Function>
class DynamicLiChao
{
private:
    
    using T = typename Function::type;
    
    T minValue, maxValue;
    vector<Function> tree;
    vector<pair<int, int>> child;
    
    void update(T a, T b, T l, T r, int v, Function func)
    {
        if (a > r || b < l) return;
        T m = l + (r - l) / 2;
        if (a == l && b == r)
        {
            if (func(m) < tree[v](m)) swap(tree[v], func);
            if (func(l) >= tree[v](l) && func(r) >= tree[v](r)) return;
            if (func(l) < tree[v](l))
            {
                if (child[v].first == -1)
                {
                    child[v].first = (int)child.size();
                    tree.push_back(Line<T>());
                    child.emplace_back(-1, -1);
                }
                update(a, min(b, m), l, m, child[v].first, func);
            }
            else
            {
                if (child[v].second == -1)
                {
                    child[v].second = (int)child.size();
                    tree.push_back(Line<T>());
                    child.emplace_back(-1, -1);
                }
                update(max(a, m + 1), b, m + 1, r, child[v].second, func);
            }
            return;
        }
        if (a <= m)
        {
            if (child[v].first == -1)
            {
                child[v].first = (int)child.size();
                tree.push_back(Line<T>());
                child.emplace_back(-1, -1);
            }
            update(a, min(b, m), l, m, child[v].first, func);
        }
        if (b > m)
        {
            if (child[v].second == -1)
            {
                child[v].second = (int)child.size();
                tree.push_back(Line<T>());
                child.emplace_back(-1, -1);
            }
            update(max(a, m + 1), b, m + 1, r, child[v].second, func);
        }
    }
    
    T get(T p, T l, T r, int v)
    {
        if (v == -1) return LONGINF;
        if (l == r) return tree[v](p);
        T m = l + (r - l) / 2;
        if (p <= m) return min(tree[v](p), get(p, l, m, child[v].first));
        else return min(tree[v](p), get(p, m + 1, r, child[v].second));
    }
    
public:
    
    DynamicLiChao(T maxValue) : minValue(0), maxValue(maxValue)
    {
        child.emplace_back(-1, -1);
        tree.push_back(Line<T>());
    }
    
    DynamicLiChao(T minValue = -1e9, T maxValue = 1e9) : minValue(minValue), maxValue(maxValue)
    {
        child.emplace_back(-1, -1);
        tree.push_back(Line<T>());
    }
    
    void update(Function func)
    {
        update(minValue, maxValue, minValue, maxValue, 0, func);
    }
    
    void update(T a, T b, Function func)
    {
        update(a, b, minValue, maxValue, 0, func);
    }
    
    T get(T p)
    {
        return get(p, minValue, maxValue, 0);
    }
    
};
