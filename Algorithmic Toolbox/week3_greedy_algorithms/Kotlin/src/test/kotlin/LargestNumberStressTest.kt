import kotlin.test.assertEquals

fun main() {
    assertEquals(largestNumber(arrayListOf("23", "3")), "323")
    assertEquals(largestNumber(arrayListOf("3", "23")), "323")
    assertEquals(largestNumber(arrayListOf("2", "23")), "232")
    assertEquals(largestNumber(arrayListOf("2", "21")), "221")
    assertEquals(largestNumber(arrayListOf("21", "2")), "221")
    assertEquals(largestNumber(arrayListOf("9", "4", "6", "1", "9")), "99641")
    assertEquals(largestNumber(arrayListOf("1", "4", "6", "9", "9")), "99641")
    assertEquals(largestNumber(arrayListOf("23", "39", "92")), "923923")
    assertEquals(largestNumber(arrayListOf("232", "2223222")), "2322223222")
}