#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;

const int N = 1123;
int x[N], y[N], M[N];

vector<int> adj[N];
int n;
int seen[N], tempo;
bool go(int i) {
	if(seen[i] == tempo) return false;
	seen[i] = tempo;
	for(int j : adj[i])
		if(M[j] == -1) {
			M[j] = i; M[i] = j;
			return true;
		}
	for(int j : adj[i])
		if(go(M[j])) {
			M[j] = i; M[i] = j;
			return true;
		}
	return false;
}

int max_match() {
	int m = 0, i;
	while(true) {
		tempo++;
		for(i = 0; i < n; i++)
			if(M[i] == -1 && go(i))
				break;
		if(i == n) break;
		m++;
	}
	return m;
}

bool ok(int mx) {
	int i, j;
	memset(M, -1, sizeof M);
	for(i = 0; i < n; i++) adj[i].clear();
	for(i = 0; i < n; i++)
		for(j = n; j < 2 * n; j++)
			if(abs(x[i] - x[j]) + abs(y[i] - y[j]) <= mx)
				adj[i].pb(j);
	return max_match() == n;
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < 2 * n; i++)
		scanf("%d %d", &x[i], &y[i]);
	int l = 0, r = 1e9;
	while(l < r) {
		int m = (l + r) / 2;
		if(ok(m)) r = m;
		else l = m + 1;
	}
	printf("%d\n", l);
}
