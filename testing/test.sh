#!/bin/bash

compile_and_call_test() {
  local filename="$1"
  local source_code="tests/$filename"

  # Compile test
  g++ -fsanitize=address "$source_code" ./harness.cc -o test
  if [ $? -ne 0 ]; then
    echo "error g++ non-zero exit code"
    return 1
  fi

  # Run test
  ./test
  local test_result=$?

  if [ $test_result -ne 0 ]; then
    echo "error ./test non-zero exit code"
    return 1
  fi

  return 0
}

main() {
  local total=0
  local passed=0

  for entry in tests/*; do
    filename=$(basename "$entry")
    echo "running test $filename"

    if compile_and_call_test "$filename"; then
      echo "test $filename: passed"
      ((passed++))
    else
      echo "test $filename: failed"
    fi

    rm -f ./test

    echo ""
    ((total++))
  done

  echo "passed $passed out of $total tests"

  if [ $passed -lt $total ]; then
    exit 1
  fi
}

main
