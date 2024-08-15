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
        read_line!(l: i32, r: i32);
        read_line!(l2: i32, r2: i32);
        if l > l2 || (l == l2 && r > r2) {
            std::mem::swap(&mut l, &mut l2);
            std::mem::swap(&mut r, &mut r2);
        }
        if r < l2 {
            println!("1");
            continue;
        }
        let mut ans = r.min(r2) - l2;
        if l < l2 {
            ans += 1;
        }
        if r != r2 {
            ans += 1;
        }
        println!("{}", ans);
    }
}
