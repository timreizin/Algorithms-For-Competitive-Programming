struct XorBasis
{
    std::vector<long long> basis;

    void insert(long long x)
    {
        for (long long i : basis)
            x = std::min(x, x ^ i);
        if (x != 0)
            basis.push_back(x);
    }

    bool check(long long x)
    {
        for (long long i : basis)
            x = std::min(x, x ^ i);
        return x == 0;
    }

    int size()
    {
        return (int)basis.size();
    }

};
