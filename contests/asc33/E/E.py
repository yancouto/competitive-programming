memo = [([-1] * 190) for i in range(1, 190)]
memo2 = []
for j in range(0, 190):
	memo2.append([([-1] * 190) for i in range(1, 190)])
memo3 = [([-1] * 190) for i in range(1, 190)]

def ch(n, p):
	if p > n or p < 0:
		return 0
	if n == 0:
		return 1
	if memo3[n][p] != -1:
		return memo3[n][p]
	r = ch(n - 1, p) + ch(n - 1, p - 1)
	memo3[n][p] = r
	return r

def choose(n, sz, left):
	if left == 0:
		return int(n == 0)
	if left > sz:
		return 0
	if memo2[n][sz][left] != -1:
		return memo2[n][sz][left]
	r = 0
	for x in range(1, n + 1):
		r += ch(n - 1, x - 1) * choose(n - x, sz, left - 1) * pd(x - 1, sz)
	memo2[n][sz][left] = r
	#print("choose(%d, %d, %d) = %d" % (n, sz, left, r))
	return r

def pd(n, mx):
	if n == 0:
		return 1
	if memo[n][mx] != -1:
		return memo[n][mx]
	r = 0
	for sz in range(1, mx + 1):
		r += choose(n, sz, sz)
	memo[n][mx] = r
	#print("pd(%d, %d) = %d" % (n, mx, r))
	return r

import sys

for i in range(1, 151):
	print('"' + str(pd(i - 1, i - 1)) + '",')
	sys.stderr.write(str(i) + "\n")
