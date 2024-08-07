# [Platinum I] 전함 - 5480 

[문제 링크](https://www.acmicpc.net/problem/5480) 

### 성능 요약

메모리: 21184 KB, 시간: 1612 ms

### 분류

값 / 좌표 압축, 자료 구조, 오프라인 쿼리, 세그먼트 트리

### 제출 일자

2024년 7월 28일 18:01:37

### 문제 설명

<p>홍준이는 대한민국의 자랑스러운 해군이다. 오늘은 전함을 타고 적과 싸우는 상황을 가정한 실전 연습을 하려고 한다. </p>

<p>전장은 n × n 크기의 그리드로 나타낼 수 있다. 가장 왼쪽 아래 점의 좌표는 (1,1)이고, 가장 오른쪽 위 점의 좌표는 (n,n)이다. 적의 함대는 전함 k개로 이루어져 있다. 각 전함 i는 길이가 0보다 크고 양 끝점이 (x<sub>i</sub>,y<sub>i</sub>), (x'<sub>i</sub>,y'<sub>i</sub>)인 선분으로 나타낼 수 있다. 또, 전함의 무게는 w<sub>i</sub>이다. 홍준이는 전함을 부수기 위해 레이저 대포를 총 l번 발사한다. 대포는 수직이나 수평 방향으로 발사할 수 있다.</p>

<p>대포를 수직으로 발사한다면, 레이저는 (a,1)과 (a,n)을 연결하는 선분으로 나타낼 수 있고, 이 선분과 만나는 전함을 모두 파괴한다. (끝점도 포함) 대포를 수평으로 발사하면, 레이저는 (1,a)와 (n,a)를 연결하는 선분으로 나타낼 수 있고, 이 선분과 만나는 전함도 모두 파괴한다.</p>

<p>홍준이는 매번 레이저 캐논을 발사할 때마다, 파괴한 전함중 가장 무거운 전함을 대통령에게 보고해야 한다.</p>

<p>아래 그림에는 5 × 5 크기의 그리드에 전함이 다섯 개 있다. 각 전함의 무게는 선분 옆에 쓰여 있다. 첫 번째 레이저를 (4,1)과 (4,5)를 연결하는 선분으로 수직 발사하면, 전함 두 개를 파괴할 수 있다. 파괴한 전함의 무게는 4와 5인데, 가장 무거운 전함은 5이므로 5를 보고한다. 그 다음, 레이저를 (1,4)와 (5,4)를 연결하는 선분으로 수평 발사하면, 두 전함을 파괴할 수 있다. 파괴한 전함의 무게는 1과 2이고, 무거운 전함은 2이므로 2를 보고한다. 두 번째 레이저를 발사했을 때, 무게가 4인 전함은 첫 번째 레이저에 의해서 파괴되었기 때문에 파괴되지 않는다.</p>

<p><img alt="" src="https://www.acmicpc.net/upload/images/battlefield.png" style="height:199px; width:234px"></p>

<p>모든 전함의 위치와 홍준이가 발사한 레이저의 정보가 주어진다. 레이저를 발사할 때마다, 파괴한 전함중 가장 무거운 전함의 무게를 구하는 프로그램을 작성하시오.</p>

### 입력 

 <p>첫째 줄에 테스트 케이스의 개수 T가 주어진다. 각 테스트 케이스의 첫째 줄에는 그리드의 크기 n, 전함의 수 k, 대포를 발사한 횟수 l이 주어진다. 1 ≤ n ≤ 1,000,000,000, 1 ≤ k,l ≤ 100,000. 다음 k개 줄에는 다섯 정수 x, y, x', y', w가 주어진다. 이 숫자는 전함의 양 끝점 (x,y), (x',y') (1 ≤ x,y,x',y' ≤ n)와 무게 w를 나타낸다. (1 ≤ w ≤ 1,000,000) 다음 l개 줄에는 두 정수 a와 b가 주어진다. (1 ≤ a ≤ n, b = 0 또는 1) b가 0인 경우에는 대포를 (1,a)와 (n,a)를 연결하는 선분으로 수평 발사한 것이고, 1인 경우에는 (a,1)와 (a,n)을 연결하는 선분으로 수직 발사한 것이다.</p>

### 출력 

 <p>각 테스트 케이스마다 l줄을 출력한다. 매번 레이저를 발사할 때마다, 파괴한 전함 중 가장 무거운 전함의 무게를 출력한다. 만약, 파괴된 전함이 없는 경우에는 0을 출력한다.</p>

