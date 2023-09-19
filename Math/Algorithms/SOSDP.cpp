template <class T>
std::vector<T> sosDP(const std::vector<T> &a, int n)
{
    std::vector<T> dp(a.size());
    for (int i = 0; i < a.size(); ++i)
        dp[i] = a[i];
    for (int i = 0; i < n; ++i)
    {
        for (int mask = 0; mask < (1 << n); ++mask)
        {
            if (mask & (1 << i)) // (!(mask & (1 << i)) for supersets
            {
                dp[mask] += dp[mask ^ (1 << i)];
            }
        }
    }
    return dp;
}
