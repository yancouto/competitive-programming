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

fn rec_moves(es: &Vec<Vec<usize>>, u: usize, mut cur_h: usize, max_h: usize) -> usize {
    let mut min_moves = 0;
    if cur_h > max_h {
        min_moves += 1;
        cur_h = 1;
    }
    for v in es[u].iter().copied() {
        min_moves += rec_moves(es, v, cur_h + 1, max_h);
    }
    min_moves
}

fn rec_moves2(es: &Vec<Vec<usize>>, u: usize, child_of_root: bool, max_h: usize) -> (usize, usize) {
    let mut min_moves = 0;
    let mut h = 1;
    for v in es[u].iter().copied() {
        let (moves, vh) = rec_moves2(es, v, false, max_h);
        min_moves += moves;
        h = h.max(vh + 1);
    }
    if h == max_h && !child_of_root {
        // pick it
        (min_moves + 1, 0)
    } else {
        // do it higher up
        (min_moves, h)
    }
}

fn min_moves(es: &Vec<Vec<usize>>, max: usize) -> usize {
    //rec_moves(es, 0, 0, max)
    let mut ans = 0;
    for v in es[0].iter().copied() {
        ans += rec_moves2(es, v, true, max).0;
    }
    ans
}

fn run() {
    read_line!(n: usize, k: usize);
    let mut es: Vec<Vec<usize>> = vec![vec![]; n];
    let p: Vec<usize> = read_line_vec();
    for (i, p_i) in p.into_iter().enumerate() {
        es[p_i - 1].push(i + 1);
    }
    let (mut l, mut r) = (1, n);
    while l < r {
        let m = (l + r) / 2;
        if min_moves(&es, m) <= k {
            r = m;
        } else {
            l = m + 1;
        }
    }
    println!("{}", l)
}

fn main() {
    read_line!(t: u64);
    for _ in 0..t {
        run();
    }
}
