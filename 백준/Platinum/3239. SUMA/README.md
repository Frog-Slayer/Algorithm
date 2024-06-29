# [Platinum II] SUMA - 3239 

[문제 링크](https://www.acmicpc.net/problem/3239) 

### 성능 요약

메모리: 3404 KB, 시간: 12 ms

### 분류

기하학, 수학, 정렬, 두 포인터

### 제출 일자

2024년 6월 30일 00:50:24

### 문제 설명

<p>We can represent a 2D vector as a pair (X,Y).</p>

<p>The sum of two or more vectors is a vector whose coordinates are the sums of the corresponding coordinates of all the vectors in the sum.</p>

<p>e.g. (1,2)+(3,4)+(5,6) = (1+3+5,2+4+6) = (9,12)</p>

<p>Weight of a vector (x,y) is defined as x*x+y*y.</p>

<p>You are given N vectors on a plain.</p>

<p>Your task is to write a program that will determine a subset of those vectors so the weight of the sum of all vectors in that subset is maximal.</p>

<p>Note: Use 64-bit integers (int64 in pascal or long long in c) </p>

### 입력 

 <p>In the first line of the input file is an integer N, 1 ≤ N ≤ 30,000, the number of vectors.</p>

<p>The following N lines contain descriptions for each of the vectors.</p>

<p>A description is made of two integers X and Y, separated by a single blank, -30,000 ≤ X,Y ≤ 30,000.</p>

<p>None of the given vectors will be (0,0). </p>

### 출력 

 <p>In the first and only line of the output file you have to write the weight of the maximum sum.</p>

