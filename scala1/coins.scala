def count_coins(money: Int, coins: List[Int]): Int = {
    if (coins == Nil || money < 0) 
        0 
    else if (money == 0) 
        1 
    else count_coins(money - coins.head, coins) + count_coins(money, coins.tail)
}
