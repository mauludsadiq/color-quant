use color_quant_k::RGB;

// Standard RGB → HSV, hue in [0,360)
fn rgb_to_hsv(rgb: RGB) -> (f32, f32, f32) {
    let r = rgb[0];
    let g = rgb[1];
    let b = rgb[2];

    let max = r.max(g.max(b));
    let min = r.min(g.min(b));
    let c = max - min;

    let mut h_deg = 0.0_f32;
    if c == 0.0 {
        h_deg = 0.0; // undefined hue → treat as 0
    } else if max == r {
        let mut h = (g - b) / c;
        if h < 0.0 {
            h += 6.0;
        }
        h_deg = 60.0 * h;
    } else if max == g {
        let h = ((b - r) / c) + 2.0;
        h_deg = 60.0 * h;
    } else {
        let h = ((r - g) / c) + 4.0;
        h_deg = 60.0 * h;
    }

    if h_deg < 0.0 {
        h_deg += 360.0;
    } else if h_deg >= 360.0 {
        h_deg -= 360.0;
    }

    let s = if max == 0.0 { 0.0 } else { c / max };
    let v = max;

    (h_deg, s, v)
}

// Simple sector naming for hue
fn name_hue(h: f32) -> &'static str {
    let h = ((h % 360.0) + 360.0) % 360.0;

    if h >= 345.0 || h < 15.0 { return "red"; }
    if h < 30.0 { return "red-orange"; }
    if h < 50.0 { return "orange"; }
    if h < 70.0 { return "yellow"; }
    if h < 100.0 { return "yellow-green"; }
    if h < 140.0 { return "green"; }
    if h < 170.0 { return "blue-green"; }
    if h < 190.0 { return "cyan"; }
    if h < 220.0 { return "blue-cyan"; }
    if h < 250.0 { return "blue"; }
    if h < 290.0 { return "blue-magenta"; }
    if h < 320.0 { return "magenta"; }
    if h < 345.0 { return "red-magenta"; }
    "red"
}

fn main() {
    let k: f32 = 5.0;
    let mut entries: Vec<(f32, u8, u8, u8, RGB, f32, f32)> = Vec::new();

    for r in 0..=5 {
        for g in 0..=5 - r {
            let b = 5 - r - g;

            let rgb: RGB = [
                r as f32 / k,
                g as f32 / k,
                b as f32 / k,
            ];
            let (h, s, v) = rgb_to_hsv(rgb);
            entries.push((h, r as u8, g as u8, b as u8, rgb, s, v));
        }
    }

    entries.sort_by(|a, b| a.0.partial_cmp(&b.0).unwrap());

    println!("K = 5 simplex palette (r+g+b = 5):");
    println!("r g b    rgb                hue(°)   sat     val     name");
    println!("---------------------------------------------------------------");

    for (h, r, g, b, rgb, s, v) in entries {
        let name = name_hue(h);
        println!(
            "{} {} {}   [{:.2}, {:.2}, {:.2}]   {:6.1}  {:6.3}  {:6.3}   {}",
            r,
            g,
            b,
            rgb[0],
            rgb[1],
            rgb[2],
            h,
            s,
            v,
            name
        );
    }
}
