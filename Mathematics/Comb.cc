namespace Comb {
const int U = 2e5 + 10;
int f[U + 3], rf[U + 3];
ll inv(ll a, ll m) { return (a == 1 ? 1 : inv(m % a, m) * (m - m / a) % m); }
void init() {
  f[0] = 1;
  for (int i = 1; i <= U; ++ i) f[i] = (ll)f[i - 1] * i % p;
  rf[U] = inv(f[U]);
  for (int i = U; i; -- i) rf[i - 1] = rf[i] * i % p;
}

ll C(int n, int m) {
  if (m < 0 || m > n) return 0;
  return (ll)f[n] * rf[m] % p * rf[n - m] % p;
}
} // namespace Comb
