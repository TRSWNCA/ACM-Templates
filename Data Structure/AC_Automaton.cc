#include <bits/stdc++.h>
using namespace std;

#define rep(i, s, t) for (int i = (int)(s); i <= (int)(t); ++ i)
#define ll           long long

char s[N];

namespace AC {
const int N = 1e6 + 10; // Nodes cnt
int ch[N][26], n, cnt, val[N], q[N], fail[N];

inline void insert() {
  int p = 0, len = strlen(s);
  rep(i, 0, len - 1) {
    if (!ch[p][s[i] - 'a'])
      ch[p][s[i] - 'a'] = ++cnt;
    p = ch[p][s[i] - 'a'];
  }
  val[p] ++;
}

inline void build() {
  int l = 1, r = 0;
  rep(i, 0, 25) if (ch[0][i]) q[++r] = ch[0][i];
  while (l <= r) {
    int p = q[l++];
    rep(i, 0, 25) {
      if (ch[p][i])
        fail[ch[p][i]] = ch[fail[p]][i], q[++r] = ch[p][i];
      else ch[p][i] = ch[fail[p]][i];
    }
  }
}

int query() {
  int p = 0, res = 0, len = strlen(s);
  rep(i, 0, len - 1) {
    p = ch[p][s[i] - 'a'];
    for (int j = p; j && val[j] != -1; j = fail[j]) {
      res += val[j], val[j] = -1;
    }
  }
  return res;
}
}

int main() {
  scanf("%d", &n);
  rep(i, 1, n) scanf("%s", s), insert();
  build();
  scanf("%s", s);
  printf("%d\n", query());
}
