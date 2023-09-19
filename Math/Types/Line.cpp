template <class T = long long>
struct Line
{
    using type = T;

    T k, b;

    Line(T k = 0, T b = 0) : k(k), b(b)
    {}

    T operator()(T x)
    {
        return k * x + b;
    }
};
