# [Platinum V] 라이언 동상 구하기 - 17447 

[문제 링크](https://www.acmicpc.net/problem/17447) 

### 성능 요약

메모리: 9816 KB, 시간: 644 ms

### 분류

기하학

### 제출 일자

2024년 8월 26일 18:29:08

### 문제 설명

<p>Bryan에겐 정사각형 모양의 예쁜 땅이 있다. 편의상 이 땅의 왼쪽 아래 꼭짓점은 (0, 0) 위치에 놓여 있고, 각 변은 X축 또는 Y축 중 하나와 평행하다고 하자.</p>

<p>이 땅 안에는 라이언 동상과 브라운 동상을 합쳐 <span style="font-style: italic;">M</span>개의 동상이 존재한다. 이 땅의 테두리에는 울타리가 쳐져 있기 때문에 동상은 놓여 있지 않다. 어느 날, bryan은 kazel이 자신의 땅을 습격하려 한다는 사실을 알게 되었다! kazel은 땅의 꼭짓점 위치에서 습격을 하기 때문에, bryan은 각 변에서 꼭짓점을 제외한 정수 좌표 위치에 기둥을 하나씩 세우고 그 기둥을 이어 새로운 사각형 울타리를 만들어서 kazel의 습격으로부터 보호할 새로운 땅을 만들기로 결심하였다.</p>

<p>Bryan은 각각의 동상에 <span style="font-style: italic;">V</span><sub><span style="font-style: italic;">i</span></sub>의 가치를 매기고, 새로운 땅에 포함되는 동상의 가치를 최대로 하기로 하였다. 새로운 땅의 울타리 위에 있는 동상 또한 새로운 땅에 포함된다.</p>

<p>또한 kazel은 브라운 동상을 노리고 습격을 하기 때문에, 아쉽지만 kazel이 다시 습격할 위험성을 줄이기 위해 브라운 동상은 새로운 땅에 최대한 포함되지 않도록 하려고 한다. 따라서 이 브라운 동상들에는 양수가 아닌 수의 가치가 매겨져 있다. (당연하지만 라이언 동상에는 양수의 가치가 매겨져 있다.)</p>

<p>Bryan은 새 울타리를 칠 재료를 준비하느라 바쁘기 때문에, 새로운 울타리를 어떻게 쳐야 하는지는 당신이 대신해서 계산해 주도록 하자.</p>

### 입력 

 <p>첫째 줄에 bryan이 처음 가진 땅의 한 변의 길이 <span style="font-style: italic;">N</span>과 동상의 개수 <span style="font-style: italic;">M</span>이 주어진다. 두 번째 줄부터 <span style="font-style: italic;">M</span>개 줄에 걸쳐서 각 동상의 위치 <span style="font-style: italic;">X</span><sub><span style="font-style: italic;">i</span></sub>, <span style="font-style: italic;">Y</span><sub><span style="font-style: italic;">i</span></sub>와 가치 <span style="font-style: italic;">V</span><sub><span style="font-style: italic;">i</span></sub>가 주어진다.</p>

<ul>
	<li>2 ≤ <span style="font-style: italic;">N</span> ≤ 500</li>
	<li>1 ≤ <span style="font-style: italic;">M</span> ≤ 500</li>
	<li>0 < <span style="font-style: italic;">X</span><sub><span style="font-style: italic;">i</span></sub>, <span style="font-style: italic;">Y</span><sub><span style="font-style: italic;">i</span></sub> < <span style="font-style: italic;">N</span></li>
	<li>-10<sup>5</sup> ≤ <span style="font-style: italic;">V</span><sub><span style="font-style: italic;">i</span></sub> ≤ 10<sup>5</sup></li>
</ul>

### 출력 

 <p>조건에 맞게 만든 새로운 땅에 포함된 동상들의 가치의 합의 최댓값을 출력한다.</p>

