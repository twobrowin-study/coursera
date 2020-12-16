from itertools import combinations
from random import randrange

maxlen = 10
rng    = 3

n = maxlen #randrange(maxlen)+1
s1 = []
for i in range(n):
    num = randrange(rng)+1# // 2 - randrange(rng)
    s1.append(num)

m = maxlen #randrange(maxlen)+1
s2 = []
for i in range(m):
    num = randrange(rng)+1# // 2 - randrange(rng)
    s2.append(num)

print(len(s1))
print(' '.join( str(x) for x in s1 ))
print(len(s2))
print(' '.join( str(x) for x in s2 ))