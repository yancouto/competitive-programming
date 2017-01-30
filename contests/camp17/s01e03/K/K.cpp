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
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

char query(int i, int j) {
	cout << (i + 1) << ' ' << (j + 1) << endl;
	cout.flush();
	string s;
	cin >> s;
	if(s == "DETECTED") return 'X';
	return s[0];
}

int n, m;

int main() {
	int i, j;
	cin >> n >> m;
	int ri = 0, rj = 0, rw = m, rh = n;
	int imp = 0;
	while(true) {
		//printf("(%d, %d) (%d, %d) %d\n", ri, rj, rw, rh, imp);
		i = ri + (imp / rw);
		j = rj + (imp % rw);
		char ans = query(i, j); imp++;
		if(ans == 'X') return 0;
		else if(ans == 'U') {
			ri--;
			if(ri < 0) { ri = 0; imp = max(0, imp - rw); rh--; }
		} else if(ans == 'D') {
			ri++;
			if(ri + rh - 1 >= n) rh--;
		} else if(ans == 'L') {
			rj--;
			if(rj < 0) { rj = 0; imp -= (imp + rw - 1) / rw; rw--; }
		} else if(ans == 'R') {
			rj++;
			if(rj + rw - 1 >= m) { imp -= (imp / rw); rw--; }
		} else abort();
	}
}
