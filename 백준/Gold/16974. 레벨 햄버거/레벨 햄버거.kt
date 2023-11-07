import java.util.StringTokenizer

var burger = LongArray(51) { 0 }
var patty = LongArray(51) { 0 }

fun main(args: Array<String>) {
    val st = StringTokenizer(readlnOrNull())
    val N : Int = st.nextToken().toInt()
    val X : Long = st.nextToken().toLong()

    patty[0] = 1
    burger[0] = 1

    for (i in 1 .. N){
        patty[i] = patty[i - 1] * 2 + 1
        burger[i] = burger[i - 1] * 2 + 3
    }

    println(countPatty(N, X))
}


fun countPatty(N : Int, X : Long) : Long {

    if (N == 0) // 패티만 하나 있음
        return 1
    if (X == 1L) // 맨 아래 장은 빵
        return 0
    //반 보다 작은 경우
    if (X < burger[N - 1] + 2) //반 + 빵
        return countPatty(N - 1,  X -1) //밑 빵 버림
    //반 + 패티 하나
    if (X == burger[N - 1] + 2)
        return patty[N - 1] + 1//밑 빵 빼고 패티 하나 추가
    //반 보다 큰 경우
    if (X < burger[N]) // 반쪽 먹고 패티하나 먹고 남은 거 먹기
        return patty[N - 1] + 1 + countPatty(N - 1, X - burger[N-1] - 2)// 빵 하나 패티 하나
    //전체와 같은 경우
    return patty[N]
}