#!/bin/bash

>your-output-all.txt

#test0
gcc -Wall -Werror -Wextra -Wconversion -Wstrict-prototypes -pedantic-errors -std=c11 ./tests/test0.c q.c -o ./tests/test0.out
for ((i=0;i<4;i++));
do
  input_file="./tests/input-test0-${i}.txt"
  output_file="./tests/your-output-test0-${i}.txt"
  ./tests/test0.out < $input_file > $output_file
  diff -y --strip-trailing-cr --suppress-common-lines $input_file $output_file
  cat $output_file >> your-output-all.txt
done

#test1
gcc -Wall -Werror -Wextra -Wconversion -Wstrict-prototypes -pedantic-errors -std=c11 ./tests/test1.c q.c -o ./tests/test1.out
for ((i=4;i<6;i++));
do
  input_file="./tests/input-test1-${i}.txt"
  output_file="./tests/your-output-test1-${i}.txt"
  ./tests/test1.out < $input_file > $output_file
  diff -y --strip-trailing-cr --suppress-common-lines $input_file $output_file
  cat $output_file >> your-output-all.txt
done

#test2
gcc -Wall -Werror -Wextra -Wconversion -Wstrict-prototypes -pedantic-errors -std=c11 ./tests/test2.c q.c -o ./tests/test2.out
for ((i=6;i<8;i++));
do
  input_file="./tests/input-test2-${i}.txt"
  output_file="./tests/your-output-test2-${i}.txt"
  ./tests/test2.out < $input_file > $output_file
  diff -y --strip-trailing-cr --suppress-common-lines $input_file $output_file
  cat $output_file >> your-output-all.txt
done

#test3
gcc -Wall -Werror -Wextra -Wconversion -Wstrict-prototypes -pedantic-errors -std=c11 ./tests/test3.c q.c -o ./tests/test3.out
for ((i=8;i<12;i++));
do
  input_file="./tests/input-test3-${i}.txt"
  output_file="./tests/your-output-test3-${i}.txt"
  ./tests/test3.out < $input_file > $output_file
  diff -y --strip-trailing-cr --suppress-common-lines $input_file $output_file
  cat $output_file >> your-output-all.txt
done

#test4
gcc -Wall -Werror -Wextra -Wconversion -Wstrict-prototypes -pedantic-errors -std=c11 ./tests/test4.c q.c -o ./tests/test4.out
for ((i=12;i<18;i++));
do
  input_file="./tests/input-test4-${i}.txt"
  output_file="./tests/your-output-test4-${i}.txt"
  ./tests/test4.out < $input_file > $output_file
  diff -y --strip-trailing-cr --suppress-common-lines $input_file $output_file
  cat $output_file >> your-output-all.txt
done

#test5
gcc -Wall -Werror -Wextra -Wconversion -Wstrict-prototypes -pedantic-errors -std=c11 ./tests/qdriver.c q.c -o ./tests/q.out
for ((i=18;i<24;i++));
do
  input_file="./tests/input-test5-${i}.txt"
  output_file="./tests/your-output-test5-${i}.txt"
  ./tests/q.out < $input_file > $output_file
  diff -y --strip-trailing-cr --suppress-common-lines $input_file $output_file
  cat $output_file >> your-output-all.txt
done

diff -y --strip-trailing-cr --suppress-common-lines your-output-all.txt output-all.txt
