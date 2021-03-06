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
### Task B. Treap

Given a number *N* < 106 and a sequence of pairs of integers from [-2<sup>31</sup>, 2<sup>31</sup>] of length *N*.

Build a treap from *N* nodes characterized by pairs of numbers *(X<sub>i</sub>, Y<sub>i</sub>)*. Each pair of numbers *(X<sub>i</sub>, Y<sub>i</sub>)* defines the key X<sub>i</sub> and the priority Y<sub>i</sub> in the treap.
Build also a binary tree. Calculate the difference between the depths of a binary tree and a treap. 

Time limit: 1 c;

Memory limit: 64 Mb.

Example:  

| In | Out |
| ---  | ----- |
|10 <br> 5 11 <br> 18 8 <br> 25 7 <br> 50 12 <br> 30 30 <br> 15 15 <br> 20 10 <br> 22 5 <br> 40 20 <br> 45 9|2|

Solution: [task B](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_1/Modul_3/TaskB/main.cpp).

***
### Task C. AVL Tree

Given the number of *N* and *N* rows. Each line contains a command to add or remove natural numbers, as well as a request for the kth order statistic. The command to add the number A is given by the positive number A, the command to delete the number A is given by the negative number -A. The request for the kth order statistics is given by the number *k*. The required query execution speed is *O(log n)*.

Time limit: 0.3 c;

Memory limit: 20 Mb.

Example:  

| In | Out |
| ---  | ----- |
|3 <br> 1 0 <br> 2 0 <br> -1 0|1 1 2|

Solution: [task C](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_1/Modul_3/TaskC/main.cpp).

***
## Fourth modul
### Task A. Hash table
Implement a multi-row data structure based on a dynamic hash table with open addressing. Stored strings are non-empty and consist of lowercase Latin letters. The hash function of the string must be implemented by calculating the value of the polynomial by the Horner method. The initial size of the table must be equal to 8. Perform rehashing when adding elements in the case when the fill factor of the table reaches 3/4. The data structure should support the operations of adding a row to a set, deleting a row from a set, and checking that a given row belongs to a set.

Time limit: 0.2 c;

Memory limit: 15 Mb.

Example:  

| In | Out |
| ---  | ----- |
|+ hello <br> + bye <br> ? bye <br> + bye <br> - bye <br> ? bye <br> ? hello|OK <br> OK <br> OK <br> FAIL <br> OK <br> FAIL <br> OK|

Solution: [task A](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_1/Modul_4/TaskA/main.cpp).

***

### Task B. Negotiation application
There is only one meeting room in a large IT firm. Those wishing to consult should fill out applications with the desired start and end times. Your task is to determine the maximum number of applications that can be satisfied. The number of applications ≤ 10<sup>6</sup>.

Time limit: 0.1 c;

Memory limit: 5 Mb.

Example:  

| In | Out |
| ---  | ----- |
|1 2 <br> 2 5 <br> 7 10 <br> 2 3 <br> 6 7<br> 4 7 <br> 3 6 <br> 3 5 <br> 1 2 <br> 4 5|5|

Solution: [task B](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_1/Modul_4/TaskB/main.cpp).

***
### Task C. Wide piramid
Given *N* cubes. It is required to determine how many ways you can build a pyramid from these cubes.

Time limit: 0.1 c;

Memory limit: 5 Mb.

Example:  

| In | Out |
| ---  | ----- |
|3|2|

Solution: [task C](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_1/Modul_4/TaskC/main.cpp).

***
### Task D. The sum of the lengths to the rest
Given an unweighted tree. The distance between two vertices will be the number of edges in the path connecting these two vertices. For each vertex, determine the sum of the distances to all other vertices.

Time limit: 0.1 c;

Memory limit: 5 Mb.

Example:  

| In | Out |
| ---  | ----- |
|3 <br> 0 1 <br> 1 2|3 <br> 2 <br> 3|

Solution: [task D](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_1/Modul_4/TaskD/main.cpp).

