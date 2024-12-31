#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

struct Matrix
{
    int n, m;
    vector< vector<ll> > mt;

    Matrix(int _n = 0, int _m = 0): n(_n), m(_m)
    {
        mt.resize(n);
        for(int i = 0; i < n; i++)
        {
            mt[i].resize(m);
            for(int j = 0; j < m; j++)
                mt[i][j] = 0;
        }
    }
};

Matrix operator* (const Matrix& A, const Matrix& B)
{
    Matrix C(A.n, B.m);
    
    for(int i = 0; i < A.n; i++)
        for(int j = 0; j < B.m; j++)
            for(int k = 0; k < A.m; k++)
                C.mt[i][j] = (C.mt[i][j] + A.mt[i][k]*B.mt[k][j] % MOD) % MOD;
    
    return C;
}

Matrix Identity(int n)
{
    Matrix I(n, n);
    for(int i = 0; i < n; i++)
        I.mt[i][i] = 1;
    return I;
}

Matrix fastPow(const Matrix& A, ll k)
{
    if(k == 0)  return Identity(A.n);
    if(k == 1)  return A;
    Matrix res = fastPow(A, k/2);
    res = res*res;
    if(k & 1)
        res = res*A;
    return res;
}