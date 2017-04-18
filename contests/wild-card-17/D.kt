fun main(args: Array<String>) {
    var (n, l, r) = readLine()!!.split(" ").map(String::toInt)
    val a = readLine()!!.split(" ").map(String::toInt)
    val b = readLine()!!.split(" ").map(String::toInt)
    val A : IntArray = IntArray(r - l + 1)
    val B : IntArray = IntArray(r - l + 1)
    l--
    r--
    for(i in l..r) {
        A[i - l] = a[i]
        B[i - l] = b[i]
    }
    var bad = false
    if(l > 0) {
        for(i in 0..l-1)
            if(a[i] != b[i])
                bad = true
    }
    if(r < n - 1) {
        for(i in r+1..n-1)
            if(a[i] != b[i])
                bad = true
    }
    A.sort()
    B.sort()
    for(i in 0..r-l)
        if(A[i] != B[i])
            bad = true
    if(bad)
        print("LIE")
    else
        print("TRUTH")
}
