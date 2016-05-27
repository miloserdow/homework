def len(lst: List[Int]): Int = {
    @tailrec
    def func(lst: List[Int], acc: Int): Int = {
        if (lst.isEmpty) 
            acc 
        else 
            func(lst.tail, acc + 1)
    }
    func(lst, 0)
}
