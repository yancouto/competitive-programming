#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 200009;
vector<int> b[MAX], b2[MAX];
int S[MAX], sz[MAX];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}
bool join(int a, int b) {
	a = find(a); b = find(b);
	if(a == b) return false;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
	return true;
}

void imp(int i) {
	printf("%d\n", i);
	exit(0);
}

int main() {
	ll k;
	scanf("%lld", &k);
	for(ll i = 1; i < MAX; i++) {
		S[i] = i; sz[i] = 1;
		set<int> s;
		for(int v : b[(i*i)%k])
			s.insert(v);
		for(int v : b2[i%k])
			s.insert(v);
		for(int v : s) {
			if(!join(i, v))
				imp(i);
		}
		b[(k-(i%k))%k].push_back(i);
		b2[(k-((i*i)%k))%k].push_back(i);
	}
	puts("-1");
	return 0;
}
