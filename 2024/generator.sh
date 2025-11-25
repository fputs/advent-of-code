#!/usr/bin/env bash

for day in {1..25}; do
  if [[ $day -lt 10 ]]; then
    d="0${day}"
  else
    d="$day"
  fi
  tee "${d}.odin" <<EOF
package aoc

import "core:fmt"
import "core:log"
import "core:os"

day${d} :: proc() {
	input, ok := os.read_entire_file("input/01")
	if !ok {
		log.fatal("Failed to read input")
	}
	fmt.println("Solution for Day ${d} is not implemented yet")
}
EOF
done
