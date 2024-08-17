# [Platinum I] Jewel heist - 3411 

[문제 링크](https://www.acmicpc.net/problem/3411) 

### 성능 요약

메모리: 17600 KB, 시간: 1044 ms

### 분류

자료 구조, 세그먼트 트리, 스위핑

### 제출 일자

2024년 8월 17일 16:05:20

### 문제 설명

<p>Arsen Lupin, the master thief, aims to steal Evil Erwin’s jewels. Erwin has n jewels on display in his store. Every precious stone is of one of k distinct colors. The exposition is so large that we can treat it as the Euclidean plane with the jewels being distinct points. The display is secured by some quite expensive alarms.</p>

<p>Lupin has invented a device: a big, robotic hand that can grab some of the Erwin’s jewels without triggering any of the alarms. The hand can make one (and only one) grab, taking all the jewels lying on some horizontal segment or below it (see the picture). Lupin could easily take all the jewels this way, but he knows that the more he takes, the harder it will be to get rid of them. He decided that the safest way is to take a set of jewels that does not contain all the k colors.</p>

<p style="text-align: center;"><img alt="" src="https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/upload/images2/jewel(1).png" style="height:278px; width:311px"></p>

<p>The robotic hand grabs jewels 1,2,4,5 and 6, carefully omitting the black ones</p>

<p>Compute how many jewels Lupin can steal with one grab of his device, without taking jewels in every color.</p>

### 입력 

 <p>The first line of the input contains the number of test cases T. The descriptions of the test cases follow:</p>

<p>Each test case starts with two integers n (2 ≤ n ≤ 200 000) and k (2 ≤ k ≤ n) denoting the number of jewels and the number of distinct colors. The next n lines denote the jewels’ positions and colors. The j-th line contains three space-separated integers x<sub>j</sub> , y<sub>j</sub> , c<sub>j</sub> (1 ≤ x<sub>j</sub> , y<sub>j</sub> ≤ 10<sup>9</sup>, 1 ≤ c<sub>j</sub> ≤ k) meaning that the j-th jewel lies at coordinates (x<sub>j</sub> , y<sub>j</sub>) and has color c<sub>j</sub>.</p>

<p>You may assume that there is at least one stone of every color at the exposition.</p>

### 출력 

 <p>Print the answers to the test cases in the order in which they appear in the input. For each test case print a single line containing the maximum possible number of stolen jewels.</p>

