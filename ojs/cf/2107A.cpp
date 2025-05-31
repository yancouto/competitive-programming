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

const int N = 1123;
int a[N];

int main() {
    int n;
    for_tests(t, tt) {
        scanf("%d", &n);
        set<int> s;
        for(int i = 0; i < n; i++) scanf("%d", &a[i]), s.insert(a[i]);
        if(s.size() == 1) puts("No");
        else {
            int mn = *s.rbegin();
            puts("Yes");
            for(int i = 0; i < n; i++)
                printf("%d%c", (a[i] == mn)? 1 : 2, " \n"[i == n - 1]);
        }
    }

}