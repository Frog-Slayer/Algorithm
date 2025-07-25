# [Platinum III] 달리기 - 12963 

[문제 링크](https://www.acmicpc.net/problem/12963) 

### 성능 요약

메모리: 2160 KB, 시간: 0 ms

### 분류

그래프 이론, 자료 구조, 그리디 알고리즘, 분리 집합

### 제출 일자

2025년 7월 24일 16:06:45

### 문제 설명

<p>민혁이는 달리기 대회를 개최하려고 한다. 이 대회는 N개의 교차로로 이루어져있는 도시에서 열리며, 교차로의 번호는 0부터 N-1까지이다.</p>

<p>도시에는 도로가 M개가 있으며, 도로에도 0번부터 M-1번까지 번호가 매겨져 있다. 도로는 양방향이며, 두 교차로를 연결한다. 같은 교차로를 연결하는 도로는 없으며, 두 교차로를 직접 연결하는 도로는 최대 1개이다. 도로 네트워크는 모두 연결되어있지 않을 수도 있다. 즉, 임의의 두 교차로 사이에 경로가 없을 수도 있다.</p>

<p>달리기 대회의 규칙은 매우 간단하다. 참가자는 0번 교차로에서 출발해서 N-1번 교차로에 도착하면 된다. 이때, i번 도로는 3<sup>i</sup>명만 지나갈 수 있다. 예를 들어, 2번 도로의 경우에는 9명만 지나갈 수 있다. 10번째로 2번 도로를 지나가려고 하는 사람은 해당 도로를 이용할 수 없다.</p>

<p>도로의 정보가 주어졌을 때, 0번 교차로에서 출발해서 N-1번 교차로에 도착할 수 있는 사람의 최대 수를 구하는 프로그램을 작성하시오.</p>

### 입력 

 <p>첫째 줄에 도시의 수 N과 도로의 수 M이 주어진다. (2 ≤ N ≤ 2000, 0 ≤ M ≤ 2000)</p>

<p>둘째 줄부터 M개의 줄에는 도로의 정보 a, b가 0번 도로부터 순서대로 주어진다. (0 ≤ a, b < N, a ≠ b) 같은 도로가 여러 번 주어지는 경우는 없다.</p>

### 출력 

 <p>0번 교차로에서 출발해서 N-1번 교차로에 도착할 수 있는 사람의 최대 수를 1,000,000,007로 나눈 나머지를 출력한다.</p>

