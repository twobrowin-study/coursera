import java.util.*

fun optimalPoints(segments: ArrayList<Segment>): IntArray {
    val greedSegments = segments.sortedBy { it.end }
    val points = mutableListOf<Int>()
    var idx = 0
    while (idx <= greedSegments.lastIndex) {
        points += greedSegments[idx].end
        while (idx <= greedSegments.lastIndex && points[points.lastIndex] >= greedSegments[idx].start) {
            idx++
        }
    }
    return points.toIntArray()
}

class Segment(var start: Int, var end: Int)

fun main(args: Array<String>) {
    val scanner = Scanner(System.`in`)
    val n = scanner.nextInt()
    val segments = ArrayList<Segment>(n)
    repeat (n) {
        val start: Int = scanner.nextInt()
        val end: Int = scanner.nextInt()
        segments += Segment(start, end)
    }
    val points = optimalPoints(segments)
    println(points.size)
    println(points.joinToString(separator = " "))
}