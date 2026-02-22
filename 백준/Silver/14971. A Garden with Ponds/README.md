# [Silver III] A Garden with Ponds - 14971 

[문제 링크](https://www.acmicpc.net/problem/14971) 

### 성능 요약

메모리: 2024 KB, 시간: 16 ms

### 분류

브루트포스 알고리즘, 구현

### 제출 일자

2026년 2월 22일 22:51:58

### 문제 설명

<p>Mr. Gardiner is a modern garden designer who is excellent at utilizing the terrain features. His design method is unique: he first decides the location of ponds and design them with the terrain features intact.</p>

<p>According to his unique design procedure, all of his ponds are rectangular with simple aspect ratios. First, Mr. Gardiner draws a regular grid on the map of the garden site so that the land is divided into cells of unit square, and annotates every cell with its elevation. In his design method, a pond occupies a rectangular area consisting of a number of cells. Each of its outermost cells has to be higher than all of its inner cells. For instance, in the following grid map, in which numbers are elevations of cells, a pond can occupy the shaded area, where the outermost cells are shaded darker and the inner cells are shaded lighter. You can easily see that the elevations of the outermost cells are at least three and those of the inner ones are at most two.</p>

<p style="text-align: center;"><img alt="" src="https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14971/1.png" style="height:148px; width:232px"></p>

<p>A rectangular area on which a pond is built must have at least one inner cell. Therefore, both its width and depth are at least three.</p>

<p>When you pour water at an inner cell of a pond, the water can be kept in the pond until its level reaches that of the lowest outermost cells. If you continue pouring, the water inevitably spills over. Mr. Gardiner considers the larger <em>capacity</em> the pond has, the better it is. Here, the capacity of a pond is the maximum amount of water it can keep. For instance, when a pond is built on the shaded area in the above map, its capacity is (3 − 1) + (3 − 0) + (3 − 2) = 6, where 3 is the lowest elevation of the outermost cells and 1, 0, 2 are the elevations of the inner cells. Your mission is to write a computer program that, given a grid map describing the elevation of each unit square cell, calculates the largest possible capacity of a pond built in the site.</p>

<p>Note that neither of the following rectangular areas can be a pond. In the left one, the cell at the bottom right corner is not higher than the inner cell. In the right one, the central cell is as high as the outermost cells.</p>

<p style="text-align: center;"><img alt="" src="https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14971/2.png" style="height:183px; width:401px"></p>

### 입력 

 <p>The input consists of at most 100 datasets, each in the following format.</p>

<pre><em>d w</em> 
<em>e</em><sub>1, 1</sub> ... <em>e</em><sub>1, <em>w</em></sub> 
... 
<em>e</em><sub><em>d</em>, 1</sub> ... <em>e<sub>d, w</sub></em> 
</pre>

<p>The first line contains <em>d</em> and <em>w</em>, representing the depth and the width, respectively, of the garden site described in the map. They are positive integers between 3 and 10, inclusive. Each of the following <em>d</em> lines contains <em>w</em> integers between 0 and 9, inclusive, separated by a space. The <em>x</em>-th integer in the <em>y</em>-th line of the <em>d</em> lines is the elevation of the unit square cell with coordinates (<em>x, y</em>).</p>

<p>The end of the input is indicated by a line containing two zeros separated by a space.</p>

### 출력 

 <p>For each dataset, output a single line containing the largest possible capacity of a pond that can be built in the garden site described in the dataset. If no ponds can be built, output a single line containing a zero.</p>

