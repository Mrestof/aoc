#!/usr/bin/python3

from typing import Final
from os import environ
from sys import stdout
from argparse import ArgumentParser, FileType, Namespace
from requests import get


BASE_URL: Final[str] = 'https://adventofcode.com'


def configure_and_get_args() -> Namespace:
    SK_FROM_STDIN = 'sk_stdin'

    parser = ArgumentParser(description='Little toolbox for "Advent of Code".')
    parser.add_argument('year', type=int, help='year from which to parse the task')
    parser.add_argument('day', type=int, help='day from which to parse the task')
    parser.add_argument('-o', '--outfile', dest='out_stream', type=FileType('w'), default=stdout,
                        help='path to a file in which the raw task will be stored')
    parser.add_argument('-sk', '--session-key', type=str, nargs='?', const=SK_FROM_STDIN,
                        help='session key which you can obtain from cookies while logged in on the site'
                             ' (if not specified, try to get the key from environment variable;'
                             ' if specified without value, get the key from stdin;'
                             ' if specified with value, get the key from the value)')
    args = parser.parse_args()

    if not args.session_key:
        try:
            args.session_key = environ['AOC_SESSION_KEY']
        except KeyError as key_name:
            print(
                f'Error in parsing the {key_name} environment variable.',
                'Make sure you have this variable set up in your current terminal session or pass it as a parameter.',
                sep='\n',
            )
            exit(1)
    elif args.session_key == SK_FROM_STDIN:
        args.session_key = input()

    return args


def get_raw_input_from_aoc(year: int, day: int, session_key: str) -> str:
    complete_url = f'{BASE_URL}/{year}/day/{day}/input'
    cookies = {'session': session_key}
    response = get(complete_url, cookies=cookies)
    return response.text


def main() -> None:
    args = configure_and_get_args()
    raw_input = get_raw_input_from_aoc(args.year, args.day, args.session_key)
    args.out_stream.write(raw_input)


if __name__ == '__main__':
    main()
