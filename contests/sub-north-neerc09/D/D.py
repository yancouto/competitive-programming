import sys
sys.stdin = open('dragon.in', 'r')
sys.stdout = open('dragon.out', 'w')

n, d = map(int, input().split())

m = 10 ** (n - 1)
k = (m + d - 1) // d
if k * d >= (10 ** n):
	print("No solution")
else:
	print(k * d)
