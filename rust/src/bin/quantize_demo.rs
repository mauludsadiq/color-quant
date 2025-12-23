
use std::env;
use color_quant_k::{QuantizerK, RGB};

fn main() {
    let args: Vec<String> = env::args().collect();
    let k: u8 = if args.len() > 1 {
        args[1].parse().expect("K must be an integer")
    } else {
        5
    };

    let q = QuantizerK::new(k);
    println!("QuantizerK with K = {}", k);

    let ok = q.check_idempotence(10_000, 1e-6);
    println!("Idempotence check: {}", ok);

    // Simple demo on a few hand-picked colors
    let samples: [RGB; 5] = [
        [1.0, 0.0, 0.0],
        [0.0, 1.0, 0.0],
        [0.0, 0.0, 1.0],
        [0.8, 0.3, 0.1],
        [0.2, 0.7, 0.5],
    ];

    for rgb in samples {
        let p = q.project_rgb(rgb);
        println!("rgb={:?} -> projected={:?}", rgb, p);
    }
}
