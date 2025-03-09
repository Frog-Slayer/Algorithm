# [Diamond IV] Cordon Bleu - 15416 

[문제 링크](https://www.acmicpc.net/problem/15416) 

### 성능 요약

메모리: 10016 KB, 시간: 2384 ms

### 분류

최대 유량, 헝가리안, 최소 비용 최대 유량

### 제출 일자

2025년 3월 9일 19:11:02

### 문제 설명

<p style="text-align:center"><img alt="" src="https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15416/1.png" style="height:184px; width:160px"></p>

<p>A Parisian entrepreneur has just opened a new restaurant “Au bon cordon bleu”, named after a famous French recipe. However, no one has any idea of which wine would be appropriate with such a dish. The entrepreneur plans to sample many different wines in order to build the wine menu.</p>

<p>The various bottles of wine he plans to taste can be obtained from different wine merchants located in or around Paris. Being a very sensitive product, high-quality wine can only be transported by highly trained couriers on motorbikes. Therefore, those couriers are very expensive.</p>

<p>A courier can be used for the transportation of several wine bottles, but can transport only one bottle at a time. All couriers get paid at the same fixed rate: one euro per kilometer. The distance function used is the Manhattan distance (also known as taxicab metric) of every individual segment of the trip: the distance from a point (x1, y1) to a point (x2, y2) is |x1 − x2| + |y1 − y2|.</p>

<p>A courier in charge of transporting a single wine bottle will get paid as many euros as the sum of the following two (Manhattan) distances: from her base to the wine merchant place, and from the wine merchant place to the restaurant.</p>

<p>Consider a more complex example: a courier in charge of transporting two wine bottles, one after the other. The amount paid will be the sum of the following distances: from his base to the location of the first bottle, then to the restaurant, then to the location of the second bottle, then to the restaurant.</p>

<p>Help the entrepreneur minimize the costs of hiring the couriers. Given a set of Cartesian coordinates corresponding to available couriers, a set of Cartesian coordinates corresponding to the locations of the precious wine bottles they need to collect, and the location of the restaurant, compute the smallest number of kilometers that the couriers will be paid for. There is no obligation to use all available couriers, and bottles can be collected in an arbitrary order.</p>

### 입력 

 <p>The input comprises several lines, each consisting of integers separated with single spaces:</p>

<ul>
	<li>The first line consists of the number N of wine bottles to collect and the number M of available couriers.</li>
	<li>The N following lines consist of the coordinates of each bottle as two integers x and y.</li>
	<li>The M following lines consist of the coordinates of each courier’s base as two integers x and y.</li>
	<li>The last line contains the coordinates of the restaurant as two integers x and y.</li>
</ul>

<p>Limits</p>

<ul>
	<li>1 ≤ N ≤ 1 000;</li>
	<li>1 ≤ M ≤ 1 000;</li>
	<li>all coordinates (x, y) verify −1 000 ≤ x ≤ 1 000 and −1 000 ≤ y ≤ 1 000.</li>
</ul>

### 출력 

 <p>A single integer: the smallest number of euros that needs to be paid to collect all bottles.</p>

