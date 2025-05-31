// WA
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif


using db = double;

int m, n, tot_hp;
int hp[100];
db p;


db memo[4009][409];
int seen[4009][409], sn = 0;

bool imp(int sa, int na) {
  if(sa > hp[0]) return true;
  if(sa * n + na > tot_hp) return true;
  return false;
}

db memo2[409][4009];
int seen2[409][4009];
db win(db p, int need, int rolls) {
  if(need > rolls) return 0;
  if(need == 0) return 1;
  if(rolls == 0) return 0;
  db &ans = memo2[need][rolls];
  if(seen2[need][rolls] == sn) return ans;
  seen2[need][rolls] = sn;
  ans = p * win(p, need - 1, rolls - 1) + (1.-p) * win(p, need, rolls-1);
  return ans;
}
db memo3[4009][4009];
int seen3[4009][4009];
db win2(db p, int need, int rolls) {
  if(need > rolls) return 0;
  if(need == 0) return 1;
  if(rolls == 0) return 0;
  db &ans = memo3[need][rolls];
  if(seen3[need][rolls] == sn) return ans;
  seen3[need][rolls] = sn;
  ans = p * win2(p, need - 1, rolls - 1) + (1.-p) * win2(p, need, rolls-1);
  return ans;
}

db solve(int left, int sa, int na) {
  if(imp(sa, na)) return 0;
  if(sa * n + na == tot_hp) return 1;
  if(left == 0) return 0;
  db &ans = memo[left][sa];
  if(seen[left][sa] == sn) return ans;
  seen[left][sa] = sn;
  // shine
  db p_shine = (db(p) / 100.);
  if(!imp(sa+1, na)) ans = p_shine * solve(left-1, sa+1,na);
  else ans = p_shine * solve(left-1, sa,na);
  //else ans = p_shine * win2(1.-p_shine, tot_hp-sa*n-na, left-1);
  //ans = (db(p) / 100.) * max(solve(left-1, sa+1, na), solve(left-1,sa,na));
  // if((sa+1)*n + na <= tot_hp && solve(left-1, sa+1, na) < solve(left-1, sa, na))
  //   debug("(%d, %d, %d) tot %d hp[0] %d sa %.10f no attack %.10f\n", left, na, sa, tot_hp, hp[0], solve(left-1, sa+1, na), solve(left-1, sa, na));
  //if(!imp(sa+1,na)) assert(solve(left-1, sa+1, na) >= solve(left-1, sa, na));
  // no shine
  if(((tot_hp-sa*n-na)%n)!=0  || (hp[0]*n + na < tot_hp)) ans += (1.-p_shine) * solve(left-1,sa,na+1);
  else {
    ans += (1.-p_shine) * max(solve(left-1,sa,na+1),
    // solve(left-1,sa,na)
      win(p_shine, (tot_hp-sa*n-na)/n, left-1)
    );
  }
  //debug("solve(%d, %d, %d) = %.10lf\n", left, sa, na, ans);
  return ans;

}

int main() {
  int t, i;
  cin >> t;
  while(t--) {
    cin >> n >> m >> p;
    tot_hp = 0;
    for(i = 0; i < n; i++) {
      cin >> hp[i];
      hp[i]--;
      tot_hp +=  hp[i];
    }
    sort(hp, hp + n);
    sn++;
    db ans = solve(m, 0, 0);
    cout << setprecision(20) << ans << '\n';
  }
}