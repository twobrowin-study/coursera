import kotlin.test.assertTrue

fun main() {
    assertTrue( optimalSummands(2) contentEquals intArrayOf(2) )
    assertTrue( optimalSummands(3) contentEquals intArrayOf(1, 2) )
    assertTrue( optimalSummands(6) contentEquals intArrayOf(1, 2, 3) )
    assertTrue( optimalSummands(8) contentEquals intArrayOf(1, 2, 5) )
}