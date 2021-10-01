/*
 * Segment Tree Beats I
 * 0 l r x Ai <- min(x, Ai)
 * 1 l r max
 * 2 l r sum
 */
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i, s, t) for (int i = (int)(s); i <= (int)(t); ++ i)

int read() {
  int x = 0, ch = getchar(), f = 0;
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = 1;
    ch = getchar();
  }
  while (ch >='0' && ch <='9')
    x = (x << 1) + (x << 3) + (ch ^ 48),
    ch = getchar();
  return f ? -x : x;
}

const int N = 1e6 + 10;
struct Node {
  int max_value, second_value, t, min_tag;
  ll sum;
} seg[N << 4];

void maintain(int o) {
  seg[o].max_value = max(seg[o << 1].max_value, seg[o << 1 | 1].max_value);
  //printf("maintain %d %d %d\n", o, seg[o << 1].max_value, seg[o << 1 | 1].max_value);
  if (seg[o << 1].max_value == seg[o << 1 | 1].max_value) { // equal
    seg[o].t = seg[o << 1].t + seg[o << 1 | 1].t;
    seg[o].second_value = max(seg[o << 1].second_value, seg[o << 1 | 1].second_value);
    seg[o].sum = seg[o << 1].sum + seg[o << 1 | 1].sum;
  } else if (seg[o << 1].max_value < seg[o << 1 | 1].max_value) { // l < r
    seg[o].t = seg[o << 1 | 1].t;
    seg[o].second_value = max(seg[o << 1 | 1].second_value, seg[o << 1].max_value);
    seg[o].sum = seg[o << 1].sum + seg[o << 1 | 1].sum;
  } else if (seg[o << 1].max_value > seg[o << 1 | 1].max_value) { // l < r
    seg[o].t = seg[o << 1].t;
    seg[o].second_value = max(seg[o << 1 | 1].max_value, seg[o << 1].second_value);
    seg[o].sum = seg[o << 1].sum + seg[o << 1 | 1].sum;
  }
}

void build(int o, int l, int r) {
  seg[o].min_tag = -1;
  if (l == r) {
    int a = read();
    seg[o] = {a, INT_MIN, 1, -1, a};
    ////printf("seg[%lld] = %lld\n", o, seg[o].sum);
    return;
  }
  int mid = (l + r) >> 1;
  build(o << 1, l, mid);
  build(o << 1 | 1, mid + 1, r);
  maintain(o);
}

void puttag(int o, int x) {
  if (x >= seg[o].max_value) return;
  seg[o].sum -= 1ll * seg[o].t * (seg[o].max_value - x);
  seg[o].max_value = x;
  seg[o].min_tag = x;
}

void pushdown(int o) {
  if (seg[o].min_tag != -1) {
    puttag(o << 1, seg[o].min_tag);
    puttag(o << 1 | 1, seg[o].min_tag);
  }
  seg[o].min_tag = -1;
}

void modify_min(int o, int l, int r, int ql, int qr, int x) {
  if (ql > r || qr < l || seg[o].max_value <= x) return;
  //printf("%d %d %d\n", o, seg[o].max_value, seg[o].second_value);
  if (ql <= l && r <= qr && seg[o].second_value < x) {
    puttag(o, x); return;
  }
  pushdown(o);
  int mid = (l + r) >> 1;
  modify_min(o << 1, l, mid, ql, qr, x);
  modify_min(o << 1 | 1, mid + 1, r, ql, qr, x);
  maintain(o);
}

ll query_sum(int o, int l, int r, int ql, int qr) {
  //printf("%d %d %d %d %d\n", o, l, r, ql, qr);
  if (ql > r || qr < l) return 0;
  if (ql <= l && r <= qr) {
    return seg[o].sum;
  }
  pushdown(o);
  int mid = (l + r) >> 1;
  return query_sum(o << 1, l, mid, ql, qr) + query_sum(o << 1 | 1, mid + 1, r, ql, qr);
}

ll query_max(int o, int l, int r, int ql, int qr) {
  //printf("%d %d %d %d %d\n", o, l, r, ql, qr);
  if (ql > r || qr < l) return 0;
  if (ql <= l && r <= qr) {
    return seg[o].max_value;
  }
  pushdown(o);
  int mid = (l + r) >> 1;
  return max(query_max(o << 1, l, mid, ql, qr), query_max(o << 1 | 1, mid + 1, r, ql, qr));
}

int main() {
  int t = read();
  while (t --) {
    int n = read(), m = read();
    rep(i, 1, 4 * n)
      seg[i] = {INT_MIN, INT_MIN, 0, -1, 0ll};
    build(1, 1, n);
    while (m --) {
      int opt = read(), l = read(), r = read();
      if (opt == 0) modify_min(1, 1, n, l, r, read());
      else if (opt == 1) printf("%lld\n", query_max(1, 1, n, l, r));
      else if (opt == 2) printf("%lld\n", query_sum(1, 1, n, l, r));
    }
  }
}
