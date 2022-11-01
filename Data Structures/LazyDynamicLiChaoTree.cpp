template <class Function>
class LazyDynamicLiChao
{
private:
    
    using T = typename Function::type;
    
    T minValue, maxValue;
    vector<Function> tree;
    vector<Function> mod;
    vector<pair<int, int>> child;
    
    void push(int v)
    {
        if (mod[v].k != 0)
        {
            if (child[v].first != -1)
            {
                mod[child[v].first].k += mod[v].k;
                tree[child[v].first].k += mod[v].k;
            }
            if (child[v].second != -1)
            {
                mod[child[v].second].k += mod[v].k;
                tree[child[v].second].k += mod[v].k;
            }
            mod[v].k = 0;
        }
        if (mod[v].b != 0)
        {
            if (child[v].first != -1)
            {
                mod[child[v].first].b += mod[v].b;
                tree[child[v].first].b += mod[v].b;
            }
            if (child[v].second != -1)
            {
                mod[child[v].second].b += mod[v].b;
                tree[child[v].second].b += mod[v].b;
            }
            mod[v].b = 0;
        }
    }
    
    void update(T a, T b, T l, T r, int v, Function func)
    {
        if (a > r || b < l) return;
        T m = l + (r - l) / 2;
        if (a == l && b == r)
        {
            if (func(m) > tree[v](m)) swap(tree[v], func);
            if (func(l) <= tree[v](l) && func(r) <= tree[v](r)) return;
            push(v);
            if (func(l) > tree[v](l))
            {
                if (child[v].first == -1)
                {
                    child[v].first = (int)child.size();
                    tree.push_back(Line<T>());
                    mod.push_back(Line<T>());
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
                    mod.push_back(Line<T>());
                    child.emplace_back(-1, -1);
                }
                update(max(a, m + 1), b, m + 1, r, child[v].second, func);
            }
            return;
        }
        push(v);
        if (a <= m)
        {
            if (child[v].first == -1)
            {
                child[v].first = (int)child.size();
                tree.push_back(Line<T>());
                mod.push_back(Line<T>());
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
                mod.push_back(Line<T>());
                child.emplace_back(-1, -1);
            }
            update(max(a, m + 1), b, m + 1, r, child[v].second, func);
        }
    }
    
    T get(T p, T l, T r, int v)
    {
        if (v == -1) return 0;
        if (l == r) return tree[v](p);
        T m = l + (r - l) / 2;
        push(v);
        if (p <= m) return max(tree[v](p), get(p, l, m, child[v].first));
        else return max(tree[v](p), get(p, m + 1, r, child[v].second));
    }
    
    void addK(T a, T b, T k, T l, T r, int v)
    {
        if (a > r || b < l) return;
        if (a == l && b == r)
        {
            mod[v].k += k;
            tree[v].k += k;
            return;
        }
        T m = l + (r - l) / 2;
        push(v);
        if (a <= m)
        {
            if (child[v].first == -1)
            {
                child[v].first = (int)child.size();
                tree.push_back(Line<T>());
                mod.push_back(Line<T>());
                child.emplace_back(-1, -1);
            }
            addK(a, min(b, m), k, l, m, child[v].first);
        }
        if (b > m)
        {
            if (child[v].second == -1)
            {
                child[v].second = (int)child.size();
                tree.push_back(Line<T>());
                mod.push_back(Line<T>());
                child.emplace_back(-1, -1);
            }
            addK(max(a, m + 1), b, k, m + 1, r, child[v].second);
        }
    }
    
    void addB(T a, T b, T k, T l, T r, int v)
    {
        if (a > r || b < l) return;
        if (a == l && b == r)
        {
            mod[v].b += k;
            tree[v].b += k;
            return;
        }
        T m = l + (r - l) / 2;
        push(v);
        if (a <= m)
        {
            if (child[v].first == -1)
            {
                child[v].first = (int)child.size();
                tree.push_back(Line<T>());
                mod.push_back(Line<T>());
                child.emplace_back(-1, -1);
            }
            addB(a, min(b, m), k, l, m, child[v].first);
        }
        if (b > m)
        {
            if (child[v].second == -1)
            {
                child[v].second = (int)child.size();
                tree.push_back(Line<T>());
                mod.push_back(Line<T>());
                child.emplace_back(-1, -1);
            }
            addB(max(a, m + 1), b, k, m + 1, r, child[v].second);
        }
    }
    
public:
    
    LazyDynamicLiChao(T maxValue) : minValue(0), maxValue(maxValue)
    {
        child.emplace_back(-1, -1);
        tree.push_back(Line<T>());
        mod.push_back(Line<T>());
    }
    
    LazyDynamicLiChao(T minValue = -1e9, T maxValue = 1e9) : minValue(minValue), maxValue(maxValue)
    {
        child.emplace_back(-1, -1);
        tree.push_back(Line<T>());
        mod.push_back(Line<T>());
    }
    
    void addLine(Function func)
    {
        update(minValue, maxValue, minValue, maxValue, 0, func);
    }
    
    void addLine(T a, T b, Function func)
    {
        update(a, b, minValue, maxValue, 0, func);
    }
    
    void addK(T a, T b, T k)
    {
        addK(a, b, k, minValue, maxValue, 0);
    }
    
    void addK(T k)
    {
        addK(minValue, maxValue, k, minValue, maxValue, 0);
    }
    
    void addB(T a, T b, T k)
    {
        addB(a, b, k, minValue, maxValue, 0);
    }
    
    void addB(T k)
    {
        addB(minValue, maxValue, k, minValue, maxValue, 0);
    }
    
    T get(T p)
    {
        return get(p, minValue, maxValue, 0);
    }
    
};
