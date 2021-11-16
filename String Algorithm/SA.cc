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
    if (p == n) { // ATTENSION
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

/*
 */
const int N = 1e5 + 10;
char s[N];
int n; ll k;
int a[30];
int sa[N], rk[N], oldrk[N << 1], id[N], px[N], cnt[N], ht[N];
int sum[N];

bool cmp(int x, int y, int w) {
  return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}

bool check(int val) { // < val has k
  ll cnt = 0;
  for (int i = 1, l, r, mid; i <= n; ++ i) {
    l = i - 1, r = n;
    while (l != r) {
      if (sum[mid = (l + r + 1) >> 1] - sum[i - 1] > val) r = mid - 1;
      else l = mid;
    }
    assert(l - i + 1 >= 0);
    cnt += l - i + 1;
    cnt -= min(l - i + 1, ht[rk[i]]);
  }
  return cnt >= k;
}

void solve() {
  scanf("%d %lld", &n, &k);
  scanf("%s", s + 1);
  rep(i, 0, 25) scanf("%d", a + i);
  rep(i, 1, n) sum[i] = sum[i - 1] + a[s[i] - 'a'];
  int p, i, w, j, m = N - 10;
  rep(i, 0, n) cnt[i] = px[i] = rk[i] = sa[i] = id[i] = 0;
  rep(i, 0, 2 * n) oldrk[i] = 0;
  for (i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];
  for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
  for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;

  for (w = 1; w < n; w <<= 1, m = p) {
    for (p = 0, i = n; i > n - w; --i) id[++p] = i;
    for (i = 1; i <= n; ++i)
      if (sa[i] > w) id[++p] = sa[i] - w;
    memset(cnt, 0, sizeof(cnt));
    for (i = 1; i <= n; ++i) ++cnt[px[i] = rk[id[i]]];
    for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; --i) sa[cnt[px[i]]--] = id[i];
    memcpy(oldrk, rk, sizeof(rk));
    for (p = 0, i = 1; i <= n; ++i)
      rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
  }

  for (i = 1, j = 0; i <= n; ++i) {  //求 height
    if (j) --j;
    while (s[i + j] == s[sa[rk[i] - 1] + j]) ++j;
    ht[rk[i]] = j;
  }
  ll tot = 1ll * n * (n + 1) / 2;
  for (int i = 1; i <= n; ++ i)
    tot -= ht[rk[i]];
  if (tot < k) return puts("-1"), void();
  int l = 1, r = 100 * n, mid;
  while (l != r)
    if (check(mid = (l + r) >> 1)) r = mid;
    else l = mid + 1;
  printf("%d\n", l);
}

int32_t main() {
  int t; scanf("%d", &t);
  while (t --) solve();
  return 0;
}
```
