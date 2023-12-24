mod year2023 {
    pub mod day1;
    pub mod day2;
}
mod consts;
use std::env::current_dir;
use std::path::{Path, PathBuf};
use std::fs::File;
use std::io::{
    Result as IoResult,
    BufReader,
    BufRead,
};


fn get_input(year: u16, day: u8) -> IoResult<BufReader<File>> {
    let mut inp_path: PathBuf = current_dir()?;
    let inp_dir_name = Path::new("inputs");
    loop {
        inp_path.push(inp_dir_name);
        if inp_path.is_dir() { break }
        // this might leave us in the root, but it's probably fine, hehe
        if !(inp_path.pop() && inp_path.pop()) { break }
    }
    inp_path.push(format!("{year}_{day}.txt"));
    let input_file: File = File::open(inp_path)?;
    let input_reader: BufReader<File> = BufReader::new(input_file);
    return Ok(input_reader);
}


fn solve_for_day(day: u8) {
    let reader: BufReader<File> = get_input(2023, day).expect("😭😭😭");
    let input: Vec<String> = reader.lines()
        .map(|line| line.expect("Error reading line"))
        .collect();
    let solver = consts::SOLVER_FOR_DAY[day as usize - 1];
    let (p1_answer, p2_answer) = solver(&input);
    println!("2023-1:1: {p1_answer}");
    println!("2023-1:2: {p2_answer}");
}

fn main() {
    for day in 1..=2 {
        solve_for_day(day);
    }
}
