#Uses python3

import sys
import numpy as np

def lcs3(a, b, c):
    #write your code here
    la, lb, lc = len(a)+1, len(b)+1, len(c)+1
    dp = np.zeros((la, lb, lc), dtype = np.int32)
    for i in range(1,la):
        for j in range(1, lb):
            for k in range(1,lc):
                if a[i-1] == b[j-1] and b[j-1] == c[k-1]:
                    dp[i,j,k] = dp[i-1,j-1,k-1]+1
                else:
                    dp[i,j,k] = np.max([dp[i-1,j,k], dp[i,j-1,k], dp[i,j,k-1]])
    return int(dp[la-1,lb-1,lc-1])

if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    an = data[0]
    data = data[1:]
    a = data[:an]
    data = data[an:]
    bn = data[0]
    data = data[1:]
    b = data[:bn]
    data = data[bn:]
    cn = data[0]
    data = data[1:]
    c = data[:cn]
    print(lcs3(a, b, c))
