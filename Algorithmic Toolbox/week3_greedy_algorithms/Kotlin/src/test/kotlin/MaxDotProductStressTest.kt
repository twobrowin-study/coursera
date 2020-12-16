import kotlin.random.Random
import kotlin.test.assertEquals


fun maxDotProductNaive(a: LongArray, b: LongArray): Long {
    fun dotProduct(a: LongArray, b: LongArray): Long {
        var result: Long = 0
        for (i in a.indices) {
            result += a[i] * b[i]
        }
        return result
    }

    var result = dotProduct(a, b)

    val tryes = mutableListOf<IntArray>()
    val idxes = a.indices.toMutableList()
    var num = 1
    for (x in 2..a.size) {
       num *= x
    }
    for (i in 0 until num) {
        val j = i % a.lastIndex
        val tmp = idxes[j]
        idxes[j] = idxes[j+1]
        idxes[j+1] = tmp
        tryes.add(idxes.toIntArray())
    }

    for ( aTry in tryes ) {
        val aRolled = mutableListOf<Long>()
        for (idx in aTry) {
            aRolled.add(a[idx])
        }
        for ( bTry in tryes ) {
            val bRolled = mutableListOf<Long>()
            for (idx in bTry) {
                bRolled.add(b[idx])
            }
            val tmp = dotProduct(aRolled.toLongArray(), bRolled.toLongArray())
            if (tmp > result) {
                result = tmp
            }
        }
    }
    return result
}

fun main() {
    assertEquals(
        maxDotProduct(longArrayOf(23), longArrayOf(39)),
        897
    )
    assertEquals(
        maxDotProduct(longArrayOf(1, 3, -5), longArrayOf(-2, 4, 1)),
        23
    )

    while (true) {
        val n = 5
        val a = LongArray(n)
        for (i in 0 until n) {
            a[i] = Random.nextLong() % 4
        }
        val b = LongArray(n)
        for (i in 0 until n) {
            b[i] = Random.nextLong() % 4
        }
        println("Running test for n = $n:")
        println("\ta = ${a.joinToString()}")
        println("\tb = ${b.joinToString()}")
        val naive = maxDotProductNaive(a, b)
        val greed = maxDotProduct(a, b)
        println("\tnaive=$naive, greed=$greed")
        assertEquals(naive, greed)
        println("OK\n")
    }
}