double ternarySearch(ld l, ld r, ld (*f)(ld), ld EPS)
{
    while (r - l > EPS)
    {
        ld m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        if (f(m1) < f(m2)) l = m1;
        else r = m2;
    }
    return f(l);
}
