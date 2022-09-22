use std::io::Read;
use std::collections::*;
use std::str::FromStr;

fn parse<'a, T: FromStr>(inp: &mut impl Iterator<Item=&'a str>) -> T where T::Err: std::fmt::Debug {
    inp.next().unwrap().parse().unwrap()
}

fn main() {
    let mut stdin = String::new();
    std::io::stdin().lock().read_to_string(&mut stdin).unwrap();
    let inp = &mut stdin.split_ascii_whitespace();
    let t: usize = parse(inp);
    for _ in 0..t {
        let (n, q): (usize, usize) = (parse(inp), parse(inp));
        let mut a: Vec<u64> = Vec::new();
        a.resize_with(n, || parse(inp));
        let mut sums: Vec<Vec<u64>> = vec![vec![]; n];
        let mut all: BTreeMap<u64, usize> = BTreeMap::new();
        let mut divs: Vec<usize> = vec![];
        'outer: for i in (1..n).rev() {
            if n % i == 0 {
                for j in &divs {
                    if (*j) % i == 0 {
                        continue 'outer;
                    }
                }
                divs.push(i);
                for j in 0..i {
                    let mut sum = 0u64;
                    for k in 0..(n/i) {
                        sum += a[j + k * i];
                    }
                    sum = sum * (i as u64);
                    *all.entry(sum).or_insert(0) += 1;
                    sums[i].push(sum);
                }
            }
        }
        println!("{}", all.iter().rev().next().unwrap().0);
        for _ in 0..q {
            let (p, x): (usize, u64) = (parse::<usize>(inp) - 1, parse(inp));
            for i in divs.iter().copied() {
                let sum = &mut sums[i][p % i];
                let mut entry = match all.entry(*sum) {
                    std::collections::btree_map::Entry::Vacant(_) => panic!(),
                    std::collections::btree_map::Entry::Occupied(oc) => oc,
                };
                if *entry.get() == 1 {
                    entry.remove();
                } else {
                    *entry.get_mut() -= 1;
                }
                *sum -= a[p] * (i as u64);
                *sum += x * (i as u64);
                *all.entry(*sum).or_insert(0) += 1;
            }
            a[p] = x;
            println!("{}", all.iter().rev().next().unwrap().0);
        }
    }
    assert_eq!(inp.next(), None);
}