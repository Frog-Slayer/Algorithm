# [Platinum IV] 유니콘 - 1048 

[문제 링크](https://www.acmicpc.net/problem/1048) 

### 성능 요약

메모리: 19688 KB, 시간: 244 ms

### 분류

다이나믹 프로그래밍, 누적 합

### 제출 일자

2024년 7월 21일 23:17:03

### 문제 설명

<p>유니콘은 체스에서 나이트와 비슷한 말이다. 단, 나이트는 두 칸을 한 방향으로 움직이고, 또 다른 한 칸을 다른 방향으로  움직이지만, 유니콘은 두 칸보다 많은 칸을 한 방향으로 움직이고, 한 칸보다 많은 칸을 또다른 방향으로 움직인다.</p>

<p>좀 더 정확하게 유니콘이 움직이는 방법을 살펴보면 다음과 같다.</p>

<ol>
	<li>유니콘을 든다.</li>
	<li>유니콘을 $4$개의 기본 방향 중 하나로 두 칸보다 많이 움직인다.</li>
	<li>유니콘을 방금 움직인 방향과 수직인 방향 $2$개 중 하나로 한 칸보다 많이 움직인다.</li>
	<li>유니콘을 놓는다.</li>
</ol>

<p>체스판의 크기는 $N \times M$이다. 체스판의 각 칸에는 알파벳 대문자의 처음 $L$개의 문자 중 하나가 쓰여 있다.</p>

<p>$N$, $M$, $L$, 그리고 단어가 주어진다. 유니콘이 움직인 경로 (유니콘을 놓은 곳)가 입력으로 주어진 단어와 일치하는 경우의 수를 출력하는 프로그램을 작성하시오.</p>

### 입력 

 <p>첫째 줄에 $N$, $M$, $L$이 주어진다. $N$과 $M$은 $300$보다 작거나 같은 자연수이다. $L$은 $26$보다 작거나 같은 자연수이다. 둘째 줄에 단어가 주어진다. 단어의 길이는 최대 $50$이며, 알파벳 대문자로만 이루어져 있다. 셋째 줄 부터 $N$개의 줄에 체스판에 쓰여 있는 단어가 주어진다.</p>

### 출력 

 <p>첫째 줄에 경로를 $1\,000\,000\,007$로 나눈 나머지를 출력한다.</p>

