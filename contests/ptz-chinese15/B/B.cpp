#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 212345;
char s[N], t[N];
int f[N];
int er = 0;

bool occ(char *a, char *b) {
	if(!(*a)) return true;
	int na = strlen(a), nb = strlen(b);
	a--; b--;
	f[1] = 0;
	for(int i = 2; i <= na; i++) {
		f[i] = f[i - 1];
		while(f[i] && a[f[i] + 1] != a[i]) f[i] = f[f[i]];
		if(a[f[i] + 1] == a[i]) f[i]++;
	}
	int v = 0;
	for(int i = 1; i <= nb - er; i++) {
		while(v && b[i] != a[v + 1]) v = f[v];
		if(b[i] == a[v + 1]) v++;
		if(v == na) return true;
	}
	return false;
}

int main() {
	scanf("%s %s", s, t);
	int x = 0, i, j;
	int n = strlen(t);
	while(true) {
		if(occ(t, s)) { printf("%d\n", x); return 0; }
		for(j = 0; j < 2; j++) {
			if(j >= n) continue;
			for(i = j; i < n && t[i] == 'a'; i += 2);
			if(i < n) continue;
			int on = n; n = 0;
			for(i = !j; i < on; i += 2)
				t[n++] = t[i];
			if(i == on) er++;
			t[n] = 0;
			break;
		}
		if(j == 2) { puts("-1"); return 0; }
		x++;
	}
}
