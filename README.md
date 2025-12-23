# Color Quantization K-Theory + CIF85 Integration

This repo is a minimal, concrete implementation of the color quantization
structure we discussed:

- **Lean 4**: algebraic projector/quantizer
  - Generic `Quantizer P embed`
  - K-level specialization `QuantizerK K`
  - Idempotent projector `P : ColorVec → ColorVec`
  - Residual `Φ = P - id` nilpotent on `Im(P)`

- **Rust**: K-level RGB projector
  - Continuous RGB `[0,1]^3` → integer palette `(r,g,b)` with
    `r,g,b ∈ {0,…,K}`, `(r,g,b) ≠ (0,0,0)`, `r+g+b ≤ K`
  - Back to `[0,1]^3` as `(r/K, g/K, b/K)`
  - Numerical idempotence check.

## Layout

- `lean/`
  - `ColorQuant.lean` – core definitions and theorems
  - `lakefile.lean`, `lean-toolchain` – project scaffolding

- `rust/`
  - `Cargo.toml` – cargo project
  - `src/lib.rs` – `QuantizerK` + projector
  - `src/bin/quantize_demo.rs` – small CLI demo

- `examples/`
  - `K3_K5_hues.md` – tabulated rational hue sets for K=3,4,5
