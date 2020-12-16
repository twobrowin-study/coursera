import kotlin.test.assertEquals

fun main() {
    assertEquals(
        getCarFueling(
            400,
            intArrayOf(0, 200, 375, 550, 750, 950)
        ),
        2
    )

    assertEquals(
        getCarFueling(
            3,
            intArrayOf(0, 1, 2, 5, 9, 10)
        ),
        -1
    )

    assertEquals(
        getCarFueling(
            200,
            intArrayOf(0, 100, 200, 300, 400, 700)
        ),
        -1
    )

    assertEquals(
        getCarFueling(
            3,
            intArrayOf(0, 2, 3, 4, 5, 6, 7, 8, 9, 11)
        ),
        3
    )
}