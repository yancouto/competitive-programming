use std::collections::BTreeMap;
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

#[derive(Debug, PartialEq, Eq, PartialOrd, Ord, Clone, Copy)]
struct Colors {
    a: char,
    b: char,
}
impl std::str::FromStr for Colors {
    type Err = ();
    fn from_str(s: &str) -> Result<Self, ()> {
        if let Ok([a, b]) = TryInto::<[char; 2]>::try_into(s.chars().collect::<Vec<_>>()) {
            Ok(Colors { a, b })
        } else {
            Err(())
        }
    }
}
impl Colors {
    fn intersects(&self, o: &Self) -> bool {
        self.a == o.a || self.a == o.b || self.b == o.a || self.b == o.b
    }
}

fn main() {
    let all: [Colors; 6] = ["BG", "BR", "BY", "GR", "GY", "RY"].map(|x| x.parse().unwrap());
    read_line!(t: i32);
    for _ in 0..t {
        read_line!(n: usize, q: usize);
        let a = read_line_vec::<Colors>();
        let mut next_left: BTreeMap<Colors, Vec<i32>> = BTreeMap::new();
        let mut next_right: BTreeMap<Colors, Vec<i32>> = BTreeMap::new();
        for cs in &all {
            let mut cur: i32 = -11234567;
            next_left.insert(
                *cs,
                a.iter()
                    .enumerate()
                    .map(|(i, c)| {
                        if c == cs {
                            cur = i as i32;
                            cur
                        } else {
                            cur
                        }
                    })
                    .collect(),
            );
            cur = 11234567;
            next_right.insert(
                *cs,
                a.iter()
                    .enumerate()
                    .rev()
                    .map(|(i, c)| {
                        if c == cs {
                            cur = i as i32;
                            cur
                        } else {
                            cur
                        }
                    })
                    .collect::<Vec<_>>()
                    .into_iter()
                    .rev()
                    .collect(),
            );
        }
        for _ in 0..q {
            read_line!(i: i32, j: i32);
            i -= 1;
            j -= 1;
            if i > j {
                std::mem::swap(&mut i, &mut j);
            }
            let (ci, cj) = (a[i as usize], a[j as usize]);
            if ci.intersects(&cj) {
                println!("{}", j - i);
            } else {
                let mut ans = 11234567;
                for c in all.iter().filter(|c| **c != ci && **c != cj) {
                    ans = ans.min(i - 2 * next_left.get(c).unwrap()[i as usize] + j);
                    let nr = next_right.get(c).unwrap()[i as usize];
                    ans = ans.min((nr - i) + (j - nr).abs());
                }
                if ans > 10000000 {
                    println!("-1");
                } else {
                    println!("{}", ans);
                }
            }
        }
    }
}
