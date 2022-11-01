class BigInt
{
private:

    const static int base = 1000000000;   //base of number, should be power of 10
    const static int base_digits = 9;     //amount of base10 digits in base

    vector<int> digits;
    int sign;

    //Trims leading zeros
    void trim()
    {
        while (!digits.empty() && digits.back() == 0)
        {
            digits.pop_back();
        }
        if (digits.empty())
        {
            sign = 1;
        }
    }

    pair<BigInt, BigInt> division(const BigInt &number1, const BigInt &number2) const
    {
        BigInt result, currentValue;
        result.sign = number1.sign * number2.sign;
        result.digits.resize(number1.digits.size());
        for (int i = (int)number1.digits.size() - 1; i >= 0; --i)
        {
            currentValue = currentValue * base + number1.digits[i];
            int l = 0, r = base;
            while (l < r)
            {
                int m = (l + r) >> 1;
                if (abs(number2) * m <= currentValue)
                {
                    l = m + 1;
                }
                else
                {
                    r = m;
                }
            }
            result.digits[i] = l - 1;
            currentValue -= abs(number2) * BigInt(l - 1);
        }
        result.trim();
        currentValue.sign = number1.sign;
        currentValue.trim();
        return {result, currentValue};
    }

public:

    //Default constructor, sets number = 0
    BigInt() : sign(1)
    {}

    //Constructor, sets number = n
    BigInt(long long n)
    {
        sign = (int)(n != 0ll ? n / abs(n) : 1ll);
        n = abs(n);
        for (; n > 0; n /= base)
        {
            digits.push_back(n % base);
        }
    }
    //Constructor, sets number = s
    BigInt(const string &s)
    {
        sign = 1;
        digits.clear();
        int pos = 0;
        while (pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+'))
        {
            if (s[pos] == '-')
            {
                sign = -sign;
            }
            ++pos;
        }
        for (int i = (int)s.size() - 1; i >= pos; i -= base_digits)
        {
            int digit = 0;
            for (int j = max(pos, i - base_digits + 1); j <= i; ++j)
            {
                digit = digit * 10 + (s[j] - '0');
            }
            digits.push_back(digit);
        }
        trim();
    }

    //Overload of operator =
    BigInt& operator=(const BigInt &number)
    {
        sign = number.sign;
        digits = number.digits;
        return *this;
    }

    //Overload of unary operator +
    BigInt operator+() const
    {
        return *this;
    }

    //Overload of unary operator -
    BigInt operator-() const
    {
        BigInt res = *this;
        res.sign = -sign;
        res.trim();
        return res;
    }

    //Overload of binary operator +
    BigInt operator+(const BigInt &number) const
    {
        if (sign == number.sign)
        {
            BigInt result = number;
            for (int i = 0, carry = 0; i < (int)max(digits.size(), number.digits.size()) || carry; ++i)
            {
                if (i == (int)result.digits.size())
                {
                    result.digits.push_back(0);
                }
                result.digits[i] += carry + (i < (int)digits.size() ? digits[i] : 0);
                carry = result.digits[i] >= base;
                if (carry)
                {
                    result.digits[i] -= base;
                }
            }
            result.trim();
            return result;
        }
        return *this - (-number);
    }

    //Overload of binary operator -
    BigInt operator-(const BigInt &number) const
    {
        if (sign == number.sign)
        {
            if (abs(*this) >= abs(number))
            {
                BigInt result = *this;
                for (int i = 0, carry = 0; i < (int)number.digits.size() || carry; ++i)
                {
                    result.digits[i] -= carry + (i < (int)number.digits.size() ? number.digits[i] : 0);
                    carry = result.digits[i] < 0;
                    if (carry)
                    {
                        result.digits[i] += base;
                    }
                }
                result.trim();
                return result;
            }
            return -(number - *this);
        }
        return *this + (-number);
    }

    //Overload of binary operator *
    BigInt operator*(const BigInt &number) const
    {
        BigInt result;
        result.sign = this->sign * number.sign;
        result.digits.resize((int)this->digits.size() + (int)number.digits.size());
        for (int i = 0; i < (int)this->digits.size(); ++i)
        {
            for (int j = 0, carry = 0; j < (int)number.digits.size() || carry; j++)
            {
                long long current = (long long)result.digits[i + j] + (long long)this->digits[i] * (j < (int)number.digits.size() ? number.digits[j] : 0) + (long long)carry;
                result.digits[i + j] = (int)(current % base);
                carry = (int)(current / base);
            }
        }
        result.trim();
        return result;
    }

    //Overload of binary operator /
    BigInt operator/(const BigInt &number) const
    {
        return division(*this, number).first;
    }

    //Overload of binary operator %
    BigInt operator%(const BigInt &number) const
    {
        return division(*this, number).second;
    }

    //Operator += overload
    void operator+=(const BigInt &number)
    {
        *this = *this + number;
    }

    //Operator -= overload
    void operator-=(const BigInt &number)
    {
        *this = *this - number;
    }

    //Operator *= overload
    void operator*=(const BigInt &number)
    {
        *this = *this * number;
    }

    //Operator /= overload
    void operator/=(const BigInt &number)
    {
        *this = *this / number;
    }

    //Operator %= overload
    void operator%=(const BigInt &number)
    {
        *this = *this % number;
    }

    //Operator < overload
    bool operator<(const BigInt &number) const
    {
        if (sign != number.sign)
        {
            return sign < number.sign;
        }
        if ((int)digits.size() != (int)number.digits.size())
        {
            return (int)digits.size() * sign < (int)number.digits.size() * number.sign;
        }
        for (int i = (int)digits.size() - 1; i >= 0; --i)
        {
            if (digits[i] != number.digits[i])
            {
                return digits[i] * sign < number.digits[i] * sign;
            }
        }
        return false;
    }

    //Operator > overload
    bool operator>(const BigInt &number) const
    {
        return number < *this;
    }

    //Operator <= overload
    bool operator<=(const BigInt &number) const
    {
        return !(number < *this);
    }

    //Operator >= overload
    bool operator>=(const BigInt &number) const
    {
        return !(*this < number);
    }

    //Operator == overload
    bool operator==(const BigInt &number) const
    {
        return !(*this < number) && !(number < *this);
    }

    //Operator != overload
    bool operator!=(const BigInt &number) const
    {
        return *this < number || number < *this;
    }

    //Input operator overload
    friend istream& operator>>(istream &in, BigInt &number)
    {
        string s;
        in >> s;
        number = s;
        return in;
    }

    //Output operator overload
    friend ostream& operator<<(ostream &out, const BigInt &number)
    {
        if (number.sign == -1)
        {
            out << '-';
        }
        out << (number.digits.empty() ? 0 : number.digits.back());
        for (int i = (int)number.digits.size() - 2; i >= 0; --i)
        {
            out << setw(base_digits) << setfill('0') << number.digits[i];
        }
        return out;
    }

    //Returns length of number
    int length() const
    {
        int result = 0, lastDigit = digits.back();
        while (lastDigit)
        {
            ++result;
            lastDigit /= 10;
        }
        result += (digits.size() - 1) * base_digits;
        return result;
    }

    //Returns absolute value of number
    friend BigInt abs(const BigInt &number)
    {
        BigInt result = number;
        result.sign *= result.sign;
        return result;
    }

    //Swap two numbers
    friend void swap(BigInt &a, BigInt &b)
    {
        swap(a.sign, b.sign);
        a.digits.swap(b.digits);
    }
};
