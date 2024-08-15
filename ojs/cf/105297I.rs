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
    read_line!(_n: i32);
    let v: Vec<i32> = read_line_vec();
    let mut only_ones = true;
    let mut only_even = true;
    for x in v {
        if x > 1 {
            only_ones = false;
        }
        if x % 2 != 0 {
            only_even = false;
        }
    }
    if only_ones || only_even {
        println!("1");
    } else {
        println!("2");
    }
}
