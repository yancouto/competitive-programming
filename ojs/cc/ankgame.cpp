#include <cstdio> 
#include <unordered_map>
#include <algorithm>
typedef unsigned long long ull;
const ull modn = 1000000007ull;
inline ull mod(ull x) { return x % modn; }
using namespace std;
unordered_map < ull, ull > mp;

int n, n1, n2;
ull ex(ull a, ull b) {
	ull res = 1ull;
	for(int i = 0; (1ull << i) <= b; i++) {
		if(b & (1ull << i))
			res = mod(res * a);
		a = mod(a * a);
	}
	return res;
}

ull fat[100005];
void pre_calc() {
	fat[0] = 1;
	for(int i = 1; i < 100003; i++)
		fat[i] = mod(fat[i - 1] * i);
}

ull comb(ull a, ull b) {
	return mod(fat[a] * ex(mod(fat[b] * fat[a - b]), modn - 2));
}


ull calc() {
	ull tot = 0;
	for(int i = 0; i <= n1; i += 2) {
		tot = mod(tot + mod(fat[n2 - 1] * mod(n2 * comb((n2 - 1) + (n1 - i), n2 - 1))));
		// printf("tot %llu\n", tot);
	}
	return tot;
}


int main() {
	pre_calc();
	int t, i, j;
	ull x;
	scanf("%d", &t);
	while (t--) {
		mp.clear();
		n1 = n2 = 0;
		scanf("%d", &n);
		for (i = 0; i < n; i++) {
			scanf("%llu", &x);
			if (x == 1ull) {
				n1++;
				continue;
			}
			n2++;
			if (mp.count(x))
				mp[x]++;
			else 
				mp[x] = 1ull;
		}
		ull d = 1;
		for (auto dd : mp) {
			d = mod(d * fat[dd.second]);
			// printf("%d -- %d times\n", dd.first, dd.second);
		}
		if(n2 == 0) printf("%d\n", n1 & 1);
		else printf("%llu\n", mod(calc() * ex(d, modn - 2)));
	}
	return 0;
}