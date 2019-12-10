#include <bits/stdc++.h>

using namespace std;

template <typename T, typename C>

struct MinCostMF {
  static constexpr T eps = (T)(1e-9);

  struct edge {
    int from;
    int to;
    T c;
    T f;
    C cost;
  };

  vector<vector<int> > G;
  vector <edge> edges;
  vector <C> d;
  queue <int> q;
  vector <bool> in_queue;
  vector <int> trace;
  int n;
  int s, t;
  T flow;
  C cost;

  MinCostMF(int n,int s, int t): n(n), s(s), t(t) {
    assert(0 <= s && s < n && 0 <= t && t < n && t != s);
    G.resize(n);
    d.resize(n);
    in_queue.resize(n);
    trace.resize(n);
    flow = 0;
    cost = 0;
  }

  void clear_flow() {
    for (const edge & e : edges) {
      e.f = 0;
    }
    flow = 0;
  }

  void add(int from, int to, T fc, T bc, C cost) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    G[from].push_back((int) edges.size());
    edges.push_back({from, to, fc, 0, cost});
    G[to].push_back((int) edges.size()); 
    edges.push_back({to, from, bc, 0, -cost});
  }

  bool expath() {
    fill(d.begin(), d.end(), numeric_limits<C>::max());
    q = queue<int>();
    q.push(s);
    d[s] = 0;
    in_queue[s] = true;
    bool found = false;

    while(q.size()) {
      int u = q.front(); q.pop();
      if(u == t) {
        found = true;
      }

      in_queue[u] = false;
      for(int id: G[u]) {
        const edge & e = edges[id];
        if(e.c - e.f > eps && d[u] + e.cost < d[e.to]) {
          d[e.to] = d[u] + e.cost;
          trace[e.to] = id;
          if(!in_queue[e.to]) {
            q.push(e.to);
            in_queue[e.to] = true;
          }
        }
      }
    }

    if(found) {
      T upflow = numeric_limits <T>::max();
      int v = t;
      while(v != s) {
        const edge & e = edges[trace[v]];
        upflow = min(upflow, e.c - e.f);
        v = e.from;
      }

      v = t;
      while(v != s) {
        edge & e = edges[trace[v]];
        e.f += upflow;
        edge & back = edges[trace[v] ^ 1];
        back.f -= upflow;
        v = e.from;
      }

      flow += upflow;
      cost += d[t] * upflow;
    }
    return found;
  }

  pair<T, C> mfmc() {
    while(expath()) {
    }
    return {flow, cost};
  }
};
