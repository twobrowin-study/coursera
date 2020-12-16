import java.util.*

fun getChange(m: Int): Int {
    val coinTypes = intArrayOf(10, 5, 1)
    var res = 0
    var mTmp = m

    for ( type in coinTypes ) {
        res  += mTmp / type
        mTmp %= type
    }

    return res
}

fun main(args: Array<String>) {
    val scanner = Scanner(System.`in`)
    val m = scanner.nextInt()
    println(getChange(m))
}