#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 1e8 + 10;

int prime[maxn], tot = 0;
int phi[maxn];

inline void sieve() {
  fill(prime, prime + maxn, 1);
  phi[1] = 1;
  for (int i = 2; i < maxn; ++ i) {
    if (prime[i]) prime[++tot] = i, phi[i] = i - 1;
    for (int j = 1; j <= tot && 1ll * i * prime[j] < maxn; ++ j) {
      prime[i * prime[j]] = 0;
      phi[i * prime[j]] = (i % prime[j]) ? phi[i] * phi[prime[j]] : phi[i] * prime[j];
      if (i % prime[j] == 0) break;
    }
  }
}
