template <class T>
T extendedGCD(T a, T b, T &x, T &y)
{
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }
    T x1, y1;
    T gcd = extendedGCD(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}
