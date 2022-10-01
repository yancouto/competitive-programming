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

trait Mod {
    fn modp(&self) -> Self;
}

impl Mod for i64 {
    fn modp(&self) -> i64 {
        self % 998244353
    }
}

fn fat(n: usize) -> i64 {
    static mut fs: [i64; 70] = [-1; 70];
    if n == 0 {
        return 1;
    }
    unsafe {
        if fs[n] == -1 {
            fs[n] = (fat(n - 1) * (n as i64)).modp();
        }
        fs[n]
    }
}

fn choose(n: usize, p: usize) -> i64 {
    static mut memo: [[i64; 70]; 70] = [[-1; 70]; 70];
    if p < 0 || p > n {
        return 0;
    }
    if p == 0 || p == n {
        return 1;
    }
    unsafe {
        if memo[n][p] == -1 {
            memo[n][p] = (choose(n - 1, p - 1) + choose(n - 1, p)).modp();
        }
        memo[n][p]
    }
}

fn solve(n: usize) -> (i64, i64, i64) {
    if n == 2 {
        return (1, 0, 1);
    }
    if n == 0 {
        return (0, 0, 1);
    }
    let (mut a, mut b, mut draw) = (0, 0, 0);
    // n goes to A, A wins
    a = (a + choose(n - 1, n / 2)).modp();
    // n goes to B, n - 1 goes to B, B wins
    b = (b + choose(n - 2, (n / 2))).modp();
    // n goes to B, n - 1 goes to A, recurse
    let (na, nb, ndraw) = solve(n - 2);
    a = (a + nb).modp();
    b = (b + na).modp();
    draw = (draw + ndraw).modp();

    (a, b, draw)
}

fn run() {
    read_line!(n: usize);
    let (a, b, draw) = solve(n);
    println!("{} {} {}", a, b, draw);
}

fn main() {
    read_line!(t: u64);
    for _ in 0..t {
        run();
    }
}
