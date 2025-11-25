package aoc

import "core:log"
import "core:os"
import "core:strings"

Pair :: struct($T: typeid) {
	a: $T,
	b: $T,
}

slurp_file :: proc(path: string) -> string {
	input, ok := os.read_entire_file(path)
	if !ok {
		log.fatal("Failed to read input")
	}
	return string(input)
}

slurp_lines :: proc(path: string) -> []string {
	return strings.split_lines(slurp_file(path))
}
