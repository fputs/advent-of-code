package aoc

import "core:math"
import "core:fmt"
import "core:sort"
import "core:strconv"
import "core:strings"

day01 :: proc() {
	input := slurp_lines("input/01")
	defer delete(input)

	left := make([dynamic]int, 0, len(input))
	right := make([dynamic]int, 0, len(input))
	for line in input {
		sp := strings.split(line, "   ")
		a, _ := strconv.parse_int(sp[0])
		b, _ := strconv.parse_int(sp[1])
		append(&left, a)
		append(&right, b)
	}
	sort.quick_sort(left[:])
	sort.quick_sort(right[:])
	
	p1: int
	for i in 0..<len(left) {
	    p1 += math.abs(left[i] - right[i])
	}
	fmt.println(p1)
	
	count: map[int]int
	for r in right {
	    count[r] += 1
	}
 
	p2: int
	for l in left {
	    p2 += l * count[l]
	}
	fmt.println(p2)
}
