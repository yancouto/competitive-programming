memo = []
for i in range(32):
	memo.append([])
	for j in range(32):
		memo[i].append([-1] * 32)


def pd(l, r, q):
	if l == 0 and r == 0 and q == 0:
		return 1
	
	me = memo[l][r][q]
	if me != -1:
		return me
	
	me = 0

	for i in range(l):
		me += pd(i, r, q + (l - i - 1))
	for i in range(r):
		me += pd(l, i, q + (r - i - 1))
	if l == 0 and q != 0:
		me += pd(l, r, q - 1)
	if r == 0 and q != 0:
		me += pd(l, r, q - 1)
	
	memo[l][r][q] = me
	return me

import sys
sys.stdin = open("permutominoes.in", "r")
sys.stdout = open("permutominoes.out", "w")

n = int(input())
res = 0
for i in range(n):
	for j in range(i + 1, n):
		res += pd(i, n - j - 1, j - i - 1)

print(str(res))
