//! <https://adventofcode.com/2015/day/1>

pub fn part1(_input: &str) -> String {
    let i = _input.chars().filter(|ch| matches!(ch, '(')).count();
    (i - (_input.len() - i)).to_string() 
}

pub fn part2(_input: &str) -> String {
    let mut f = 0;
    for (i, ch) in _input.chars().enumerate() {
        if ch == '(' {
            f += 1;
        } else {
            f -= 1;
        }
        if f == -1 {
            return (i + 1).to_string();
        }
    }
    "failed".to_string()
}
