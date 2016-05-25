def reverse(lst: List[Int]) = {
    @tailrec
    def func(lst: List[Int], acc: List[Int]) : List[Int] = {
        if (lst.isEmpty) 
            acc 
        else 
            func(lst.tail, lst.head :: acc)
    }
    func(lst, List())
}
