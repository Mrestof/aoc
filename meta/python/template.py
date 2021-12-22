from aocd.models import Puzzle  # type: ignore


YEAR = 0
DAY = 0


def solve_a(data: list[str]) -> int:
    ...


def solve_b(data: list[str]) -> int:
    ...


def run_on_test_data(variants: str) -> None:
    with open('test-input.txt', 'r') as data:
        test_input_data = data.read().splitlines()

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
    run_on_test_data('ab')
