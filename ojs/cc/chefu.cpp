#include <cstdio> 
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
const int MAX = 200009;
int n, q;
int a[MAX], b[MAX];
bool dec(int i, int j) { return i > j; }

int main() {
	int i, s, e;
	scanf("%d %d", &n, &q);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for(i = 0; i < q; i++) {
		scanf("%d %d", &s, &e);
		b[s - 1]++;
		b[e]--;
	}
	for(i = 1; i < n; i++)
		b[i] += b[i - 1];
	sort(a, a + n, dec);
	sort(b, b + n, dec);
	ull sum = 0;
	for(i = 0; i < n; i++)
		sum += static_cast<ull>(a[i]) * static_cast<ull>(b[i]);
	printf("%llu\n", sum);
	return 0;
}