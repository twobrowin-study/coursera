import java.util.*

fun optimalSummands(n: Int): IntArray {
    val summands = mutableListOf(1)
    var nTmp = n
    while (nTmp > summands[summands.lastIndex]) {
        nTmp -= summands[summands.lastIndex]
        if (nTmp <= summands[summands.lastIndex]) {
            summands[summands.lastIndex] += nTmp
        } else {
            summands += summands[summands.lastIndex] + 1
        }
    }
    return summands.toIntArray()
}

fun main(args: Array<String>) {
    val scanner = Scanner(System.`in`)
    val n = scanner.nextInt()
    val summands = optimalSummands(n)
    println(summands.size)
    println(summands.joinToString(separator = " "))
}