#include <bits/stdc++.h>

using namespace std;

template <typename C>
class SegmentTree{
public:
  int n;
  vector<int> l, r;
  vector <C> T;
  vector<pair<C, int> > minval, maxval;

  SegmentTree(int n): n(n) {
    assert(n > 0);
    l.resize(4 * n + 100);
    r.resize(4 * n + 100);
    T.resize(4 * n + 100);
    minval.resize(4 * n + 100);
    maxval.resize(4 * n + 100);
    build(1, 1, n);
  }

  void build(int x,int i, int j) {
    l[x] = i; r[x] = j;
    if(l[x] == r[x]) {
      minval[x].first = numeric_limits<C>::max();
      maxval[x].first = numeric_limits<C>::min();
      minval[x].second = maxval[x].second = i;
    }
    else {
      int mid = (i + j) / 2;
      build(2 * x, i, mid);
      build(2 * x + 1, mid + 1, j);
      minval[x] = min(minval[2 * x], minval[2 * x + 1]);
      maxval[x] = max(maxval[2 * x], maxval[2 * x + 1]);
    }
  }

  void up(int x) {
    maxval[x].first += T[x];
    minval[x].first += T[x];
    if(l[x] != r[x]) {
      T[2 * x] += T[x];
      T[2 * x + 1] += T[x];
    }
    T[x] = 0;
  }

  void update(int x,int i, int j,int v) {
    up(x);
    if(l[x] > j || r[x] < i) return;
    if(l[x] >= i && r[x] <= j) {
      T[x] += v;
      up(x);
      return;
    }
    update(2 * x, i, j);
    update(2 * x + 1, i, j);
    minval[x] = min(minval[2 * x], minval[2 * x + 1]);
    maxval[x] = max(maxval[2 * x], maxval[2 * x + 1]);
  }

  void set(int x,int i, int v) {
    //cout << x << " " << l[x] << " " << r[x] << " " << i << endl;
    up(x);
    if(l[x] > i || r[x] < i) return;
    if(l[x] == i && r[x] == i) {
      minval[x].first = maxval[x].first = v;
      T[x] = 0;
      return;
    } 
    set(2 * x, i, v);
    set(2 * x + 1, i, v);
    minval[x] = min(minval[2 * x], minval[2 * x + 1]);
    maxval[x] = max(maxval[2 * x], maxval[2 * x + 1]);
  }

  pair<C, int> getmax(int x,int i,int j) {
    up(x);
    if(l[x] > j || r[x] < i) return {numeric_limits<C>::min(), 0};
    if(l[x] >= i && r[x] <= j) 
      return maxval[x];
    return max(getmax(2 * x, i, j), getmax(2 * x + 1, i, j));
  }

  pair<C, int> getmin(int x,int i,int j) {
    up(x);
    if(l[x] > j || r[x] < i) return {numeric_limits<C>::max(), 0};
    if(l[x] >= i && r[x] <= j) 
      return minval[x];
    return min(getmin(2 * x, i, j), getmin(2 * x + 1, i, j));
  }

  void update(int i,int j, int v) {update(1, i, j, v);}
  void set(int i, int v) {set(1, i, v);}
  pair<C, int> getmax(int i, int j) {return getmax(1, i, j);}
  pair<C, int> getmin(int i, int j) {return getmin(1, i, j);}
};
