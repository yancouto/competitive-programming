#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
const ll modn = 998244353;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#define debug
#else
#define debug printf
#endif

int n, a, x;
char s[312345];

int go() {
  scanf("%s", s);
  n = strlen(s);
  if(!s[1]) return 1;
  int lsa = -1;
  int lsg = -1;
  for(int i = 0; s[i]; i++) {
    if(s[i] == '*') {
      if(lsa == -1) lsa = i;
      else return -1;
    }
    if(s[i] == '>' && s[i+1] == '<')
      return -1;
    if(s[i] == '<') lsg = i;
  }
  if(lsa != -1) {
    if((lsa && s[lsa-1] == '>') || s[lsa+1] == '<') return -1;
    return max(lsa + 1, n - lsa);
  }
  if(lsg != -1)
    return max(lsg+1, n-lsg-1);
  return n;
}

int main() {
  int t;
  scanf("%d", &t);
  while(t--) printf("%d\n", go());
}