/* SA: rk sa*/

const int N = 2e5 + 10;
char s[N];
int n, sa[N], rk[N], oldrk[N << 1], id[N], px[N], cnt[N];

bool cmp(int x, int y, int w) {
  return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}

int main() {
  int p, w, m = 300, i;
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  rep(i, 1, n) s[i + n] = s[i];
  n <<= 1;
  rep(i, 1, n) ++cnt[rk[i] = s[i]];
  rep(i, 1, m) cnt[i] += cnt[i - 1];
  for (int i = n; i >= 1; -- i) sa[cnt[rk[i]] -- ] = i;
  for (w = 1; ; w <<= 1, m = p) {
    for (p = 0, i = n; i > n - w; -- i) id[++p] = i;
    for (int i = 1; i <= n; ++ i)
      if (sa[i] > w) id[++p] = sa[i] - w;
    memset(cnt, 0, sizeof(cnt));
    rep(i, 1, n) ++cnt[px[i] = rk[id[i]]];
    rep(i, 1, m) cnt[i] += cnt[i - 1];
    for (int i = n; i; -- i) sa[cnt[px[i]] --] = id[i];
    memcpy(oldrk, rk, sizeof(rk));
    for (p = 0, i = 1; i <= n; ++ i)
      rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
    if (p == n) {
      rep(i, 1, n) sa[rk[i]] = i;
      break;
    }
  }
  rep (i, 1, n) if (sa[i] <= (n >> 1)) putchar(s[sa[i] + (n >> 1) - 1]);
}

/*
 * max length of subarray that occurs K times
 * array is number
 */
int n, ht[N], q[N], K;
int s[N];

int main() {
  int i, m = N, w, p;
  scanf("%d %d", &n, &K); K --;
  rep(i, 1, n) scanf("%d", s + i);
  for (int i = 1, k = 0; i <= n; ++i) { // calc height[]
    if (k) --k;
    while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
    ht[rk[i]] = k;
  }
  int ans = 0;
  rep(i, 1, n) {
    while (l <= r && ht[q[r]] >= ht[i]) r --;
    q[++r] = i;
    while (q[l] <= i - K) l ++;
    ans = max(ans, ht[q[l]]);
  }
  printf("%d", ans);
}
