std::vector<std::vector<long long>> floydWarshall(const std::vector<std::vector<long long>> &adj)
{
    constexpr long long INF = 1e18;
    std::vector<std::vector<long long>> distances = adj;
    for (int k = 0; k < adj.size(); ++k)
        for (int i = 0; i < adj.size(); ++i)
            for (int j = 0; j < adj.size(); ++j)
                if (distances[i][k] < INF && distances[j][k] < INF)
                    distances[i][j] = std::min(distances[i][j], distances[i][k] + distances[k][j]);
    return distances;
}
