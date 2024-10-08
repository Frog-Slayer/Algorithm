# [Diamond V] 점수의 합 - 12964 

[문제 링크](https://www.acmicpc.net/problem/12964) 

### 성능 요약

메모리: 2032 KB, 시간: 4 ms

### 분류

최대 유량, 최대 유량 최소 컷 정리, 트리

### 제출 일자

2024년 9월 10일 20:19:51

### 문제 설명

<p>N개의 정점으로 이루어진 트리 A와 B가 주어진다. 두 트리의 정점은 0번부터 N-1번까지 번호가 매겨져 있다.</p>

<p>0부터 N-1까지 각 정수에는 점수가 배정되어져 있다. 점수는 정수이며, i의 점수는 s[i]로 나타낸다.</p>

<p>아래와 같은 조건을 갖는 {0, 1, ..., N-1}의 부분 집합 S를 선택하는 프로그램을 작성하시오.</p>

<ul>
	<li>트리 A에서 S에 포함되어 있는 노드는 연결된 서브 그래프를 이루어야 한다.</li>
	<li>트리 B에서 S에 포함되어 있는 노드는 연결된 서브 그래프를 이루어야 한다.</li>
</ul>

<p>가능한 부분 집합 S중에서, 점수의 합이 최대가 되는 것을 구하는 프로그램을 작성하시오.</p>

### 입력 

 <p>첫째 줄에 N이 주어진다. (2 ≤ N ≤ 50)</p>

<p>둘째 줄부터 N-1개의 줄에는 트리 A를 이루는 간선 a, b가 주어진다.</p>

<p>다음 N-1개의 줄에는 트리 B를 이루는 간선 c, d가 주어진다.</p>

<p>마지막 줄에는 정수의 점수가 0부터 N-1까지 주어진다. (-1,000 ≤ 점수 ≤ 1,000)</p>

### 출력 

 <p>첫째 줄에 점수의 최댓값을 출력한다.</p>

