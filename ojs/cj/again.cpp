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
#include "again.h"

ll a[200], b[200];
int main() {
	ll id = MyNodeId(), no = NumberOfNodes(), n = GetN();
	ll A = 0, B = 0;
	for(ll i = id; i < n; i += no)
		A += GetA(i), B += GetB(i);
	A = mod(A); B = mod(B);
	PutLL(0, A); PutLL(0, B); Send(0);
	A = 0; B = 0;
	if(!id) {
		for(ll i = 0; i < no; i++) {
			Receive(i);
			a[i] = GetLL(i);
			b[i] = GetLL(i);
			A += a[i]; B += b[i];
		}
		ll sum = mod(mod(A) * mod(B));
		//printf("sum %lld\n", sum);
		for(ll i = 0; i < no; i++) {
			//printf("[%d]-= %lld * %lld = %lld\n", i, a[i], b[(no - i) % no], a[i] * b[(no - i) % no]);
			sum = mod(sum - mod(a[i] * b[(no - i) % no]) + modn);
		}
		printf("%lld\n", sum);
	}
}
