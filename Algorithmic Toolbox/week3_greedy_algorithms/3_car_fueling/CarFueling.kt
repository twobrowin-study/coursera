import java.util.*

fun getCarFueling(mostTravel: Int, stops: IntArray): Int {
    var nOfFilings = 0
    var curPos = 0
    var idx = 0
    while ( idx <= stops.lastIndex && curPos < stops[stops.lastIndex] ) {
        if ( stops[idx] > curPos + mostTravel ) {
            return -1
        }
        while ( idx <= stops.lastIndex && stops[idx] <= curPos + mostTravel ) {
            idx++
        }
        curPos = stops[idx-1]
        nOfFilings++
    }

    return nOfFilings-1
}

fun main(args: Array<String>) {
    val scanner = Scanner(System.`in`)
    val distance = scanner.nextInt()
    val mostTravel = scanner.nextInt()
    val n = scanner.nextInt()
    val stops = IntArray(n+2)
    stops[0] = 0
    for (i in 1..n) {
        stops[i] = scanner.nextInt()
    }
    stops[stops.lastIndex] = distance
    println(getCarFueling(mostTravel, stops))
}