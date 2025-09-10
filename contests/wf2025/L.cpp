#include <bits/stdc++.h>
using namespace std;

const int N = 1123456;
int accN[2*N];


int main() {
  int n, yc, ya, y1, y2;
  int *acc = accN + N;
  scanf("%d %*d %d %*d %d", &n, &yc, &ya);
  for(int i = 0; i < n; i++) {
    scanf("%*d %d %*d %d", &y1, &y2);
    acc[min(y1, y2)]++;
    acc[max(y1, y2)]--;
  }
  if(ya >= yc) {
    puts("0");
    return 0;
  }
  for(int i = -1000009; i <= 1000009; i++)
    acc[i] += acc[i-1];
    int ct = 0;
  for(int i = yc-1; i >= ya; i--) {
    if(acc[i] == 0) ct++;
  }
  printf("%d\n", ct);
}