use std::collections::BTreeMap;
use std::collections::BTreeSet;
use std::convert::TryInto;

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

fn gcd(a: i32, b: i32) -> i32 {
    if a > b {
        gcd(b, a)
    } else if a == 0 {
        b
    } else {
        gcd(b % a, a)
    }
}

const MAX: i32 = 1000_000_3;

fn main() {
    let mut cr = [0u8; MAX as usize];
    let mut mex = [0i32; MAX as usize];
    mex[1] = 1;
    let mut count = 0;
    for i in 2..MAX {
        if cr[i as usize] == 1 {
            continue;
        }
        mex[i as usize] = count;
        count += 1;
        if i == 2 {
            count += 1;
        }
        if MAX / i < i {
            continue;
        }
        let mut j = i * i;
        while j < MAX {
            if cr[j as usize] == 0 {
                cr[j as usize] = 1;
                mex[j as usize] = mex[i as usize];
            }
            j += i;
        }
    }
    read_line!(t: i32);
    for _ in 0..t {
        read_line!(n: usize);
        let a = read_line_vec::<i32>();
        let mut val = 0;
        for ai in a {
            val = val ^ mex[ai as usize];
        }
        if val != 0 {
            println!("Alice");
        } else {
            println!("Bob");
        }
    }
}
