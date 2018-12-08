
jmp start

arg1 db 1, 2, 5, 6
arg2 db 3, 5, 6, 1
res db ?, ?, ?, ?

start:

lea si, arg1
lea bx, arg2
lea di, res

mov cx, 4

sum:       
    mov al, [si]
    add al, [bx]
    mov [di], al
   
    inc si
    inc bx
    inc di
   
    loop sum

ret



