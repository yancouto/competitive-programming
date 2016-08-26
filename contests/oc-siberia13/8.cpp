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
const int N = 100009;
int v[256];
char s[N], p[N], s1[N], p1[N];
int f[N];
int ok[N];

inline void kmp(char *s, int *f) {
	f[0] = -1;
	for(int i = 1; s[i]; i++) {
		f[i] = f[i - 1];
		while(f[i] != -1 && s[f[i]+1] != s[i])
			f[i] = f[f[i]];
		if(s[f[i]+1] == s[i]) f[i]++;
	}
}

int aux[256];
int main() {
	int i, a1, a2;
	scanf("%d %d", &a1, &a2);
	scanf("%s", s);
	for(i = 0; s[i]; i++)
		v[s[i]] = 1;
	scanf("%s", s);
	for(i = 0; s[i]; i++)
		v[s[i]] = 2;
	scanf("%s", s1);
	scanf("%s", p1);
	int n = strlen(p1);
	vector<char> A2;
	for(i = 0; i < 256; i++)
		if(v[i] == 2)
			A2.pb(i);
	A2.pb(';');
	for(char c : A2) {
		bool go = false;
		//printf("testing %c\n", c);
		for(i = 0; p1[i]; i++) {
			if(v[p1[i]] == 1 || p1[i] == c)
				p[i] = p1[i];
			else p[i] = '*';
			if(p1[i] == c) go = true;
		}
		//printf("c %c\n", c);
		if(!go && c != ';') continue;
		//printf("conitnuing\n");
		//puts(p);
		//printf("continuing\n");
		kmp(p, f);
		for(char c2 : A2) {
			if(c == ';' && c2 != ';') continue;
			if(c2 == ';' && c != ';') continue;
			for(i = 0; s1[i]; i++)
				if(v[s1[i]] == 1) s[i] = s1[i];
				else if(s1[i] == c2) s[i] = c;
				else s[i] = '*';
			//puts(s);
			int q = -1;
			for(i = 0; s[i]; i++) {
				while(q != -1 && p[q+1] != s[i])
					q = f[q];
				if(p[q+1] == s[i]) q++;
				if(q == n - 1) {
					//printf("match starting %d\n", i - n + 1);
					ok[i - n + 1]++; q = f[q];
				}
			}
		}
	}
	int all = 0, tot = 1;
	for(i = 0; i < n; i++)
		if(!aux[p1[i]] && v[p1[i]] == 2)
			tot++, aux[p1[i]] = true;
	//puts(s);
	for(i = 0; s1[i]; i++)
		if(ok[i] == tot)
			all++;
	//for(i = 0; s1[i]; i++)
	//	printf("%d ", ok[i]);
	//putchar('\n');
	printf("%d\n", all);
}
