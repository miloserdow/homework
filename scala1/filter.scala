def list_filter(lst: List[Int], x: Int): List[Int] = {
    if (lst == Nil) 
        Nil 
    else if (lst.head == x) 
        List(lst.head) ++ list_filter(lst.tail, x) 
    else 
        list_filter(lst.tail, x)
}
