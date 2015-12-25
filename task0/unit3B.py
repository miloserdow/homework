# Solve both 3b and 3c as it uses recursion 
def binpow(a, n):
	if n == 0:
		return 1
	if n % 2 == 1:
		return a * binpow(a, n - 1)
	x = binpow(a, n // 2)
	return x * x

a, n = map(int, input().split())
print(binpow(a, n))