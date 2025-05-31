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

const int N = 212345;
ll a[N];
char s[N];

int main() {
    int n, i; ll k;
    for_tests(t, tt) {
        scanf("%d %lld %s", &n, &k, s);
        for(i = 0; i < n; i++) scanf("%lld", &a[i]);
        ll sum = 0, mx = 0;
        for(i = 0; i < n; i++) {
            sum += a[i];
            if(sum < 0 || s[i] == '0') sum = 0;
            mx = max(mx, sum);
            if(mx > k) {
                puts("No");
                break;
            }
        }
        for(int j = 0; j < n; j++)
            if(s[j] == '0')
                a[j] = -1e13;
        if(i < n) continue;
        if(mx < k) {
            for(i = 0; i < n && s[i] == '1'; i++);
            if(i == n) {
                puts("No");
                continue;
            }
            ll mx_bef = 0;
            ll mx_aft = 0;
            ll cur = 0;
            for(int j = i - 1; j >= 0; j--) {
                cur += a[j];
                mx_bef = max(mx_bef, cur);
            }
            cur = 0;
            for(int j = i + 1; j < n && s[j] == '1'; j++) {
                cur += a[j];
                mx_aft = max(mx_aft, cur);
            }
            a[i] = k - (mx_aft + mx_bef);
        }
        puts("Yes");
        for(i = 0; i < n; i++) printf("%lld%c", a[i], " \n"[i == n - 1]);
    }
}