
template <class T = long double>
T ternarySearch(T l, T r, const T (*f)(T), const T &EPS)
{
    while (r - l > EPS)
    {
        T m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        if (f(m1) < f(m2))
            l = m1;
        else
            r = m2;
    }
    return f(l);
}
