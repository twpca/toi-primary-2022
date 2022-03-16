"""judge all tests"""
import argparse
from concurrent.futures import ProcessPoolExecutor
import json
import multiprocessing
import os
import subprocess
import sys
from . import common


def init_args():
  """init_args"""
  parser = argparse.ArgumentParser()
  parser.add_argument(
      '--probs',
      nargs='*',
      default=[],
      help='Problems wanted to be validated, leave it blank to run all.')
  parser.add_argument(
      '--ignore-probs',
      nargs='*',
      default=[],
      help='Problems wanted to be ignored, leave it blank to run all.')
  parser.add_argument(
      '--writers',
      nargs='*',
      default=[],
      help='Judge only some writers code, leave it blank to run all.')
  parser.add_argument('--ignore-solutions',
                      action='store_true',
                      help='Ignore all solutions.')
  parser.add_argument('--ignore-validators',
                      action='store_true',
                      help='Ignore all validators.')
  parser.add_argument(
      '--sleep',
      action='store_true',
      help=
      'Sleep after compile finish (resolve permission issue for samba mount)')
  return parser.parse_args()


def generate_new_hash(tests):
  """generate_new_hash"""
  result = {}
  for _, case in tests.items():
    for t in case:
      base = os.path.basename(t['input_file'])
      result[base] = t.input_sha1
  return result


def main():
  """main"""
  args = init_args()
  problems = common.get_probs()

  for prob in problems:
    prob_id = prob.prob_id

    # ignore problem
    if args.probs and prob_id not in args.probs:
      continue
    if args.ignore_probs and prob_id in args.ignore_probs:
      continue
    if 'generator' not in prob or not prob.generator:
      continue

    print('Generate tests, prob = %s' % prob_id)

    # generate .in
    common.Compiler.compile(prob.generator.generator, sleep=args.sleep)
    subprocess.check_call(prob.generator.generator.execute.split(' '),
                          cwd=prob.generator.generator.dirname)
    tests = common.get_tests(prob_id,
                             root=os.path.join(os.getcwd(), 'generator'),
                             check_output=False)
    if os.path.exists(prob.generator.generator.execname):
      os.unlink(prob.generator.generator.execname)

    # generate .out
    common.Compiler.compile(prob.generator.solution, sleep=args.sleep)
    for _, case in tests.items():
      for t in case:
        subprocess.check_call(prob.generator.solution.execute.split(' '),
                              cwd=prob.generator.solution.dirname,
                              stdin=open(t['input_file']),
                              stdout=open(t['output_file'], 'w'))
    if os.path.exists(prob.generator.solution.execname):
      os.unlink(prob.generator.solution.execname)

    # check hashes
    for _, case in tests.items():
      for t in case:
        base = os.path.basename(t['input_file'])
        if t.input_sha1 != prob.generator.input_hash.get(base):
          print('Hash check failed, expect %s, got %s' %
                (prob.generator.input_hash.get(base), t.input_sha1))
          print('hash generated:')
          print(
              json.dumps(generate_new_hash(tests),
                         indent=2,
                         ensure_ascii=False,
                         sort_keys=True))
          sys.exit(1)

    # check duplicate files
    for _, case in tests.items():
      for t in case:
        in_base = os.path.basename(t['input_file'])
        in_to = os.path.join(os.getcwd(), 'testdata', t.prob_id, in_base)
        out_base = os.path.basename(t['output_file'])
        out_to = os.path.join(os.getcwd(), 'testdata', t.prob_id, out_base)
        if not os.path.exists(os.path.dirname(out_to)):
          os.makedirs(os.path.dirname(out_to), exist_ok=True)
        if os.path.exists(in_to) or os.path.exists(out_to):
          print('Failed: Input %s %s exists' % (in_to, out_to))
          sys.exit(1)

    # check duplicate files
    for _, case in tests.items():
      for t in case:
        in_base = os.path.basename(t['input_file'])
        in_to = os.path.join(os.getcwd(), 'testdata', t.prob_id, in_base)
        out_base = os.path.basename(t['output_file'])
        out_to = os.path.join(os.getcwd(), 'testdata', t.prob_id, out_base)
        print('Generate: ', in_to, out_to)
        os.rename(t['input_file'], in_to)
        os.rename(t['output_file'], out_to)


if __name__ == '__main__':
  sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', buffering=1)
  main()
