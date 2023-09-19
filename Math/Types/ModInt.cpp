template <class T = long long, T MOD = T(1e9 + 7)>
class ModNumber
{
private:

    T number;

    static T binPow(T a, T n)
    {
        T res = 1;
        while (n)
        {
            if (n & 1) res = (res * a) % MOD;
            a = (a * a) % MOD;
            n >>= 1;
        }
        return res;
    }

public:

    ModNumber(long long n = 0) : number(T(n) % MOD)
    {}

    friend ModNumber<T, MOD> operator+(const ModNumber<T, MOD> &n1, const ModNumber<T, MOD> &n2)
    {
        return ((n1.number + n2.number) % MOD + MOD) % MOD;
    }

    friend ModNumber<T, MOD> operator-(const ModNumber<T, MOD> &n1, const ModNumber<T, MOD> &n2)
    {
        return ((n1.number - n2.number) % MOD + MOD) % MOD;
    }

    friend ModNumber<T, MOD> operator*(const ModNumber<T, MOD> &n1, const ModNumber<T, MOD> &n2)
    {
        return ((n1.number * n2.number) % MOD + MOD) % MOD;
    }

    friend ModNumber<T, MOD> operator/(const ModNumber<T, MOD> &n1, const ModNumber<T, MOD> &n2)
    {
        return ((n1.number * binPow(n2.number, MOD - 2)) % MOD + MOD) % MOD;
    }

    void operator+=(const ModNumber<T, MOD> &number)
    {
        *this = *this + number;
    }

    void operator-=(const ModNumber<T, MOD> &number)
    {
        *this = *this - number;
    }

    void operator*=(const ModNumber<T, MOD> &number)
    {
        *this = *this * number;
    }

    void operator/=(const ModNumber<T, MOD> &number)
    {
        *this = *this / number;
    }

    friend std::ostream& operator<<(std::ostream &out, const ModNumber<T, MOD> &n)
    {
        out << n.number;
        return out;
    }

    friend std::istream& operator>>(std::istream &in, ModNumber<T, MOD> &n)
    {
        in >> n.number;
        n.number %= MOD;
        return in;
    }

    ModNumber<T, MOD>& operator++()
    {
        ++number;
        number %= MOD;
        return *this;
    }

    ModNumber<T, MOD>& operator--()
    {
        --number;
        if (number < MOD) number += MOD;
        return *this;
    }

    ModNumber<T, MOD> operator++(int)
    {
        ModNumber<T, MOD> temp(number);
        ++(*this);
        return temp;
    }

    ModNumber<T, MOD> operator--(int)
    {
        ModNumber<T, MOD> temp(number);
        --(*this);
        return temp;
    }

    friend bool operator==(const ModNumber<T, MOD> &n1, const ModNumber<T, MOD> &n2)
    {
        return n1.number == n2.number;
    }

    friend bool operator!=(const ModNumber<T, MOD> &n1, const ModNumber<T, MOD> &n2)
    {
        return n1.number != n2.number;
    }

    friend bool operator>(const ModNumber<T, MOD> &n1, const ModNumber<T, MOD> &n2)
    {
        return n1.number > n2.number;
    }

    friend bool operator>=(const ModNumber<T, MOD> &n1, const ModNumber<T, MOD> &n2)
    {
        return n1.number >= n2.number;
    }

    friend bool operator<(const ModNumber<T, MOD> &n1, const ModNumber<T, MOD> &n2)
    {
        return n1.number < n2.number;
    }

    friend bool operator<=(const ModNumber<T, MOD> &n1, const ModNumber<T, MOD> &n2)
    {
        return n1.number <= n2.number;
    }

    ModNumber<T, MOD> operator+() const
    {
        return ModNumber<T, MOD>(number);
    }

    ModNumber<T, MOD> operator-() const
    {
        return ModNumber<T, MOD>(((-number) % MOD + MOD) % MOD);
    }

    T getNumber()
    {
        return number;
    }
};
