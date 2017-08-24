#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define fst first
#define snd second

int p[] = {2, 3, 5, 7, 11, 13, 17};
int pn = 7;

const int M = 2310 * 13 * 17;
int mrk[M+1], nx[M + 1];

int jmp[M];

int main() {
	ll i; int j;
	for(i = 0; i < pn; i++)
		for(j = p[i]; j <= M; j += p[i])
			mrk[j] = 1;
	nx[M] = M + 1;
	for(i = M - 1; i >= 0; i--)
		if(mrk[i + 1] == 0)
			nx[i] = i + 1;
		else
			nx[i] = nx[i + 1];
	//int t = 0;
	//for(i = 1; i <= M; i++)
	//	t += !mrk[i];
	//printf("%d out of %d\n", t, M);
	ll tot = 1;

	ll n;
	scanf("%lld", &n);
	map<ll, int> all_ps;
	for(i = 0; i < pn; i++) {
		int ct = 0;
		while((n % p[i]) == 0) {
			n /= p[i];
			tot /= (1 + ct);
			ct++;
			tot *= (1 + ct);
		}
	}
	i = 1;
	int jn = 0;
	while(i <= M) {
		jmp[jn++] = nx[i] - i;
		i = nx[i];
	}
	j = 0;
	for(i = M + 1; i * i <= n;) {
		int ct = 0;
		while(!(n % i)) {
			n /= i;
			tot /= (1 + ct);
			ct++;
			tot *= (1 + ct);
		}
		i += jmp[j++];
		if(j == jn) j = 0;
	}
	if(n > 1) tot *= 2;
	printf("%lld\n", tot);
}
