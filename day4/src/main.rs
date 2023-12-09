use std::{collections::HashSet, usize};

fn main() {
    let data = include_str!("../input.txt");
    let lines = data.lines();

    let mut task1 = 0;

    for line in lines {
        let (_, card) = line.split_once(": ").unwrap();
        let (winning, provided) = card.split_once(" | ").unwrap();
        let winning: HashSet<usize> = winning.split_whitespace().map(|x| x.parse::<usize>().unwrap()).collect();
        let provided: HashSet<usize> = provided
            .split_whitespace()
            .map(|x| x.parse::<usize>()
            .unwrap())
            .collect();

        task1 += winning
            .intersection(&provided)
            .fold(0, |acc, _| {
                if acc == 0 {
                    1
                } else {
                    acc * 2
                }
            });
    }

    // 23941
    println!("[task1] sum: {}", task1);
}
