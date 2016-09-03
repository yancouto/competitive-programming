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
const int N = 1123456;
int bitn[N], bits[N];
int get(int bit[], int i) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[i];
	return sum;
}

void add(int bit[], int i, int x) {
	for(i += 2; i < N; i += (i & -i))
		bit[i] += x;
}

void add(int bit[], int l, int r, int x) {
	add(bit, l, x); add(bit, r + 1, -x);
}

int S[N], sz[N], mn[N], mx[N], y[N];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	if(sz[a] < sz[b]) swap(a, b);
	S[b] = a;
	sz[a] += sz[b];
	mn[a] = min(mn[a], mn[b]);
	mx[a] = max(mx[a], mx[b]);
}


char s[100];
int main() {
	int i, n, a, b;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%*d %d", &y[i]), S[i] = i, sz[i] = 1, mn[i] = mx[i] = y[i];
		for(i = 0; i < N; i++) bitn[i] = 0, bits[i] = 0;
		for_tests(m, mi) {
			scanf("%s %d", s, &a);
			if(s[0] == 'r') {
				scanf("%d", &b);
				if((a = find(a)) == (b = find(b))) continue;
				add(bitn, mn[a], mx[a]-1, -1);
				add(bits, mn[a], mx[a]-1, -sz[a]);
				add(bitn, mn[b], mx[b]-1, -1);
				add(bits, mn[b], mx[b]-1, -sz[b]);
				join(a, b); a = find(a);
				add(bitn, mn[a], mx[a]-1, 1);
				add(bits, mn[a], mx[a]-1, sz[a]);
			} else {
				scanf("%*s"); //.5
				printf("%d %d\n", get(bitn, a), get(bits, a));
			}
		}
	}
}
