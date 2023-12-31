# [Platinum III] 트리 인코딩 - 1573 

[문제 링크](https://www.acmicpc.net/problem/1573) 

### 성능 요약

메모리: 2020 KB, 시간: 0 ms

### 분류

다이나믹 프로그래밍, 재귀

### 제출 일자

2023년 11월 23일 23:26:48

### 문제 설명

<p>이진 트리는 비어있거나 루트 노드와 두 개의 이진 트리 (왼쪽 서브트리, 오른쪽 서브트리)로 구성되어 있다. 이 문제에 나오는 이진 트리의 모든 노드는 알파벳 소문자만을 가지고 있다. 만약, 이진 트리가 다음과 같은 조건을 만족한다면, 그리고 그때에만 이진 검색 트리라고 한다.</p>

<ol>
	<li>노드의 왼쪽 서브트리에 있는 모든 문자는 노드에 있는 알파벳보다 사전순으로 앞이다.</li>
	<li>노드의 오른쪽 서브트리에 있는 모든 문자는 노드에 있는 알파벳보다 사전순으로 뒤다.</li>
</ol>

<p>다음은 4개의 노드를 가진 이진 검색 트리이다.</p>

<pre>    c         c      a
   / \       / \      \
  b   d     a   d      c
 /           \        / \
a             b      b   d</pre>

<p>위와 같은 이진 검색 트리를 프리오더로 트리순회 하면, cbad, cabd, acbd와 같은 문자열을 얻을 수 있다.</p>

<p>세준이는 N개의 노드를 가진 모든 이진 검색 트리를 만들었다. (등장하는 알파벳은 a부터 차례대로 N개) 그리고 나서, 모든 트리를 프리오더 순회한 뒤에 사전순으로 정렬했다.</p>

<p>N과 index가 주어질 때, index번째 N개의 노드를 가진 이진 검색 트리의 프리오더 결과를 출력하는 프로그램을 작성하시오.</p>

### 입력 

 <p>첫째 줄에 트리의 크기 N과 index가 주어진다. N은 19보다 작거나 같은 자연수, index는 2,000,000,000보다 작거나 같은 자연수이다. N=19일 때, 이진 검색 트리의 개수는 2,000,000,000보다 작다.</p>

### 출력 

 <p>첫째 줄에 정답을 출력한다. 만약 그런 트리가 없을 때는 -1을 출력한다.</p>

