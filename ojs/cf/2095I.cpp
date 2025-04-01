#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string N[9] = {
    "la", "le", "lon", "sha", "she", "shon", "ta", "te", "ton",
};

ll convert(char s[]) {
  int i = 0;
  ll tot = 0;
  while (s[i]) {
    int aeo = 1, add = 0;
    if (s[i] == 'l')
      add = 0;
    else if (s[i] == 's')
      add = 3, aeo = 2;
    else if (s[i] == 't')
      add = 6;
    else
      assert(false);
    int digit, nx = i + aeo + 1;
    if (s[i + aeo] == 'a')
      digit = 0 + add;
    else if (s[i + aeo] == 'e')
      digit = 1 + add;
    else if (s[i + aeo] == 'o')
      digit = 2 + add, nx = i + aeo + 2;
    else
      assert(false);
    tot = tot * 9ll + ll(digit);
    i = nx;
    if (!s[i] || (s[i] == 's' && !s[i + 1])) return tot;
  }
}

void print(ll x) {
  if (x == 0) {
    printf("las\n");
    return;
  }
  vector<int> v;
  for (; x > 0; x /= 9) {
    int y = (x % 9ll);
    v.push_back(y);
  }
  reverse(v.begin(), v.end());
  for (int d : v) printf("%s", N[d].c_str());
  printf("s\n");
}

char a[112345], b[112345];
int main() {
  scanf("%s %s", a, b);
  ll na = convert(a), nb = convert(b);
  print(na + nb);
}