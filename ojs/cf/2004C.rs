fn get_line() -> String {
    let mut line = String::new();
    while line.is_empty() {
        std::io::stdin().read_line(&mut line).unwrap();
    }
    line.pop().unwrap();
    line
}

macro_rules! read_line {
    ( $($name:ident : $typ:ty),+ ) => {
        let line = get_line();
        let mut tokens = line.split_ascii_whitespace();
        $(
            let mut $name: $typ = tokens.next().unwrap().parse().unwrap();
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
    read_line!(t: i32);
    for _ in 0..t {
        read_line!(n: usize, k: i64);
        let mut a = read_line_vec::<i64>();
        a.sort_by_key(|x| -x);
        let mut score = 0i64;
        for i in 0..n {
            if 2 * i < n {
                score += a[2 * i];
            }
            if 2 * i + 1 >= n {
                break;
            }
            score -= a[2 * i + 1];
            let inc = (a[2 * i] - a[2 * i + 1]).min(k);
            k -= inc;
            score -= inc;
        }
        println!("{}", score);
    }
}
