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

fn can(a: &[i64], b: &[i64], d: i64) -> Option<(Vec<i64>, i64, i64)> {
    let mut hb = HashMap::new();
    for bi in b {
        *hb.entry(*bi).or_insert(0) += 1;
    }
    let mut ans = vec![];
    // dec order
    for ai in a.iter().copied() {
        let bj = hb.entry(ai + d).or_insert(0);
        if *bj > 0 {
            ans.push(-ai);
            *bj -= 1;
            continue;
        }
        let bj = hb.entry((ai - d).abs()).or_insert(0);
        if *bj <= 0 {
            return None;
        }
        ans.push(ai);
        *bj -= 1;
    }
    ans.sort();
    let min = ans[0].min(0);
    for x in &mut ans {
        *x -= min;
    }
    Some((ans, -min, d - min))
}

fn solve() {
    read_line!(n: usize);
    let mut a: Vec<i64> = read_line_vec();
    a.sort();
    a.reverse();
    let b: Vec<i64> = read_line_vec();
    let mut possible_d: Vec<i64> = (0..n)
        .flat_map(|i| [a[0] + b[i], (a[0] - b[i]).abs()])
        .collect();
    possible_d.sort();

    for d in possible_d {
        if let Some((v, p1, p2)) = can(&a, &b, d) {
            println!("YES");
            for x in v {
                print!("{} ", x);
            }
            println!("\n{} {}", p1, p2);
            return;
        }
    }
    println!("NO");
}

fn main() {
    read_line!(t: u64);
    for _ in 0..t {
        solve();
    }
}
