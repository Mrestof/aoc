fn get_num(line: String) -> u32 {
    let mut left_char = '0';
    let mut right_char = '0';
    for c in line.chars() {
        if c.is_digit(10) {
            left_char = c;
            break;
        }
    }
    for c in line.chars().rev() {
        if c.is_digit(10) {
            right_char = c;
            break;
        }
    }
    let left_digit: u32 = left_char.to_digit(10).unwrap();
    let right_digit: u32 = right_char.to_digit(10).unwrap();
    let res: u32 = left_digit * 10 + right_digit;
    return res
}

pub fn part1(input: &Vec<String>) -> u32 {
    let mut sum: u32 = 0;
    for line in input {
        sum += get_num(line.to_string());
    }
    return sum;
}

const NUM_NAMES: [&str; 9] = [
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
];

fn get_first_num(line: &str, reversed: bool) -> u32 {
    let mut out_num: u32 = 0;
    let mut c: char;
    let mut nn_len: usize;
    let mut cur_nn: &str;
    let mut end_idx: usize;
    // cringe rust doesn't allow to easily reverse a range and type the variable
    // as either Range or Rev<Range>, gotta do some impl Iterator<...> stuff or
    // just use vec to collect them, meh
    let indexes: Vec<usize> = if reversed {
        (0..line.len()).rev().collect()
    } else {
        (0..line.len()).collect()
    };
    'cl: for cidx in indexes {
        c = line.as_bytes()[cidx] as char;
        if c.is_digit(10) { out_num = c.to_digit(10).unwrap_or(0); break }
        for i in 0..9 {
            nn_len = NUM_NAMES[i].len();
            if nn_len + cidx < line.len() {
                end_idx = cidx + nn_len;
            } else {
                end_idx = line.len();
            }
            cur_nn = &line[cidx..end_idx];
            if cur_nn == NUM_NAMES[i] { out_num = i as u32 + 1; break 'cl }
        }
    }
    return out_num
}

fn get_num_improved(line: &str) -> u32 {
    let left_digit: u32 = get_first_num(line, false);
    let right_digit: u32 = get_first_num(line, true);
    let res: u32 = left_digit * 10 + right_digit;
    return res;
}

pub fn part2(input: &Vec<String>) -> u32 {
    let mut sum: u32 = 0;
    for line in input {
        sum += get_num_improved(line);
    }
    return sum;
}
