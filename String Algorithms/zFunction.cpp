#include <vector>
#include <string>

std::vector<int> zetF(const std::string &s)
{
    std::vector<int> zF(s.size());
    for (int i = 1, l = 0, r = 0; i < s.size(); ++i)
    {
        if (i <= r) zF[i] = std::min(r - i + 1, zF[i - l]);
        while (i + zF[i] < s.size() && s[zF[i]] == s[i + zF[i]]) ++zF[i];
        if (i + zF[i] - 1 > r)
        {
            l = i;
            r = i + zF[i] - 1;
        }
    }
    return zF;
}
