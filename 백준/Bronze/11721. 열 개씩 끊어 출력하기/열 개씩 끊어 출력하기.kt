import java.lang.Integer.min

fun main(args: Array<String>) {

    var input : String? = readlnOrNull();
    for (i in input!!.indices step 10)
        println(input.substring(i, min(i + 10, input.length)))

}