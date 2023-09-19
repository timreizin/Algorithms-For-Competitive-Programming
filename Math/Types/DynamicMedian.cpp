template <class T>
class DynamicMedian
{
private:

    std::multiset<T> l;
    std::multiset<T> r;

public:

    DynamicMedian(const T minT, const T maxT)
    {
        l.insert(minT);
        r.insert(maxT);
    }

    void insert(const T val)
    {
        if (l.size() == r.size())
        {
            if (val <= (*r.begin()))
                l.insert(val);
            else
            {
                r.insert(val);
                l.insert(*r.begin());
                r.erase(r.begin());
            }
        }
        else
        {
            if (val >= (*r.begin()))
                r.insert(val);
            else
            {
                l.insert(val);
                r.insert(*l.rbegin());
                l.erase((--l.end()));
            }
        }
    }

    void erase(T val)
    {
        if (l.size() == r.size())
        {
            if (val >= (*r.begin()))
                r.erase(r.find(val));
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
                l.erase(l.find(val));
            else
            {
                r.erase(r.find(val));
                r.insert(*l.rbegin());
                l.erase((--l.end()));
            }
        }
    }

    T median()
    {
        return (*l.rbegin());
    }
};
