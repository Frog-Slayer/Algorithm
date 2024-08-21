# [Platinum I] 민원이 넘쳐흘러 - 17423 

[문제 링크](https://www.acmicpc.net/problem/17423) 

### 성능 요약

메모리: 21148 KB, 시간: 992 ms

### 분류

이분 탐색, 값 / 좌표 압축, 자료 구조, 느리게 갱신되는 세그먼트 트리, 매개 변수 탐색, 세그먼트 트리, 스위핑

### 제출 일자

2024년 8월 21일 11:30:57

### 문제 설명

<p style="text-align: center;"><em>🎵 DJ욱제는 슈퍼카 위에서 디제잉을 하고 있다. 🎵</em></p>

<p style="text-align: justify;"><em>DJ욱제</em>는 자신의 엄청난 디제잉을 사람들에게 알리기로 했다. 그래서 새벽 3시에 슈퍼카를 타고 아파트 단지를 누비며 최고 볼륨으로 디제잉을 하기 시작했다. 😎</p>

<p style="text-align: justify;">하지만 스피커 하나로는 예술의 경지에 다가갈 수 없었다. 그래서 <em>DJ욱제</em>는 다음과 같이 광역디제잉(<s>광역딜</s>)을 하기로 했다.</p>

<ol>
	<li style="text-align: justify;">아파트 단지는 2차원 격자로 표현되며, 두 점 (<em>x</em><sub>1</sub>, <em>y</em><sub>1</sub>), (<em>x</em><sub>2</sub>, <em>y</em><sub>2</sub>)의 거리는 |<em>x</em><sub>1</sub> - <em>x</em><sub>2</sub>| + |<em>y</em><sub>1</sub> - <em>y</em><sub>2</sub>| 이다.</li>
	<li style="text-align: justify;"><em>DJ욱제</em>는 <em>N</em>개의 스피커를 각 (<em>x<sub>i</sub></em>, <em>y<sub>i</sub></em>)에 설치했다.</li>
	<li style="text-align: justify;">스피커들은 크기가 제각각이다. <em>i</em>번째 스피커의 크기가 <em>S<sub>i</sub></em>이고 볼륨이 <em>V</em>이면, 그 스피커의 음악은 스피커와의 거리가 <em>V</em>×<em>S<sub>i</sub></em> 이내인 모든 점에서 들을 수 있다.</li>
	<li style="text-align: justify;">볼륨은 정수 단위로만 조작 가능하며, 모든 스피커의 볼륨은 같다.</li>
	<li style="text-align: justify;">『 <strong>예술은 볼륨이다.</strong> 』</li>
</ol>

<p style="text-align: justify;"><em>DJ욱제</em>는 볼륨을 높이며 예술의 경지에 다다르고 있다! 하지만 예술을 모르는 어떤 사람들은 한 번에 <strong>두 개 이상의 스피커에서 음악이 들리면</strong> 민원을 넣는다고 한다. (;;) 그래서 <em>DJ욱제</em>는 민원이 들어오지 않는 선에서 볼륨을 최대한으로 키우기로 했다. 소리가 들리는 범위의 경계선이나 경계점이 겹치는 경우는 음악이 겹치지 않는 걸로 치자.</p>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/a4f4b6ae-caf7-411a-8fee-f35155a474d0/-/crop/1883x1090/0,0/-/preview/" style="width: 777px; height: 450px;"></p>

<p style="text-align: justify;"><em>DJ욱제</em>의 예술(볼륨)을 온 몸으로 느껴보자! <em>DJ욱제</em>의 예술(볼륨)은 얼마나 커질 수 있을까?</p>

### 입력 

 <p>첫째 줄에 스피커 개수 <em>N</em>이 주어진다.</p>

<p>둘째 줄에 스피커의 크기 <em>S<sub>1</sub></em>, <em>S<sub><span style="font-size: 10.8333px;">2</span></sub></em>, ..., <em>S<sub>N</sub></em>가 순서대로 주어진다.</p>

<p>셋째 줄부터 <em>N</em>개의 줄에 걸쳐, <em>i+2</em>번째 줄에 <em>i</em>번 스피커의 좌표 <em>x<sub>i</sub></em>, <em>y<sub>i</sub></em>가 주어진다. 중복되는 좌표는 없다.</p>

<p>주어지는 모든 입력은 1 이상의 정수이다.</p>

### 출력 

 <p><em>DJ욱제</em>가 다다를 수 있는 예술(볼륨)의 최대 크기를 출력한다.</p>

