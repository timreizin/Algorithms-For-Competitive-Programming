template <class T>
class Matrix
{
private:

    std::vector<std::vector<T>> matrix;

public:

    Matrix() {}

    Matrix(int n, int m, T val = T()) : matrix(n, std::vector(m, val))
    {}

    Matrix(std::vector<std::vector<T>> matrix) : matrix(matrix)
    {}

    void resize(const int newN, const int newM)
    {
        matrix = vector(newN, vector(newM, T()));
    }

    void clear()
    {
        matrix.clear();
    }

    std::pair<int, int> size() const
    {
        return {matrix.size(), (matrix.size() == 0 ? 0 : matrix[0].size())};
    }

    std::vector<T>& operator[](const int index)
    {
        return matrix[index];
    }

    std::vector<T> operator[](const int index) const
    {
        return matrix[index];
    }

    friend Matrix<T> operator*(const Matrix<T> &m, const T &n)
    {
        Matrix<T> result = m;
        for (std::vector<T> &i : result.matrix)
            for (T &j : i)
                j *= n;
        return result;
    }

    friend Matrix<T> operator*(const T &n, const Matrix<T> &m)
    {
        Matrix<T> result = m;
        for (std::vector<T> &i : result.matrix)
            for (T &j : i)
                j *= n;
        return result;
    }

    friend std::vector<T> operator*(const Matrix<T> &m, const std::vector<T> &v)
    {
        std::vector<T> result;
        for (const std::vector<T> &i : m.matrix)
        {
            T sum = 0;
            for (int j = 0; j < v.size(); ++j)
                sum += i[j] * v[j];
            result.push_back(sum);
        }
        return result;
    }

    friend std::vector<T> operator*(const std::vector<T> &v, const Matrix<T> &m)
    {
        std::vector<T> result;
        for (std::vector<T> i : m.matrix)
        {
            T sum = 0;
            for (int j = 0; j < v.size(); ++j)
                sum += i[j] * v[j];
            result.push_back(sum);
        }
        return result;
    }

    friend Matrix<T> operator*(const Matrix<T> &m1, const Matrix<T> &m2)
    {
        Matrix<T> result(m1.size().first, m2.size().second);
        for (int i = 0; i < result.size().first; ++i)
            for (int j = 0; j < result.size().second; ++j)
                for (int k = 0; k < m1.size().first; ++k)
                    result[i][j] += m1[i][k] * m2[k][j];
        return result;
    }

    void operator*=(const T &n)
    {
        *this = *this * n;
    }

    void operator*=(const Matrix<T> &m)
    {
        *this = *this * m;
    }
};
