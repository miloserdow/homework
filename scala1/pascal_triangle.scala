def pascal(x: Int, y: Int): Int = {
    if ((x == y) || (y == 0)) 
        1 
    else 
        pascal(x - 1, y) + pascal(x - 1, y - 1)
}