***
# DIHT - 2018/2019 - second term - tasks - rudykh
## First modul
### Task A. Graph interface
Realisation of graph:
* ListGraph;
* MatrixGraph
* SetGraph
* ArcGraph

Solution: [task A](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_1/TaskA).

***
### Task B. Number of different paths
An unweighted undirected graph is given. A graph can have several shortest paths between some vertices. Find the number of different shortest paths between given vertices. The required complexity is *O(V + E)*.

Time limit: 0.1 c;

Memory limit: 5 Mb.

Example:  

| In | Out |
| ---  | ----- |
|4 <br> 5 <br> 0 1 <br> 0 2 <br> 1 2 <br> 1 3 <br> 2 3 <br> 0 3|2|

Solution: [task B](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_1/TaskB/main.cpp).
***
### Task C. Minimum length cycle
An unweighted undirected graph is given. Find a cycle of minimum length.

Time limit: 1 c;

Memory limit: 100 Mb.

Example:  

| In | Out |
| ---  | ----- |
|6 6 <br> 0 1 <br> 0 2 <br> 2 3 <br> 2 4 <br> 3 5 <br> 4 5|4|

Solution: [task C](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_1/TaskC/main.cpp).
***
### Task D. Bipartite graph
An unweighted undirected graph is given. Determine if it is a bipartite graph. The required complexity is *O(V + E)*.

Time limit: 1 c;

Memory limit: 64 Mb.

Example:  

| In | Out |
| ---  | ----- |
|3 <br> 3 <br> 0 1 <br> 1 2 <br> 0 2|YES|

Solution: [task D](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_1/TaskD/main.cpp).
***
### Task E. Strongly connected graph
Oriented graph is given. Determine the minimum number of edges to add to make the graph strongly connected. Loops are possible in the graph.

Time limit: 1 c;

Memory limit: 64 Mb.

Example:  

| In | Out |
| ---  | ----- |
|4 <br> 4 <br> 1 2 <br> 2 3 <br> 3 1 <br> 3 4|1|

Solution: [task E](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_1/TaskE/main.cpp).
***
## Second modul
### Task A. Cities
It is required to find the shortest route between cities. A city may exit the road, which returns to the same city.

Time limit: 1 c;

Memory limit: 20 Mb.

Example:  

| In | Out |
| ---  | ----- |
|6 <br> 9 <br> 0 3 1 <br> 0 4 2 <br> 1 2 7 <br> 1 3 2 <br> 1 4 3 <br> 1 5 3 <br> 2 5 3 <br> 3 4 4 <br> 3 5 6 <br> 0 2|9|

Solution: [task A](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_2/TaskA/main.cpp).
***
### Task B. Trade Arbitrage
You must write a trading adviser to seek arbitration.
Arbitrage is trading in a chain of different currencies in the hope of making money on small differences in ratios.
Print YES, if there is arbitration, and NO, otherwise.

Time limit: 1 c;

Memory limit: 64 Mb.

Solution: [task B](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_2/TaskB/main.cpp).
***
### Task C. Octopuses

Solution: [task C](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_2/TaskC/main.cpp).
***
### Task D. Barley-break
Find a solution of fifteen game.

Time limit: 6 c;

Memory limit: 1 Gb.

Example:  

| In | Out |
| ---  | ----- |
|1 2 3 0 5 6 7 4 9 10 11 8 13 14 15 12 |3 <br> D D D|

Solution: [task D](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_2/TaskD/main.cpp).
***
### Task E. Floid
A complete oriented weighted graph is given by an adjacency matrix. Build a matrix of shortest paths between its vertices. It is guaranteed that there are no negative weight cycles in the graph.

Solution: [task E](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_2/TaskE/main.cpp).
***
## Third modul
### Task A. Minimum spanning tree
Algorithm Prima.

Solution: [task A](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_3/TaskA/main.cpp).
***
### Task B. Max flow
A directed graph is given, each edge of which has an integer throughput. Find the maximum flow from vertex number 1 to vertex number n.

