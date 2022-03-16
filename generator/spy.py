"""spy"""
import random


def out(subtask, variant, n, m):
  """out"""
  fn = '%d_%s_%d_%d.in' % (subtask, variant, n, m)
  with open(fn, 'w') as f:
    print(n, m, file=f)


def subtask1():
  """subtask1"""
  # full test
  for i in range(2, 17):
    for j in range(2, 17):
      if i * j <= 16:
        out(1, 'small', i, j)


def subtask2():
  """subtask2"""
  # (2, 2), (2, 3),         ..., (2, 15)
  #         (3, 2), (4, 2), ..., (15, 2)
  for j in range(2, 16):
    out(2, 'small', 2, j)
    if j != 2:
      out(2, 'small', j, 2)

  # largest tests, 990 ~ 1000
  for j in range(990, 1001):
    out(2, 'large', 2, j)
    out(2, 'large', j, 2)

  # random
  for j in random.choices(range(16, 990), k=30):
    if random.randint(0, 1) == 0:
      out(2, 'random', 2, j)
    else:
      out(2, 'random', j, 2)


def subtask3():
  """subtask3"""
  # n, m= 12~17, full set
  for i in range(12, 18):
    for j in range(12, 18):
      out(3, 'small', i, j)

  # random one dimension, as many vertices as possible
  for _ in range(1, 30):
    i = random.randint(12, 2000 // 12)
    j = 2000 // i

    if random.randint(0, 1) == 0:
      i, j = j, i
    out(3, '2000p_random1', i, j)

  # some interested i's
  for i in [12, 13, 14, 15, 16, 161, 162, 163, 164, 165, 166]:
    j = 2000 // i
    if random.randint(0, 1) == 0:
      i, j = j, i
    out(3, '2000p_corner', i, j)

  # random
  for _ in range(1, 15):
    i = random.randint(12, 2000 // 12)
    j = random.randint(12, min(2000 // i, 1000))
    out(3, 'random', i, j)


def subtask4():
  """subtask4"""
  # subtask4 includes subtask1, 2, 3

  ore_test_invalid = [  # (n, min_m, max_m)
      (3, 6, 11),  # (3, 3, 5) included in subtask 1
      (4, 5, 8),  # (4, 2, 4) included in subtask 1
      (5, 5, 7),
      (6, 6, 7),
  ]
  for n, mn, mx in ore_test_invalid:
    for m in range(mn, mx + 1):
      i = n
      j = m
      if random.randint(0, 1) == 0:
        i, j = j, i
      out(4, 'ore_invalid', i, j)

  # i=3~11, j=2000/i, not covered in previous subtasks
  for i in range(3, 12):
    j = 2000 // i
    if random.randint(0, 1) == 0:
      i, j = j, i
    out(4, '2000p_corner', i, j)

  # random, i = 3~11
  for _ in range(3, 15):
    i = random.randint(2, 11)
    j = random.randint(2, min(2000 // i, 1000))
    if random.randint(0, 1) == 0:
      i, j = j, i
    out(4, 'random_narrow', i, j)


def main():
  """main"""
  random.seed(114514)
  subtask1()
  subtask2()
  subtask3()
  subtask4()


if __name__ == '__main__':
  main()
