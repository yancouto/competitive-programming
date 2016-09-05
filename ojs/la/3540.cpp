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

char s1[1000], s2[1000];
int n3[1000];
int main() {
	int i, j;
	for_tests(t, tt) {
		scanf("%s", s1);
		scanf("%s", s2);
		for(i = 0; s1[i] == '0'; i++);
		for(j = 0; s2[j] == '0'; j++);
		int cr = 0, k = 0;
		while(s1[i] && s2[j]) {
			int v1 = s1[i] - '0';
			int v2 = s2[j] - '0';
			int v = v1 + v2 + cr;
			n3[k++] = v % 10;
			cr = v / 10;
			i++; j++;
		}
		while(s1[i]) {
			int v1 = s1[i] - '0';
			int v = v1 + cr;
			n3[k++] = v % 10;
			cr = v / 10;
			i++;
		}
		while(s2[j]) {
			int v2 = s2[j] - '0';
			int v = v2 + cr;
			n3[k++] = v % 10;
			cr = v / 10;
			j++;
		}
		if(cr) n3[k++] = cr;
		for(i = 0; i < k - 1 && n3[i] == 0; i++);
		for(; i < k; i++) printf("%d", n3[i]);
		putchar('\n');
	}
}
