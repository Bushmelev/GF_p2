#ifndef GF_p2_H
#define GP_p2_H 1

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cassert>

// Extended Euclid's Algorithm
// Input: integer numbers m, n, one of them must be nonzero.
// Output: d = gcd(m, n) and integers u, v such that
//     d = u*m + v*n
void extEucl(
    int m, int n,
    int& d, int& u, int& v
);

// Fast Power Algorithm
int powermod(int a, int n, int m, bool check_sq);

int factorial(int N);

class GF_p2_Exception {
private:
    const char* errorText;
public:
    GF_p2_Exception(const char* reason = "") :
        errorText(reason)
    {}

    const char* what() { return errorText; }
};

class GF_p2 {
private:
    std::vector<int> v;
    static int m;
    static int r;
public:
    void setVector(int a, int b) { v[0] = a; v[1] = b; }
    static void setMod(int mmm) { m = abs(mmm); }
    static void setRes(int m) {
        for (int i = m-1; i >= 0; i--) {
            r = powermod(i, m, m, true);
            if (r != 1) {
                r = i;
                std::cout << "f(x) = x^2-" << r << std::endl;
                break;
            }
        }
    }

    GF_p2() : v{ 0, 0 } {}

    GF_p2& operator+=(const GF_p2& u) {
        v[0] = (v[0] + u.v[0]) % m;
        v[1] = (v[1] + u.v[1]) % m;
        return *this;
    }

    GF_p2& operator-=(const GF_p2& u) {
        v[0] = (v[0] - u.v[0]) % m;
        v[1] = (v[1] - u.v[1]) % m;
        return *this;
    }
    GF_p2& operator*=(const GF_p2& u) {
        int a = v[0]; int b = v[1]; int c = u.v[0]; int d = u.v[1];
        v[0] = (a * d + b * c) % m;
        v[1] = (a * c * r + b * d) % m;
        return *this;
    }
    
    GF_p2 inverse() const {
        int a = v[0]; int b = v[1];
        int h, h_inv, d, i, j;
        h = (a * a * r - b * b) % m;
        if (h < 0)
            h += m;
        //h_inv = (int) pow(h, m-2) % m;
        extEucl(h, m, d, i, j);
        h_inv = i;
        assert(d == i * h + j * m);
        if (d == 1) {
            a = (h_inv * a) % m;
            b = (h_inv * (-b)) % m;
            GF_p2 u; u.setVector(a, b);
            return u; 
        }
        else
            throw GF_p2_Exception("Element is not invertible modulo m");
    }
    
    GF_p2& operator/=(const GF_p2& k) {
        GF_p2 u; u.setVector(v[0], v[1]);
        u = k.inverse(); 
        int a = v[0]; int b = v[1]; int c = u.v[0]; int d = u.v[1];
        v[0] = (a * d + b * c) % m;
        v[1] = (a * c * r + b * d) % m;
        return *this;
    }

    bool operator==(const GF_p2& k) const {
        int a, b;
        if ((v[0] < 0) | (v[1] < 0)) {
            a = (v[0] + m) % m;
            b = (v[1] + m) % m;
        }
        else {
            a = v[0];
            b = v[1];
        }
        return ((a == k.v[0]) & (b == k.v[1]));
    }

    bool operator!=(const GF_p2& k) const {
        return !operator==(k);
    }

    std::string print() const{
        std::string str;
        if (v[0] == 0) {
            if (v[1] == 0)
                str = std::to_string(0) + "\n";
            else
                str = std::to_string(v[1]) + "\n";
        }
        else {
            if (v[1] > 0)
                str = std::to_string(v[0]) + "x+" + std::to_string(v[1]) + "\n";
            else
                if (v[1] < 0)
                    str = std::to_string(v[0]) + "x" + std::to_string(v[1]) + "\n";
                else
                    str = std::to_string(v[0]) + "x" + "\n";
        }
        return str;
    }

    GF_p2 power(int n) const{
        int C;
        int a = 0; int b = 0;
        for (int k = n; k >= 0; k--) {
            C = factorial(n) / factorial(k) / factorial(n - k);
            if (k % 2 == 1) {
                if (k == 1)
                    a = (a += (powermod(v[0], k, m, false) * powermod(v[1], n - k, m, false) * C)) % m;
                else
                    a = (a += (powermod(v[0], k, m, false) * powermod(v[1], n - k, m, false) * C * (k / 2) * r)) % m;
            }
            else {
                if (k == 0)
                    b = (b += powermod(v[0], k, m, false) * powermod(v[1], n - k, m, false) * C) % m;
                else
                    b = (b += (powermod(v[0], k, m, false) * powermod(v[1], n - k, m, false) * C * (k / 2) * r)) % m;
            }
        }
        GF_p2 u; u.setVector(a, b);
        return u;
    }
};

inline GF_p2 operator+(const GF_p2& v, const GF_p2& u) {
    GF_p2 res = v;
    res += u;
    return res;
}

inline GF_p2 operator-(const GF_p2& v, const GF_p2& u) {
    GF_p2 res = v;
    res -= u;
    return res;
}

inline  GF_p2 operator*(const GF_p2& v, const GF_p2& u) {
    GF_p2 res = v;
    res *= u;
    return res;
}

inline GF_p2 operator/(const GF_p2& a, const GF_p2& b) {
    GF_p2 res = a;
    res /= b;
    return res;
}

inline std::ostream& operator<<(std::ostream& s, const GF_p2& x) {
    s << x.print();
    return s;
}

inline std::istream& operator>>(std::istream& s, GF_p2& x) {
    int a, b;
    s >> a >> b;
    if (s.good())
        x.setVector(a, b);
    return s;
}
#endif /* GF_p2_H */