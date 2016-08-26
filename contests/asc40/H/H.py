import bisect
import math
import sys
ps = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113]
memo = [-1] * 40
t = 0
sys.stdin = open('handsome.in', 'r')
sys.stdout = open('handsome.out', 'w')
while True:
	n = int(input())
	if n == 0:
		break
	t += 1
	#print("Case #%d: " % (t), end = '')
	if memo[n] != -1:
		print(memo[n])
		continue
	T = 1
	for i in range(n):
		T *= ps[i]
	tot = math.floor(math.sqrt(T))
	m = n // 2
	vec = []
	for bm in range(1 << m):
		mul = 1
		for j in range(m):
			if ((bm >> j) & 1) == 1:
				mul *= ps[j]
		vec.append(mul)
	vec.sort()
	best = -1
	a = 0
	for bm in range(1 << (n - m)):
		mul = 1
		for j in range(n - m):
			if ((bm >> j) & 1) == 1:
				mul *= ps[m + j]
		if mul <= tot:
			se = math.floor(tot / mul)
			pos = bisect.bisect_right(vec, se) - 1
			assert(pos >= 0)
			mul *= vec[pos]
			ans = abs(mul - (T // mul))
			if best == -1 or best > ans:
				best = ans
				a = min(mul, T // mul)
	print(a)
	memo[n] = a
