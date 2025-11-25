package aoc

import "core:fmt"
import "core:log"
import "core:os"

day14 :: proc() {
	input, ok := os.read_entire_file("input/01")
	if !ok {
		log.fatal("Failed to read input")
	}
	fmt.println("Solution for Day 14 is not implemented yet")
}
