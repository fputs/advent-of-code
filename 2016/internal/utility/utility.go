package utility

import (
	"crypto/md5"
	"encoding/hex"
	"log"
)

func Error(err error) {
	if err != nil {
		log.Panic(err)
	}
}

type Point struct {
	x int
	y int
}

func NewPoint(x, y int) Point {
	return Point{x, y}
}

func GetMD5Hash(in string) string {
	hash := md5.Sum([]byte(in))
	return hex.EncodeToString(hash[:])
}

func RuneMap(in string) (m map[rune]int) {
	m = make(map[rune]int)
	for _, c := range in {
		m[c]++
	}
	return m
}
