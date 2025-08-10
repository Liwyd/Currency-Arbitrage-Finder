use std::f64;
use std::io::{self, Read};

#[derive(Clone)]
struct Edge {
    u: usize,
    v: usize,
    w: f64,
}

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_whitespace();

    let n: usize = iter.next().unwrap().parse().unwrap();
    let m: usize = iter.next().unwrap().parse().unwrap();

    let mut edges = Vec::with_capacity(m);

    for _ in 0..m {
        let u: usize = iter.next().unwrap().parse().unwrap();
        let v: usize = iter.next().unwrap().parse().unwrap();
        let rate: f64 = iter.next().unwrap().parse().unwrap();
        edges.push(Edge { u, v, w: -rate.ln() });
    }

    let mut dist = vec![f64::INFINITY; n];
    dist[0] = 0.0;

    for _ in 0..n - 1 {
        let mut updated = false;
        for e in &edges {
            if dist[e.u] + e.w < dist[e.v] {
                dist[e.v] = dist[e.u] + e.w;
                updated = true;
            }
        }
        if !updated {
            break;
        }
    }

    let arbitrage = edges.iter().any(|e| dist[e.u] + e.w < dist[e.v]);

    if arbitrage {
        println!("Arbitrage opportunity detected");
    } else {
        println!("No arbitrage opportunity");
    }
}
