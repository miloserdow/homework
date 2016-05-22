def sum(lst: List[Int]): Int = {
    if (lst == Nil) 
       0 
    else 
       lst.head + sum(lst.tail)
}
