import re
s, s2 = input(), input() # get 2 strings from the keyboard

# Here we use re to build a list of positions of s2 in s (with overlappings)
cnt = len([m.start() for m in re.finditer('(?=' + s2 + ')', s)])
print(cnt)