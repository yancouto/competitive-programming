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

fn go() {
    read_line!(n: i64, m: i64);

    let di = [1, 1, 2, 2, -1, -1, -2, -2];
    let dj = [2, -2, 1, -1, 2, -2, 1, -1];
    for i in 0..n {
        for j in 0..m {
            if !(0..di.len()).any(|k| {
                let ni = i + di[k];
                let nj = j + dj[k];
                ni >= 0 && ni < n && nj >= 0 && nj < m
            }) {
                println!("{} {}", i + 1, j + 1);
                return;
            }
        }
    }
    println!("1 1");
}

fn main() {
    read_line!(t: u64);
    for _ in 0..t {
        go();
    }
}
