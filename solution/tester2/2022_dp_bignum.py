"""2022_dp_bignum.py

O(n0 * n2) DP using big number
Expect: pass subtask 1,2
"""

import sys

n0, n2 = [int(x) for x in input().split()]
n = n0 + n2

# init pw
pw = [1]
for i in range(1, n + 1):
  pw.append(pw[-1] * 10 % 11)

dp = [[[-1] * (11) for _j in range(0, n2 + 1)] for _i in range(0, n0 + 1)]
dp[0][0][0] = 1
for p in range(n, 0, -1):
  used = n - p + 1

  for i in range(0, min(n0, used) + 1):
    j = used - i
    if j < 0 or j > n2:
      continue

    for k in range(0, 11):
      dp[i][j][k] = 0
      # 0
      if i > 0 and dp[i - 1][j][k] != -1:
        dp[i][j][k] += dp[i - 1][j][k]
      # 2
      mod = 2 * pw[n - p] % 11
      pre = (k - mod) % 11
      if j > 0 and dp[i][j - 1][pre] != -1:
        dp[i][j][k] += dp[i][j - 1][pre]

if dp[n0][n2][0] < 2:
  print('-1')
  sys.exit(0)

# 2nd biggest
ans = []
i = n0
j = n2
k = 0
cnt = 2
while i > 0 or j > 0:
  mod = 2 * pw[i + j - 1] % 11
  pre = (k - mod) % 11

  if j > 0 and dp[i][j - 1][pre] >= cnt:
    ans.append('2')
    j -= 1
    k = pre
  else:
    ans.append('0')
    if j > 0:
      cnt -= dp[i][j - 1][pre]
    i -= 1
print(''.join(ans))

# 2nd smallest
ans = []
i = n0
j = n2
k = 0
cnt = 2
while i > 0 or j > 0:
  mod = 2 * pw[i + j - 1] % 11
  pre = (k - mod) % 11

  if i > 0 and dp[i - 1][j][k] >= cnt:
    ans.append('0')
    i -= 1
  else:
    ans.append('2')
    if i > 0:
      cnt -= dp[i - 1][j][k]
    k = pre
    j -= 1
print(''.join(ans))
