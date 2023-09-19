void fft(std::vector<std::complex<long double>> &a, const std::vector<int> &indexInEnd, const std::vector<std::complex<long double>> &roots)
{
    int n = (int)a.size();
    for (int i = 0; i < n; ++i)
        if (i < indexInEnd[i])
            swap(a[i], a[indexInEnd[i]]);
    for (int length = 1, rootStep = n / 2; length < n; length <<= 1, rootStep >>= 1)
    {
        for (int i = 0; i < n; i += 2 * length)
        {
            for (int j = i; j < i + length; ++j)
            {
                std::complex<long double> value = roots[(j - i) * rootStep] * a[j + length];
                a[j + length] = a[j] - value;
                a[j] = a[j] + value;
            }
        }
    }
}

void inverseFft(std::vector<std::complex<long double>> &a, const std::vector<int> &indexInEnd, const std::vector<std::complex<long double>> &roots)
{
    fft(a, indexInEnd, roots);
    for (int i = 0; i < a.size(); ++i)
        a[i] /= a.size();
    reverse(a.begin() + 1, a.end());
}

std::vector<long long> convolution(std::vector<long long> &a, std::vector<long long> &b)
{
    int resultSize = (int)a.size() + (int)b.size() - 1;
    int n = 1 << (32 - __builtin_clz(resultSize) - ((resultSize & (resultSize - 1)) == 0));
    std::vector<std::complex<long double>> tA(n), tB(n);
    for (int i = 0; i < a.size(); ++i)
        tA[i] = a[i];
    for (int i = 0; i < b.size(); ++i)
        tB[i] = b[i];
    std::vector<int> indexInEnd(n);
    for (int i = 1, log2 = -1, length = (31 - __builtin_clz(n)); i < n; ++i)
    {
        if (!(i & (i - 1)))
            ++log2;
        indexInEnd[i] = indexInEnd[i ^ (1 << log2)];
        indexInEnd[i] |= (1 << (length - log2 - 1));
    }
    std::vector<std::complex<long double>> roots(n);
    for (int i = 0; i < n; ++i)
    {
        long double alpha = 2 * std::numbers::pi * i / n;
        roots[i] = {cos(alpha), sin(alpha)};
    }
    fft(tA, indexInEnd, roots);
    fft(tB, indexInEnd, roots);
    std::vector<std::complex<long double>> tC(n);
    for (int i = 0; i < n; ++i)
        tC[i] = tA[i] * tB[i];
    inverseFft(tC, indexInEnd, roots);
    std::vector<long long> c((int)a.size() + (int)b.size() - 1);
    for (int i = 0; i < (int)c.size(); ++i)
        c[i] = (long long)(tC[i].real() + 0.5);
    return c;
}
