#!/usr/bin/env python2
#
# <= 40 instructions
import sys

N = int(sys.stdin.readline())

def go(N, B):
    if N == 0:
        return ['ZE A']
    if N == 1:
        return ['ST A']
    if N == 2:
        return ['PH X', 'PH X', 'AD', 'PL A']
    b = 2
    for c in range(3, min(B, N+1)):
        if N % c < N % b:
            b = c
    res = go(N/b, B)
    res.extend(['PH A']*b)
    res.extend(['AD']*(b-1))
    res.extend(['PH X', 'AD']*(N%b))
    res.append('PL A')
    return res

best = go(N, 2)
for B in range(3, 10):
    P = go(N, B)
    if len(P) < len(best):
        best = P
        
print 'ST X'
print '\n'.join(best)
print 'DI A'

