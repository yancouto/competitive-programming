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

int L, n, a[103], c[103];
double A, C;
int mmx[102][53][503];
int mmn[102][53][503];
bool at[102][53][503];

void pre() {
	int i, l, sum;
	for(l = 0; l <= L; l++)
		for(sum = 0; sum <= 500; sum++)
			mmn[n][l][sum] = 200000000,
			mmx[n][l][sum] = -200000000;
	mmn[n][0][0] = mmx[n][0][0] = 0;
	for(i = n - 1; i >= 0; i--)
		for(l = 0; l <= L; l++)
			for(sum = 0; sum <= 500; sum++) {
				mmn[i][l][sum] = mmn[i + 1][l][sum];
				mmx[i][l][sum] = mmx[i + 1][l][sum];
				if(l && sum >= a[i]) {
					mmn[i][l][sum] = min(mmn[i][l][sum], mmn[i + 1][l - 1][sum - a[i]] + c[i]);
					mmx[i][l][sum] = max(mmx[i][l][sum], mmx[i + 1][l - 1][sum - a[i]] + c[i]);
				}
			}
	at[0][L][0] = 1;
	for(i = 0; i < n; i++)
		for(l = 0; l <= L; l++)
			for(sum = 0; sum <= 500; sum++)
				if(at[i][l][sum]) {
					at[i + 1][l][sum] = true;
					if(l) at[i + 1][l - 1][sum + a[i]] = true;
				}
}

int main() {
	memset(mmx, -1, sizeof mmx);
	memset(mmn, -1, sizeof mmn);
	int i, AA = 0, CC = 0;
	scanf("%d %d", &n, &L);
	if(n - L < L) L = n - L;
	for(i = 0; i < n; i++) scanf("%d", &a[i]), AA += a[i];
	for(i = 0; i < n; i++) scanf("%d", &c[i]), CC += c[i];
	A = AA; C = CC;
	pre();
	double ans = 1/0.;
	for(int sum = 0; sum <= 500; sum++)
		if(at[n][0][sum]) {
			double v1 = mmn[0][L][sum], v2 = mmx[0][L][sum];
			ans = min(ans, min(C * v1 - v1 * v1, C * v2 - v2 * v2) / double(A * sum - sum * sum));
		}
	printf("%.3f\n", ans);
}
