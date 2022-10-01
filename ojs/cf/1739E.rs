use std::collections::*;
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

struct Dp {
    hall: [Vec<u8>; 2],
    memo: BTreeMap<(usize, usize, bool), i32>,
}

impl Dp {
    fn solve(&mut self, i: usize, j: usize, op_clean: bool) -> i32 {
        if j == self.hall[0].len() - 1 {
            return if self.hall[1 - i][j] == b'1' { 1 } else { 0 };
        }
        if let Some(ans) = self.memo.get(&(i, j, op_clean)) {
            return *ans;
        }
        let dirty_right = self.hall[i][j + 1] == b'1';
        let dirty_op = (self.hall[1 - i][j] == b'1') && !op_clean;
        let ret;
        if !dirty_right && !dirty_op {
            ret = self.solve(i, j + 1, false);
        } else if dirty_right && !dirty_op {
            // clean for free, no confusion
            ret = self.solve(i, j + 1, false) + 1;
        } else if !dirty_right && dirty_op {
            // either go to other side and clean,
            // or use a move
            ret = (self.solve(1 - i, j, true) + 1).max(self.solve(i, j + 1, false));
        } else {
            // Need to manually clean one of them or robot gets confused
            // need to move twice sometimes
            ret = (self.solve(i, j + 1, false) + 1).max(
                self.solve(1 - i, j + 1, true)
                    + 1
                    + if self.hall[1 - i][j + 1] == b'1' {
                        1
                    } else {
                        0
                    },
            );
        }
        self.memo.insert((i, j, op_clean), ret);
        ret
    }
}

fn main() {
    read_line!(n: usize);
    let up = get_line();
    let down = get_line();
    let hall: [Vec<u8>; 2] = [up.into(), down.into()];
    let mut dp = Dp {
        hall,
        memo: BTreeMap::new(),
    };
    println!("{}", dp.solve(0, 0, false));
}
