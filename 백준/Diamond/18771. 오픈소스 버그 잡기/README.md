# [Diamond V] 오픈소스 버그 잡기 - 18771 

[문제 링크](https://www.acmicpc.net/problem/18771) 

### 성능 요약

메모리: 80900 KB, 시간: 336 ms

### 분류

최대 유량, 최대 유량 최소 컷 정리

### 제출 일자

2024년 12월 19일 19:05:26

### 문제 설명

<p>당신은 취미로 오픈 소스 SDK인 "Le Great SDK" (LG SDK)의 버그를 종종 고치곤 한다. 최근 발견된 다양한 버그들과 그들의 연관성 때문에 재미있는 문제를 풀게 되었다.</p>

<p>현재 총 n개의 버그가 신고된 상태이고, 각 버그 리포트를 읽어본 후 각 버그를 고치는 것이 얼마나 재미있을지 수치화 했다. 버그는 1번부터 n번까지 번호가 매겨져 있다.</p>

<p>구체적으로 i번 버그를 고친다면 당신은 f<sub>i</sub> 만큼의 재미를 얻게 되는데, 이 값은 양의 정수 혹은 음의 정수이다. 이 값이 음의 정수인 경우는 너무 지루한 버그라서 버그를 고치는 과정을 즐기지 못하는 의미이다.</p>

<p>흥미도가 양수인 버그만 고칠 수 있다면 좋겠지만, 버그 리포트를 읽어본 결과 어떤 버그는 해당 버그를 고치기 위해 다른 버그까지 고쳐야 하는 관계가 있음을 알게 되었다. 즉, 버그 i를 고치기 위해서는 원치 않더라도 다른 버그 j를 고쳐야만 버그 i를 온전히 고쳤다고 할 수 있는 경우가 있다. </p>

<p>예를 들어, 현재까지 신고된 버그가 총 n = 3개이고 흥미도는 f<sub>1</sub> = 5, f<sub>2</sub> = -2, f<sub>3</sub> = 3 이라고 하자. 버그 1을 고치기 위해서는 버그 2도 함께 고쳐야 하고, 버그 2를 고치기 위해서 다른 버그를 고칠 필요는 없다. 마지막으로 버그 3을 고치기 위해서는 버그 1,2를 모두 고쳐야 한다.</p>

<p>이 경우, 버그 2만 고친다면 총 흥미도는 -2가 될 것이고, 버그 1, 2를 고친다면 흥미도가 3이 되어 양수가 된다. 버그 셋을 모두 고친다면 총 흥미도가 6이 된다.</p>

<p>버그의 수와 각 버그의 흥미도, 그리고 버그 간의 관계가 주어졌을 때, 흥미도가 최대화 되도록 하는 버그만 고치고 싶다. 이 경우 달성할 수 있는 흥미도의 최댓값을 구해보자.</p>

### 입력 

 <p>첫 줄에 테스트 케이스의 수 T가 주어진다.</p>

<p>각 테스트 케이스의 첫째 줄에 버그의 수 n이 주어진다. 둘째 줄에는 n개의 정수가 공백으로 구분되어 주어지는데 이는 각 버그의 흥미도 f<sub>i</sub>를 의미한다.</p>

<p>다음 n줄에 걸쳐서 각 줄에 하나 이상의 정수가 주어진다. i번째 줄에 주어진 첫 정수는 i번째 버그를 고치기 위해 몇 개의 다른 버그를 고쳐야 하는지 나타낸다. 만약 그 수가 x<sub>i</sub> 라면 같은 줄에 공백으로 구분된 x<sub>i</sub>개의 정수가 더 주어지며 이들이 버그 i를 고치기 위해 함께 고쳐야 다른 버그들을 나타낸다. 이때 주어지는 x<sub>i</sub>개의 버그는 중복으로 주어지지 않는다.</p>

### 출력 

 <p>각 테스트 케이스 마다 흥미도의 최댓값을 한 줄에 하나씩 출력한다.</p>

