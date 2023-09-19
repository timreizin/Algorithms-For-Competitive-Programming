template <class T>
std::vector<int> compress(std::vector<T> values, bool isSorted = false)
{
    std::vector compressed = values;
    if (!isSorted)
        std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());
    for (T &i : compressed)
        i = std::distance(values.begin(), std::lower_bound(values.begin(), values.end(), i));
    return compressed;
}
