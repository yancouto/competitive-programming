#include <bits/stdc++.h>
using namespace std;

char s[112][112];
int p[112];
char t[1123];

int main() {
  int i, n, m, r;
  scanf("%d %d %d", &n, &m, &r);
  for (i = 0; i < n; i++) scanf("%s", s[i]), p[i] = i;
  int lst = n - 1;
  while (scanf(" %*s %s", t) > 0) {
    do {
      for (i = 0; i < m && s[p[lst]][i] != 'P'; i++);
      if (i == m) {
        lst--;
        continue;
      }
    } while (false);
    s[p[lst]][i] = 'N';
    if (t[3] == 'w') continue;
    int up = strlen(t) - 9;
    for (i = 0; i < up; i++) swap(p[lst - i], p[lst - 1 - i]);
  }
  for (i = 0; p[i] != r - 1; i++);
  printf("%d\n", i + 1);
}