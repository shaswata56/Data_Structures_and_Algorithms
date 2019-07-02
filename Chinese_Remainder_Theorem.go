package main

import "fmt"

func gcdExtended(a int, b int, x *int, y *int) int {

	if a == 0 {
		*x = 0
		*y = 1
		return b
	}

	var x1, y1 int
	gcd := gcdExtended(b % a, a, &x1, &y1)

	*x = y1 - (b / a) * x1
	*y = x1

	return gcd
}

func mmi(a, m int) int {

	var x, y int
	gcd := gcdExtended(a, m, &x, &y)

	if gcd == 1 {
		return (x % m + m) % m
	} else {
		return -1
	}
}

func getMinX(num, rem []int, n int) int {

	product, result := 1, 0

	for i := 0; i < n; i++ {
		product *= num[i]
	}

	for i := 0; i < n; i++ {
		p := product / num[i]
		result += rem[i] * mmi(p, num[i]) * p
	}

	return result % product
}

func main()  {

	var n int
	fmt.Scan(&n)
	var arr, rem = make([]int, n), make([]int, n)

	fmt.Print("Enter array-1 : ")
	for i := 0; i < n; i++ {
		fmt.Scan(&arr[i])
	}

	fmt.Print("Enter array-2 : ")
	for i := 0; i < n; i++ {
		fmt.Scan(&rem[i])
	}

	fmt.Printf("x = %d", getMinX(arr, rem, n))
}
