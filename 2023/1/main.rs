use std::fs::File;
use std::io::{BufRead, BufReader};


fn get_num(line: String) -> u32 {
    let mut left_char = '0';
    let mut right_char = '0';
    for char in line.chars() {
        if char.is_digit(10) {
            left_char = char;
            break;
        }
    }
    println!("left char: {left_char}");
    for char in line.chars().rev() {
        if char.is_digit(10) {
            right_char = char;
            break;
        }
    }
    println!("right char: {right_char}");
    let left_digit: u32 = left_char.to_digit(10).unwrap();
    let right_digit: u32 = right_char.to_digit(10).unwrap();
    let res: u32 = left_digit * 10 + right_digit;
    println!("res: {res}");
    return res
}

fn main() {
    let filename = "input.txt";
    // open file in readonly mode (ignore errors)
    let file = File::open(filename).unwrap();
    let reader = BufReader::new(file);
    let mut sum: u32 = 0;
    // Read the file line by line
    for (index, line) in reader.lines().enumerate() {
        let line = line.unwrap();  // ignore errors
        // show the line and its number
        println!("{}", line);
        sum += get_num(line);
        // if index == 3 { break };
    }
    println!("first answer: {sum}");
}
