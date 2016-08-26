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
const int N = 112345;
int a[N], b[N];

int main() {
	int i, B, n;
	scanf("%d %d", &B, &n);
	a[0] = b[0] = 1;
	int l = 0, r = n - 1;
	if(a[l] == B - 1) l++;
	if(b[r] == B - 1) r--;
	while(l < r) {
		a[l]++;
		b[r]++;
		if(a[l] == B - 1) l++;
		if(b[r] == B - 1) r--;
	}
	//printf("A: ");
	//for(i = 0; i < n; i++) printf("%d ", a[i]);
	//printf("\nB: ");
	//for(i = 0; i < n; i++) printf("%d ", b[i]);
	//printf("\n");
	for(i = n - 1; i >= 0; i--) {
		a[i] -= b[i];
		//if(a[i] < 0) a[i - 1] -= (-a[i] / B), a[i] = -((-a[i]) % B);
		while(a[i] < 0) a[i] += B, a[i - 1]--;
	}
	for(i = 0; i < n - 1 && a[i] == 0; i++);
	for(; i < n; i++)
		if(a[i] < 10) putchar(a[i] + '0');
		else putchar(a[i] - 10 + 'A');
	putchar('\n');
}
