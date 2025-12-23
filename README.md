## Repository Overview

This repository implements a **K-level RGB color quantization kernel** together with a **formal proof kernel** for its collapse properties.

* The **Rust crate** `color_quant_k` provides an operational quantizer `QuantizerK` acting on continuous RGB values and several binaries for enumerating and applying a K=5 palette.
* The **Lean 4 library** `ColorQuant` provides an abstract notion of a quantizer, proves generic collapse properties (idempotence and zero residual on the image), and instantiates these for a finite K=5 color lattice and a K=5 simplex palette. 

The result is a small but complete system where:

* Rust is the **execution engine** (acting on bytes / images).
* Lean is the **proof kernel** (acting on symbolic types and propositions).

---

## Lean Component: Formal Collapse Kernel

### 1. Abstract Quantizer and Collapse Properties

The Lean side is organized around a general `Quantizer` structure: 

```lean
structure Quantizer (α : Type u) where
  Q : α → α
  palette : α → Prop
  closed : ∀ x, palette (Q x)
  fixed : ∀ {x}, palette x → Q x = x
```

From this definition, the library proves two central properties:

1. **Idempotence of the projector**:

   ```lean
   theorem idempotent (q : Quantizer α) (x : α) :
     q.Q (q.Q x) = q.Q x :=
     q.fixed (q.closed x)
   ```

2. **Zero residual on the image**, via a residual operator `Phi` and predicate `isZeroPair`:

   ```lean
   def Phi (q : Quantizer α) (x : α) : α × α := (q.Q x, x)
   def isZeroPair (p : α × α) : Prop := p.1 = p.2

   theorem phi_zero_on_image (q : Quantizer α) (x : α) :
     isZeroPair (Phi q (q.Q x)) := by
     unfold isZeroPair Phi
     apply idempotent
   ```

These theorems capture, in a type-generic way, the idea that:

* Applying `Q` twice is the same as applying it once (projector).
* On already-quantized points (the image of `Q`), the residual `(Q x, x)` collapses to a zero pair.

### 2. K=5 Color Lattice

The file `lean/ColorQuant.lean` then specializes the abstract quantizer to a finite K=5 RGB lattice. 

* **Unbounded color vectors**:

  ```lean
  structure ColorVec where
    r : Nat
    g : Nat
    b : Nat
  ```

* **Bounded K=5 colors**:

  ```lean
  structure Color5 where
    r : Nat
    g : Nat
    b : Nat
    hr : r ≤ 5
    hg : g ≤ 5
    hb : b ≤ 5
  ```

* **Clamping operator** and lemma:

  ```lean
  def clamp5 (n : Nat) : Nat :=
    if n ≤ 5 then n else 5

  theorem clamp5_le (n : Nat) : clamp5 n ≤ 5 := ...
  ```

* **Lifting unbounded colors into the K=5 cube**:

  ```lean
  def liftK5 (c : ColorVec) : Color5 :=
    let r5 := clamp5 c.r
    let g5 := clamp5 c.g
    let b5 := clamp5 c.b
    have hr : r5 ≤ 5 := clamp5_le c.r
    have hg : g5 ≤ 5 := clamp5_le c.g
    have hb : b5 ≤ 5 := clamp5_le c.b
    { r := r5, g := g5, b := b5, hr := hr, hg := hg, hb := hb }
  ```

### 3. Trivial K=5 Quantizer and Image-Level Properties

A first, cube-level quantizer is defined as the identity on `Color5`:

```lean
def Q5 (c : Color5) : Color5 := c
def palette5 (_c : Color5) : Prop := True
```

With corresponding closure/fixedness lemmas:

```lean
theorem Q5_closed : ∀ c : Color5, palette5 (Q5 c) := ...
theorem Q5_fixed  : ∀ {c : Color5}, palette5 c → Q5 c = c := ...
```

Bundled as a `Quantizer Color5`:

```lean
def Quantizer5 : Quantizer Color5 :=
  { Q := Q5
    palette := palette5
    closed := Q5_closed
    fixed := Q5_fixed }
```

From which the general theorems specialize:

