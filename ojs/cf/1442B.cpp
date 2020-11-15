#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 998244353;
inline ll mod(ll x) { return x % modn; }

const int N = 212345;
int a[N], b[N], rev[N], pr[N], nx[N], dont_care[N];
int n, k;

ll go() {
    scanf("%d %d", &n, &k);
    pr[0] = -1;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        nx[i] = i + 1;
        pr[i + 1] = i;
        rev[a[i]] = i;
    }
    set<int> all;
    for(int i = 0; i < k; i++) {
        scanf("%d", &b[i]);
        all.insert(b[i]);
    }
    ll ans = 1;
    for(int i = 0; i < k; i++) {
        all.erase(b[i]);
        int j = rev[b[i]];
        set<int> pos;
        if (pr[j] != -1) pos.insert(pr[j]);
        if (nx[j] != n) pos.insert(nx[j]);
        set<int> pos2;
        for (const int &x : pos) {
            if (!all.count(a[x])) {
                pos2.insert(x);
            }
        }
        if (pos2.size() == 0) return 0;
        ans = mod(ans * ll(pos2.size()));
        int x = *pos2.begin();
        if(pr[x] != -1) nx[pr[x]] = nx[x];
        if(nx[x] != n) pr[nx[x]] = pr[x];
    }
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) printf("%lld\n", go());
}
