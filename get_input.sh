#!/bin/sh
set -eu

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 SESSION_TOKEN" >&2
    echo "Downloads every day of every year from 2015 through 2025." >&2
    exit 1
fi

token=$1

year=2015
while [ "$year" -le 2025 ]; do
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
    year=$((year + 1))
done
