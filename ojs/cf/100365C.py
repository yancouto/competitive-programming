import sys

sys.stdin = open('arbitrage.in', 'r')
sys.stdout = open('arbitrage.out', 'w')

def less(f, g):
	return f[0] * g[1] < g[0] * f[1]

def min(f, g):
	if less(f, g):
		return f
	else:
		return g

def swp(f):
	return f[::-1]

def times(f, g):
	return [f[0] * g[0], f[1] * g[1]]

def gcd(a, b):
	if b == 0:
		return a
	return gcd(b, a % b)

def simpl(f):
	g = gcd(f[0], f[1])
	return [f[0] // g, f[1] // g]

def prn(f, end='\n'):
	print("%d/%d" % (f[0], f[1]), end=end)

n = int(input())
mn = []
mx = []
for i in range(n):
	j = 0
	mn.append([])
	mx.append([])
	for j in range(n):
		frcs = input().split(' ')
		mn[i].append(list(map(int, frcs[0].split('/'))))
		mx[i].append(list(map(int, frcs[1].split('/'))))

for i in range(n):
	for j in range(n):
		mx[i][j] = min(mx[i][j], swp(mn[j][i]))

d = [[1, 0]] * n
d[0] = [1, 1]

for k in range(n):
	for i in range(n):
		for j in range(n):
			if i == j or d[i][1] == 0:
				continue
			d[j] = min(d[j], times(d[i], mx[i][j]))

A = []
for i in range(n):
	A.append([])
	for j in range(n):
		if i == j:
			A[i].append([1, 1])
			continue
		if less(times(d[i], mx[i][j]), d[j]):
			print("Impossible")
			exit(0)
		A[i].append(times(d[j], swp(d[i])))

for i in range(n):
	for j in range(n):
		A[i][j] = simpl(A[i][j])
		print("%d/%d" % (A[i][j][0], A[i][j][1]), end=' ')
	print('')
