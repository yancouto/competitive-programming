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

fn main() {
    read_line!(t: u64);
    for _ in 0..t {
        read_line!(_n: usize);
        read_line!(s: String);
        let mut proto = vec![];
        let mut nx = vec![usize::MAX; 26];
        let mut pr = vec![usize::MAX; 26];
        let mut right: Vec<usize> = (0..26).collect();
        let mut left: Vec<usize> = (0..26).collect();
        let mut groups = 26;
        for c in s.chars() {
            let c = (c as usize) - b'a' as usize;
            if pr[c] == usize::MAX {
                for i in 0..26 {
                    if i != c && nx[i] == usize::MAX && (groups == 1 || left[i] != c) {
                        left[right[c]] = left[i];
                        right[left[i]] = right[c];
                        nx[i] = c;
                        pr[c] = i;
                        groups -= 1;
                        break;
                    }
                }
            }
            proto.push(pr[c]);
        }
        println!(
            "{}",
            String::from_utf8(
                proto
                    .into_iter()
                    .map(|x| x as u8 + b'a')
                    .collect::<Vec<_>>()
            )
            .unwrap()
        );
    }
}
