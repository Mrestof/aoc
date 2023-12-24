use crate::year2023;


pub const SOLVER_FOR_DAY: [fn(&Vec<String>) -> (u32, u32); 2] = [
    year2023::day1::both,
    year2023::day2::both,
];
