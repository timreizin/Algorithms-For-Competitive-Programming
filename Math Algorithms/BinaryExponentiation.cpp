const long long MOD = 9982244353;

long long binPow(long long a, long long n)
{
    long long res = 1;
    while (n)
    {
        if (n & 1) res = res * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return res;
}
