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
int ti[1009], tf[1009], ri[1009], s[1009], f[1009], r[1009];
int at(int i, int tm) {
	return s[i] + (tm - ti[i]) * (2 * ri[i] - 1);
}
bool meet(int i, int j) {
	if(ti[i] > tf[j] || tf[i] < ti[j]) return false;
	int fr = max(ti[i], ti[j]), to = min(tf[i], tf[j]);
	if(ri[i] == ri[j]) return at(i, fr) == at(j, fr);
	if(!ri[i]) swap(i, j);
	if(at(i, to) < at(j, to) || at(i, fr) > at(j, fr)) return false;
	return true;
}

int main() {
	int i, n, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d %d", &ti[i], &s[i], &f[i]);
		tf[i] = ti[i] + abs(f[i] - s[i]);
		ri[i] = f[i] > s[i];
	}
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++) {
			r[i] += (i != j) && meet(i, j);
		}
	for(i = 0; i < n; i++)
		printf("%d ", r[i]);
	putchar('\n');
}
