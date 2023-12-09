use std::{collections::{HashSet, HashMap}, usize};

struct Counter {
    data: HashMap<usize, usize>
}

impl Counter {
    fn new() -> Self {
        Self {
            data: HashMap::new()
        }
    }

    fn inc_many(&mut self, keys: &Vec<usize>) {
        for key in keys {
            self.inc(*key);
        }
    }

    fn inc(&mut self, key: usize) {
        self.data.entry(key).or_insert(0);
        self.data.entry(key).and_modify(|counter| *counter += 1);
    }

    fn dec(&mut self, key: usize) {
        self.data.entry(key).and_modify(|c| *c -= 1);
    }

    fn get(&self, key: usize) -> usize {
        *self.data.get(&key).unwrap_or(&0)
    }
}


fn main() {
    let data = include_str!("../input.txt");
    let lines = data.lines();

    let mut task1 = 0;

    // key is card number, value is winning number
    let mut copies = Counter::new(); // TODO: need iterator for Counter
    let mut cache: HashMap<usize, Vec<usize>> = HashMap::new();
    let mut counter = Counter::new();

    for (line_no, line) in lines.clone().enumerate() {
        let card_number = line_no + 1;
        let (_, card) = line.split_once(": ").unwrap();
        let (winning, provided) = card.split_once(" | ").unwrap();
        let winning: HashSet<usize> = winning.split_whitespace().map(|x| x.parse::<usize>().unwrap()).collect();
        let provided: HashSet<usize> = provided
            .split_whitespace()
            .map(|x| x.parse::<usize>()
            .unwrap())
            .collect();

        let count = winning.intersection(&provided).count();

        task1 += (1..=count).fold(0, |acc, _| {
            if acc == 0 {
                1
            } else {
                acc * 2
            }
        });

        let win_cards: Vec<usize> = (card_number+1..=card_number+count).collect();
        counter.inc(card_number);
        counter.inc_many(&win_cards);

        copies.inc_many(&win_cards);
        cache.insert(card_number, win_cards);
    }

    let lines_total = lines.count();

    for card in 1..lines_total {
        let iterations = copies.get(card);

        for _ in 0..iterations {
            let win_cards = cache.get(&card).unwrap();
            counter.inc_many(win_cards);
            copies.inc_many(win_cards);
            copies.dec(card);
        }
    }

    let task2: usize = counter.data
    .values()
    .sum();

    println!("[task1] sum: {}", task1);
    println!("[task2] sum: {}", task2);
}
