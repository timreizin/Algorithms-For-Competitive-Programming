class Treap
{
public:

    struct Value
    {
        long long value;
        long long sum;

        Value(long long value = 0) : value(value), sum(value)
        {}

        void update(Value l, Value r)
        {
            sum = value + l.sum + r.sum;
        }

        void push(Value l, Value r)
        {

        }

    };

    struct Node
    {
        inline static std::mt19937 gen{std::random_device{}()};
        inline static std::uniform_int_distribution<> rand{0, (int)1e9};

        int size;
        int priority;
        int left;
        int right;
        Value value;
        bool isRev;

        Node(Value value = Value()) : value(value), left(-1), right(-1), size(1), priority(rand(gen)), isRev(false)
        {}

        void update(Node &l, Node &r)
        {
            size = 1 + l.size + r.size;
            value.update(l.value, r.value);
        }

        void push(Node &l, Node &r)
        {
            if (isRev)
            {
                isRev = false;
                l.isRev = !l.isRev;
                r.isRev = !r.isRev;
                std::swap(l.left, l.right);
                std::swap(r.left, r.right);
            }
            value.push(l.value, r.value);
        }

    };

private:

    int root = -1;
    std::vector<Node> tree;
    Node empty;

    int getSize(int v)
    {
        return v == - 1 ? 0 : tree[v].size;
    }

    void getArray(int v, std::vector<Value> &arr)
    {
        if (v == -1)
            return;
        tree[v].push((tree[v].left == -1 ? empty : tree[tree[v].left]), (tree[v].right == -1 ? empty : tree[tree[v].right]));
        getArray(tree[v].left, arr);
        arr.push_back(tree[v].value);
        getArray(tree[v].right, arr);
    }

public:

    Treap()
    {
        empty.size = 0;
    }

    Treap(std::vector<Value> &a)
    {
        empty.size = 0;

    }

    std::pair<int, int> split(int v, int pos)
    {
        if (v == -1) return {-1, -1};
        tree[v].push((tree[v].left == -1 ? empty : tree[tree[v].left]), (tree[v].right == -1 ? empty : tree[tree[v].right]));
        if (getSize(tree[v].left) <= pos)
        {
            auto [l, r] = split(tree[v].right, pos - getSize(tree[v].left) - 1);
            tree[v].right = l;
            tree[v].update((tree[v].left == -1 ? empty : tree[tree[v].left]), (tree[v].right == -1 ? empty : tree[tree[v].right]));
            return {v, r};
        }
        else
        {
            auto [l, r] = split(tree[v].left, pos);
            tree[v].left = r;
            tree[v].update((tree[v].left == -1 ? empty : tree[tree[v].left]), (tree[v].right == -1 ? empty : tree[tree[v].right]));
            return {l, v};
        }
    }

    std::pair<int, int> split(int pos)
    {
        return split(root, pos);
    }

    int merge(int l, int r)
    {
        if (r == -1)
            return l;
        else if (l == -1)
            return r;
        if (tree[l].priority < tree[r].priority)
        {
            tree[l].push((tree[l].left == -1 ? empty : tree[tree[l].left]), (tree[l].right == -1 ? empty : tree[tree[l].right]));
            tree[l].right = merge(tree[l].right, r);
            tree[l].update((tree[l].left == -1 ? empty : tree[tree[l].left]), (tree[l].right == -1 ? empty : tree[tree[l].right]));
            return l;
        }
        else
        {
            tree[r].push((tree[r].left == -1 ? empty : tree[tree[r].left]), (tree[r].right == -1 ? empty : tree[tree[r].right]));
            tree[r].left = merge(l, tree[r].left);
            tree[r].update((tree[r].left == -1 ? empty : tree[tree[r].left]), (tree[r].right == -1 ? empty : tree[tree[r].right]));
            return r;
        }
    }

    void insert(int &v, int pos, Value value = Value())
    {
        auto [l, r] = split(v, pos - 1);
        tree.emplace_back(value);
        l = merge(l, (int)tree.size() - 1);
        v = merge(l, r);
    }

    void insert(int &v, int pos, int a)
    {
        auto [l, r] = split(v, pos - 1);
        l = merge(l, a);
        v = merge(l, r);
    }

    void insert(int pos, Value value = Value())
    {
        insert(root, pos, value);
    }

    void insert(int pos, int a)
    {
        insert(root, pos, a);
    }

    void setRoot(int _root)
    {
        root = _root;
    }

    std::vector<Value> getArray(int v)
    {
        std::vector<Value> arr;
        getArray(v, arr);
        return arr;
    }

    std::vector<Value> getArray()
    {
        return getArray(root);
    }

    void reverse(int &v, int a, int b)
    {
        int l, m, r;
        std::tie(m, r) = split(b);
        std::tie(l, m) = split(m, a - 1);
        tree[m].isRev = !tree[m].isRev;
        std::swap(tree[m].left, tree[m].right);
        v = merge(merge(l, m), r);
    }

    void reverse(int a, int b)
    {
        reverse(root, a, b);
    }

    Value getValue(int &v, int a, int b)
    {
        int l, m, r;
        std::tie(m, r) = split(b);
        std::tie(l, m) = split(m, a - 1);
        Value res = tree[m].value;
        v = merge(merge(l, m), r);
        return res;
    }

    Value getValue(int a, int b)
    {
        return getValue(root, a, b);
    }

    int erase(int &v, int a, int b)
    {
        int l, m, r;
        std::tie(m, r) = split(b);
        std::tie(l, m) = split(m, a - 1);
        v = merge(l, r);
        return m;
    }

    int erase(int pos)
    {
        return erase(root, pos, pos);
    }

    int erase(int a, int b)
    {
        return erase(root, a, b);
    }

    int size(int v)
    {
        return tree[v].size;
    }

    int size()
    {
        return tree[root].size;
    }

    //TODO: add linear build

};
