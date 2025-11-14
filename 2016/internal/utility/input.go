package utility

import (
	"os"
	"strconv"
	"strings"
)

func GetInput(path string) string {
	data, err := os.ReadFile(path)
	Error(err)
	return string(data)
}

func GetLines(path string) []string {
	data := GetInput(path)
	return strings.Split(data, "\n")
}

func GetInts(path string) []int {
	data := GetLines(path)
	r := make([]int, len(data))
	for _, line := range data {
		t, err := strconv.Atoi(line)
		Error(err)
		r = append(r, t)
	}
	return r
}
