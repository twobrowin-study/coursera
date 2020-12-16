import kotlin.test.assertEquals

fun main() {
    assertEquals(180.0,
        getFractionalKnapsack(
            50,
            intArrayOf(60, 100, 120),
            intArrayOf(20, 50, 30)
        )
    )

    assertEquals(166.66666666666666,
        getFractionalKnapsack(
            10,
            intArrayOf(500),
            intArrayOf(30)
        )
    )

}