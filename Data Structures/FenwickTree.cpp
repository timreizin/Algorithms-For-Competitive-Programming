#include <vector>

template <class T = long long>
class FenwickTree
{
private:
    
    int amount;
    std::vector<T> tree;
    
    T get(int pos)
    {
        T result = 0;
        for (; pos >= 0; pos = (pos & (pos + 1)) - 1) result += tree[pos];
        return result;
    }
    
public:
    
    void update(int pos, T value)
    {
        for (; pos < amount; pos |= pos + 1) tree[pos] += value;
    }
    
    FenwickTree(int n) : amount(n)
    {
        tree.resize(n);
    }
    
    FenwickTree(int n, const std::vector<T> &a)
    {
        FenwickTree((int)a.size());
        for (int i = 0; i < n; ++i) update(i, a[i]);
    }
    
    T get(int a, int b)
    {
        return get(b) - (a == 0 ? 0 : get(a - 1));
    }
};
