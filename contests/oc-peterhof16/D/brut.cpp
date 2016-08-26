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

int M[20][20], Me;

inline int id(int a, int b) {
	if(a > b) swap(a, b);
	if(!M[a][b]) M[a][b] = ++Me;
	return M[a][b];
}

ll st[1123456]; int sn;
vector<int> vec[1123456];

int ok[20];
vector<int> a;
void rec(int i, ll num) {
	if(i == 9) {
		num |= (1ll << id(a.back(), a.front()));
		vec[sn] = a;
		st[sn++] = num;
		return;
	}
	for(int j = 0; j < 9; j++)
		if(!ok[j]) {
			ok[j] = 1;
			a.pb(j);
			rec(i + 1, num | (1ll << id(a[i - 1], j)));
			a.pop_back();
			ok[j] = 0;
		}
}

vector<int> ans;
void brut(int i, ll num) {
	if(ans.size() == 4) {
		for(int v : ans) {
			for(int x : vec[v])
				printf("%d ", x + 1);
			putchar('\n');
		}
		exit(0);
	}
	if(!(num & st[i])) { ans.pb(i); brut(i + 1, num | st[i]); ans.pop_back(); }
	brut(i + 1, num);
}

int main() {
	ok[0] = true;
	a.pb(0);
	rec(1, 0);
	ans.pb(0);
	brut(1, st[0]);
	puts("NOOO");
}
