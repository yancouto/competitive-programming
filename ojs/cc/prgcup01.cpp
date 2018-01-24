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

int d[8][8][8][8];
inline bool valid(int i, int j) {
	return i >= 0 && i < 8 && j >= 0 && j < 8;
}

int di[] = {2,  2, -2, -2, 1,  1, -1, -1};
int dj[] = {1, -1,  1, -1, 2, -2,  2, -2};

void go(int si, int sj) {
	queue<pii> q;
	q.push(pii(si, sj));
	d[si][sj][si][sj] = 0;
	while(!q.empty()) {
		pii x = q.front(); q.pop();
		for(int d = 0; d < 8; d++) {
			int ni = x.fst + di[d], nj = x.snd + dj[d];
			if(valid(ni, nj) && ::d[si][sj][ni][nj] == -1) {
				::d[si][sj][ni][nj] = ::d[si][sj][x.fst][x.snd] + 1;
				q.push(pii(ni, nj));
			}
		}
	}
}

int main() {
	memset(d, -1, sizeof d);
	int i, j;
	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
			go(i, j);
	for_tests(tn, tt) {
		char a, b, c, d;
		scanf(" %c %c %c %c", &a, &b, &c, &d);
		printf("%d\n", ::d[a - 'a'][b - '1'][c - 'a'][d - '1']);
	}
}
