import scala.annotation.tailrec

object set {
    type Set = Int => Boolean
    def contains(s: Set, elem: Int): Boolean = s(elem)

    def singletonSet(elem: Int): Set = x =>
        x == elem

    def union(s: Set, t: Set): Set = x =>
        contains(s, x) || contains(t, x)

    def intersect(s: Set, t: Set): Set = x =>
        contains(s, x) && contains(t, x)

    def diff(s: Set, t: Set): Set = x =>
        contains(s, x) && !contains(t, x)

    def filter(s: Set, p: Int => Boolean): Set = x =>
        contains(s, x) && p(x) // oops :)

    def takeAll(s: Set): String = {
        val bound = 1000
        def toString(s: Set): String = {
            val xs = for (i <- -bound to bound if contains(s, i)) yield i
            xs.mkString("{", ",", "}")
        }
        toString(s)
    }

    def forall(s: Set, p: Int => Boolean): Boolean = {
        val bound = 1000
        @tailrec
        def iter(a: Int): Boolean = {
            if (a > bound)
                true
            else if (contains(s, a) && !p(a))
                false
            else
                iter(a + 1)
        }
        iter(-bound)
    }

    def exists(s: Set, p: Int => Boolean): Boolean = {
        val bound = 1000
        @tailrec
        def iter(a: Int): Boolean = {
            if (a > bound)
                false
            else if (contains(s, a) && p(a))
                true
            else
                iter(a + 1)
        }
        iter(-bound)
    }

    def map(s: Set, f: Int => Int): Set = {
        val bound = 1000
        def iter(a: Int): Set = {
            if (a > bound)
                x => false
            else if (contains(s, a))
                union(singletonSet(f(a)), iter(a + 1))
            else 
                iter(a + 1)
        }
        iter(-bound)
    }
    def f (x: Int) : Int = x * x
    def p(x: Int) : Boolean = x == 1
}
