#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

const int MAX = 20*9615;
int dv[MAX];
void pre() {
	int i, j;
	for(i = 2; i < MAX; i++) {
		if(dv[i]) continue;
		for(j = i; j < MAX; j += i)
			if(!dv[j])
				dv[j] = i;
	}
}

vector<int> dvs(int x) {
	vector<int> d;
	while(dv[x]) {
		int aux = dv[x]; d.pb(0);
		while(!(x % aux)) {
			d.back()++;
			x /= aux;
		}
	}
	return move(d);
}


int s2(int x) {
	vector<int> v = dvs(x);
	ull tot = 1; int xx = *min_element(v.begin(), v.end());
	for(int z = 2; z <= xx; z++) {
		int a = 1;
		for(int zz : v)
			if(zz % z)
				a = 0;
		if(a) tot += s2(z);
	}
	//printf("s2(%d) = %llu\n", x, tot);
	return tot;
}

ull solve(vector<int> &v) {
	//for(int x : v) {
	//	printf("%d ", x);
	//}
	//putchar('\n');
	int x = *max_element(v.begin(), v.end());
	ull tot = 0;
	for(int z = 2; z <= x; z++) {
		ull aux = 1;
		for(int xx : v)
			aux *= (1 + (xx / z));
		//printf("for %d = %llu\nold = %llu\n", z, aux, tot);
		tot += (aux - 1) * s2(z);
		//printf("new = %llu\n", tot);
	}
	return tot;
}

int mdc(int a, int b) {
	if(b == 0) return a;
	return mdc(b, a % b);
}

int main() {
	int a, b, c;
	pre();
	while(scanf(" %d^%d^%d", &a, &b, &c) != EOF) {
		vector<int> vv = dvs(a);
		int m = 0;
		for(int x : vv)
			m = mdc(x, m);
		vector<int> v;
		for(int i = 2; i < MAX; i++) {
			int tt = 0;
			while(!(b % i)) {
				tt += c;
				b /= i;
			}
			while(!(m % i)) {
				tt++;
				m /= i;
			}
			if(tt > 0) v.pb(tt);
		}
		printf("%llu\n", solve(v));

	}
	return 0;
}
