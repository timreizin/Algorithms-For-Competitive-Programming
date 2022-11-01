struct dynMed
{
    multiset<int> l{-1};
    multiset<int> r{(int)1e9 + 1};

    void insert(int val)
    {
        if (l.size() == r.size())
        {
            if (val <= (*r.begin())) l.insert(val);
            else
            {
                r.insert(val);
                l.insert(*r.begin());
                r.erase(r.begin());
            }
        }
        else
        {
            if (val >= (*r.begin())) r.insert(val);
            else
            {
                l.insert(val);
                r.insert(*l.rbegin());
                l.erase((--l.end()));
            }
        }
    }

    void erase(int val)
    {
        if (l.size() == r.size())
        {
            if (val >= (*r.begin()))
            {
                r.erase(r.find(val));
            }
            else
            {
                l.erase(l.find(val));
                l.insert(*r.begin());
                r.erase(r.begin());
            }
        }
        else
        {
            if (val <= (*l.rbegin()))
            {
                l.erase(l.find(val));
            }
            else
            {
                r.erase(r.find(val));
                r.insert(*l.rbegin());
                l.erase((--l.end()));
            }
        }
    }

    int median()
    {
        return (*l.rbegin());
    }
};
