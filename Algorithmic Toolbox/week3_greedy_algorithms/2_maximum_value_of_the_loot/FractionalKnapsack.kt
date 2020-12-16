import java.util.*

fun getFractionalKnapsack(capacity: Int, values: IntArray, weights: IntArray): Double {
    var capacityTmp = capacity
    return values.zip(weights).sortedByDescending {
        it.first.toDouble()/it.second.toDouble()
    }.map {
        val toAdd = minOf(capacityTmp, it.second)
        capacityTmp -= toAdd
        val toReturn = it.first.toDouble() * toAdd.toDouble() / it.second.toDouble()
        toReturn
    }.sum()
}

fun main(args: Array<String>) {
    val scanner = Scanner(System.`in`)
    val n = scanner.nextInt()
    val capacity = scanner.nextInt()
    val values = IntArray(n)
    val weights = IntArray(n)
    for (i in 0 until n) {
        values[i] = scanner.nextInt()
        weights[i] = scanner.nextInt()
    }
    println(getFractionalKnapsack(capacity, values, weights))
}