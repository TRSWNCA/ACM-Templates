char nc() {
  static char buf[1<<20], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1 ++;
}

int read() {
  int x = 0, ch = nc();
  for (; ch < '0' || ch > '9'; ch = nc());
  for (; ch >= '0' && ch <= '9'; ch = nc())
    x = (x << 1) + (x << 3) + (ch ^ 48);
  return x;
}

