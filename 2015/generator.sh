#!/usr/bin/env bash

mkdir -p include

for year in {2015..2024}; do
  rm -rf "src/${year}"
  mkdir -p "src/${year}"

  rm "include/advent${year}.h"
  tee "include/advent${year}.h" <<EOF
#ifndef ADVENT_${year}_H
#define ADVENT_${year}_H

void advent${year}day01(void);
void advent${year}day02(void);
void advent${year}day03(void);
void advent${year}day04(void);
void advent${year}day05(void);
void advent${year}day06(void);
void advent${year}day07(void);
void advent${year}day08(void);
void advent${year}day09(void);
void advent${year}day10(void);
void advent${year}day11(void);
void advent${year}day12(void);
void advent${year}day13(void);
void advent${year}day14(void);
void advent${year}day15(void);
void advent${year}day16(void);
void advent${year}day17(void);
void advent${year}day18(void);
void advent${year}day19(void);
void advent${year}day20(void);
void advent${year}day21(void);
void advent${year}day22(void);
void advent${year}day23(void);
void advent${year}day24(void);
void advent${year}day25(void);

void (*solutions${year}[25])(void) = {
  advent${year}day01,
  advent${year}day02,
  advent${year}day03,
  advent${year}day04,
  advent${year}day05,
  advent${year}day06,
  advent${year}day07,
  advent${year}day08,
  advent${year}day09,
  advent${year}day10,
  advent${year}day11,
  advent${year}day12,
  advent${year}day13,
  advent${year}day14,
  advent${year}day15,
  advent${year}day16,
  advent${year}day17,
  advent${year}day18,
  advent${year}day19,
  advent${year}day20,
  advent${year}day21,
  advent${year}day22,
  advent${year}day23,
  advent${year}day24,
  advent${year}day25
};

#endif
EOF

  for day in {1..25}; do
    if [[ $day -lt 10 ]]; then
      d="0${day}"
    else
      d="$day"
    fi
    tee "src/${year}/${d}.c" <<EOF
#include <stdio.h>
#include <stdlib.h>

#include "lfinput.h"

void advent${year}day${d}(void) {
  char *input = get_input("input/${year}/${d}");
  printf("Solution for Day ${d} of ${year} is not completed yet\n");
  free(input);
}
EOF
  done
done
