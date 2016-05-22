def reverse(lst: List[Int]): List[Int] = {
    if (lst.tail == Nil) 
        List(lst.head) 
    else 
        reverse(lst.tail) ++ List(lst.head)
}
