a = list(map(int, input().split()))
print('YES' if a == a[::-1] else 'NO')