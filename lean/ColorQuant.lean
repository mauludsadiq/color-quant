structure Quantizer (α : Type u) where
  Q : α → α
  palette : α → Prop
  closed : ∀ x, palette (Q x)
  fixed : ∀ {x}, palette x → Q x = x

namespace Quantizer

theorem idempotent (q : Quantizer α) (x : α) : q.Q (q.Q x) = q.Q x :=
  q.fixed (q.closed x)

def Phi (q : Quantizer α) (x : α) : α × α := (q.Q x, x)

def isZeroPair (p : α × α) : Prop := p.1 = p.2

theorem phi_zero_on_image (q : Quantizer α) (x : α) : isZeroPair (Phi q (q.Q x)) := by
  unfold isZeroPair Phi
  apply idempotent

end Quantizer

structure ColorVec where
  r : Nat
  g : Nat
  b : Nat

structure Color5 where
  r : Nat
  g : Nat
  b : Nat
  hr : r ≤ 5
  hg : g ≤ 5
  hb : b ≤ 5

namespace ColorQuant

def clamp5 (n : Nat) : Nat :=
  if n ≤ 5 then n else 5

theorem clamp5_le (n : Nat) : clamp5 n ≤ 5 := by
  unfold clamp5
  by_cases h : n ≤ 5
  · rw [if_pos h]
    exact h
  · rw [if_neg h]
    exact Nat.le_refl 5

def liftK5 (c : ColorVec) : Color5 :=
  let r := c.r
  let g := c.g
  let b := c.b
  let r5 := clamp5 r
  let g5 := clamp5 g
  let b5 := clamp5 b
  have hr : r5 ≤ 5 := clamp5_le r
  have hg : g5 ≤ 5 := clamp5_le g
  have hb : b5 ≤ 5 := clamp5_le b
  ⟨r5, g5, b5, hr, hg, hb⟩

def Q5 (c : Color5) : Color5 := c

def palette5 (_c : Color5) : Prop := True

theorem Q5_closed : ∀ c : Color5, palette5 (Q5 c) := by
  intro _c
  trivial

theorem Q5_fixed : ∀ {c : Color5}, palette5 c → Q5 c = c := by
  intro c _
  rfl

def Quantizer5 : Quantizer Color5 :=
  { Q := Q5
    palette := palette5
    closed := Q5_closed
    fixed := Q5_fixed }

theorem Quantizer5_projector_idem (c : Color5) :
    Quantizer5.Q (Quantizer5.Q c) = Quantizer5.Q c :=
  Quantizer.idempotent Quantizer5 c

theorem Quantizer5_phi_zero_on_image (c : Color5) :
    Quantizer.isZeroPair (Quantizer.Phi Quantizer5 (Quantizer5.Q c)) :=
  Quantizer.phi_zero_on_image Quantizer5 c

theorem Quantizer5_on_liftK5_fixed (c : ColorVec) :
    Quantizer5.Q (liftK5 c) = liftK5 c := by
  rfl

def palette5_simplex (c : Color5) : Prop := c.r + c.g + c.b = 5

def safe_sub (a b : Nat) : Nat :=
  if a ≥ b then a - b else 0

def taxicab_dist (c1 c2 : Color5) : Nat :=
  safe_sub c1.r c2.r + safe_sub c1.g c2.g + safe_sub c1.b c2.b

def project_to_simplex (c : Color5) : Color5 :=
  if c.r + c.g + c.b = 5 then c else ⟨2, 2, 1, by decide, by decide, by decide⟩

def Q5_real : Color5 → Color5 := project_to_simplex

theorem Q5_real_closed : ∀ (c : Color5), palette5_simplex (Q5_real c) := by
  intro c
  unfold Q5_real project_to_simplex palette5_simplex
  by_cases h : c.r + c.g + c.b = 5
  · rw [if_pos h]
    exact h
  · rw [if_neg h]
    native_decide

theorem Q5_real_fixed : ∀ {c : Color5}, palette5_simplex c → Q5_real c = c := by
  intro c h
  unfold Q5_real project_to_simplex
  unfold palette5_simplex at h
  simp [h]

def Quantizer5_simplex : Quantizer Color5 :=
  { Q := Q5_real
    palette := palette5_simplex
    closed := Q5_real_closed
    fixed := Q5_real_fixed }

theorem color5_induction {P : Color5 → Prop} 
  (h : ∀ (r g b : Nat) (hr : r ≤ 5) (hg : g ≤ 5) (hb : b ≤ 5), P ⟨r, g, b, hr, hg, hb⟩) :
  ∀ c, P c := by
  intro c
  cases c
  apply h

end ColorQuant
