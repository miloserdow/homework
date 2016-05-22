def len(lst: List[Int]): Int = {
    if (lst == Nil) 
       0 
    else
       1 + len(lst.tail)
}
