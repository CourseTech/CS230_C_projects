#! /usr/bin/env bash
# Run the bomb
gdb -tui ./binary_bomb



#    0x15a0 <phase4>         endbr32                                                                                                                                    │
# │   0x15a4 <phase4+4>       push   %ebp                                                                                                                                │
# │   0x15a5 <phase4+5>       mov    %esp,%ebp                                                                                                                           │
# │   0x15a7 <phase4+7>       sub    $0x10,%esp                                                                                                                          │
# │   0x15aa <phase4+10>      call   0x19e1 <__x86.get_pc_thunk.ax>                                                                                                      │
# │   0x15af <phase4+15>      add    $0x2a05,%eax                                                                                                                        │
# │   0x15b4 <phase4+20>      movl   $0x0,-0xc(%ebp)                                                                                                                     │
# │   0x15bb <phase4+27>      movl   $0x2,-0x8(%ebp)                                                                                                                     │
# │   0x15c2 <phase4+34>      jmp    0x15eb <phase4+75>                                                                                                                  │
# │   0x15c4 <phase4+36>      movl   $0x6,-0x4(%ebp)                                                                                                                     │
# │   0x15cb <phase4+43>      jmp    0x15e1 <phase4+65>                                                                                                                  │
# │   0x15cd <phase4+45>      mov    -0xc(%ebp),%edx                                                                                                                     │
# │   0x15d0 <phase4+48>      mov    -0x8(%ebp),%eax                                                                                                                     │
# │   0x15d3 <phase4+51>      add    %eax,%edx                                                                                                                           │
# │   0x15d5 <phase4+53>      mov    -0x4(%ebp),%eax                                                                                                                     │
# │   0x15d8 <phase4+56>      add    %edx,%eax                                                                                                                           │
# │   0x15da <phase4+58>      mov    %eax,-0xc(%ebp)                                                                                                                     │
# │   0x15dd <phase4+61>      subl   $0x1,-0x4(%ebp) 
# │   0x15e1 <phase4+65>      cmpl   $0x0,-0x4(%ebp)                                                                                                                     │
# │   0x15e5 <phase4+69>      jg     0x15cd <phase4+45>                                                                                                                  │
# │   0x15e7 <phase4+71>      addl   $0x1,-0x8(%ebp)                                                                                                                     │
# │   0x15eb <phase4+75>      cmpl   $0x5,-0x8(%ebp)                                                                                                                     │
# │   0x15ef <phase4+79>      jle    0x15c4 <phase4+36>                                                                                                                  │
# │   0x15f1 <phase4+81>      mov    -0xc(%ebp),%eax                                                                                                                     │
# │   0x15f4 <phase4+84>      cmp    0x8(%ebp),%eax                                                                                                                      │
# │   0x15f7 <phase4+87>      sete   %al                                                                                                                                 │
# │   0x15fa <phase4+90>      movzbl %al,%eax                                                                                                                            │
# │   0x15fd <phase4+93>      leave                                                                                                                                      │
# │   0x15fe <phase4+94>      ret 