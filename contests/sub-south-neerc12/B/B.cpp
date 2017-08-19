#include <bits/stdc++.h>
#define cout if (0) cout
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int N = 6e2+7;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef pii tA;
typedef null_type tB; // or null_type if you want a set
typedef tree<tA, tB, less<tA>, rb_tree_tag, tree_order_statistics_node_update> ord_set;
// map: tA -> tB com comparador less<tA>
// pode usar como um map normalmente
// s.find_by_order(k) :: retorna iterador para o k-esimo elemento (0-index) (ou s.end())
// s.order_of_key(x)  :: retorna a qtd de elementos estritamente menores que x

ll x[N], l[N], r[N];
int p[N];

struct evt {
	int x, y;
	int i;

	bool operator < (const evt & ot) const {
		return x < ot.x;
	}
} op[N], cl[N];

int n, m, qs;
int inp[4];

int main () {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &qs);

	for (int i = 0; i < qs; i++) {
		for (int j = 0; j < 4; j++)
			scanf("%d", &inp[j]);

		if (inp[0] == inp[2]) {
			x[n] = inp[0];
			l[n] = inp[1];
			r[n] = inp[3];
			if (l[n] > r[n])
				swap(l[n], r[n]);
			p[n] = n++;
		} else {
			op[m].x = inp[0];
			cl[m].x = inp[2];
			
			op[m].y = cl[m].y = inp[1];
			op[m].i = cl[m].i = i;

			if (op[m].x > cl[m].x)
				swap(op[m].x, cl[m].x);
			m++;
		}
	}

	sort(p, p+n, [] (int i, int j) {
		return x[i] < x[j];
	});
	sort(op, op+m);
	sort(cl, cl+m);

	ll rs = 0;
	for (int _i = 0; _i < n; _i++) {
		int i = p[_i];
		cout << "tentando " << i << endl;

		ord_set s;
		int os = 0;
		int cs = 0;

		while (os < m && op[os].x <= x[i]) {
			if (op[os].y >= l[i] && op[os].y <= r[i]) {
				s.insert(pii(op[os].y, op[os].i));
				cout << "insere " << op[os].i << endl;
			}
			os++;
		}

		while (cs < m && cl[cs].x < x[i]) {
			s.erase(pii(cl[cs].y, cl[cs].i));
			cout << "erase " << cl[cs].i << endl;
			cs++;
		}

		for (int _j = _i+1; _j < n; _j++) {
			int j = p[_j];

			cout << "com " << j << endl;

			while (cs < m && cl[cs].x < x[j]) {
				s.erase(pii(cl[cs].y, cl[cs].i));
				cout << "erase " << cl[cs].i << endl;
				cs++;
			}

			ll an = s.order_of_key(pii(r[j],N)) - s.order_of_key(pii(l[j],-1));
			rs += an*(an-1)/2;
		}
	}

	printf("%lld\n", rs);
}
