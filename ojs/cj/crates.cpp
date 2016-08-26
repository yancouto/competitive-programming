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
#include "crates.h"

ll a[11234567];

int main() {
	ll id = MyNodeId(), no = NumberOfNodes(), n = GetNumStacks();
	ll l = (id * n) / no, r = ((id + 1ll) * n) / no;
	ll sz = r - l;
	ll sum = 0, bef = 0;
	for(ll i = 0; i < sz; i++) {
		a[i] = GetStackHeight(i + l + 1);
		sum += a[i];
	}
	if(id) {
		Receive(id - 1);
		bef = GetLL(id - 1);
		sum += bef;
	}
	if(id < no - 1) {
		PutLL(id + 1, sum);
		Send(id + 1);
		Receive(no - 1);
		sum = GetLL(no - 1);
	} else {
		for(ll i = 0; i < no - 1; i++) {
			PutLL(i, sum);
			Send(i);
		}
	}
	ll need = l * ll(sum / n) + min(sum % n, l);
	ll tot = 0;
	if(sz) {
		tot = mod(abs(bef - need));
		a[0] += bef - need;
	}
	for(ll i = 0; i < sz - 1; i++) {
		need = (sum / n) + ((i + l) < (sum % n));
		tot = mod(tot + abs(a[i] - need));
		a[i + 1] += a[i] - need;
	}
	if(id) { PutLL(0, tot); Send(0); }
	else {
		for(ll i = 1; i < no; i++) {
			Receive(i);
			tot = mod(tot + GetLL(i));
		}
		printf("%d\n", (int) tot);
	}
}
