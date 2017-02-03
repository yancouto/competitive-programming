import math
def comb(n, p):
	return math.factorial(n) / (math.factorial(p) * math.factorial(n - p))

memo = [-1 for i in range(0, 206)]
def solve(n):
	if n == 0:
		return 1
	if memo[n] != -1:
		return memo[n]
	r = 0
	for i in range(2, n + 1, 1):
		#print("here %d * %d * %d" % (solve(n - i), comb(n - 1, i - 1), (2 ** i)))
		r += solve(n - i) * comb(n - 1, i - 1) * math.factorial(i - 1) * (2 ** i)
	r += solve(n - 1)
	memo[n] = r
	#print("solve %d = %d" % (n, r))
	return r

for i in range(0, 201):
	print("\"%d\"," % (solve(i)))

