#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 35000009;

#include <message.h>
#include "winning_move.h"

ll st[N/2]; int sn;
ll ans[N]; int an;
int main() {
	ll id = MyNodeId(), no = NumberOfNodes(), n = GetNumPlayers();
	for(ll i = id; i < n; i += no)
		st[sn++] = GetSubmission(i);
	sort(st, st + sn, greater<ll>());
	int steps = 0;
	while((1 << steps) < no) steps++;
	for(int s = 0; s < steps; s++) {
		if((id >> s) & 1) {
			ll cur = id ^ (1 << s);
			//printf("sn %d:", sn);
			//for(int i = sn - 1; i >= 0; i--) printf(" %lld", st[i]);
			//putchar('\n');
			PutInt(cur, sn);
			for(int i = sn - 1; i >= 0; i--)
				PutLL(cur, st[i]);
			Send(cur);
			//printf("%lld sending to %lld on step %d\n", id, cur, s);
			break;
		} else {
			ll ind = id ^ (1 << s);
			//printf("%lld reading from %lld on step %d\n", id, ind, s);
			if(ind >= no) continue;
			Receive(ind);
			int cur = GetInt(ind);
			ll lst;
			if(cur) lst = GetLL(ind);
			while(sn && cur) {
				if(st[sn-1] < lst) ans[an++] = st[--sn];
				else {
					ans[an++] = lst; cur--;
					if(cur) lst = GetLL(ind);
				}
			}
			while(sn) ans[an++] = st[--sn];
			if(cur) {
				ans[an++] = lst;
				while(--cur) ans[an++] = GetLL(ind);
			}
			assert(!sn && !cur);
			if(id == 0 && s == steps - 1) {
				assert(an == n); int i;
				for(i = 0; i < n; i++)
					if((!i || ans[i - 1] != ans[i]) && (i == n - 1 || ans[i + 1] != ans[i]))
						break;
				if(i < n) printf("%lld\n", ans[i]);
				else printf("0\n");
				return 0;
			}
			while(an) st[sn++] = ans[--an];
		}
	}
}
