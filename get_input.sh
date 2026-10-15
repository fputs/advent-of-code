#!/bin/sh
set -eu

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 YEAR SESSION_TOKEN" >&2
    echo "YEAR is four digits, for example 2015." >&2
    exit 1
fi

year=$1
token=$2

case $year in
    2015|2016|2017|2018|2019|2020|2021|2022|2023|2024|2025) ;;
    *)
        echo "YEAR must be from 2015 to 2025." >&2
        exit 1
        ;;
esac

mkdir -p "inputs/$year"

day=1
while [ "$day" -le 25 ]; do
    dd=$(printf '%02d' "$day")
    dest="inputs/$year/$dd"
    url="https://adventofcode.com/$year/day/$day/input"
    raw=$(mktemp)
    if curl -fsS --cookie "session=$token" "$url" -o "$raw"; then
        perl -pe 'chomp if eof' "$raw" > "$dest"
        rm -f "$raw"
        echo "saved $dest"
    else
        rm -f "$raw"
        echo "no input for $year day $day" >&2
    fi
    day=$((day + 1))
done
