# [Diamond V] Escape - 3364 

[문제 링크](https://www.acmicpc.net/problem/3364) 

### 성능 요약

메모리: 7048 KB, 시간: 4 ms

### 분류

쌍대 그래프, 최대 유량, 그래프 이론, 최대 유량 최소 컷 정리, 평면 그래프

### 제출 일자

2024년 12월 18일 07:36:17

### 문제 설명

<p>A group of war prisoners are trying to escape from a prison. They have thoroughly planned the escape from the prison itself, and after that they hope to find shelter in a nearby village. However, the village (marked as B, see picture below) and the prison (marked as A) are separated by a canyon which is also guarded by soldiers. These soldiers sit in their pickets and rarely walk; the range of view of each soldier is limited to exactly 100 meters. Thus, depending on the locations of soldiers, it may be possible to pass the canyon safely, keeping the distance to the closest soldier strictly larger than 100 meters at any moment.</p>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/140de59c-1747-425c-9540-70376a2f428c/-/preview/" style="width: 364px; height: 301px;"></p>

<p>You are to write a program which, given the width and the length of the canyon and the coordinates of every soldier in the canyon, and assuming that soldiers do not change their locations, first determines whether prisoners can pass the canyon unnoticed. If this is impossible then the prisoners (having seen enough violence) would like to know the minimum number of soldiers that have to be eliminated in order to pass the canyon safely. A soldier may be eliminated regardless of whether he is visible to any other soldier or not.</p>

### 입력 

 <p>The first line contains three integers L, W, and N – the length and the width of the canyon, and the number of soldiers, respectively. Each of the following N lines contains a pair of integers X<sub>i</sub> and Y<sub>i</sub> – the coordinates of i-th soldier in the canyon (0 ≤ X<sub>i</sub> ≤ L, 0 ≤ Y<sub>i</sub> ≤ W). The coordinates are given in meters, relative to the canyon: the southwestern corner of the canyon has coordinates (0, 0), and the northeastern corner of the canyon has coordinates (L, W), as seen in the picture above.</p>

<p>Note that passing the canyon may start at coordinate (0, y<sub>s</sub>) for any 0 ≤ y<sub>s</sub> ≤ W and end at coordinate (L, y<sub>e</sub>) for any 0 ≤ y<sub>e</sub> ≤ W. Neither y<sub>s</sub> nor y<sub>e</sub> need to be integer.</p>

### 출력 

 <p>In the first and only line of the output file the program should print the minimum number of soldiers that have to be eliminated in order for the prisoners to pass the canyon safely. If the prisoners can escape without any elimination, the program should print 0 (zero).</p>

