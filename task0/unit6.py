s = input().replace(' ', '').lower()
print('YES' if s == s[::-1] else 'NO')