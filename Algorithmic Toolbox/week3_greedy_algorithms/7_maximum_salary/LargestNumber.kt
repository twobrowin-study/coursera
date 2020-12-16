import java.util.*
import kotlin.collections.ArrayList

fun largestNumber(a: ArrayList<String>): String {
    var ans = ""
    val aTmp = a.toMutableList()
    while (aTmp.isNotEmpty()) {
        var maxStr = aTmp[0]
        for (str in aTmp.slice(1..aTmp.lastIndex)) {
            if (str.plus(maxStr) >= maxStr.plus(str)) {
                maxStr = str
            }
        }
        ans = ans.plus(maxStr)
        aTmp.remove(maxStr)
    }
    return ans
}

fun main(args: Array<String>) {
    val scanner = Scanner(System.`in`)
    val n = scanner.nextInt()
    val a = ArrayList<String>(n)
    repeat(n) {
        a += scanner.next()
    }
    println(largestNumber(a))
}
