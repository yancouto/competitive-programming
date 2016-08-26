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

#include <message.h>
#include "lisp_plus_plus.h"

int o[256];
int main() {
	ll id = MyNodeId(), no = NumberOfNodes(), n = GetLength();
	ll l = (id * n) / no, r = ((id + 1ll) * n) / no;
	o['('] = 1; o[')'] = -1;
	ll sum = 0, st = 0;
	for(ll i = l; i < r; i++)
		sum += o[GetCharacter(i)];
	if(id) { Receive(id - 1); st = GetLL(id - 1); }
	if(id < no - 1) { PutLL(id + 1, st + sum); Send(id + 1); }
	ll mx = 0; bool ok = true;
	for(ll i = l; i < r; i++) {
		st += o[GetCharacter(i)];
		if(ok && st >= 0) mx = i + 1;
		else ok = false;
	}
	if(l <= n - 1 && n - 1 < r && st) ok = false;
	PutLL(0, mx); PutInt(0, ok); Send(0);
	if(!id) {
		mx = 0; ok = true;
		for(ll i = 0; i < no; i++) {
			Receive(i);
			ll v = GetLL(i);
			if(ok) mx = max(mx, v);
			ok = ok & GetInt(i);
		}
		if(ok) printf("-1\n");
		else printf("%lld\n", mx);
	}
}
