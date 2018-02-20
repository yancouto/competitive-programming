#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

char c;
inline void rd(int &x) {
	while(isspace(c = getchar_unlocked()));
	x = (c - '0');
	while(isdigit(c = getchar_unlocked()))
		x = (x << 3) + (x << 1) + (c - '0');
}

int A[3123][3123];

ll best, sum;
int n, m, k;

const int X = 112345;
deque<int> qmn[X], qmx[X];

int acc[3123][3123];

vector<pii> inters(int up, int down) {
	if(up == -1 && down == n) return vector<pii>();
	if(up != -1 && down != n && down - k + 1 <= up)
		return vector<pii>{pii(0, k - 1)};
	vector<pii> ans;
	//printf("inters %d, %d\n", up, down);
	if(up != -1) ans.pb(pii(0, up));
	if(down != n && down - k + 1 < k) ans.pb(pii(down - k + 1, k - 1));
	return ans;
}

void clr(int j, int x, int y=1) {
	//printf("\nfixing %d\n", x);
	for(pii p : inters((qmx[x].empty()? -1 : qmx[x].front()), (qmn[x].empty()? n : qmn[x].front()))) {
		//printf("(%lld, %lld) += %d\n", p.first, p.second, -y);
		acc[p.first][j] += -y;
		acc[p.second + 1][j] += y;
	}
}

void add(int j, int x) {
	clr(j, x, -1);
}

void go(int oi) {
	//printf("\n============\n");
	//printf("go(%d)\n", oi);
	for(int j = 0; j < m; j++) {
		//printf("at col %d\n", j);
		for(int i = oi; i < oi + k && i < n; i++) {
			int x = A[i][j];
			clr(max(j - k + 1, 0), x);
			while(!qmx[x].empty() && qmx[x].back() < i - oi)
				qmx[x].pop_back();
			qmx[x].pb(i - oi);
			add(max(j - k + 1, 0), x);
		}
		//printf("line---\n");
		for(int i = oi + k; i < oi + 2 * k && i < n; i++) {
			int x = A[i][j];
			clr(max(j - k + 1, 0), x);
			while(!qmn[x].empty() && qmn[x].back() > i - oi)
				qmn[x].pop_back();
			qmn[x].pb(i - oi);
			add(max(j - k + 1, 0), x);
		}
		if(j >= k) {
			//printf("removing row %d\n", j - k);
			for(int i = oi; i < oi + k && i < n; i++) {
				int x = A[i][j - k];
				clr(max(j - k + 1, 0), x);
				if(!qmx[x].empty() && qmx[x].front() == i - oi)
					qmx[x].pop_front();
				add(max(j - k + 1, 0), x);
			}
			for(int i = oi + k; i < oi + 2 * k && i < n; i++) {
				int x = A[i][j - k];
				clr(max(j - k + 1, 0), x);
				if(!qmn[x].empty() && qmn[x].front() == i - oi)
					qmn[x].pop_front();
				add(max(j - k + 1, 0), x);
			}
		}
	}
	int i, j;
	for(i = 0; i < k; i++)
		for(j = 1; j < m; j++)
			acc[i][j] += acc[i][j - 1];
	for(j = 0; j < m; j++)
		for(i = 1; i < k; i++)
			acc[i][j] += acc[i - 1][j];
	for(i = 0; i < k && i + oi <= n - k; i++)
		for(j = 0; j <= m - k; j++) {
			//printf("ans[%d][%d] = %d\n", i + oi, j, acc[i][j]);
			sum += acc[i][j];
			best = max<ll>(best, acc[i][j]);
		}
	for(i = 0; i < k; i++)
		for(j = 0; j < m; j++)
			acc[i][j] = 0;
	for(i = oi; i < oi + 2 * k && i < n; i++)
		for(j = 0; j < m; j++)
			qmn[A[i][j]].clear(),
			qmx[A[i][j]].clear();
	//puts("======\n");
}

pii brut();


int main() {
	srand(time(NULL));
	//while(true) {
	best = sum = 0;
	rd(n); rd(m); rd(k);
	//n = (rand() % 3) + 2;
	//m = (rand() % 3) + 2;
	//k = min({(rand() % 3) + 1, n, m});
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			rd(A[i][j]);
			//A[i][j] = rand() % 3;
	for(i = 0; i <= n - k; i += k)
		go(i);
	printf("%lld %lld\n", best, sum);

	//pii br = brut();
	//if(pii(best, sum) != br) {
	//	printf("vs %lld %lld\n", br.first, br.second);
	//	printf("%d %d %d\n", n, m, k);
	//	for(i = 0; i < n; i++)
	//		for(j = 0; j < m; j++)
	//			printf("%d%c", A[i][j], j == m - 1? '\n' : ' ');
	//	return 0;
	//}
	//}
}

int freq[112345];
ll cur;
inline void add(int x) {
	if(freq[x]++ == 0)
		cur++;
	//printf("add %d cur %d\n", x, cur);
}

inline void rem(int x) {
	if(--freq[x] == 0)
		cur--;
	//printf("rem %d cur %d\n", x, cur);
}

pii brut() {
	memset(freq, 0, sizeof freq);
	cur = 0;
	int i, j, g;
	for(i = 0; i < k; i++)
		for(j = 0; j < k; j++)
			add(A[i][j]);
	ll tot = cur;
	ll best = cur;
	//printf("at(0, 0) + %d = cur %d\n", k, cur);
	for(i = 0; i + k - 1 < n; i++) {
		if(i & 1) {
			for(j = m - 1 - k; j >= 0; j--) {
				for(g = 0; g < k; g++) {
					rem(A[i + g][j + k]);
					add(A[i + g][j]);
				}
				//printf("at(%d, %d) + %d = cur %d\n", i, j, k, cur);
				best = max(best, cur);
				tot += cur;
			}
			if(i + k < n) {
				for(g = 0; g < k; g++) {
					rem(A[i][g]);
					add(A[i + k][g]);
				}
				best = max(best, cur);
				tot += cur;
				//printf("at(%d, 0) + %d = cur %d\n", i + 1, k, cur);
			}
		} else {
			for(j = 0; j + k < m; j++) {
				for(g = 0; g < k; g++) {
					rem(A[i + g][j]);
					add(A[i + g][j + k]);
				}
				//printf("at(%d, %d) + %d = cur %d\n", i, j + 1, k, cur);
				best = max(best, cur);
				tot += cur;
			}
			if(i + k < n) {
				for(g = 0; g < k; g++) {
					rem(A[i][m - 1 - g]);
					add(A[i + k][m - 1 - g]);
				}
				best = max(best, cur);
				tot += cur;
				//printf("at(%d, %d) + %d = cur %d\n", i + 1, m - k, k, cur);
			}
		}
	}
	return pii(best, tot);
}
