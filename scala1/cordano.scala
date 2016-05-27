import math._
object Cordano {
    def sign(x: Double): Int =
        if (x < 0) -1 else if (x > 0) 1 else 0
    def solve(sequence: Array[Double]): List[Double] = {
        if (sequence.length == 3) {
            val a: Double = sequence(0)
            val b: Double = sequence(1)
            val c: Double = sequence(2)
            val D: Double = b * b - 4 * a * c
            if (D > 0) {
                List((-b - sqrt(D)) / (2 * a),
                  (-b + sqrt(D)) / (2 * a))
            } 
            else if (D == 0) {
                List(-b / (2 * a))
            } 
            else {
                Nil
            }
        } 
        else if (sequence.length == 4) {
            if (sequence(0) == 0) {
            solve(sequence.drop(1))
        } else if (sequence(0) == 1) {
            val a: Double = sequence(1)
            val b: Double = sequence(2)
            val c: Double = sequence(3)
            val q: Double = (a * a - 3 * b) / 9
            val r: Double = (2 * a * a * a - 9 * a * b + 27 * c) / 54
            if (r * r - q * q * q < 0) {
                val t: Double = acos(r / sqrt(q * q * q)) / 3
                List(2 * sqrt(q) * cos(t) - a / 3, 2 * sqrt(q) * cos(t + 2 * Pi / 3) - a / 3, 2 * 
sqrt(q) 
* cos(t - 2 * Pi / 3) - a / 3)
            } 
            else {
                val A: Double = sign(r) * pow(abs(r) + sqrt(r * r - q * q * q), 1 / 3)
                val B: Double = if (A == 0) 0 else q / A
                val x1 = (A + B) - a / 3
                if (A == B && A != 0)
                    List(x1, -A - a / 3)
                else
                    List(x1)
            }
        } else {
            solve(sequence.map(_ / sequence(0)).toArray)
        }
    } else {
      println("Error")
      Nil
    }
  }
}
