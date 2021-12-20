from aocd.models import Puzzle  # type: ignore


def solve_a(measurements: tuple[int, ...]) -> int:
    rise_count = 0
    measurements_phased = measurements[:-1], measurements[1:]

    for i, j in zip(*measurements_phased):
        if j - i > 0:
            rise_count += 1

    return rise_count


def solve_b(measurements: tuple[int, ...]) -> int:
    rise_count = 0

    for i in range(len(measurements)):
        prev_grp = sum(measurements[i:i+3])
        next_grp = sum(measurements[i+1:i+4])
        rise_count += 1 if next_grp - prev_grp > 0 else 0

    return rise_count


def run_on_test_data() -> None:
    test_input = '199\n200\n208\n210\n200\n207\n240\n269\n260\n263\n'
    measurements = [int(measure) for measure in test_input.splitlines()]
    print(solve_a(tuple(measurements)))
    print(solve_b(tuple(measurements)))


def main() -> None:
    puzzle = Puzzle(2021, 1)  # type: ignore
    measurements = [int(measure) for measure in puzzle.input_data.splitlines()]  # type: ignore
    puzzle.answer_a = solve_a(tuple(measurements))
    puzzle.answer_b = solve_b(tuple(measurements))


if __name__ == '__main__':
    main()
