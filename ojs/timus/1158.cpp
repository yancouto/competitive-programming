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
char s[20];
int tr[105][128], p[105];

int main() {
	scanf("%d %d %d %*s", &n, &m, &x);
	int tn = 0;
	for(i = 0; i < x; i++) {
		scanf("%s", s);
		int v = 0;
		for(j = 0; s[j]; j++) {
			if(!tr[v][s[j]])
				tr[v][s[j]] = ++tn;
			v = tr[v][s[j]];
		}
	}
	queue<int> q;
	for(i = 0; i < 128; i++)
		if(tr[0][i])
			q.push(tr[0][i]), p[tr[0][i]] = 0;
	while(!q.empty()) {
		x = q.front(); q.pop();
		for(i = 0; i < 128; i++) {
			if(!tr[x][i]) continue;
			int v = p[x];
			while(v && !tr[v][i])
				v = p[v];
			v = tr[v][i];
			p[tr[x][i]] = v;
			q.push(tr[x][i]);
		}
	}
	
}
