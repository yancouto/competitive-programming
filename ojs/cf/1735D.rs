use std::collections::*;
fn get_line() -> String {
    let mut line = String::new();
    while line.is_empty() {
        std::io::stdin().read_line(&mut line).unwrap();
    }
    line
}

macro_rules! read_line {
    ( $($name:ident : $typ:ty),+ ) => {
        let line = get_line();
        let mut tokens = line.split_ascii_whitespace();
        $(
            let $name: $typ = tokens.next().unwrap().parse().unwrap();
        )+
        debug_assert_eq!(tokens.next(), None);
    };
}

fn read_line_vec<T>() -> Vec<T>
where
    T: std::str::FromStr,
    T::Err: std::fmt::Debug,
{
    get_line()
        .split_ascii_whitespace()
        .map(|s| s.parse::<T>())
        .collect::<Result<Vec<T>, _>>()
        .unwrap()
}

fn main() {
    read_line!(n: usize, k: usize);
    let cards: Vec<Vec<u8>> = (0..n).map(|_| read_line_vec::<u8>()).collect();
    let mut rev_map: BTreeMap<Vec<u8>, usize> = BTreeMap::new();
    for (idx, card) in cards.iter().cloned().enumerate() {
        rev_map.insert(card, idx);
    }
    let mut good_pairs = vec![0; n];
    for i in 0..n {
        for j in (i + 1..n) {
            let wanted_cards: Vec<u8> = cards[i]
                .iter()
                .copied()
                .zip(cards[j].iter().copied())
                .map(|(a, b)| if a == b { a } else { 3 - a - b })
                .collect();
            if let Some(idx) = rev_map.get(&wanted_cards) {
                good_pairs[*idx] += 1;
            }
        }
    }
    let mut ans = 0;
    for g in good_pairs {
        ans += (g * (g - 1)) / 2;
    }
    println!("{}", ans);
}
