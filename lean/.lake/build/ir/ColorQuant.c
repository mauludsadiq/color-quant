// Lean compiler output
// Module: ColorQuant
// Imports: public import Init
#include <lean/lean.h>
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-label"
#elif defined(__GNUC__) && !defined(__CLANG__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif
#ifdef __cplusplus
extern "C" {
#endif
LEAN_EXPORT lean_object* l_ColorQuant_safe__sub(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Color5_ctorIdx(lean_object*);
LEAN_EXPORT lean_object* l_Color5_ctorIdx___boxed(lean_object*);
LEAN_EXPORT lean_object* l_ColorQuant_Q5__real___boxed(lean_object*);
LEAN_EXPORT lean_object* l_ColorQuant_taxicab__dist___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_ColorQuant_Quantizer5__simplex___lam__0___boxed(lean_object*);
static lean_object* l_ColorQuant_project__to__simplex___closed__0;
LEAN_EXPORT lean_object* l_ColorQuant_Q5(lean_object*);
LEAN_EXPORT lean_object* l_ColorQuant_Quantizer5___lam__0(lean_object*);
LEAN_EXPORT lean_object* l_ColorQuant_Q5__real(lean_object*);
LEAN_EXPORT lean_object* l_ColorQuant_Quantizer5;
LEAN_EXPORT lean_object* l_ColorQuant_Quantizer5___lam__0___boxed(lean_object*);
LEAN_EXPORT lean_object* l_ColorQuant_safe__sub___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Quantizer_ctorIdx(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_ColorQuant_Quantizer5__simplex;
LEAN_EXPORT lean_object* l_ColorQuant_project__to__simplex(lean_object*);
LEAN_EXPORT lean_object* l_ColorQuant_project__to__simplex___boxed(lean_object*);
LEAN_EXPORT lean_object* l_ColorQuant_clamp5___boxed(lean_object*);
LEAN_EXPORT lean_object* l_ColorVec_ctorIdx___boxed(lean_object*);
LEAN_EXPORT lean_object* l_ColorQuant_Quantizer5__simplex___lam__0(lean_object*);
LEAN_EXPORT lean_object* l_ColorQuant_Q5___boxed(lean_object*);
uint8_t lean_nat_dec_eq(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_ColorQuant_taxicab__dist(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Quantizer_Phi(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_ColorQuant_clamp5(lean_object*);
lean_object* lean_nat_sub(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Quantizer_ctorIdx___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Quantizer_Phi___redArg(lean_object*, lean_object*);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
lean_object* lean_nat_add(lean_object*, lean_object*);
LEAN_EXPORT uint8_t l_ColorQuant_Q5__real__closed___nativeDecide__1__1;
LEAN_EXPORT lean_object* l_ColorQuant_liftK5(lean_object*);
LEAN_EXPORT lean_object* l_ColorVec_ctorIdx(lean_object*);
LEAN_EXPORT lean_object* l_Quantizer_ctorIdx(lean_object* x_1, lean_object* x_2) {
_start:
{
lean_object* x_3; 
x_3 = lean_unsigned_to_nat(0u);
return x_3;
}
}
LEAN_EXPORT lean_object* l_Quantizer_ctorIdx___boxed(lean_object* x_1, lean_object* x_2) {
_start:
{
lean_object* x_3; 
x_3 = l_Quantizer_ctorIdx(x_1, x_2);
lean_dec(x_2);
return x_3;
}
}
LEAN_EXPORT lean_object* l_Quantizer_Phi___redArg(lean_object* x_1, lean_object* x_2) {
_start:
{
lean_object* x_3; lean_object* x_4; 
lean_inc(x_2);
x_3 = lean_apply_1(x_1, x_2);
x_4 = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(x_4, 0, x_3);
lean_ctor_set(x_4, 1, x_2);
return x_4;
}
}
LEAN_EXPORT lean_object* l_Quantizer_Phi(lean_object* x_1, lean_object* x_2, lean_object* x_3) {
_start:
{
lean_object* x_4; 
x_4 = l_Quantizer_Phi___redArg(x_2, x_3);
return x_4;
}
}
LEAN_EXPORT lean_object* l_ColorVec_ctorIdx(lean_object* x_1) {
_start:
{
lean_object* x_2; 
x_2 = lean_unsigned_to_nat(0u);
return x_2;
}
}
LEAN_EXPORT lean_object* l_ColorVec_ctorIdx___boxed(lean_object* x_1) {
_start:
{
lean_object* x_2; 
x_2 = l_ColorVec_ctorIdx(x_1);
lean_dec_ref(x_1);
return x_2;
}
}
LEAN_EXPORT lean_object* l_Color5_ctorIdx(lean_object* x_1) {
_start:
{
lean_object* x_2; 
x_2 = lean_unsigned_to_nat(0u);
return x_2;
}
}
LEAN_EXPORT lean_object* l_Color5_ctorIdx___boxed(lean_object* x_1) {
_start:
{
lean_object* x_2; 
x_2 = l_Color5_ctorIdx(x_1);
lean_dec_ref(x_1);
return x_2;
}
}
LEAN_EXPORT lean_object* l_ColorQuant_clamp5(lean_object* x_1) {
_start:
{
lean_object* x_2; uint8_t x_3; 
x_2 = lean_unsigned_to_nat(5u);
x_3 = lean_nat_dec_le(x_1, x_2);
if (x_3 == 0)
{
return x_2;
}
else
{
lean_inc(x_1);
return x_1;
}
}
}
LEAN_EXPORT lean_object* l_ColorQuant_clamp5___boxed(lean_object* x_1) {
_start:
{
lean_object* x_2; 
x_2 = l_ColorQuant_clamp5(x_1);
lean_dec(x_1);
return x_2;
}
}
LEAN_EXPORT lean_object* l_ColorQuant_liftK5(lean_object* x_1) {
_start:
{
uint8_t x_2; 
x_2 = !lean_is_exclusive(x_1);
if (x_2 == 0)
{
lean_object* x_3; lean_object* x_4; lean_object* x_5; lean_object* x_6; lean_object* x_7; lean_object* x_8; 
x_3 = lean_ctor_get(x_1, 0);
x_4 = lean_ctor_get(x_1, 1);
x_5 = lean_ctor_get(x_1, 2);
x_6 = l_ColorQuant_clamp5(x_3);
lean_dec(x_3);
x_7 = l_ColorQuant_clamp5(x_4);
lean_dec(x_4);
x_8 = l_ColorQuant_clamp5(x_5);
lean_dec(x_5);
lean_ctor_set(x_1, 2, x_8);
lean_ctor_set(x_1, 1, x_7);
lean_ctor_set(x_1, 0, x_6);
return x_1;
}
else
{
lean_object* x_9; lean_object* x_10; lean_object* x_11; lean_object* x_12; lean_object* x_13; lean_object* x_14; lean_object* x_15; 
x_9 = lean_ctor_get(x_1, 0);
x_10 = lean_ctor_get(x_1, 1);
x_11 = lean_ctor_get(x_1, 2);
lean_inc(x_11);
lean_inc(x_10);
lean_inc(x_9);
lean_dec(x_1);
x_12 = l_ColorQuant_clamp5(x_9);
lean_dec(x_9);
x_13 = l_ColorQuant_clamp5(x_10);
lean_dec(x_10);
x_14 = l_ColorQuant_clamp5(x_11);
lean_dec(x_11);
x_15 = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(x_15, 0, x_12);
lean_ctor_set(x_15, 1, x_13);
lean_ctor_set(x_15, 2, x_14);
return x_15;
}
}
}
LEAN_EXPORT lean_object* l_ColorQuant_Q5(lean_object* x_1) {
_start:
{
lean_inc_ref(x_1);
return x_1;
}
}
LEAN_EXPORT lean_object* l_ColorQuant_Q5___boxed(lean_object* x_1) {
_start:
{
lean_object* x_2; 
x_2 = l_ColorQuant_Q5(x_1);
lean_dec_ref(x_1);
return x_2;
}
}
LEAN_EXPORT lean_object* l_ColorQuant_Quantizer5___lam__0(lean_object* x_1) {
_start:
{
lean_inc_ref(x_1);
return x_1;
}
}
static lean_object* _init_l_ColorQuant_Quantizer5() {
_start:
{
lean_object* x_1; 
x_1 = lean_alloc_closure((void*)(l_ColorQuant_Quantizer5___lam__0___boxed), 1, 0);
return x_1;
}
}
LEAN_EXPORT lean_object* l_ColorQuant_Quantizer5___lam__0___boxed(lean_object* x_1) {
_start:
{
lean_object* x_2; 
x_2 = l_ColorQuant_Quantizer5___lam__0(x_1);
lean_dec_ref(x_1);
return x_2;
}
}
LEAN_EXPORT lean_object* l_ColorQuant_safe__sub(lean_object* x_1, lean_object* x_2) {
_start:
{
uint8_t x_3; 
x_3 = lean_nat_dec_le(x_2, x_1);
if (x_3 == 0)
{
lean_object* x_4; 
x_4 = lean_unsigned_to_nat(0u);
return x_4;
}
else
{
lean_object* x_5; 
x_5 = lean_nat_sub(x_1, x_2);
return x_5;
}
}
}
LEAN_EXPORT lean_object* l_ColorQuant_safe__sub___boxed(lean_object* x_1, lean_object* x_2) {
_start:
{
lean_object* x_3; 
x_3 = l_ColorQuant_safe__sub(x_1, x_2);
lean_dec(x_2);
lean_dec(x_1);
return x_3;
}
}
LEAN_EXPORT lean_object* l_ColorQuant_taxicab__dist(lean_object* x_1, lean_object* x_2) {
_start:
{
lean_object* x_3; lean_object* x_4; lean_object* x_5; lean_object* x_6; lean_object* x_7; lean_object* x_8; lean_object* x_9; lean_object* x_10; lean_object* x_11; lean_object* x_12; lean_object* x_13; 
x_3 = lean_ctor_get(x_1, 0);
x_4 = lean_ctor_get(x_1, 1);
x_5 = lean_ctor_get(x_1, 2);
x_6 = lean_ctor_get(x_2, 0);
x_7 = lean_ctor_get(x_2, 1);
x_8 = lean_ctor_get(x_2, 2);
x_9 = l_ColorQuant_safe__sub(x_3, x_6);
x_10 = l_ColorQuant_safe__sub(x_4, x_7);
x_11 = lean_nat_add(x_9, x_10);
lean_dec(x_10);
lean_dec(x_9);
x_12 = l_ColorQuant_safe__sub(x_5, x_8);
x_13 = lean_nat_add(x_11, x_12);
lean_dec(x_12);
lean_dec(x_11);
return x_13;
}
}
LEAN_EXPORT lean_object* l_ColorQuant_taxicab__dist___boxed(lean_object* x_1, lean_object* x_2) {
_start:
{
lean_object* x_3; 
x_3 = l_ColorQuant_taxicab__dist(x_1, x_2);
lean_dec_ref(x_2);
lean_dec_ref(x_1);
return x_3;
}
}
static lean_object* _init_l_ColorQuant_project__to__simplex___closed__0() {
_start:
{
lean_object* x_1; lean_object* x_2; lean_object* x_3; 
x_1 = lean_unsigned_to_nat(1u);
x_2 = lean_unsigned_to_nat(2u);
x_3 = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(x_3, 0, x_2);
lean_ctor_set(x_3, 1, x_2);
lean_ctor_set(x_3, 2, x_1);
return x_3;
}
}
LEAN_EXPORT lean_object* l_ColorQuant_project__to__simplex(lean_object* x_1) {
_start:
{
lean_object* x_2; lean_object* x_3; lean_object* x_4; lean_object* x_5; lean_object* x_6; lean_object* x_7; uint8_t x_8; 
x_2 = lean_ctor_get(x_1, 0);
x_3 = lean_ctor_get(x_1, 1);
x_4 = lean_ctor_get(x_1, 2);
x_5 = lean_nat_add(x_2, x_3);
x_6 = lean_nat_add(x_5, x_4);
lean_dec(x_5);
x_7 = lean_unsigned_to_nat(5u);
x_8 = lean_nat_dec_eq(x_6, x_7);
lean_dec(x_6);
if (x_8 == 0)
{
lean_object* x_9; 
x_9 = l_ColorQuant_project__to__simplex___closed__0;
return x_9;
}
else
{
lean_inc_ref(x_1);
return x_1;
}
}
}
LEAN_EXPORT lean_object* l_ColorQuant_project__to__simplex___boxed(lean_object* x_1) {
_start:
{
lean_object* x_2; 
x_2 = l_ColorQuant_project__to__simplex(x_1);
lean_dec_ref(x_1);
return x_2;
}
}
LEAN_EXPORT lean_object* l_ColorQuant_Q5__real(lean_object* x_1) {
_start:
{
lean_object* x_2; 
x_2 = l_ColorQuant_project__to__simplex(x_1);
return x_2;
}
}
LEAN_EXPORT lean_object* l_ColorQuant_Q5__real___boxed(lean_object* x_1) {
_start:
{
lean_object* x_2; 
x_2 = l_ColorQuant_Q5__real(x_1);
lean_dec_ref(x_1);
return x_2;
}
}
static uint8_t _init_l_ColorQuant_Q5__real__closed___nativeDecide__1__1() {
_start:
{
uint8_t x_1; 
x_1 = 1;
return x_1;
}
}
LEAN_EXPORT lean_object* l_ColorQuant_Quantizer5__simplex___lam__0(lean_object* x_1) {
_start:
{
lean_object* x_2; 
x_2 = l_ColorQuant_project__to__simplex(x_1);
return x_2;
}
}
static lean_object* _init_l_ColorQuant_Quantizer5__simplex() {
_start:
{
lean_object* x_1; 
x_1 = lean_alloc_closure((void*)(l_ColorQuant_Quantizer5__simplex___lam__0___boxed), 1, 0);
return x_1;
}
}
LEAN_EXPORT lean_object* l_ColorQuant_Quantizer5__simplex___lam__0___boxed(lean_object* x_1) {
_start:
{
lean_object* x_2; 
x_2 = l_ColorQuant_Quantizer5__simplex___lam__0(x_1);
lean_dec_ref(x_1);
return x_2;
}
}
lean_object* initialize_Init(uint8_t builtin, lean_object*);
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_ColorQuant(uint8_t builtin, lean_object* w) {
lean_object * res;
if (_G_initialized) return lean_io_result_mk_ok(lean_box(0));
_G_initialized = true;
res = initialize_Init(builtin, lean_io_mk_world());
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
l_ColorQuant_Quantizer5 = _init_l_ColorQuant_Quantizer5();
lean_mark_persistent(l_ColorQuant_Quantizer5);
l_ColorQuant_project__to__simplex___closed__0 = _init_l_ColorQuant_project__to__simplex___closed__0();
lean_mark_persistent(l_ColorQuant_project__to__simplex___closed__0);
l_ColorQuant_Q5__real__closed___nativeDecide__1__1 = _init_l_ColorQuant_Q5__real__closed___nativeDecide__1__1();
l_ColorQuant_Quantizer5__simplex = _init_l_ColorQuant_Quantizer5__simplex();
lean_mark_persistent(l_ColorQuant_Quantizer5__simplex);
return lean_io_result_mk_ok(lean_box(0));
}
#ifdef __cplusplus
}
#endif