Solution: [task B](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_3/TaskB/main.cpp).
***
### Task C. Tea
In one of the departments of a large organization, n people work. Like almost all employees of this organization, they like to drink tea in between work. Moreover, they are quite disciplined and take exactly one break a day, during which they drink tea. In order to make this break as pleasant as possible, each of the employees in this department must drink tea of one of his favorite varieties. On different days, the employee can drink tea of ​​different varieties. For convenience, we number the tea varieties with numbers from 1 to m. Recently, department employees bought a large set of tea bags, which contains a1 tea bags of tea grade number 1, a2 tea bags of tea grade number 2, ..., am tea bags of tea grade number m. Now they want to know for what maximum number of days a purchased set can last for them so that each day each employee gets a bag of tea of one of his favorite varieties. Each employee of the department drinks exactly one cup of tea per day, which is brewed from one bag. At the same time, tea bags are not brewed again. Find max number of days.

Solution: [task C](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_3/TaskC/main.cpp).
***
## Fourth Modul
### Task A. RMQ
Given a number *N* and a sequence of *N* integers. Find the second order statistic on given ranges.
To solve the problem, use the Sparse Table data structure.

Solution: [task A](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_4/TaskA/main.cpp).
***
### Task B. Unit sequence
An array of zeros and ones a0, a1, ..., an-1 is given. For each query [left, right], find a subsegment al, al + 1, ..., ar of this array (0 <= left <= l <= r <= right <n) such that the numbers al, al + 1, ..., ar are the maximum possible sequence of units. The required response time to the request is *O(log n)*.

Solution: [task B](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_4/TaskB/main.cpp).
***
### Task C. LCA
Find LCA for a given tree.

Solution: [task C](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_4/TaskC/main.cpp).
***
### Task D. Super array of strings
Implement an “array of strings” data structure based on a treap by an implicit key with the following methods:
*    // Add a line to position. \\
*    // All subsequent lines are moved one position forward. \\
*    void InsertAt (int position, const std :: string & value); \\
*    // Delete the line from position. \\
*    // All subsequent lines are shifted back one position. \\
*    void DeleteAt (int position); \\
*    // Get the line from position. \\
*    std :: string GetAt (int position);

All methods should work for *O(log n)* on average, where *n* is the current number of lines in the array.

Solution: [task D](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_2/Modul_4/TaskD/main.cpp).
***
# DIHT - 2019/2020 - third term - tasks - rudykh
## First modul. [contest](https://contest.yandex.ru/contest/13875/enter/)
### Task A. Substring search
Find all occurrences of the pattern in a string. The length of the pattern is *p*, the length of the string is *n*. Time *O(n + p)*, memory is *O(p)*.

Use one of the methods:
* Using the prefix function;
* Using the z-function.

Example:  

| In | Out |
| ---  | ----- |
|aba <br> abacababa| 0 4 6|

Solution: [task А](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_3/Modul_1/TaskA/main.cpp).

***
### Task B1. String recovery by prefix function

Find the lexicographically minimal string constructed by the prefix function in the alphabet a-z.

Example:

| In | Out |
| ---- | ----- |
|0 1 2 3 0 | aaaab |

Solution: [task B1](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_3/Modul_1/TaskB1/main.cpp).

---
### Task B2. Строка по Z-функции (3 балла)

Find the lexicographically minimal string constructed by the z-function in the alphabet a-z.

Example:

| In | Out |
| ---- | ----- |
|5 3 2 1 0 | aaaab|

Solution: [task B2](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_3/Modul_1/TaskB2/main.cpp).

---
### Task C. Aho-Corasic
The search pattern is given by a string of length m, in which, in addition to ordinary characters, “?” Characters can occur. Find the positions of all occurrences of the template in text of length n. Each occurrence of the template assumes that all ordinary characters coincide with the corresponding ones from the text, and instead of the “?” Symbol, an arbitrary character occurs in the text.

Example:

| In | Out |
| ---- | ----- |
|ab??aba <br> ababacaba| 2|

Solution: [task C](https://github.com/rudykh/Cpp-tasks/blob/master/Sem_3/Modul_1/TaskC/main.cpp).

---
