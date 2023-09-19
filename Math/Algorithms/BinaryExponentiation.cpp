template <class T = long long>
T binPow(T base, long long power)
{
    T result = 1;
    while (power)
    {
        if (power & 1)
            result = result * base;
        base = base * base;
        power >>= 1;
    }
    return result;
}
