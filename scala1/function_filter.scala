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
        lst.head :: list_filter(func, lst.tail)
    else 
        list_filter(func, lst.tail)
}
