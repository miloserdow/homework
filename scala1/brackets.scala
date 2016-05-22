def check(lst: List[Char], balance: Int = 0): Boolean = {
    if (lst == Nil) { 
        if (balance == 0) 
            true 
        else 
            false
    }
    else if(lst.head == '(') {
        check(lst.tail, balance + 1) 
    }
    else { 
        check(lst.tail, balance - 1)
    }
}
