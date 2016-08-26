#include <cstdio>

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int n;
		scanf("%d", &n);
		printf("%s\n", (n % 4)? "First" : "Second");
	}
	return 0;
}