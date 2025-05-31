#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

const int N = 112345;
int a[N];

int main() {
    int n, k;
    for_tests(t, tt) {
        scanf("%d %d", &n, &k);
        ll sum = 0;
        for(int i = 0; i < n; i++) scanf("%d", &a[i]), sum += a[i];
        sort(a, a + n);
        if(max(a[n - 1] - 1, a[n - 2]) - a[0] > k) puts("Jerry");
        else if(sum % 2) puts("Tom");
        else puts("Jerry");
    }
}