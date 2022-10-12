#include <vector>

std::pair<std::vector<int>, std::vector<int>> sieveOfEratosthenes(int n)
{
    std::vector<int> smallestDivisor(n + 1, 0);
    std::vector<int> primes;
    for (int i = 2; i <= n; ++i)
    {
        if (smallestDivisor[i] == 0)
        {
            smallestDivisor[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && primes[j] <= smallestDivisor[i] && i * primes[j] <= n; ++j)
            smallestDivisor[i * primes[j]] = primes[j];
    }
    return {primes, smallestDivisor};
}
