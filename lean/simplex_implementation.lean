-- K=5 Simplex Projection Algorithm
def find_closest_simplex_point (c : Color5) : Color5 :=
  -- For K=5, the simplex is all points where r + g + b = 5
  -- We need to find the closest point on this plane to c
  -- Using taxicab distance for now (could extend to Euclidean)
  let candidates : List (Nat × Nat × Nat) := [
    (5, 0, 0), (4, 1, 0), (4, 0, 1), (3, 2, 0), (3, 1, 1), (3, 0, 2),
    (2, 3, 0), (2, 2, 1), (2, 1, 2), (2, 0, 3), (1, 4, 0), (1, 3, 1),
    (1, 2, 2), (1, 1, 3), (1, 0, 4), (0, 5, 0), (0, 4, 1), (0, 3, 2),
    (0, 2, 3), (0, 1, 4), (0, 0, 5)
  ]
  let valid_candidates : List Color5 := candidates.filterMap (λ (r, g, b) =>
    if h : r ≤ 5 ∧ g ≤ 5 ∧ b ≤ 5 then
      some ⟨r, g, b, h.left, h.right.left, h.right.right⟩
    else
      none)
  -- Find minimum by taxicab distance
  match valid_candidates with
  | [] => c  -- fallback, shouldn't happen
  | (candidate :: rest) =>
    let min_candidate := rest.foldl (λ best next =>
      if taxicab_dist next c < taxicab_dist best c then next else best) candidate
    min_candidate

def project_to_simplex (c : Color5) : Color5 :=
  find_closest_simplex_point c

-- Now prove the theorems
theorem Q5_real_closed : ∀ (c : Color5), palette5_simplex (Q5_real c) := by
  intro c
  unfold Q5_real project_to_simplex find_closest_simplex_point
  simp [palette5_simplex]
  -- All candidates satisfy r + g + b = 5 by construction
  rfl

theorem Q5_real_fixed : ∀ {c : Color5}, palette5_simplex c → Q5_real c = c := by
  intro c h
  unfold Q5_real project_to_simplex find_closest_simplex_point palette5_simplex at h
  -- If c is already on simplex, it should be the closest point to itself
  have : taxicab_dist c c = 0 := by
    unfold taxicab_dist safe_sub
    simp
  -- The algorithm should pick c when distance is minimal
  simp [h]
