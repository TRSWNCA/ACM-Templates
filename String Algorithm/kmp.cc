#include <cstdio>
#include <cstring>

const int maxn = 1e7 + 10;
char s[maxn], str[maxn];
int next[maxn];

int get(int x, char ch) {
	while (1) {
		if (str[x] == ch)
			return x + 1;
		if (!x)
			return 0;
		x = next[x];
	}
}

int main() {
	scanf("%s %s", s, str);
	int n = strlen(s);
	int m = strlen(str);
	next[1] = 0;
	for (int i = 2; i <= m; ++i) next[i] = get(next[i - 1], str[i - 1]);
	int ans = 0, t = 0;
	for (int i = 0; i < n; ++i) {
		t = get(t, s[i]);
		if (t == m) ++ans;
	}
	printf("%d", ans);
}


