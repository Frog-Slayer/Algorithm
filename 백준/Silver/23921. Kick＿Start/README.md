# [Silver III] Kick_Start - 23921 

[문제 링크](https://www.acmicpc.net/problem/23921) 

### 성능 요약

메모리: 2564 KB, 시간: 336 ms

### 분류

조합론, 수학, 문자열

### 제출 일자

2025년 6월 3일 00:23:41

### 문제 설명

<p>Ksenia is very fond of reading so she kicks off each day by reading a fragment from her favourite book before starting with the rest of her morning routine. A fragment is simply a <a href="https://en.wikipedia.org/wiki/Substring">substring</a> of the text. Ksenia is somewhat superstitious and believes that her day will be lucky if the fragment she reads starts with the string KICK, then goes on with 0 or more characters, and eventually ends with the string START, even if the overall fragment makes little sense.</p>

<p>Given the text of the book, count the number of different lucky fragments that Ksenia can read before the book gets old and she needs to buy another one. Two fragments are considered to be different if they start or end at different positions in the text, even if the fragments read the same. Also note that different lucky fragments may overlap.</p>

### 입력 

 <p>The first line of the input gives the number of test cases <b>T</b>. <b>T</b> lines follow, each containing a single string <b>S</b> consisting of upper case English letters only.'</p>

### 출력 

 <p>For each test case, output one line containing <code>Case #x: y</code>, where <code>x</code> is the test case number (starting from 1) and <code>y</code> is the number of different lucky fragments in the text of this test case.</p>

