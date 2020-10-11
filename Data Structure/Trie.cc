const int maxn = 1e6 + 10;
int tree[maxn][26];
bool isLeaf[maxn];
int pos = 0;

inline void insert(char *s) {
  int p = 0;
  while (*s != '\0') {
    int t = *s - 'a';
    if (tree[p][t] == 0)
      tree[p][t] = ++pos;
    p = tree[p][t];
  }
  isLeaf[p] = 1;
}

inline int query(char *s) {
  int p = 0;
  while (*s != '\0') {
    int t = *s - 'a';
    if (tree[p][t] == 0)
      return 0;
    p = tree[p][t];
  }
  return isLeaf[p];
}