```lean
theorem Quantizer5_projector_idem (c : Color5) :
  Quantizer5.Q (Quantizer5.Q c) = Quantizer5.Q c :=
  Quantizer.idempotent Quantizer5 c

theorem Quantizer5_phi_zero_on_image (c : Color5) :
  Quantizer.isZeroPair (Quantizer.Phi Quantizer5 (Quantizer5.Q c)) :=
  Quantizer.phi_zero_on_image Quantizer5 c
```

And a bridge result linking arbitrary integer colors with K=5:

```lean
theorem Quantizer5_on_liftK5_fixed (c : ColorVec) :
  Quantizer5.Q (liftK5 c) = liftK5 c := by
  rfl
```

This shows that once an unbounded color has been clamped into the K=5 cube via `liftK5`, the cube-level quantizer does not change it further.

### 4. K=5 Simplex Palette and Projector

The **simplex palette** is defined by the constraint `r + g + b = 5`:

```lean
def palette5_simplex (c : Color5) : Prop := c.r + c.g + c.b = 5
```

Along with a simple distance and projection:

```lean
def safe_sub (a b : Nat) : Nat :=
  if a ≥ b then a - b else 0

def taxicab_dist (c1 c2 : Color5) : Nat :=
  safe_sub c1.r c2.r + safe_sub c1.g c2.g + safe_sub c1.b c2.b

def project_to_simplex (c : Color5) : Color5 :=
  if c.r + c.g + c.b = 5 then c else ⟨2, 2, 1, by decide, by decide, by decide⟩

def Q5_real : Color5 → Color5 := project_to_simplex
```

The associated projector properties are:

```lean
theorem Q5_real_closed : ∀ (c : Color5), palette5_simplex (Q5_real c) := ...
theorem Q5_real_fixed  : ∀ {c : Color5}, palette5_simplex c → Q5_real c = c := ...
```

These are bundled into a simplex-level quantizer:

```lean
def Quantizer5_simplex : Quantizer Color5 :=
  { Q := Q5_real
    palette := palette5_simplex
    closed := Q5_real_closed
    fixed := Q5_real_fixed }
```

Thus, `Quantizer5_simplex` is a projector onto the finite set of K=5 simplex colors (`r+g+b=5`), with idempotence and zero residual on its image inherited from the generic `Quantizer` theorems.

### 5. Finite Induction Principle

Finally, the file provides an induction/elimination principle over `Color5`:

```lean
theorem color5_induction {P : Color5 → Prop}
  (h : ∀ (r g b : Nat) (hr : r ≤ 5) (hg : g ≤ 5) (hb : b ≤ 5),
        P ⟨r, g, b, hr, hg, hb⟩) :
  ∀ c, P c := by
  intro c
  cases c
  apply h
```

This shows that any property `P` on K=5 colors can be reduced to a finite case analysis over all triples `(r, g, b)` with bounds `≤ 5`. 

Auxiliary lemmas for basic natural number arithmetic are defined locally in `lean/NatArithmetic.lean` (e.g. `nat_le_trans`, `add_le_add_right`), avoiding external dependencies. 

---

## Rust Component: Operational K-Level Quantizer

### 1. Core Types and Quantizer

The Rust crate defines:

* A discrete integer RGB color:

  ```rust
  #[derive(Debug, Clone, Copy, PartialEq, Eq)]
  pub struct Color {
      pub r: u8,
      pub g: u8,
      pub b: u8,
  }
  ```

* A continuous RGB representation:

  ```rust
  pub type RGB = [f32; 3];
  ```

