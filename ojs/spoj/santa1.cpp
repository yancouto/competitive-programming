#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

char S[112345];
int main() {
	char op;
	set<pii> s;
	map<string, pii> mp;
	s.insert(pii(-100, 0));
	s.insert(pii(1e8, 0));
	ll cur = 0;
	for_tests(m, qm) {
		scanf(" %c %s", &op, S);
		if(op == 'A') {
			scanf("%d %lld", &mp[S].fst, &mp[S].snd);
			auto it = s.insert(mp[S]).fst;
			cur -= next(it)->snd * prev(it)->snd;
			cur += it->snd * next(it)->snd;
			cur += it->snd * prev(it)->snd;
		} else {
			auto it = s.find(mp[S]);
			cur -= it->snd * next(it)->snd;
			cur -= it->snd * prev(it)->snd;
			cur += next(it)->snd * prev(it)->snd;
			s.erase(it);
		}
		printf("%lld\n", cur);
	}
}
