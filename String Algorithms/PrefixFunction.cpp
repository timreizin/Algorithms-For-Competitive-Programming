std::vector<int> prefixFunction(const std::string &s)
{
    std::vector<int> prefixF(s.size());
    for (int i = 1, j; i < s.size(); ++i)
    {
        for (j = prefixF[i - 1]; j > 0 && s[i] != s[j]; j = prefixF[j - 1]) {}
        prefixF[i] = j;
        if (s[i] == s[j]) 
            ++prefixF[i];
    }
    return prefixF;
}
