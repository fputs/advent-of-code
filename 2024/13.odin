package aoc

import "core:fmt"
import "core:log"
import "core:os"

day13 :: proc() {
	input, ok := os.read_entire_file("input/01")
	if !ok {
		log.fatal("Failed to read input")
	}
	fmt.println("Solution for Day 13 is not implemented yet")
}
