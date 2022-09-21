use std::io::BufRead;
use std::collections::BTreeMap;

fn do_partit_impl(fibs: &Vec<usize>, mut val: usize) -> Option<Vec<usize>> {
    let mut ans = vec![];
    for j in (1..fibs.len()).rev() {
        if fibs[j] <= val {
            val -= fibs[j];
            if let Some(prev) = ans.last() {
                if *prev == j + 1 {
                    return None;
                }
            }
            ans.push(j);
        }
    }
    debug_assert_eq!(val, 0);
    Some(ans)
}

fn do_partit(memo: &mut BTreeMap<usize, Option<Vec<usize>>>, fibs: &Vec<usize>, val: usize) -> Option<Vec<usize>> {
    memo.entry(val).or_insert_with(|| do_partit_impl(fibs, val)).clone()
}

fn try_with(memo: &mut BTreeMap<usize, Option<Vec<usize>>>, fibs: &Vec<usize>, arr: &Vec<usize>, first_0: usize) -> bool {
    let mut used: Vec<bool> = vec![false; fibs.len()];
    for i in 0..arr.len() {
        let val = arr[i] - if i == first_0 { 1 } else { 0 };
        let mut p = if let Some(p) = do_partit(memo, fibs, val) {
            p
        } else {
            return false;
        };
        if i == first_0 {
            if matches!(p.last(), Some(1)) {
                return false;
            }
            p.push(0);
        }
        for val in p {
            if used[val] {
                return false;
            }
            used[val] = true;
        }
    }
    used.into_iter().skip_while(|b| *b).all(|b| !b)
}

fn main() {
    let mut lines = std::io::stdin().lock().lines();
    let t: usize = lines.next().unwrap().unwrap().parse().unwrap();
    let mut fibs = vec![1, 1];
    while *fibs.last().unwrap() <= 1000000000 {
        let n = fibs.len();
        fibs.push(fibs[n - 1] + fibs[n - 2]);
    }
    let mut memo = BTreeMap::new();
    for _ in 0..t {
        let k: usize = lines.next().unwrap().unwrap().parse().unwrap();
        let arr: Vec<usize> = lines.next().unwrap().unwrap().split_whitespace().map(|s| s.parse::<usize>().unwrap()).collect::<Vec<_>>();
        let mut ok = false;
        for i in 0..k {
            if try_with(&mut memo, &fibs, &arr, i) {
                ok = true;
                break;
            }
        }
        if ok {
            println!("YES");
        } else {
            println!("NO");
        }
    }
}