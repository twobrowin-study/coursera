from itertools import combinations
import sys

input = sys.stdin.read()
data = list(map(int, input.split()))

n = data[0]
data = data[1:]
s1 = data[:n]

data = data[n:]
m = data[0]
data = data[1:]
s2 = data[:m]

answer = 0
result = []
for seq_len in range(1, min(len(s1), len(s2))+1):
    for subseq1 in combinations(s1, seq_len):
        for subseq2 in combinations(s2, seq_len):
            if subseq1 == subseq2:
                answer = seq_len
                result = subseq1
        
print(result, answer)