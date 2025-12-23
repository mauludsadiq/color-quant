
use rand::Rng;

/// Simple RGB color in integer palette space.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct Color {
    pub r: u8,
    pub g: u8,
    pub b: u8,
}

/// Continuous RGB in [0,1]^3.
pub type RGB = [f32; 3];

/// K-level quantizer.
///
/// - Maps continuous `RGB` in [0,1]^3 to integer triples (r,g,b)
///   with 0 ≤ r,g,b ≤ K, (r,g,b) ≠ (0,0,0), and r+g+b ≤ K.
/// - Then maps back to `[0,1]^3` as `(r/K, g/K, b/K)`.
#[derive(Debug, Clone, Copy)]
pub struct QuantizerK {
    pub k: u8,
}

impl QuantizerK {
    pub fn new(k: u8) -> Self {
        assert!(k > 0, "K must be positive");
        Self { k }
    }

    /// Quantize a continuous RGB to a discrete palette element.
    pub fn quantize(&self, rgb: RGB) -> Color {
        let k = self.k as f32;

        // Clamp input to [0,1]
        let clamp01 = |x: f32| x.max(0.0).min(1.0);
        let r = clamp01(rgb[0]);
        let g = clamp01(rgb[1]);
        let b = clamp01(rgb[2]);

        // Initial naive scaling to [0,K]
        let mut ri = (r * k).round() as i32;
        let mut gi = (g * k).round() as i32;
        let mut bi = (b * k).round() as i32;

        // Clamp to [0,K]
        let maxv = self.k as i32;
        ri = ri.clamp(0, maxv);
        gi = gi.clamp(0, maxv);
        bi = bi.clamp(0, maxv);

        // Ensure we are not at (0,0,0): enforce at least one channel is 1.
        if ri == 0 && gi == 0 && bi == 0 {
            ri = 1;
        }

        // Enforce simplex constraint r+g+b ≤ K by proportional rescaling if needed.
        let mut sum = ri + gi + bi;
        if sum > maxv {
            // Compute floating scale and rescale all channels.
            let scale = maxv as f32 / sum as f32;
            ri = ((ri as f32) * scale).round() as i32;
            gi = ((gi as f32) * scale).round() as i32;
            bi = ((bi as f32) * scale).round() as i32;

            // Recompute sum; if still >K due to rounding, trim largest channels.
            sum = ri + gi + bi;
            if sum > maxv {
                while sum > maxv {
                    if ri >= gi && ri >= bi && ri > 0 {
                        ri -= 1;
                    } else if gi >= ri && gi >= bi && gi > 0 {
                        gi -= 1;
                    } else if bi > 0 {
                        bi -= 1;
                    }
                    sum = ri + gi + bi;
                }
            }
        }

        Color {
            r: ri as u8,
            g: gi as u8,
            b: bi as u8,
        }
    }

    /// Project a continuous RGB to the K-level palette and back to [0,1]^3.
    pub fn project_rgb(&self, rgb: RGB) -> RGB {
        let c = self.quantize(rgb);
        let k = self.k as f32;
        [c.r as f32 / k, c.g as f32 / k, c.b as f32 / k]
    }

    /// Numerical check of idempotence:
    /// project(project(x)) ≈ project(x) up to a small epsilon.
    pub fn check_idempotence(&self, n_samples: usize, eps: f32) -> bool {
        let mut rng = rand::thread_rng();
        for _ in 0..n_samples {
            let rgb = [rng.gen::<f32>(), rng.gen::<f32>(), rng.gen::<f32>()];
            let p1 = self.project_rgb(rgb);
            let p2 = self.project_rgb(p1);

            for i in 0..3 {
                if (p1[i] - p2[i]).abs() > eps {
                    eprintln!("Idempotence violation: p1={:?}, p2={:?}", p1, p2);
                    return false;
                }
            }
        }
        true
    }
}
