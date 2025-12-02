#!/bin/env bash

FOUT=./fileoutput.txt

# TODO: this big chunk of code that finds the latest changes can be probably
# done via Make more easier
filename=$1
if [[ -z "$filename" ]]; then
  last_edited=$(find src -type f -name '*.c' -printf '%T@ %p\n' | sort | tail -1 | cut -d' ' -f2)
  if [[ ! $last_edited =~ .+\.c ]]; then
    printf 'usage: %s FILE\n' "$0"
    printf '(or the last edited file must be *.c)\n'
    exit 1
  fi
  filename=$last_edited
fi

year_part=${filename#*/year} # strip everything through "year"
year=${year_part%/*}        # keep up to the next slash
day_part=${filename#*/day}   # take the filename "day1.c"
day=${day_part%.*}          # drop the ".c" suffix

fin="../../inputs/${year}-${day}.txt"

find-up () {
  local path=$(pwd)
  while [[ "$path" != "" && ! -e "$path/$1" ]]; do
    path=${path%/*}
  done
  echo "$path"
}

if [[ ! -e "$fin" ]]; then
  if [[ ! $(command -v aocd) ]]; then
    venv_name="${1:-.venv}"
    closest_venv_loc=$(find-up $venv_name)
    source $closest_venv_loc/$venv_name/bin/activate
  fi
  aocd "$year" "$day" > ../../inputs/${year}-${day}.txt
fi

if [[ ! -d ".bin/lib" ]]; then
  mkdir -p ".bin/lib"
fi

bin_name="./.bin/${year}-${day}"

gcc_warnings=\
'-Wall -Wextra -Wpedantic -Wreturn-type -Wdouble-promotion -Wfloat-conversion'

printf '###############\n'
printf '%s\n' "$filename"
printf '###############\n'
printf '=== compile ===\n'
set -e
gcc -c -g src/lib/myutils.c -o .bin/lib/myutils.o
ar rcs .bin/lib/libmyutils.a .bin/lib/myutils.o
gcc -O0 -g $gcc_warnings $filename -o $bin_name -L.bin/lib -lmyutils -lm -lbsd
set +e
printf '===  start  === (%s)\n' "$(date +"%H:%M:%S.%3N")"

$bin_name <$fin |& tee $FOUT
return_code=${PIPESTATUS[0]}
if [[ $(tail -c1 $FOUT | wc -l) -eq 0 ]]; then
  printf '\e[7m%%\e[0m\n'
fi

printf '===   end   === (%s)\n' "$(date +"%H:%M:%S.%3N")"
if [[ "$return_code" = "0" ]]; then
  printf 'return code: %s\n' "$return_code"
else
  printf '\e[7mreturn code: %s\e[0m\n' "$return_code"
fi
