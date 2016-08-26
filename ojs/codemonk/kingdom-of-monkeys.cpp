#include <cstdio>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
const int MAX = 100009;
int n, m;
int S[MAX], size[MAX];
ull ban[MAX];

int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i]; 
}
void join(int a, int b) {
	if(a == b) return;
	if(size[a] < size[b]) swap(a, b);
	size[a] += size[b];
	ban[a] += ban[b];
	S[b] = a;
}
int es[MAX][2];

int main() {
	int t, i;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++) {
			S[i] = i;
			size[i] = 1;
		}
		for(i = 0; i < m; i++) {
			scanf("%d %d", &es[i][0], &es[i][1]);
			es[i][0]--; es[i][1]--;
		}
		for(i = 0; i < n; i++)
			scanf("%llu", &ban[i]);
		for(i = 0; i < m; i++) {
			int a = find(es[i][0]);
			int b = find(es[i][1]);
			join(a, b);
		}
		ull coins = 0;
		for(i = 0; i < n; i++)
			coins = max(coins, ban[find(i)]);
		printf("%llu\n", coins);
	}
	return 0;
}