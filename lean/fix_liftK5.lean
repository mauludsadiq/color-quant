def liftK5 (c : ColorVec) : Color5 :=
  let r5 := clamp5 c.r
  let g5 := clamp5 c.g
  let b5 := clamp5 c.b
  have hr : r5 ≤ 5 := clamp5_le c.r
  have hg : g5 ≤ 5 := clamp5_le c.g
  have hb : b5 ≤ 5 := clamp5_le c.b
  { r := r5, g := g5, b := b5, hr := hr, hg := hg, hb := hb }
