package main

import (
	"aoc/internal/solutions"
	"aoc/internal/utility"
	"errors"
	"fmt"
	"strconv"
)

func main() {
	var input string

	fmt.Print("Enter day (1-25): ")
	_, err := fmt.Scanln(&input)
	utility.Error(err)

	day, err := strconv.Atoi(input)
	utility.Error(err)

	if day < 1 || day > 25 {
		utility.Error(errors.New("day out of range"))
	}

	solutions.Run(day)
}
