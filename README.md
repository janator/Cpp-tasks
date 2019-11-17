# DIHT - 2018/2019 - first term - tasks - rudykh
## Second modul
### Task A. Sort strings

Write a program that prints a set of lines in lexicographic order.
Lines are separated by the character ’\n’. If the last character in the input stream is ’\n’, assume that there is no empty line after it. It is known that either *n* < 100 or *n* ≤ 1000, but the number of inversions in this set of lines is less than 100. The maximum line length is 255 characters. Write your own string comparison function.

Time limit: 1 c;

Memory limit: 3 Mb.

Example:  

| In | Out |
| ---  | ----- |
|4 <br> caba <br> abba <br> ab <br> aba| ab <br> aba <br> abba <br> caba|

Solution: [task А](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_1/Modul_2/TaskA/main.cpp).

***
### Task B. Сontemporaries


A group of people is called contemporaries if there was such a moment when they could get together. At this moment, each of them should have turned 18 years old, but not yet turned 80 years old. A list of the Life of Great People is given. You need tot get the maximum number of contemporaries. On the day of the 18th birthday, a person can already take part in meetings, but on the day of the 80th birthday and on the day of death he can't.

Time limit: 0.25 с;

Memory limit: 64 Mb.

Example:

| In | Out |
| ---- | ----- |
|3 <br> 2 5 1980 13 11 2055 <br> 1 1 1982 1 1 2030 <br> 2 1 1920 2 1 2000 | 3 |

Solution: [task B](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_1/Modul_2/TaskB/main.cpp)

---
### Task C. Kth order statistic

Given non-negative integers *n, k* and an array of integers from the range [0..10^9] of size *n*.
It is required to find the kth order statistic.
Write a non-recursive algorithm.

Additional memory requirements: *O(n)*.

Required average run time: *O(n)*.

Time limit: 0.15 с;

Memory limit: 64 Mb.

Example:

| In | Out |
| ---- | ----- |
|10 4 <br> 1 2 3 4 5 6 7 8 9 10 | 5|

Solution: [task C](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_1/Modul_2/TaskC/main.cpp)

---
### Task D. number of inversions

Given a sequence of integers from the range (-10^9 .. 10^9). The length of the sequence isn't more than 10^6. It is required to print the number of such pairs of indices *(i, j)* from *[0..n-1]* such that (*i < j* and *a[i]> a [j]*). 

Time limit: 1 с;

Memory limit: 64 Mb.

Example:

| In | Out |
| ---- | ----- |
|3 <br> 2 <br> 2| 2|

Solution: [task D](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_1/Modul_2/TaskD/main.cpp)

---

### Task E. Binary MSD for int_64

An array of non-negative 64-bit integers is given. The number of numbers is not more than 10^6. Sort the array using the MSD method by bits (binary QuickSort).

Time limit: 1 с;

Memory limit: 10 Mb.

Example:

| In | Out |
| ---- | ----- |
|3<br>4 1000000 7| 4 7 1000000 |

Solution: [task E](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_1/Modul_2/TaskE/main.cpp)

---


### Task F. The quickest sort

An array of integers is given in the range [0..10^9]. The size of the array is a multiple of 10 and is limited from above by a value of 2.5 * 10^7 elements. It is necessary to sort the elements of the array in minimum time and display every tenth element of the sorted sequence.

Implement QuickSort-based sorting.

The minimum set of optimizations that must be implemented:
1. Input/output optimization;
2. Optimization of the choice of the support element;
3. Partition optimization;
4. Recursion optimization;
5. Optimization of trailing recursion.

Time limit: 20 с;

Memory limit: 300 Mb.

Example:

| In | Out |
| ---- | ----- |
|3 0 2 1 5 4 21 4 6 5| 21 |

Solution: [task F](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_1/Modul_2/TaskF/main.cpp)

---
## Third modul
### Task A. Tree traversal pre-order

Given a number *N* ≤ 104 and a sequence of integers from [-2^^31..231] of length *N*. It is required to construct a binary tree defined by the naive insertion order. Print the items in post-order (bottom to top). Recursion is prohibited.

Time limit: 0.2 c;

Memory limit: 64 Mb.

Example:  

| In | Out |
| ---  | ----- |
|10 <br> 7 <br> 2 <br> 10 <br> 8 <br> 5 <br> 3 <br> 6 <br> 4 <br> 1 <br> 9| 1 4 3 6 5 2 9 8 10 7|

Solution: [task А](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_1/Modul_3/TaskA/main.cpp).

***
### Task B. AVL Tree

Given the number of *N* and *N* rows. Each line contains a command to add or remove natural numbers, as well as a request for the kth order statistic. The command to add the number A is given by the positive number A, the command to delete the number A is given by the negative number -A. The request for the kth order statistics is given by the number *k*. The required query execution speed is *O(log n)*.

Time limit: 0.3 c;

Memory limit: 20 Mb.

Example:  

| In | Out |
| ---  | ----- |
|3 <br> 1 0 <br> 2 0 <br> -1 0|1 1 2|

Solution: [task C](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_1/Modul_3/TaskC/main.cpp).

***
