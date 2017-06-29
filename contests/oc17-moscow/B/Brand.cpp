#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 1000001;

double rnd() { return rand() / double(RAND_MAX); }

int f[N];
int mx = -1;
int pr[N];
vector<int> nec[N];
int est = 0;

void go(double p) {
	int cur = 0;
	for(int i = 1; i < N; i++) {
		if(pr[i] != i) {
			f[i] = 1;
			for(int p2 : nec[i])
				f[i] = f[i] * f[p2];
		} else f[i] = (rnd() <= p? 1 : -1);
		cur += f[i];
		if(abs(cur) > 20) {
			mx = max(mx, i);
			if(cur > 20) est++;
			else est--;
			return;
		}
	}
	for(int i = 1; i < N; i++)
		printf("%d ", f[i]);
	putchar('\n');
	exit(0);
}

int main () {
	srand(time(NULL));
	int i, j;
	vector<int> ps(1, 1);
	pr[1] = 1;
	for(i = 2; i < N; i++)
		if(!pr[i]) {
			ps.pb(i);
			for(j = i; j < N; j += i)
				pr[j] = i;
		}
	for(i = 2; i < N; i++) {
		int x = i;
		int prev = -1;
		for(; x != 1; x /= pr[x]) {
			if(prev == pr[x]) prev = -1;
			else {
				if(prev != -1) nec[i].pb(prev);
				prev = pr[x];
			}
		}
	}
	double p = 0;
	scanf("%lf", &p);
	for(i = 0; ; i++) {
		if(!(i % 100000)) fprintf(stderr, "Test %d -- mx so far %d -- est %d\n", i, mx, est);
		go(p);
	}
}
