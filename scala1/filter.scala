def list_filter(lst: List[Int], x: Int): List[Int] = {
    if (lst.isEmpty)
        Nil
    else if (lst.head > 0)
        lst.head :: list_filter(lst.tail)
    else list_filter(lst.tail)
}
