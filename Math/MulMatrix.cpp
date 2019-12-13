#include <bits/stdc++.h>

using namespace std;

template<int MOD>
struct ModInt {
  static const int Mod = MOD;
  unsigned x;
  ModInt(): x(0) { }
  ModInt(signed sig) { int sigt = sig % MOD; if(sigt < 0) sigt += MOD; x = sigt; }
  ModInt(signed long long sig) { int sigt = sig % MOD; if(sigt < 0) sigt += MOD; x = sigt; }
  int get() const { return (int)x; }
  
  ModInt &operator+=(ModInt that) { if((x += that.x) >= MOD) x -= MOD; return *this; }
  ModInt &operator-=(ModInt that) { if((x += MOD - that.x) >= MOD) x -= MOD; return *this; }
  ModInt &operator*=(ModInt that) { x = (unsigned long long)x * that.x % MOD; return *this; }
  
  ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
  ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }
  ModInt operator*(ModInt that) const { return ModInt(*this) *= that; }
};
typedef ModInt<1000000007> mint;
 
struct Matrix {
  typedef mint Num;
  static const int MaxN = 102;
  int hei, wid;
  Num v[MaxN][MaxN];
  Matrix() {}
  Matrix(int n, int m): hei(n), wid(m) { mset(v, 0); }
  inline int height() const { return hei; }
  inline int width() const { return wid; }
  inline Num& at(int i, int j) { return v[i][j]; }
  inline const Num& at(int i, int j) const { return v[i][j]; }
  static Matrix identity(int n) {
    Matrix A(n, n);
    rep(i, n) A.at(i, i) = 1;
    return A;
  }
  inline static Matrix identity(const Matrix& A) { return identity(A.height()); }
  Matrix& operator*=(const Matrix& B) {
    int n = height(), m = B.width(), p = B.height();
    assert(p == width());
    const unsigned (*b)[MaxN] = reinterpret_cast<const unsigned (*)[MaxN]>(B.v);
    Num w[MaxN][MaxN];
    unsigned long long pp = (1ULL << 32) % mint::Mod;
    rep(i, n) {
      const unsigned *ai = reinterpret_cast<const unsigned*>(v[i]);
      rep(j, m) {
        unsigned x0 = 0; unsigned long long x1 = 0;
        rep(k, p) {
          unsigned long long y = (unsigned long long)ai[k] * b[k][j];
          unsigned long long t = x0 + y;
          x1 += t >> 32;
          x0  = t & 0xffffffff;
        }
        w[i][j].x = (x0 + x1 % mint::Mod * pp) % mint::Mod;
      }
    }
    memcpy(v, w, sizeof(v));
    return *this;
  }
};
 
Matrix operator^(const Matrix& t, ll k) {
  Matrix A = t, B = Matrix::identity(t);
  while(k) {
    if(k & 1) B *= A;
    A *= A;
    k >>= 1;
  }
  return B;
}
