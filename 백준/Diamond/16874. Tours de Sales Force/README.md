# [Diamond IV] Tours de Sales Force - 16874 

[문제 링크](https://www.acmicpc.net/problem/16874) 

### 성능 요약

메모리: 10372 KB, 시간: 13736 ms

### 분류

비트마스킹, 다이나믹 프로그래밍, 비트필드를 이용한 다이나믹 프로그래밍, 최대 유량, 헝가리안, 최소 비용 최대 유량, 외판원 순회 문제

### 제출 일자

2025년 3월 10일 14:37:56

### 문제 설명

<p>The Weight For It company sells home gym equipment to clients in multiple states. Each salesperson in a state is currently in charge of a specific district made up of 3-8 clients. Each salesperson has mapped out the shortest path with which to visit all of their clients in one day (this is known as their sales tour).</p>

<p>Sales have gotten a little light for Weight For It so they’ve decided to cut their sales force in half, reassigning each of the districts of the fired half of the workforce in one state to one in the un-fired half. In order to be fair, each of the un-fired sales persons are assigned exactly one of these districts. After the assignments the remaining salespeople will have to recalculate their minimum sales tours, and as a further cost cutting measure Weight For It would like to assign the districts so that the overall length of all these new sales tours is as small as possible.</p>

<p>For example, Figure I.1 on the left shows the configuration of four districts in one state. Suppose that the salespeople for districts A and B are fired. Then the best reassignment for those districts would be to assign the six clients from district A to the salesperson for district C and the four clients from district B to the salesperson for district D. The resulting shortest sales tours for each of the new districts C' and D' are shown on the right.</p>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/0b48890a-4d1e-490d-bee3-92cbf8d9e9ae/-/preview/" style="width: 511px; height: 162px;"></p>

<p style="text-align: center;">Figure I.1: (a) Four districts before firings. (b) Two districts after firings. This example corresponds to Sample Input 1.</p>

### 입력 

 <p>Input starts with a positive even integer d (d ≤ 50) indicating the number of districts. Each of the next d lines lists the number and locations of the clients in each of the districts, one district per line starting with district one. Each of these lines starts with an integer n (3 ≤ n ≤ 8) indicating the number of clients in the district, followed by n integer coordinate pairs x y (−10 000 ≤ x, y ≤ 10 000) indicating the locations of the clients. The first d/2 districts listed are those of the fired salespersons. The distance between any two clients is the Euclidean distance and all client locations are distinct.</p>

### 출력 

 <p>Display the sum of all the sales tours prior to the firings followed by the sum of all the sales tours after the firings. Your answers should be correct to within an absolute error of 10<sup>−2</sup>.</p>