* A **K-level quantizer**:

  ````rust
  #[derive(Debug, Clone, Copy)]
  pub struct QuantizerK {
      pub k: u8,
  }

  impl QuantizerK {
      pub fn new(k: u8) -> Self {
          assert!(k > 0, "K must be positive");
          Self { k }
      }
  }
  ``` :contentReference[oaicite:5]{index=5}  
  ````

The main quantization function:

```rust
pub fn quantize(&self, rgb: RGB) -> Color {
    let k = self.k as f32;

    // Clamp input to [0,1]
    let clamp01 = |x: f32| x.max(0.0).min(1.0);
    let r = clamp01(rgb[0]);
    let g = clamp01(rgb[1]);
    let b = clamp01(rgb[2]);

    // Scale to [0,K] with rounding
    let mut ri = (r * k).round() as i32;
    let mut gi = (g * k).round() as i32;
    let mut bi = (b * k).round() as i32;

    // Clamp to [0,K]
    let maxv = self.k as i32;
    ri = ri.clamp(0, maxv);
    gi = gi.clamp(0, maxv);
    bi = bi.clamp(0, maxv);

    // Avoid (0,0,0)
    if ri == 0 && gi == 0 && bi == 0 {
        ri = 1;
    }

    // Enforce simplex constraint r+g+b ≤ K
    let mut sum = ri + gi + bi;
    if sum > maxv {
        let scale = maxv as f32 / sum as f32;
        ri = ((ri as f32) * scale).round() as i32;
        gi = ((gi as f32) * scale).round() as i32;
        bi = ((bi as f32) * scale).round() as i32;

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

    Color { r: ri as u8, g: gi as u8, b: bi as u8 }
}
```

A projection back to `[0,1]^3` is provided by:

```rust
pub fn project_rgb(&self, rgb: RGB) -> RGB {
    let c = self.quantize(rgb);
    let k = self.k as f32;
    [c.r as f32 / k, c.g as f32 / k, c.b as f32 / k]
}
```

And an empirical **idempotence check** over random samples:

````rust
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
``` :contentReference[oaicite:6]{index=6}  

This numerically mirrors the Lean theorem `idempotent`: applying the projection twice is approximately equal to applying it once.

### 2. Binaries

The crate exposes three main binaries under `rust/src/bin`:

1. **`enumerate_k5.rs`** – K=5 simplex palette enumerator:

   - Iterates over all integer triples `(r,g,b)` with `r+g+b=5`.
   - Converts to normalized RGB in `[0,1]^3`.
   - Computes HSV and assigns a hue sector name (e.g. `"red"`, `"yellow-green"`, `"blue-magenta"`).
   - Prints a sorted table of entries by hue. :contentReference[oaicite:7]{index=7}  

2. **`quantize_demo.rs`** – Quantizer demonstration:

   - Reads `K` from the command line (default `K=5`).
   - Constructs `QuantizerK`.
   - Runs `check_idempotence(10_000, 1e-6)` to empirically verify idempotence.
   - Quantizes a small set of hand-picked RGB samples and prints `rgb → projected`. :contentReference[oaicite:8]{index=8}  

3. **`quantize_image_k5.rs`** – Image quantization pipeline:

   - CLI: `quantize_image_k5 <input.png/jpg> <output.png>`.
   - Loads an image via the `image` crate.
   - For each pixel:
     - Converts `[u8;3]` → `[f32;3]` in `[0,1]`.
     - Applies `QuantizerK::new(5).project_rgb`.
     - Converts back to `[u8;3]`.
   - Writes the result and reports dimensions and path. :contentReference[oaicite:9]{index=9}  

---

## Conceptual Summary

Formally, this repository implements:

1. A **generic collapse kernel** on an arbitrary type `α` (Lean `Quantizer α`), with **proved** properties:
   - `Q` is a projector: `Q (Q x) = Q x`.
   - The residual `(Q x, x)` is identically zero on the image of `Q`.

2. A **concrete K=5 color lattice** (`Color5`) and **simplex palette** (`r+g+b=5`), with:
   - Verified closure of the simplex projector (`Q5_real_closed`).
   - Verified fixed-point behavior on simplex elements (`Q5_real_fixed`).
   - A finite induction principle over the K=5 state space (`color5_induction`). :contentReference[oaicite:10]{index=10}  

3. A **Rust implementation** of a K-level RGB quantizer (`QuantizerK`) that:
   - Enforces `0 ≤ r,g,b ≤ K`, `(r,g,b) ≠ (0,0,0)`, and `r+g+b ≤ K`.
   - Provides numerical evidence of idempotence via Monte-Carlo sampling.
   - Applies the quantization to real images and enumerates the K=5 simplex palette. :contentReference[oaicite:11]{index=11}  

Taken together, the repo is a self-contained example of a **formally specified, operationally implemented collapse quantizer** for color: Lean provides the generic algebra and finite K=5 proofs; Rust applies the same structure to bytes, pixels, and images.
````
