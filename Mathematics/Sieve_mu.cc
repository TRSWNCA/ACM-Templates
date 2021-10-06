#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1e8 + 10;

int prime[N], tot = 0, mu[N];

inline void sieve() {
  mu[1] = 1, tot = 0;
  for (int i = 2; i < N; ++ i) {
    if (!prime[i]) prime[++tot] = i, mu[i] = -1;
    for (int j = 1; j <= tot && 1ll * i * prime[j] < N; ++ j) {
      prime[i * prime[j]] = 1;
      mu[i * prime[j]] = (i % prime[j]) ?
        0 : -mu[i];
      if (i % prime[j] == 0) break;
    }
  }
}
