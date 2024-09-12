# [Diamond IV] Meteor Shower - 13329 

[문제 링크](https://www.acmicpc.net/problem/13329) 

### 성능 요약

메모리: 18432 KB, 시간: 436 ms

### 분류

볼록 껍질, 자료 구조, 기하학, 스위핑, 트리를 사용한 집합과 맵

### 제출 일자

2024년 9월 13일 04:39:44

### 문제 설명

<p>NSC(Naro Space Center) has just discovered that n large meteorites are falling to Korea. NSC is plannning to blow up the meteorites using laserguided missile system. In order not to miss a single meteorite, NSC needs to identify the meteorites which are completely blocked by others at a specific moment. We call them invisible meteorites.</p>

<p>Each meteorite is represented by a convex polygon. All meteorites are seperated from each other, i.e., any two convex polygons do not intersect each other. The figure below shows an example of a situation with 5 meteorites and a laser-guided missile launcher. In the figure, a meteorite labeled with is invisible because any point on it can’t be touched by a laser beam from the launcher. </p>

<p style="text-align: center;"><img alt="" src="https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/13329/1.png" style="height:227px; width:312px"></p>

<p>Given a list of convex polygons representing meteorites at some moment, write a program to find the number of the meteorites which are invisible from the laser-guided missile launcher.</p>

### 입력 

 <p>Your program is to read from standard input. The input starts with a line containing an integer n(1 ≤ n ≤ 100,000), where n is the number of convex polygons representing meteorites at a specific moment. In the following n lines, each line contains 2m+1 integers m, x<sub>1</sub>, y<sub>1</sub>, x<sub>2</sub>, y<sub>2</sub>, ..., x<sub>m</sub>, and y<sub>m</sub> (3 ≤ m ≤ 10<sup>5</sup>, -10<sup>8</sup> ≤ x<sub>i</sub> ≤ 10<sup>8</sup>, 1 ≤ y<sub>i</sub> ≤ 10<sup>8</sup>), where m is the number of vertices of a convex polygon Q and (x<sub>i</sub>, y<sub>i</sub>)'s are coordinates of m vertices of Q in the counter-clockwise order. The laser-guided missile launcher is located at (0, 0), i.e., the origin of the coordinate system. The total number of vertices of all convex polygons is less than or equal to 10<sup>6</sup>, Notice that any two convex polygons do not intersect each other. Also, you may assume that the line connecting any two vertices of all convex polygons does not pass through the origin, i.e., the location of the laser-guided missile launcher.</p>

### 출력 

 <p>Your program is to write to standard output. Print exactly one line which contains an integer representing the number of the meteorites which are invisible from the laser-guided missile launcher.</p>

