void ntt(std::vector<long long> &a, const std::vector<int> &indexInEnd, const std::vector<long long> &roots)
{
    int n = (int)a.size();
    for (int i = 0; i < n; ++i)
        if (i < indexInEnd[i])
            std::swap(a[i], a[indexInEnd[i]]);
    for (int length = 1, rootStep = n / 2; length < n; length <<= 1, rootStep >>= 1)
    {
        for (int i = 0; i < n; i += 2 * length)
        {
            for (int j = i; j < i + length; ++j)
            {
                long long value = (roots[(j - i) * rootStep] * a[j + length]) % MOD;
                a[j + length] = (a[j] - value + MOD) % MOD;
                a[j] = (a[j] + value) % MOD;
            }
        }
    }
}

void inverseNtt(std::vector<long long> &a, const std::vector<int> &indexInEnd, const std::vector<long long> &roots)
{
    ntt(a, indexInEnd, roots);
    long long inverseSize = binPow(a.size(), MOD - 2);
    for (int i = 0; i < a.size(); ++i)
        a[i] = (a[i] * inverseSize) % MOD;
    reverse(a.begin() + 1, a.end());
}

std::vector<long long> convolution(std::vector<long long> a, std::vector<long long> b)
{
    if (a.size() < b.size())
        a.swap(b);
    int resultSize = (int)a.size() + (int)b.size() - 1;
    int n = 1 << (32 - __builtin_clz(resultSize) - ((resultSize & (resultSize - 1)) == 0));
    a.resize(n);
    b.resize(n);
    long long g = binPow(3, (MOD - 1) / n);
    std::vector<int> indexInEnd(n);
    for (int i = 1, log2 = -1, length = (31 - __builtin_clz(n)); i < n; ++i)
    {
        if (!(i & (i - 1)))
            ++log2;
        indexInEnd[i] = indexInEnd[i ^ (1 << log2)];
        indexInEnd[i] |= (1 << (length - log2 - 1));
    }
    std::vector<long long> roots(n);
    roots[0] = 1;
    for (int i = 1; i < n; ++i)
        roots[i] = (roots[i - 1] * g) % MOD;
    ntt(a, indexInEnd, roots);
    ntt(b, indexInEnd, roots);
    for (int i = 0; i < n; ++i)
        a[i] = (a[i] * b[i]) % MOD;
    inverseNtt(a, indexInEnd, roots);
    a.resize(resultSize);
    return a;
}
