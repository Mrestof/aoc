from collections import Counter
from aocd.models import Puzzle  # type: ignore


YEAR = 2021
DAY = 3


def solve_a(data: list[str]) -> int:
    gamma_rate_str = ''

    for bit_pos in range(len(data[0])):
        frequency = Counter(num[bit_pos] for num in data)
        gamma_rate_str += '1' if frequency['1'] > frequency['0'] else '0'

    epsilon_rate_str = ''.join('0' if bit == '1' else '1' for bit in gamma_rate_str)

    gamma_rate_num = int(gamma_rate_str, 2)
    epsilon_rate_num = int(epsilon_rate_str, 2)

    return gamma_rate_num * epsilon_rate_num


# TODO: try to merge two parts for finding rating into one as a functoin
#       or other way
def solve_b(data: list[str]) -> int:
    # find oxygen generator rating
    oxy_rating = 0
    matched_nums = data.copy()
    for bit_pos in range(len(matched_nums[0])):
        frequency = Counter(num[bit_pos] for num in matched_nums)
        criteria = '1' if frequency['1'] >= frequency['0'] else '0'
        for num_pos, num in enumerate(matched_nums):
            if num[bit_pos] != criteria:
                matched_nums[num_pos] = ''  # mark all not matching nums
        matched_nums = list(filter(None, matched_nums))  # delete marked nums
        if len(matched_nums) == 1:
            oxy_rating = int(''.join(matched_nums[0]), 2)

    # find CO2 scrubber rating
    co2_rating = 0
    matched_nums = data.copy()
    for bit_pos in range(len(matched_nums[0])):
        frequency = Counter(num[bit_pos] for num in matched_nums)
        criteria = '0' if frequency['0'] <= frequency['1'] else '1'
        for num_pos, num in enumerate(matched_nums):
            if num[bit_pos] != criteria:
                matched_nums[num_pos] = ''  # mark all not matching nums
        matched_nums = list(filter(None, matched_nums))  # delete marked nums
        if len(matched_nums) == 1:
            co2_rating = int(''.join(matched_nums[0]), 2)

    return oxy_rating * co2_rating


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
    main('ab')
