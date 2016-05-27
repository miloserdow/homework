def push_back(lst: List[Int], x: Int): List[Int] = {
    if (lst.isEmpty)
        x :: Nil
    else lst.head :: add(lst.tail, x)
}
