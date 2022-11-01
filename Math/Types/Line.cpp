template <class T = ll>
struct Line
{
    using type = T;
    
    T k, b;
    
    Line(T k = 0, T b = LONGINF) : k(k), b(b)
    {}
    
    T operator()(T x)
    {
        return k * x + b;
    }
};
