(module
  (type (;0;) (func (param i32)))
  (type (;1;) (func (param i32 i32 i32 i32)))
  (type (;2;) (func (param i32 i32 i32)))
  (type (;3;) (func))
  (import "env" "_draw_commit_circle" (func (;0;) (type 2)))
  (import "env" "_connect_circles" (func (;1;) (type 1)))
  (import "env" "_print" (func (;2;) (type 0)))
  (import "env" "memory" (memory (;0;) 256 256))
  (func (;3;) (type 3)
    i32.const 1024
    call 2
    i32.const 1
    i32.const 4
    i32.const 1031
    call 0
    i32.const 2
    i32.const 2
    i32.const 1036
    call 0
    i32.const 3
    i32.const 3
    i32.const 1040
    call 0
    i32.const 3
    i32.const 5
    i32.const 1046
    call 0
    i32.const 2
    i32.const 2
    i32.const 3
    i32.const 3
    call 1
    i32.const 2
    i32.const 2
    i32.const 1
    i32.const 4
    call 1
    i32.const 3
    i32.const 3
    i32.const 3
    i32.const 5
    call 1
    i32.const 1054
    call 2)
  (export "_draw" (func 3))
  (data (;0;) (i32.const 1024) "before\00blue\00red\00green\00magenta\00after"))
