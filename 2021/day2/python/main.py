from aocd.models import Puzzle  # type: ignore


YEAR = 2021
DAY = 2


def solve_a(data: list[str]) -> int:
    horizontal_pos = 0
    depth = 0

    for cmd, arg in map(str.split, data):
        match cmd:
            case 'forward':
                horizontal_pos += int(arg)
            case 'down':
                depth += int(arg)
            case 'up':
                depth -= int(arg)

    return horizontal_pos * depth


def solve_b(data: list[str]) -> int:
    horizontal_pos = 0
    depth = 0
    aim = 0

    for cmd, arg in map(str.split, data):
        match cmd:
            case 'forward':
                horizontal_pos += int(arg)
                depth += aim * int(arg)
            case 'down':
                aim += int(arg)
            case 'up':
                aim -= int(arg)

    return horizontal_pos * depth


def run_on_test_data(variants: str) -> None:
    with open('test-input.txt', 'r') as data:
        test_input_data = data.readlines()

    print(f'solving variants: {variants}')
    if 'a' in variants:
        print(solve_a(test_input_data))
    if 'b' in variants:
        print(solve_b(test_input_data))


def main(variants: str) -> None:
    puzzle = Puzzle(YEAR, DAY)  # type: ignore
    data = puzzle.input_data.splitlines()  # type: ignore

    print(f'solving variants: {variants}')
    if 'a' in variants:
        puzzle.answer_a = solve_a(data)
    if 'b' in variants:
        puzzle.answer_b = solve_b(data)


if __name__ == '__main__':
    main('ab')
