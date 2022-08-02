# Prime Factors of a given number

## Description

The problem consists of taking a set of numbers (whether it be from a file or the command line) and calculating all it's prime factors. The numbers have to be integers and the range of numbers that the program can process is form 0 to $2 \cdot 10^{63} -1$. Any number outside this range is considered an _invalid number_.

Prime numbers are numbers that can only be divided by 1 and itself. So, for example if we have 2016 we can divide this number by 2, by 3 and by 7, this means this number is not a prime number. Another example, 13 can be divided only by 13, which makes it a prime number. If we take the number 2016, it's prime factorization is $2^5 \cdot 3^2 \cdot 7$.

Prime numbers are used in a wide variety of fields and have a lot of applications on daily devices that we don't notice. The most noticeable example is passwords. Most passwords or encrypted software is protected by a very large prime number that it's not easy to decipher.

This program uses threads to calculate the prime numbers of a given number as fast as possible. Threads are mecanisms that programming languages have, to tell the computer to do more than one task at the same time. Here, it's used the C language to program the solution to the problem. C uses pthreads as it's mecanism to divide the tasks in the computer. Because we implemented threads, there's also the option for the user to set the number of threads that can be used in the program. Note that if you do not specify the amount of threads that are gonna be used then the program takes the number of threads as the number of processors your system has. Next are presented some examples of the possible input and possible output of the program.

**Example input:**

```bash
1
7
25
87
378
1400
-40
```

**Example output:**

```bash
1: NA
7: 7
25: 5^2
87: 3 29
378: 2 3^3 7
1400: 2^3 5^2 7
-40: invalid number
```

## User Guide

### To compile

Open the linux terminal. Once you're here, navigate though it using the commands ```cd``` to get to where you have the entire project saved. Once you're at the location just type ```make``` and the program will compile.

### To run

To run the program through the test cases, on the terminal, type ```make test``` and the results will be displayed in the terminal.

### Examples run and output

#### 1)

```make```

```make test```

#### **Output 1**

```bash
icdiff --no-headers tests/output000.txt <(bin/primefact_serial < tests/input000.txt)
icdiff --no-headers tests/output001.txt <(bin/primefact_serial < tests/input001.txt)
icdiff --no-headers tests/output002.txt <(bin/primefact_serial < tests/input002.txt)
```

#### 2)

```make```

You can also type in the numbers you want to know the prime factorization to. Also it is presented how the program takes in the number of threads.

```bash
$ bin/primefact_pthread 100
145
35469
2154
367
12457
32598
6245
3214
325
6874
```

The number 100 specifies 100 threads to be used.

#### **Output 2**

```bash
145: 5 29
35469: 3^2 7 563
2154: 2 3 359
367: 367
12457: 12457
32598: 2 3^2 1811
6245: 5 1249
3214: 2 1607
325: 5^2 13
6874: 2 7 491
```

## Problem Design

[Click here to see the design](./design/README.md)

## Problem Report

[Click here to see the report](./report/README.md)

## Credits

**Author:** Ariel Solis Monge

**Contact:**
