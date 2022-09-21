use std::io::BufRead;
use std::collections::*;

fn main() {
    let mut lines = std::io::stdin().lock().lines();
    let t: usize = lines.next().unwrap().unwrap().parse().unwrap();
    for _ in 0..t {
        let n: usize = lines.next().unwrap().unwrap().parse().unwrap();
        let arr: Vec<usize> = lines.next().unwrap().unwrap().split_whitespace().map(|s| s.parse::<usize>().unwrap()).collect::<Vec<_>>();
        let mut next: HashMap<usize, usize> = HashMap::new();
        let mut ans = vec![0usize; n + 2];
        let mut tot = 0;
        next.insert(0, n - 1);
        for i in (0..n).rev() {
            ans[i] = ans[i + 1] + (if arr[i] == 0 { 0 } else { 1 });
            tot = tot ^ arr[i];
            if let Some(j) = next.get(&tot) {
                ans[i] = ans[i].min((j - i) + ans[j + 1]);
            }
            if i > 0 {
                next.insert(tot, i - 1);
            }
        }
        println!("{}", ans[0]);
    }
}