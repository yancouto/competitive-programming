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
vector<int> mvs;

int n;
int a[100], b[100];

void go(int l) {
	while(l <= 0) l += n;
	while(l > n) l -= n;
	mvs.pb(l);
	int r = l + 3;
	while(r > n) r -= n;
	swap(b[l], b[r]);
	l++; while(l > n) l -= n;
	r--; while(r <= 0) r += n;
	swap(b[l], b[r]);
}

bool ok() {
	for(int i = 1; i <= n; i++)
		if(b[i] != i)
			return false;
	return true;
}

int main() {
	int i, j, cic;
	srand(time(NULL));
	while(scanf("%d", &n) != EOF) {
		n *= 2;
		for(i = 1; i <= n; i++) scanf("%d", &a[i]);
		do {
			mvs.clear();
			cic = rand() % n;
			for(i = 1; i <= n - cic; i++) b[i] = a[i + cic];
			for(i = n - cic + 1; i <= n; i++) b[i] = a[i - (n - cic)];
			const int M = 50 + (rand() % 50);
			for(i = 0; i < M; i++) {
				int l = (rand() % n) + 1;
				go(l);
			}
			for(i = 1; i <= n - 4; i++) {
				for(j = i; b[j] != i; j++);
				//printf("DOING %d\n", i);
				assert(b[j] == i && j <= n);
				while(j - 3 >= i) go(j - 3), j -= 3;
				assert(b[j] == i);
				if(j == i + 1) go(i), j++;
				assert(b[j] == i);
				if(j == i + 2) { go(i + 1); j++; go(i); j = i; }
				assert(b[j] == i && j == i);
				//printf("DONE %d\n", i);
			}
		} while(!ok());
		printf("%d\n", (int) mvs.size() + !!cic);
		if(cic) printf("2 %d\n", cic);
		for(int x : mvs)
			printf("1 %d\n", x);
	}
}
