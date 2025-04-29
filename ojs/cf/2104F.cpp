#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) \
  int t;                 \
  scanf("%d", &t);       \
  for (int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

vector<string> all;
char s[100];
const int N = 612345;
int mn[N], ct = 0;
int aux[100];
int seq[100];

void gen(int dig, bool needs_non0, bool has09, int tot) {
  if (dig == 10) {
    if (needs_non0) return;
    if (tot < 16 && !has09) {
      s[tot] = '0';
      s[tot + 1] = '9';
      gen(dig, needs_non0, true, tot + 2);
    }
    if (tot < 18) {
      for (int i = 0; i < 9; i++) {
        s[tot] = '0' + i;
        s[tot + 1] = '0' + (i + 1);
        s[tot + 2] = 0;
        string ss = s;
        sort(ss.begin(), ss.end());
        if (ss == "01") continue;
        int any = -1;
        for (int j = 1; j <= 9; j++)
          if (aux[j] > 0) {
            any = j;
            break;
          }
        int ctt = 0;
        bool b = false;
        if (tot == aux[0] * 2 + aux[9] * 2 + has09 * 2 && aux[0] == aux[9] &&
            aux[0] > 0 && i > 0) {
          seq[ctt++] = i;
          for (int j = 0; j < 2 * aux[9]; j++) seq[ctt++] = 9;
          if (has09) seq[ctt++] = 9;
          b = true;
        } else {
          if (any == -1 && aux[0] > 0) continue;
          if (any == -1 && aux[0] == 0 && i == 0) continue;
          if (any != -1) seq[ctt++] = any;
          for (int j = 0; j <= 9; j++) {
            int to = aux[j];
            if (any == j) to--;
            for (int k = 0; k < to; k++) seq[ctt++] = j;
          }
          seq[ctt++] = i;
          if (has09) seq[ctt++] = 9;
        }
        ll num = 0;
        for (int j = 0; j < ctt; j++) num = num * 10ll + seq[j];
        all.push_back(ss);
        mn[ct++] = num;
      }
    }
    return;
  } else
    // skip this digit
    gen(dig + 1, needs_non0, false, tot);
  // Try adding duplinha
  if (tot < 16) {
    s[tot] = s[tot + 1] = '0' + dig;
    aux[dig] += 1;
    gen(dig, dig == 0 ? true : false, false, tot + 2);
    aux[dig] -= 1;
  }
}

int main() {
  gen(0, false, false, 0);
  for (int i = 10; i <= 1000000000; i *= 10) {
    mn[ct++] = i - 1;
  }
  sort(mn, mn + ct);
  int n;
  for_tests(t, tt) {
    scanf("%d", &n);
    printf("%d\n", upper_bound(mn, mn + ct, n) - mn);
  }
}