def balance(chars: List[Char]): Boolean = {
  def numbs(ls: List[Char], op: Int): Boolean = {
    if (ls.isEmpty) 
       op == 0
    else if (ls.head == '(') 
      numbs(ls.tail, op + 1)
    else if (ls.head == ')') {
      if (op != 0) 
        numbs(ls.tail, op - 1)
      else 
        false
    }
    else numbs(ls.tail, op)
  }
  numbs(chars, 0)
}
