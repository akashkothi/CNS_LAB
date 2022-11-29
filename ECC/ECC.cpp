#include <bits/stdc++.h>
#include <time.h>
using namespace std;

int modulo(int a, int b)
{
    while (a < 0)
        a = a + b;
    return a % b;
}

int mul_inverse(int a, int b)
{
    for (int i = 1; i < b; i++)
    {
        if (modulo(a * i, b) == 1)
            return i;
    }
    cout << "No Multiplicative inverse for " << a << endl;
    exit(0);
}

pair<int, int> getPointMultiplication(int n, int Gx, int Gy, int p, int a, int b)
{
    if (n == 2)
    {
        int m = modulo(modulo(3 * Gx * Gx + a, p) * mul_inverse(2 * Gy, p), p);
        return {modulo(m * m - Gx - Gx, p), modulo(m * (Gx - modulo(m * m - Gx - Gx, p)) - Gy, p)};
    }
    pair<int, int> pnext = getPointMultiplication(n - 1, Gx, Gy, p, a, b);
    int m = modulo(modulo(pnext.second - Gy, p) * mul_inverse(pnext.first - Gx, p), p);
    return {modulo(m * m - Gx - pnext.first, p), modulo(m * (Gx - modulo(m * m - Gx - pnext.first, p)) - Gy, p)};
}

pair<int, int> getPointAddition(pair<int, int> p1, pair<int, int> p2, int p, int a, int b)
{
    int m = modulo(modulo(p2.second - p1.second, p) * mul_inverse(p2.first - p1.first, p), p);
    return {modulo(m * m - p1.first - p2.first, p), modulo(m * (p1.first - modulo(m * m - p1.first - p2.first, p)) - p1.second, p)};
}

int main()
{
    int p, a, b;
    cout << "Enter the values of p, a, b:" << endl;
    cin >> p >> a >> b;
    int Gx, Gy;
    cout << "Enter the coordinates of G:" << endl;
    cin >> Gx >> Gy;

    int nA, nB;
    cout << "Enter private nA and nB: " << endl;
    cin >> nA >> nB;
    pair<int, int> pA = getPointMultiplication(nA, Gx, Gy, p, a, b);
    pair<int, int> pB = getPointMultiplication(nB, Gx, Gy, p, a, b);

    cout << "Public key of A: (" << pA.first << ", " << pA.second << ")" << endl;
    cout << "Public key of B: (" << pB.first << ", " << pB.second << ")" << endl;

    pair<int, int> kA, kB;
    kA = getPointMultiplication(nA, pB.first, pB.second, p, a, b);
    kB = getPointMultiplication(nB, pA.first, pA.second, p, a, b);
    cout << "Secret key of A: (" << kA.first << ", " << kA.second << ")" << endl;
    cout << "Secret key of B: (" << kB.first << ", " << kB.second << ")" << endl;

    int pmx, pmy;
    cout << "Enter the coordinates of plain text:" << endl;
    cin >> pmx >> pmy;

    int k = rand() % 200;
    cout << "Randomly choosen k = " << k << endl;
    pair<pair<int, int>, pair<int, int>> cipher = {getPointMultiplication(k, Gx, Gy, p, a, b),
                                                   getPointAddition({pmx, pmy}, getPointMultiplication(k, pB.first, pB.second, p, a, b), p, a, b)};
    return 0;
}