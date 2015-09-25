n = int(input())
primes = []
isprime = [True] * (n + 1)
j = 2
while j <= n:
	k = 2
	if isprime[j]:
		primes.append(j)
		while j * k <= n:
			isprime[j * k] = False
			k += 1
	j += 1
print(' '.join(str(x) for x in primes))