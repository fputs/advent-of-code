# advent-of-code

Rust solutions for Advent of Code, 2015 through 2025.

## Run

```bash
cargo run -- 15 1
```

The first argument is a two-digit year. The second is a day from 1 to 25.
`15 1` runs 2015 day 1 and prints both parts.

Puzzle input is read from `inputs/2015/01` (year, then a zero-padded day).
The same path is used when you run `target/debug/aoc` from another directory.

## Write a solution

Each day is a module with two functions. 2015 day 1 is `src/y2015/day01.rs`:

```rust
pub fn part1(input: &str) -> String {
    input.lines().count().to_string()
}

pub fn part2(_input: &str) -> String {
    String::from("not implemented")
}
```

Return the answer as a `String`. Numbers can use `.to_string()`.
The puzzle text is linked at the top of the file. Stubs compile and print
`not implemented` until you replace them.

## Inputs

`get_input.sh` downloads every day of one year. Copy the `session` cookie
from your browser on adventofcode.com.

```bash
./get_input.sh 2015 SESSION_TOKEN
```

The year argument here is four digits, because that is what the site uses
in its URL.

## Add a year

Copy `src/y2025` to `src/y2026`, then register `mod y2026` and a `2026` arm
in `src/main.rs`. Bump `MAX_YEAR` in that file, and the year list in
`get_input.sh`.
