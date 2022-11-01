struct XorBasis
{
    vector<ll> basis;
    
    void insert(ll x)
    {
        for (ll i : basis) x = min(x, x ^ i);
        if (x != 0) basis.push_back(x);
    }
    
    bool check(ll x)
    {
        for (ll i : basis) x = min(x, x ^ i);
        return x == 0;
    }
    
    int size()
    {
        return (int)basis.size();
    }
    
};
