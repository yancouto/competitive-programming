import numpy as np
num = ["ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"]
A = np.zeros([26, 10])
for i in range(10):
	for c in num[i]:
		A[ord(c) - ord('A'), i] += 1
t = int(input())
for T in range(t):
	s = input()
	f = np.zeros(26)
	for c in s:
		f[ord(c) - ord('A')] += 1
	sol = np.linalg.lstsq(A, f)[0]
	#print("Case #%d: " % (T + 1), end = '');
	for i in range(10):
		v = int(round(sol[i]))
		for j in range(v):
			print(i, end = '')
	print("")
