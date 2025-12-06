package aoc

import "core:fmt"
import "core:math"
import "core:strconv"
import "core:strings"

day02 :: proc() {
	input := slurp_lines("input/02")
	defer delete(input)

	p1: int
	p2: int
	for line in input {
		sp := strings.split(line, " ")
		report := make([dynamic]int, 0, len(sp))
		for s in sp {
			i, _ := strconv.parse_int(s)
			append(&report, i)
		}
		if validate(report) {
			p1 += 1
		}

		p2_valid := true
		for i := 0; i < len(report); i += 1 {
			cpy := make([dynamic]int, 0, len(report))
			copy(cpy[:], report[:])
			ordered_remove(&cpy, i)
			if !validate(cpy) {
				p2_valid = false
				delete(cpy)
				break
			}
			delete(cpy)
		}
		if p2_valid {
			p2 += 1
		}
		delete(report)
	}
	fmt.println(p1)
	fmt.println(p2)
}

validate :: proc(report: [dynamic]int) -> bool {
	increasing := false
	if report[0] < report[1] {
		increasing = true
	}

	for i := 1; i < len(report); i += 1 {
		if increasing && report[i - 1] > report[i] {
			return false
		}
		if !increasing && report[i - 1] < report[i] {
			return false
		}
		diff := math.abs(report[i - 1] - report[i])
		if diff < 1 || diff > 3 {
			return false
		}
	}
	return true
}
