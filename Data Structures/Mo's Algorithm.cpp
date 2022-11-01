class Mo
{
private:

    struct query
    {
        int l;
        int r;
        int index;

        query(int al, int ar, int aindex) : l(al), r(ar), index(aindex)
        {}
    };

    struct value
    {
        vector<int> counter;
        int res = 0;
    };

    int size;
    int divider;
    int n;
    vector<int> arr;
    vector<vector<query>> blocks;

    void add(int ind, value &val)
    {
        ++val.counter[arr[ind]];
        if (val.counter[arr[ind]] == 1) ++val.res;
    }

    void del(int ind, value &val)
    {
        --val.counter[arr[ind]];
        if (val.counter[arr[ind]] == 0) --val.res;
    }

    void adjust(int &l, int &r, query &q, value &val)
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

    Mo(vector<int> aarr, vector<pair<int, int>> queries, int an = -1, int adivider = -1) : size((int)queries.size()), arr(aarr)
    {
        n = an;
        if (n == -1) for (auto [l, r] : queries) n = max(n, r);
        if (adivider == -1) adivider = sqrt(n);
        divider = max(adivider, 1);
        blocks.resize(n / divider + 1);
        for (int i = 0; i < queries.size(); ++i) blocks[queries[i].first / divider].emplace_back(queries[i].first, queries[i].second, i);
        for (auto &i : blocks) sort(i.begin(), i.end(), [](query a, query b){ return a.r < b.r; });
    }

    vector<int> operator()()
    {
        vector<int> res(size);
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
