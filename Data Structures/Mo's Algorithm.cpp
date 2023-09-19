class Mo
{
private:

    struct query
    {
        int l;
        int r;
        int index;

        query(int l, int r, int index) : l(l), r(r), index(index)
        {}
    };

    struct value
    {
        std::vector<int> counter;
        int res = 0;
    };

    int size;
    int divider;
    int n;
    std::vector<int> arr;
    std::vector<std::vector<query>> blocks;

    void add(int ind, value &val)
    {
        ++val.counter[arr[ind]];
        if (val.counter[arr[ind]] == 1)
            ++val.res;
    }

    void del(int ind, value &val)
    {
        --val.counter[arr[ind]];
        if (val.counter[arr[ind]] == 0)
            --val.res;
    }

    void adjust(int &l, int &r, const query &q, value &val)
    {
        while (r < q.r)
        {
            ++r;
            add(r, val);
        }
        while (l > q.l)
        {
            --l;
            add(l, val);
        }
        while (l < q.l)
        {
            del(l, val);
            ++l;
        }
    }

public:

    Mo(const std::vector<int> arr, const std::vector<std::pair<int, int>> queries, int n = -1, int divider = -1) : size((int)queries.size()), arr(arr), divider(divider), n(n)
    {
        if (n == -1)
            for (auto [l, r] : queries)
                n = std::max(n, r);
        if (divider == -1)
            divider = sqrt(n);
        divider = std::max(divider, 1);
        blocks.resize(n / divider + 1);
        for (int i = 0; i < queries.size(); ++i)
            blocks[queries[i].first / divider].emplace_back(queries[i].first, queries[i].second, i);
        for (auto &i : blocks)
            std::sort(i.begin(), i.end(), [](query a, query b){ return a.r < b.r; });
    }

    std::vector<int> operator()()
    {
        std::vector<int> res(size);
        for (int i = 0; i < blocks.size(); ++i)
        {
            int l = i * divider, r = i * divider - 1;
            value val;
            val.counter.resize(n + 1);
            for (query q : blocks[i])
            {
                adjust(l, r, q, val);
                res[q.index] = val.res;
            }
        }
        return res;
    }

};
