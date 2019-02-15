(module
  (type (;0;) (func (param i32)))
  (type (;1;) (func (param i32 i32)))
  (import "env" "_print" (func (;0;) (type 1)))
  (func (;1;) (type 0) (param i32)
    i32.const 1
    local.get 0
    call 0
    i32.const 2
    i32.const 100
    call 0
    i32.const 3
    local.get 0
    i32.const 1
    i32.shl
    call 0)
  (export "_print_val" (func 1)))
