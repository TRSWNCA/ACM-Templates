#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n + 1, 0), tg(n + 1, 0);
  vector<vector<bool> > b(n + 1, vector<bool>(20, 0));
  for (int i = 1; i <= n; ++ i) cin >> a[i];
  while (q--) {
    int t, l, r, x;
    cin >> t >> l >> r >> x;
    if (t == 0) {
      tg[l] ^= x;
      tg[r + 1] ^= x;
    } else {
      for (int i = 0; i <= 19; i++)
        if ((x & (1 << i)) && (l + (1 << i) - 1) <= r) {
          b[l][i] = b[l][i] ^ 1;
          tg[l] ^= (x >> i) << i;
          tg[l + (1 << i)] ^= (x >> i) << i;
          l += (1 << i);
          x += (1 << i);
        }
      for (int i = 19; i >= 0; i--) {
        if ((l + (1 << i) - 1) <= r) {
          b[l][i] = b[l][i] ^ 1;
          tg[l] ^= (x >> i) << i;
          tg[l + (1 << i)] ^= (x >> i) << i;
          l += (1 << i);
          x += (1 << i);
        }
      }
    }
  }
  for (int i = 19; i >= 1; i--)
    for (int j = 1; j <= n; j++) {
      if (!b[j][i]) continue;
      b[j][i - 1] = b[j][i - 1] ^ 1;
      if (j + (1 << (i - 1)) <= n) {
        b[j + (1 << (i - 1))][i - 1] = b[j + (1 << (i - 1))][i - 1] ^ 1;
        tg[j + (1 << (i - 1))] ^= (1 << (i - 1));
        if (j + (1 << i) <= n)
          tg[j + (1 << i)] ^= (1 << (i - 1));
      }
    }
  for (int i = 1; i <= n; i++) {
    tg[i] ^= tg[i - 1];
    cout << (a[i] ^ tg[i]) << " ";
  }
}
