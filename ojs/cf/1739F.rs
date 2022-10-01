use std::collections::*;
fn get_line() -> String {
    let mut line = String::new();
    while line.is_empty() {
        std::io::stdin().read_line(&mut line).unwrap();
    }
    debug_assert_eq!(line.pop().unwrap(), '\n');
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

fn is_line(v: &mut Vec<usize>, g: &Vec<HashSet<usize>>, c: usize, prev: usize) -> bool {
    v.push(c);
    let mut first = true;
    for d in g[c].iter().copied() {
        if d == prev {
            continue;
        }
        if first == false {
            return false;
        }
        first = false;
        if !is_line(v, g, d, c) {
            return false;
        }
    }
    true
}

#[derive(Clone, Copy)]
struct Node {
    link: usize,
    val: i32,
    p: usize,
    child: [usize; 12],
}

struct Aho {
    node: [Node; 2100],
    cur: usize,
}

impl Aho {
    fn new() -> Self {
        Self {
            node: [Node {
                link: 0,
                val: 0,
                p: 0,
                child: [0; 12],
            }; 2100],
            cur: 0,
        }
    }

    fn next_node(&mut self) -> usize {
        self.cur += 1;
        self.cur
    }

    fn add(&mut self, cur: usize, key: &[usize], val: i32) {
        if let Some((c, rest)) = key.split_first() {
            let c = *c;
            if self.node[cur].child[c] == 0 {
                let mut p = cur;
                while p != 0 && self.node[p].child[c] == 0 {
                    p = self.node[p].p;
                }
                let new = self.next_node();
                self.node[new].link = self.node[p].child[c];
                self.node[new].p = cur;
                self.node[cur].child[c] = new;
            }
            self.add(self.node[cur].child[c], rest, val);
        } else {
            self.node[cur].val += val;
            return;
        }
    }
}

fn acc(aho: &mut Aho) {
    let mut d = VecDeque::new();
    d.push_back(0);
    while let Some(u) = d.pop_front() {
        aho.node[u].val += aho.node[aho.node[u].link].val;
        for i in 0..12 {
            let v = aho.node[u].child[i];
            if v != 0 {
                d.push_back(v);
            }
        }
    }
}

fn dp(memo: &mut [i32], aho: &Aho, bm: usize, u: usize) -> i32 {
    if bm == 0 {
        return 0;
    }
    let key = bm | (u << 12);
    if memo[key] != -1 {
        return memo[key];
    }
    let mut ans = 0;
    for i in 0..12 {
        if ((bm >> i) & 1) == 1 {
            let mut v = u;
            while v != 0 && aho.node[v].child[i] == 0 {
                v = aho.node[v].link;
            }
            v = aho.node[v].child[i];
            ans = ans.max(dp(memo, aho, bm ^ (1 << i), v) + aho.node[v].val);
        }
    }
    memo[key] = ans;
    ans
}
fn build(memo: &mut [i32], aho: &Aho, bm: usize, u: usize) {
    if bm == 0 {
        println!("");
        return;
    }
    let ans = dp(memo, aho, bm, u);
    for i in 0..12 {
        if ((bm >> i) & 1) == 1 {
            let mut v = u;
            while v != 0 && aho.node[v].child[i] == 0 {
                v = aho.node[v].link;
            }
            v = aho.node[v].child[i];
            if ans == dp(memo, aho, bm ^ (1 << i), v) + aho.node[v].val {
                print!("{}", ((i as u8) + b'a') as char);
                build(memo, aho, bm ^ (1 << i), v);
                break;
            }
        }
    }
}

fn main() {
    read_line!(n: usize);
    let mut aho = Aho::new();
    for _ in 0..n {
        read_line!(ci: i32, s: String);
        let mut g = vec![HashSet::new(); 12];
        let s: Vec<u8> = s.into();
        let mut prev = (s[0] - b'a') as usize;
        for c in &s[1..] {
            let c = (c - b'a') as usize;
            g[prev].insert(c);
            g[c].insert(prev);
            prev = c;
        }
        let c1 = (0..12).find(|i| g[*i].len() == 1);
        if let Some(c1) = c1 {
            let mut v = vec![];
            if is_line(&mut v, &g, c1, 255) {
                aho.add(0, &v, ci);
                v.reverse();
                aho.add(0, &v, ci);
            }
        }
    }
    acc(&mut aho);
    let mut memo = vec![-1; (1 << 12) * 1002];
    build(&mut memo, &aho, (1 << 12) - 1, 0);
}
