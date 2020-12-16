import kotlin.test.assertTrue

fun main() {
    assertTrue(
            optimalPoints( arrayListOf(
                    Segment(1, 3),
                    Segment(2, 5),
                    Segment(3, 6),
            )) contentEquals intArrayOf(3)
    )

    assertTrue(
            optimalPoints( arrayListOf(
                    Segment(4, 7),
                    Segment(1, 3),
                    Segment(2, 5),
                    Segment(5, 6),
            )) contentEquals  intArrayOf(3, 6)
    )
}