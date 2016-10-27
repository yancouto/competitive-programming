#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const int modn = 10007;
inline int mod(int x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

int p3[100], ans[20000], a2[20000];
int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, 1, -1};
inline int get(int b, int i) { return (b / p3[i]) % 3; }

inline int set(int b, int i, int x) {
	return (b % p3[i]) + (b / p3[i + 1]) + p3[i] * x;
}


int memo[5003][20000];
int seen[5003][20000];
int solve(int i, int b) {
	//if(b == 10610) printf("solve(%d, %d)\n", i, b);
	if(i == 0) return (b == 0);
	int &r = memo[i][b];
	if(seen[i][b]) assert(seen[i][b] == 1);
	if(seen[i][b]) return r;
	seen[i][b] = 2;
	if(ans[b] == -1) { seen[i][b] = 1; return r = solve(i - 1, a2[b]); }
	int j = ans[b];
	if(j >= 9) printf("ans[%d] = %d\n", b, ans[b]);
	assert(b + p3[j] > b);
	//printf("(%d, %d) -> (%d, %d)\n", i, b, i, b + p3[j] * 2);
	r = solve(i, b + p3[j] * 2);
	for(int d = 0; d < 4; d++) {
		int ni = (j / 3) + di[d], nj = (j % 3) + dj[d];
		if(ni < 0 || nj < 0 || ni >= 3 || nj >= 3 || get(b, 3 * ni + nj) > 0) continue;
		assert(get(b, 3 * ni + nj) == 0);
		assert(b + p3[j] * 1 + p3[3 * ni + nj] * 1 > b);
		//printf("(%d, %d) -> (%d, %d)\n", i, b, i, b + p3[j] + p3[3*ni + nj]);
		r = mod(r + solve(i, b + p3[j] * 1 + p3[3 * ni + nj] * 1));
	}
	//printf("DONE %d,%d\n", i, b);
	seen[i][b] = 1;
	return r;
}


int main() {
	int i, j;
	p3[0] = 1;
	for(i = 1; i < 20; i++)
		p3[i] = p3[i - 1] * 3;
	for(i = 0; i < p3[9]; i++) {
		for(j = 0; j < 9; j++)
			if(get(i, j) == 0) { ans[i] = j; break; }
		if(j == 9) {
			ans[i] = -1;
			for(j = 0; j < 9; j++) a2[i] += p3[j] * (get(i, j) - 1);
		}
	}
	for(i = 2; i <= 5000; i += 2)
		printf("%d,", solve(i, 0));
}
