# [Platinum II] Dead-End Detector - 17154 

[문제 링크](https://www.acmicpc.net/problem/17154) 

### 성능 요약

메모리: 79768 KB, 시간: 848 ms

### 분류

너비 우선 탐색, 깊이 우선 탐색, 그래프 이론, 그래프 탐색

### 제출 일자

2024년 6월 8일 14:32:01

### 문제 설명

<p>The council of your home town has decided to improve road sign placement, especially for dead ends. They have given you a road map, and you must determine where to put up signs to mark the dead ends. They want you to use as few signs as possible.</p>

<p>The road map is a collection of locations connected by two-way streets. The following rule describes how to obtain a complete placement of dead-end signs. Consider a street S connecting a location x with another location. The x-entrance of S gets a dead-end sign if, after entering S from x, it is not possible to come back to x without making a U-turn. A U-turn is a 180- degree turn immediately reversing the direction.</p>

<p>To save costs, you have decided not to install redundant dead-end signs, as specified by the following rule. Consider a street S with a dead-end sign at its x-entrance and another street T with a dead-end sign at its y-entrance. If, after entering S from x, it is possible to go to y and enter T without making a U-turn, the dead-end sign at the y-entrance of T is redundant. See Figure E.1 for examples.</p>

<table class="table table-bordered" style="width: 100%;">
	<tbody>
		<tr>
			<td style="width: 50%; text-align: center;"><img alt="" src="https://upload.acmicpc.net/3a83ae42-86e6-4de9-bf9e-a8ae722c7933/-/preview/" style="width: 194px; height: 152px;"></td>
			<td style="width: 50%; text-align: center;"><img alt="" src="https://upload.acmicpc.net/08c618b5-d4c5-4762-b831-c6c3a0aa0f75/-/preview/" style="width: 188px; height: 170px;"></td>
		</tr>
		<tr>
			<td style="text-align: center;">(a) Sample Input 1</td>
			<td style="text-align: center;">(b) Sample Input 2</td>
		</tr>
	</tbody>
</table>

<p style="text-align: center;">Figure E.1: Illustration of sample inputs, indicating where non-redundant dead-end signs are placed.</p>

### 입력 

 <p>The first line of input contains two integers n and m, where n (1 ≤ n ≤ 5 · 10<sup>5</sup>) is the number of locations and m (0 ≤ m ≤ 5 · 10<sup>5</sup>) is the number of streets. Each of the following m lines contains two integers v and w (1 ≤ v < w ≤ n) indicating that there is a two-way street connecting locations v and w. All location pairs in the input are distinct.</p>

### 출력 

 <p>On the first line, output k, the number of dead-end signs installed. On each of the next k lines, output two integers v and w marking that a dead-end sign should be installed at the v-entrance of a street connecting locations v and w. The lines describing dead-end signs must be sorted in ascending order of v-locations, breaking ties in ascending order of w-locations.</p>

