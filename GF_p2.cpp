#include "GF_p2.h"
#include <cassert>

// Extended Euclid's Algorithm
// Input: integer numbers m, n, one of them must be nonzero.
// Output: d = gcd(m, n) and integers u, v such that
//     d = u*m + v*n
void extEucl(
    int m, int n,
    int& d, int& u, int& v
) {
    // Invariant:
    //     gcd(a, b) = gcd(m, n),
    //     a = u1*m + v1*n,
    //     b = u2*m + v2*n
    int a = m, b = n;
    int u1 = 1, v1 = 0;
    int u2 = 0, v2 = 1;
    assert(a == u1 * m + v1 * n && b == u2 * m + v2 * n);
    while (b != 0) {
        assert(a == u1 * m + v1 * n && b == u2 * m + v2 * n);
        int q = a / b; int r = a % b;
        assert(a == q * b + r);
        a = b; b = r;
        // (a, b) <-- (b, r)
        // u1' = u2; v1' = v2
        // r = a - q*b = (u1*m + v1*n) - q*(u2*m + v2*n) =
        //   = (u1 - q*u2)*m + (v1 - q*v2)*n
        // u2' = u1 - q*u2; v2' = v1 - q*v2;
        int tmp = u1; u1 = u2;
        u2 = tmp - q * u2;
        tmp = v1; v1 = v2;
        v2 = tmp - q * v2;
    }
    assert(b == 0);
    assert(a == u1 * m + v1 * n && b == u2 * m + v2 * n);
    d = a;
    u = u1; v = v1;
}

int powermod(int a, int n, int m, bool check_sq) {
    assert(n >= 0 && m != 0);
    // b^k * p == a^n (mod m)
    int b = a; int k = n; int p = 1;
    if (check_sq == true)
        k = (n - 1) / 2;
    while (k > 0) {
        if (k % 2 == 0) {
            k /= 2; b = (b * b) % m;
        }
        else {
            k -= 1;
            p = (p * b) % m;
        }
    }
    return p;
}

int factorial(int N)
{
    if (N < 0) 
        return 0; 
    if (N == 0)
        return 1;
    else 
        return N * factorial(N - 1); 
}

int GF_p2::m = 1;
int GF_p2::r = 1;

