mod year2023 {
    pub mod day1;
}
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

fn main() {
    // let reader: BufReader<File> = get_input(2023, 1).expect("😭😭😭");
    // let input: Vec<String> = reader.lines()
    //     .map(|line| line.expect("Error reading line"))
    //     .collect();
    // let p1_answer = year2023::day1::part1(&input);
    // println!("2023-1:1: {p1_answer}");
    // let p2_answer = year2023::day1::part2(&input);
    // println!("2023-1:2: {p2_answer}");
    let s = "zcndrqjsfourthreethree11seven";
    println!("{:?}", year2023::day1::get_num_improved(s.to_string()));
    println!("line: {s}");
}
