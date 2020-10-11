// for loj 119
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2500 + 10;
const int maxm = 6200 * 2 + 10;

int n, m, s, t, idx;

#define int long long

int edge[maxm], head[maxn], to[maxm], Next[maxm], d[maxn];
bool v[maxn];
priority_queue< pair<int, int> > q;

inline void addline(int x, int y, int z) {
  edge[++idx] = z, to[idx] = y, Next[idx] = head[x], head[x] = idx;
}

inline int dijkstra() {
  fill(d, d + n + 1, 1e18);
  memset(v, 0, sizeof(v));
  d[s] = 0; q.push(make_pair(0, s));
  while (q.size()) {
    int x = q.top().second; q.pop();
    if (v[x]) continue;
    v[x] = 1;
    for (int i = head[x]; i; i = Next[i]) {
      int y = to[i], z = edge[i];
      if (d[y] > d[x] + z) {
        d[y] = d[x] + z;
        q.push(make_pair(-d[y], y));
      }
    }
  }
  return d[t];
}

signed main() {
  scanf("%d %d %d %d", &n, &m, &s, &t);
  for (int i = 1, x, y, z; i <= m; ++ i) {
    scanf("%lld %lld %lld", &x, &y, &z);
    addline(x, y, z), addline(y, x, z);
  }
  printf("%lld", dijkstra());
}

