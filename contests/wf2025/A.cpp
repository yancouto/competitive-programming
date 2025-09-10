#include <bits/stdc++.h>
using namespace std;
#define pb push_back

const int N = 212345;
int sz[N], l[N], r[N];

void imp() {
  puts("impossible");
  exit(0);
}

int n;
bool solve(int i, bool mx, vector<int> &ans) {
  if(i == 0) return true;
  if(sz[i] == 1) {
    ans.pb(i);
    // printf("base (%d, %d)\n", i, mx);
    return true;
  }
  vector<int> ansl, ansr;
  if(!solve(l[i], mx, ansl)) return false;
  if(!solve(r[i], mx, ansr)) return false;
  int a = sz[l[i]], b = sz[r[i]];
  int pa = INT_MAX, nxa = -1;
  if(b <= a)
    pa = a - b, nxa = (a == b? i : (ansl.empty()? i: ansl.front()));
  if(a > 0 && a - 1 <= b) {
    int nxb = (a-1 == b? i : (ansr.empty()? i : ansr.front()));
    if(nxa == -1 || (mx? (nxb > nxa) : (nxb < nxa))) {
      int pb = b - a + 1;
      ans.swap(ansr);
      vector<int> restr;
      while(ans.size() > pb) {
        restr.pb(ans.back());
        ans.pop_back();
      }
      ans.pb(i);
      reverse(ansl.begin(), ansl.end());
      while(!ansl.empty() || !restr.empty()) {
        if(!ansl.empty()) {
          ans.pb(ansl.back());
          ansl.pop_back();
        }
        if(!restr.empty()) {
          ans.pb(restr.back());
          restr.pop_back();
        }
      }
      // printf("[B]solve(%d, %d) size %d\n", i, mx, ans.size());
      return true;
    }
  }
  if(b <= a) {
    ans.swap(ansl);
    vector<int> restl;
    while(ans.size() > pa) {
      restl.pb(ans.back());
      ans.pop_back();
    }
    ans.pb(i);
    reverse(ansr.begin(), ansr.end());
    while(!restl.empty() || !ansr.empty()) {
      if(!ansr.empty()) {
        ans.pb(ansr.back());
        ansr.pop_back();
      }
      if(!restl.empty()) {
        ans.pb(restl.back());
        restl.pop_back();
      }
    }
    // printf("[A]solve(%d, %d) size %d\n", i, mx, ans.size());
    return true;
  }
  // puts("bad");
  return false;
}

int main() {
  int i;
  scanf("%d", &n);
  for(i = 1; i <= n; i++)
    scanf("%d %d", &l[i], &r[i]);
  for(i = n; i >= 1; i--)
    sz[i] = 1 + (l[i]? sz[l[i]] : 0) + (r[i]? sz[r[i]] : 0);

  vector<int> mn, mx;
  if(!solve(1, false, mn)) imp();
  assert(!mn.empty());
  if(!solve(1, true, mx)) imp();
  for(i = 0; i < n; i++) printf("%d ", mn[i]);
  putchar('\n');
  for(i = 0; i < n; i++) printf("%d ", mx[i]);
  putchar('\n');
}