theorem nat_le_trans {a b c : Nat} (h1 : a ≤ b) (h2 : b ≤ c) : a ≤ c := by
  induction' h2 with k hk
  · assumption
  · apply Nat.le_step
    assumption

theorem add_le_add_right {a b : Nat} (h : a ≤ b) (c : Nat) : a + c ≤ b + c := by
  induction' h with k hk
  · rfl
  · apply Nat.succ_le_succ
    assumption
