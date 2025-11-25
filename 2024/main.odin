package aoc

import "core:strconv"
import "core:fmt"
import "core:os"

main :: proc() {
	buf := [4]u8{}
    fmt.print("Enter a day between 1 and 25: ")
    sz, err := os.read(os.stdin, buf[:])
    if err != nil {
        fmt.println(err)
        panic("read failure")
    }
    
    day, _ := strconv.parse_int(string(buf[:sz]))
    
    switch(day) {
    case 1: day01()
    case 2: day02()
    case 3: day03()
    case 4: day04()
    case 5: day05()
    case 6: day06()
    case 7: day07()
    case 8: day08()
    case 9: day09()
    case 10: day10()
    case 11: day11()
    case 12: day12()
    case 13: day13()
    case 14: day14()
    case 15: day15()
    case 16: day16()
    case 17: day17()
    case 18: day18()
    case 19: day19()
    case 20: day20()
    case 21: day21()
    case 22: day22()
    case 23: day23()
    case 24: day24()
    case 25: day25()
    }
}

