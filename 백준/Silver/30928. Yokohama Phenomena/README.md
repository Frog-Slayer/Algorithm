# [Silver I] Yokohama Phenomena - 30928 

[문제 링크](https://www.acmicpc.net/problem/30928) 

### 성능 요약

메모리: 2024 KB, 시간: 0 ms

### 분류

다이나믹 프로그래밍, 그래프 이론, 그래프 탐색, 깊이 우선 탐색

### 제출 일자

2026년 1월 25일 20:23:25

### 문제 설명

<p>Do you know about Yokohama Phenomena? The phenomenon takes place when three programmers, sitting around a table, hold a single pen together above a board. A grid of squares is drawn on the board, with each square marked with a single letter. Although none of the participants purposely moves the pen, its nib, as if it has a will, goes down to one of the squares marked with <code>Y</code>, and then starts moving on the board. The squares passed are marked with <code>O</code>, <code>K</code>, <code>O</code>, <code>H</code>, <code>A</code>, and <code>M</code> in this order, and then the nib stops on the square marked with <code>A</code>.</p>

<p>Let us call the series of squares along such a trajectory of the nib a <em>YOKOHAMA trace</em>. A YOKOHAMA trace is defined as follows.</p>

<ul>
	<li>It is a series of eight squares in the given grid of squares.</li>
	<li>Every square in the series, except for the first one, shares an edge with (is edge-adjacent to) its directly preceding square in the series.</li>
	<li>The letters marked in the eight squares of the series are <code>Y</code>, <code>O</code>, <code>K</code>, <code>O</code>, <code>H</code>, <code>A</code>, <code>M</code>, and <code>A</code>, in this order.</li>
</ul>

<p>Note that the same square may appear more than once in the series.</p>

<p>Figure A.1 (a) is an illustration of the board corresponding to Sample Input 1. Figures A.1 (b) and (c) show trajectories on two of the YOKOHAMA traces. Both traces start at the leftmost square in the upper row. The same square marked with <code>O</code> appears twice in the trace illustrated in Figure A.1 (c).</p>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/e078cca6-7b8d-45a9-ab61-229c241d6d5a/-/preview/" style="width: 523px; height: 150px;"></p>

<p style="text-align: center;">Figure A.1. A board and trajectories on two of the YOKOHAMA traces</p>

<p>You are given a grid of squares, each marked with one of six letters, <code>A</code>, <code>H</code>, <code>K</code>, <code>M</code>, <code>O</code>, or <code>Y</code>. Your task is to count how many distinct YOKOHAMA traces are possible on it.</p>

### 입력 

 <p>The input consists of a single test case of the following format.</p>

<blockquote>
<p>$n$ $m$</p>

<p>$x_{1,1}$ $\cdots$ $x_{1,m}$</p>

<p>$\vdots$</p>

<p>$x_{n,1}$ $\cdots$ $x_{n,m}$</p>
</blockquote>

<p>The first two integers $n$ and $m$ ($1 ≤ n ≤ 10$, $1 ≤ m ≤ 10$) describe the size of the grid. The grid has squares arranged in an $n \times m$ matrix. The following $n$ lines describe the letters marked in the squares. The square at the $i$-th row and the $j$-th column in the grid ($1 ≤ i ≤ n$, $1 ≤ j ≤ m$) has letter $x_{i,j}$ marked in it. Each $x_{i,j}$ is one of the six letters, <code>A</code>, <code>H</code>, <code>K</code>, <code>M</code>, <code>O</code>, or <code>Y</code>.</p>

### 출력 

 <p>Output a line containing the number of distinct YOKOHAMA traces.</p>

