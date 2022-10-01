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

fn solve() {
    read_line!(n: usize);
    let d = read_line_vec();
    let mut a = vec![0; n];
    a[0] = d[0];
    for i in 1..n {
        if d[i] == 0 {
            a[i] = a[i - 1];
        } else if d[i] > a[i - 1] {
            a[i] = a[i - 1] + d[i];
        } else {
            println!("-1");
            return;
        }
    }
    for i in 0..n {
        print!("{}{}", a[i], if i == n - 1 { '\n' } else { ' ' });
    }
}

fn main() {
    read_line!(t: u64);
    for _ in 0..t {
        solve();
    }
}
