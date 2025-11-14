#!/usr/bin/env sh

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 YEAR SESSION_TOKEN" >&2
    exit 1
fi

if [ "$1" -lt 2015 ] || [ "$1" -gt 2025 ]; then
    echo "Error: YEAR must be between 2015 and 2025." >&2
    exit 1
fi

get(){
		curl -s --cookie "session=$1" "$2" | perl -pe 'chomp if eof' > "$3"
}

mkdir -p "$1/input"
for day in {1..25}; do
	if [[ day -lt 10 ]]; then
		d="0$day"
	else
		d="$day"
	fi
	url="https://adventofcode.com/$1/day/$day/input"
	get "$2" "$url" "$1/input/$d"
done
echo "test" > "$1/input/test"
