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

int val[] = {100, 75, 60, 50, 45, 40, 36, 32, 29, 26, 24, 22, 20, 18, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0};
int a[20];

bool pos(int x) {
	int i;
	multiset<int> s;
	for(i = 0; i < 31; i++)
		if(i != x)
			s.insert(val[i]);
	for(i = 0; i < 20; i++) s.insert(0);
	for(i = 0; i < 10; i++) {
		int nd = val[x] - a[i];
		auto it = s.lower_bound(nd);
		if(it == s.end()) return true;
		s.erase(it);
	}
	return false;
}

int main() {
	int i;
	for(i = 0; i < 10; i++)
		scanf("%d", &a[i]);
	for(i = 0; i < 32 && pos(i); i++);
	if(i < 31) printf("%d\n", i);
	else printf("1000\n");
}
