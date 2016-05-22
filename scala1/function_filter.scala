def isEven(x: Int): Boolean = {
    if (x % 2 == 0) 
        true 
    else 
        false
}

def list_filter_func(lst: List[Int], func: (Int) => Boolean): List[Int] = {
    if (lst == Nil) 
        Nil 
    else if (func(lst.head))
        List(lst.head) ++ list_filter(lst.tail, lst.head) 
    else 
        list_filter(lst.tail, lst.head)
}
