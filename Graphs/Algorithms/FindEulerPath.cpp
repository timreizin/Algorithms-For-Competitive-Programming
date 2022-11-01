bool findEulerPath(vector<vector<pair<int, int>>> &adjUsed, vector<int> &path, bool isCycle = true, int v = -1)
{
    path.clear();
    int counter = 0;
    bool was = (v == -1);
    int maxEdge = 0;
    for (int i = 1; i < adjUsed.size(); ++i)
    {
        if (adjUsed[i].size() & 1)
        {
            if (v == -1) v = i;
            if (v == i) was = true;
            ++counter;
        }
        for (auto [j, e] : adjUsed[i]) maxEdge = max(maxEdge, e);
    }
    if (counter > 2 || counter == 1 || !was || (counter == 2 && isCycle)) return false;
    stack<int> st;
    if (v == -1) v = 1;
    st.push(v);
    vector<bool> usedEdges(maxEdge + 1);
    vector<int> start(adjUsed.size());
    while (!st.empty())
    {
        int v = st.top();
        bool isEdge = false;
        for (;start[v] < adjUsed[v].size(); ++start[v])
        {
            if (!usedEdges[adjUsed[v][start[v]].second])
            {
                usedEdges[adjUsed[v][start[v]].second] = true;
                st.push(adjUsed[v][start[v]].first);
                isEdge = true;
                break;
            }
        }
        if (!isEdge)
        {
            st.pop();
            path.push_back(v);
        }
    }
    for (int i = 1; i < adjUsed.size(); ++i) if (start[i] == 0 && adjUsed[i].size() > 0) return false;
    reverse(path.begin(), path.end());
    return true;
}
