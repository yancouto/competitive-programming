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

const int N = 112345;

int n, t[N], m[N], c[N], p[N];

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d %d %d", &t[i], &m[i], &c[i]), p[i] = i;
    sort(p, p + n, [](int i, int j) { return t[i] < t[j]; });
    int tot = 0;
    queue<int> q;
    int nx_free = 0;
    vector<int> sad;
    int lst_player = 0;
    for(int i_ = 0; i_ < n; i_++) {
        int i = p[i_];
        while(!q.empty() && t[i] >= nx_free) {
            int j = q.front(); q.pop();
            //printf("%2d plays (%d,%d) after %2d ended\n", j+1, nx_free, m[j], lst_player+1);
            lst_player = j;
            nx_free = nx_free + m[j];
        }
        if(t[i] >= nx_free) {
            //printf("Play %2d at (%d,%d) with no one angry\n", i+1, t[i],t[i]+m[i]);
            nx_free = t[i] + m[i];
            lst_player = i;
        } else if(c[i] == 0) {
            //printf("Add %2d to queue\n", i+1);
            q.push(i);
        } else {
            //printf("%2d plays (%d,%d) and %2d is sad\n", i+1, t[i], t[i] + m[i], lst_player+1);
            sad.pb(lst_player);
            nx_free = t[i] + m[i];
            lst_player = i;
        }
    }
    printf("%d\n", sad.size());
    for(int x: sad) printf("%d ", x + 1);
}