# [Diamond V] Simple Polygon - 6620 

[문제 링크](https://www.acmicpc.net/problem/6620) 

### 성능 요약

메모리: 12248 KB, 시간: 1080 ms

### 분류

자료 구조, 기하학, 선분 교차 판정, 스위핑, 트리를 사용한 집합과 맵

### 제출 일자

2024년 10월 18일 20:50:51

### 문제 설명

<p>A polygon P determined by points p<sub>1</sub>, p<sub>2</sub>, . . . , p<sub>n</sub> is a closed chain of line segments (called edges) p<sub>1</sub>p<sub>2</sub>, p<sub>2</sub>p<sub>3</sub>, . . . , p<sub>n</sub>p<sub>1</sub> in the plane. Polygon P is simple, if no two edges have any points in common, with the obvious exception of two consecutive segments having one common point (called vertex). Note however, that if a vertex is part of any other (third) edge, the polygon is no longer simple.</p>

<p>Any polygon that is not simple is called self-intersecting. In two example figures below, the first polygon is simple, the second one is self-intersecting.</p>

<p style="text-align: center;"><img alt="" src="https://www.acmicpc.net/upload/images2/simplepoly.png" style="height:220px; width:571px"></p>

<p>Your task is to determine whether a given polygon is simple or self-intersecting.</p>

### 입력 

 <p>The input contains several test cases. Each test case corresponds to one polygon. First line of the test case contains N, the number of points (1 ≤ N ≤ 40 000). Each of the following N lines contains coordinates of point P<sub>i</sub>, that is X<sub>i</sub>, Y<sub>i</sub> separated by space, 1 ≤ X<sub>i</sub>,Y<sub>i</sub> ≤ 30 000.</p>

<p>The last test case is followed by a line containing zero.</p>

### 출력 

 <p>For each test case output either “YES” (the polygon is simple) or “NO” (the polygon is self-intersecting).</p>

