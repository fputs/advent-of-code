//! Advent of Code runner.
//!
//! `aoc <yy> <day>` loads `inputs/20yy/dd` and calls that day's `part1` and `part2`.

mod y2015;
mod y2016;
mod y2017;
mod y2018;
mod y2019;
mod y2020;
mod y2021;
mod y2022;
mod y2023;
mod y2024;
mod y2025;

use std::env;
use std::fs;
use std::path::{Path, PathBuf};
use std::process::ExitCode;

const MIN_YEAR: u16 = 2015;
const MAX_YEAR: u16 = 2025;

fn main() -> ExitCode {
    let args: Vec<String> = env::args().skip(1).collect();
    let (year, day) = match parse_args(&args) {
        Ok(parsed) => parsed,
        Err(message) => {
            eprintln!("{message}");
            eprintln!();
            eprint_usage();
            return ExitCode::from(2);
        }
    };

    let path = match find_input(year, day) {
        Ok(path) => path,
        Err(message) => {
            eprintln!("{message}");
            return ExitCode::from(1);
        }
    };

    let input = match fs::read_to_string(&path) {
        Ok(input) => input,
        Err(error) => {
            eprintln!("could not read {}: {error}", path.display());
            return ExitCode::from(1);
        }
    };

    let (part1, part2) = solve(year, day, &input);
    println!("Part 1: {part1}");
    println!("Part 2: {part2}");
    ExitCode::SUCCESS
}

fn eprint_usage() {
    let first = MIN_YEAR % 100;
    let last = MAX_YEAR % 100;
    eprintln!("Usage: aoc <year> <day>");
    eprintln!();
    eprintln!("  year  two digits ({first:02}-{last:02})");
    eprintln!("  day   1-25");
    eprintln!();
    eprintln!("Example: cargo run -- 15 1");
}

fn parse_args(args: &[String]) -> Result<(u16, u8), String> {
    if args.len() != 2 {
        return Err("expected a year and a day".to_string());
    }
    let year = parse_year(&args[0])?;
    let day = parse_day(&args[1])?;
    Ok((year, day))
}

fn parse_year(raw: &str) -> Result<u16, String> {
    if raw.len() != 2 || !raw.bytes().all(|byte| byte.is_ascii_digit()) {
        return Err(format!(
            "year must be two digits, for example 15 (got {raw})"
        ));
    }
    let short: u16 = raw.parse().expect("two digits");
    let year = 2000 + short;
    if !(MIN_YEAR..=MAX_YEAR).contains(&year) {
        return Err(format!(
            "year must be from {MIN_YEAR} to {MAX_YEAR} (got {year})"
        ));
    }
    Ok(year)
}

fn parse_day(raw: &str) -> Result<u8, String> {
    if raw.is_empty() || raw.len() > 2 || !raw.bytes().all(|byte| byte.is_ascii_digit()) {
        return Err(format!("day must be from 1 to 25 (got {raw})"));
    }
    let day: u8 = raw.parse().expect("one or two digits");
    if !(1..=25).contains(&day) {
        return Err(format!("day must be from 1 to 25 (got {day})"));
    }
    Ok(day)
}

fn find_input(year: u16, day: u8) -> Result<PathBuf, String> {
    let relative = PathBuf::from(format!("inputs/{year}/{day:02}"));
    if relative.is_file() {
        return Ok(relative);
    }
    let from_manifest = Path::new(env!("CARGO_MANIFEST_DIR")).join(&relative);
    if from_manifest.is_file() {
        return Ok(from_manifest);
    }
    Err(format!(
        "no input file for {year} day {day}\nlooked for {}\nfetch it with ./get_input.sh {year} SESSION_TOKEN",
        relative.display()
    ))
}

fn solve(year: u16, day: u8, input: &str) -> (String, String) {
    match year {
        2015 => y2015::run(day, input),
        2016 => y2016::run(day, input),
        2017 => y2017::run(day, input),
        2018 => y2018::run(day, input),
        2019 => y2019::run(day, input),
        2020 => y2020::run(day, input),
        2021 => y2021::run(day, input),
        2022 => y2022::run(day, input),
        2023 => y2023::run(day, input),
        2024 => y2024::run(day, input),
        2025 => y2025::run(day, input),
        _ => unreachable!("year is checked before solve"),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn args(values: &[&str]) -> Vec<String> {
        values.iter().map(|value| (*value).to_string()).collect()
    }

    #[test]
    fn parses_year_and_day() {
        assert_eq!(parse_args(&args(&["15", "1"])).unwrap(), (2015, 1));
        assert_eq!(parse_args(&args(&["24", "09"])).unwrap(), (2024, 9));
        assert_eq!(parse_args(&args(&["25", "25"])).unwrap(), (2025, 25));
    }

    #[test]
    fn rejects_bad_args() {
        assert!(parse_args(&args(&[])).is_err());
        assert!(parse_args(&args(&["15"])).is_err());
        assert!(parse_args(&args(&["15", "1", "extra"])).is_err());
        assert!(parse_args(&args(&["2015", "1"])).is_err());
        assert!(parse_args(&args(&["14", "1"])).is_err());
        assert!(parse_args(&args(&["26", "1"])).is_err());
        assert!(parse_args(&args(&["15", "0"])).is_err());
        assert!(parse_args(&args(&["15", "26"])).is_err());
        assert!(parse_args(&args(&["15", "001"])).is_err());
        assert!(parse_args(&args(&["ab", "1"])).is_err());
    }
}
