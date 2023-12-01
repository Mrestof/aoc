use std::fs::File;
use std::io::{BufRead, BufReader};


// TODO: expect unwraps


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

fn main() {
    let filename = "input.txt";
    // open file in readonly mode (ignore errors)
    let file = File::open(filename).unwrap();
    let reader = BufReader::new(file);
    let mut sum: u32 = 0;
    // Read the file line by line
    for line in reader.lines() {
        let line = line.unwrap();  // ignore errors
        // show the line and its number
        println!("{}", line);
        sum += get_num(line);
    }
    println!("first answer: {sum}");
}
