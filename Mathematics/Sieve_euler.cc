#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1e7 + 10;

int prime[N], tot = 0;
int phi[N];

inline void sieve() {
  phi[1] = 1;
  for (int i = 2; i < N; ++ i) {
    if (!prime[i]) prime[++tot] = i, phi[i] = i - 1;
    for (int j = 1; j <= tot && 1ll * i * prime[j] < N; ++ j) {
      prime[i * prime[j]] = 1;
      phi[i * prime[j]] = (i % prime[j]) ?
        phi[i] * phi[prime[j]] : phi[i] * prime[j];
      if (i % prime[j] == 0) break;
    }
  }
}
