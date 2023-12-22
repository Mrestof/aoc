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

pub fn get_num_improved(line: String) -> u32 {
    let mut left_digit: u32 = 0;
    let mut right_digit: u32 = 0;
    let mut num_mask: Vec<bool> = vec![true; 9];
    let mut cum_name: Vec<char> = vec![];
    'cl: for c in line.chars() {
        if c.is_digit(10) { left_digit = c.to_digit(10).unwrap_or(0); break; }
        for i in 0..9 {
            // BUG: with the following string: "zcndrqjsfourthreethree11seven"
            // four doesn't get recognized
            if !num_mask[i] { continue }
            println!("{c}, {cum_name:?}");
            if c != NUM_NAMES[i].as_bytes()[cum_name.len()] as char {
                num_mask[i] = false; continue
            }
            cum_name.push(c);
            println!("{c}, {cum_name:?}");
            if cum_name.len() == NUM_NAMES[i].len() {
                left_digit = i as u32 + 1; break 'cl
            }
            continue 'cl; // BUG: possible reason for a bug, because we don't mask out all wrong
                          // number
        }
        for flag in &mut num_mask { *flag = true }
        cum_name.clear();
    }
    let mut num_mask: Vec<bool> = vec![true; 9];
    let mut cum_name: Vec<char> = vec![];
    let mut char_index: usize;
    'cl: for c in line.chars().rev() {
        if c.is_digit(10) { right_digit = c.to_digit(10).unwrap_or(0); break; }
        for i in 0..9 {
            if !num_mask[i] { continue }
            if cum_name.len() >= NUM_NAMES[i].len() {
                num_mask[i] = false; continue
            }
            //println!("{:?}, {:?}, {:?}", i, NUM_NAMES[i].len(), cum_name.len());
            char_index = NUM_NAMES[i].len() - cum_name.len() - 1;
            if c != NUM_NAMES[i].as_bytes()[char_index] as char {
                num_mask[i] = false; continue
            }
            cum_name.insert(0, c);
            //println!("{c}, {cum_name:?}");
            if cum_name.len() == NUM_NAMES[i].len() {
                right_digit = i as u32 + 1; break 'cl
            }
            continue 'cl;
        }
        for flag in &mut num_mask { *flag = true }
        cum_name.clear();
    }
    let res: u32 = left_digit * 10 + right_digit;
    println!("{res}");
    return res;
}

pub fn part2(input: &Vec<String>) -> u32 {
    let mut sum: u32 = 0;
    for line in input {
        println!("line: {line}");
        sum += get_num_improved(line.to_string());
    }
    return sum;
}
