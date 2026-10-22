pub fn lines(input: &str) -> Vec<&str> {
    input
    .lines()
    .collect()
}

pub fn ints(input: &str) -> Vec<i32> {
    input
    .lines()
    .map(|line| line.parse().expect("each line is an integer"))
    .collect()
}