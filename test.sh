#!/bin/bash

if [ "$#" -lt 3 ]; then
  echo "Usage: $0 1-4 problem Debug/Release (test case)" >&2
  exit 1
fi

if [ "$#" -eq 4 ]; then
  labb$1/$3/labb$1-$2-runner.exe < labb$1/labb$1-$2-runner/Tests/$4.in > labb$1/labb$1-$2-runner/Tests/$4.out
  diff labb$1/labb$1-$2-runner/Tests/$4.out labb$1/labb$1-$2-runner/Tests/$4.ans
else
  for f in labb$1/labb$1-$2-runner/Tests/*.in
  do
    test=$(basename "$f" ".in")
    labb$1/$3/labb$1-$2-runner.exe < labb$1/labb$1-$2-runner/Tests/$test.in > labb$1/labb$1-$2-runner/Tests/$test.out
    diff labb$1/labb$1-$2-runner/Tests/$test.out labb$1/labb$1-$2-runner/Tests/$test.ans
  done
fi