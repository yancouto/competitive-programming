use std::collections::*;

fn get_line() -> String {
    let mut line = String::new();
    while line.is_empty() {
        std::io::stdin().read_line(&mut line).unwrap();
    }
    line
}

trait Mod {
    fn modp(&self) -> Self;
}

impl Mod for i64 {
    fn modp(&self) -> i64 {
        self % 998244353
    }
}

struct Dp {
    n: Vec<u8>,
    memo: HashMap<(usize, u8, bool, bool, bool, bool, bool, bool), i64>,
}

impl Dp {
    fn solve_impl(
        &mut self,
        i: usize,
        carry: u8,
        eqxy: bool,
        eqxz: bool,
        eqyz: bool,
        eqa: bool,
        eqb: bool,
        eqc: bool,
    ) -> i64 {
        if i >= self.n.len() {
            return if carry == 0 && !eq { 1 } else { 0 };
        }
        let mut count: i64 = 0;
        let ni: u8 = self.n[i] - b'0';
        for bin in 0..16 {
            let next_carry = bin & 1;
            let a = (bin >> 1) & 1;
            let b = (bin >> 2) & 1;
            let c = (bin >> 3) & 1;
            if (eqa && a > ni) || (eqb && b > ni) || (eqc && c > ni) {
                continue;
            }
            let mut xy = (a ^ b) + (a ^ c) + next_carry;
            let z = b ^ c;
            if carry == 1 {
                if xy < 2 {
                    continue;
                }
                xy -= 2;
            } else {
                if xy >= 2 {
                    continue;
                }
            }
            assert!(xy <= 1);
            if eq && xy > z {
                continue;
            }
            count = (count
                + self.solve(
                    i + 1,
                    next_carry,
                    eq && xy == z,
                    eqa && a == ni,
                    eqb && b == ni,
                    eqc && c == ni,
                ))
            .modp();
        }
        count
    }

    fn solve(
        &mut self,
        i: usize,
        carry: u8,
        eqxy: bool,
        eqxz: bool,
        eqyz: bool,
        eqa: bool,
        eqb: bool,
        eqc: bool,
    ) -> i64 {
        let key = (i, carry, eqxy, eqxz, eqyz, eqa, eqb, eqc);
        if let Some(ans) = self.memo.get(&key) {
            return *ans;
        }
        let ans = self.solve_impl(i, carry, eqxy, eqxz, eqyz, eqa, eqb, eqc);
        self.memo.insert(key, ans);
        ans
    }
}

fn main() {
    let n = get_line().trim().to_string();
    let mut dp = Dp {
        n: n.into(),
        memo: HashMap::new(),
    };
    let x = dp.solve(0, 0, true, true, true, true) + dp.solve(0, 1, true, true, true, true);
    println!("{}", x.modp());
}
