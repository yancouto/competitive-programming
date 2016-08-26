// WAAAAAAA
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
inline int count_1s(int x) { return __builtin_popcount(x); }
inline int count_1s(ull x) { return __builtin_popcountll(x); }
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000;
inline ull mod(ull x) { return x % modn; }
#ifndef ONLINE_JUDGE
#	define debug(args...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");
#else
#	define debug(args...)
#endif
const int MAX = 10009;
int N, K;
struct cont {
	int i;
	int v;
	bool operator < (const cont &o) const { return i < o.i; }
}cs[MAX];

ull get(int i, ull b[]) {
	ull sum = 0; i += 2;
	while(i) {
		sum = mod(sum + b[i]);
		i -= (i & -i);
	}
	return sum;
}
ull get(int i, int j, ull b[]) {
	return get(j, b) - get(i - 1, b);
}
void add(int i, ull val, ull b[]) {
	i += 2;
	while(i < MAX) {
		b[i] = mod(b[i] + val);
		i += (i & -i);
	}
}


ull bit[53][2][MAX];
ull memo[10003][53][2];
ull& m(int i, int k, bool b) { return memo[i][k][b]; }
ull* b(int i, bool b) { return bit[i][b]; }
int main() {
	int i, j;
	for_tests(t, tt) {
		scanf("%d %d", &N, &K);
		map<int, int> s;
		for(i = 0; i < N; i++) {
			scanf("%d %d", &cs[i].i, &cs[i].v);
			s[cs[i].v] = 1;
		}
		i = 0;
		for(auto &it : s)
			it.second = i++;
		sort(cs, cs + N);
		for(i = 0; i < N; i++)
			cs[i].v = s[cs[i].v];
		j = 0;
		for(i = 0; i < N; i++) {
			cs[j] = cs[i];
			if(j == 0 || cs[j].v != cs[j - 1].v) j++;
		}
		N = j;
		memset(bit, 0, sizeof bit);
		if(K == 0) {
			j = 0;
			for(i = 0; i < N; i++) {
				cs[j] = cs[i];
				if(!b(1, true)[cs[j].v]) {
					b(1, true)[cs[j].v] = 1;
					j++;
				} 
			}
			N = j;
			for(i = N - 1; i >= 0; i--) {
				m(i, 0, true) = mod(1 + get(cs[i].v + 1, s.size(), b(0, true)));
				add(cs[i].v, m(i, 0, true), b(0, true));
				m(i, 0, false) = mod(1 + get(cs[i].v - 1, b(0, false)));
				add(cs[i].v, m(i, 0, false), b(0, false));
			}
			ull tot = 0;
			for(i = 0; i < N; i++)
				tot = mod(tot + m(i, 0, true) + m(i, 0, false));
			printf("Case %d: %llu\n", tt, tot + 1 - s.size());
			continue;
		}
		for(i = N - 1; i >= 0; i--) {
			m(i, 0, true) = m(i, 0, false) = 1;
			// printf("m(%d, 0, true) = 1\nm(%d, 0, false) = 1\n", i, i);
			add(cs[i].v, 1, b(0, false));
			add(cs[i].v, 1, b(0, true));
			for(j = 1; j <= K; j++) {
				m(i, j, true) = mod(get(cs[i].v + 1, s.size(), b(j - 1, false)) + get(cs[i].v - 1, b(j, true)));
				add(cs[i].v, m(i, j, true), b(j, true));
				m(i, j, false) = mod(get(cs[i].v - 1, b(j - 1, true)) + get(cs[i].v + 1, s.size(), b(j, false)));
				add(cs[i].v, m(i, j, false), b(j, false));
				// printf("m(%d, %d, true) = %llu\nm(%d, %d, false) = %llu\n", i, j, m(i, j, true), i, j, m(i, j, false));
			}
			m(i, j, true) = get(cs[i].v + 1, s.size(), b(j - 1, false));
			add(cs[i].v, m(i, j, true), b(j, true));
			m(i, j, false) = get(cs[i].v - 1, b(j - 1, true));
			add(cs[i].v, m(i, j, false), b(j, false));
			// printf("m(%d, %d, true) = %llu\nm(%d, %d, false) = %llu\n", i, j, m(i, j, true), i, j, m(i, j, false));
		}
		ull tot = 0;
		for(i = 0; i < N; i++)
			tot = mod(tot + m(i, K + 1, true) + m(i, K + 1, false));
		printf("Case %d: %llu\n", tt, tot);
	}
	return 0;
}