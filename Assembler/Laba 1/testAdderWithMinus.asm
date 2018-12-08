MAX_PATH EQU 255
N = 0
N2 = 0

jmp main


proc_writeln:
    pusha
    cld
    mov ah, 0eh
    write:
        lodsb
        test al,al
        jz exit_write
        int 10h
        jmp write 
        exit_write: 
           mov ah, 0eh    ; FuHKcuya BbIBODA 
           mov al, 0ah    ; IIepeBoD cTPoKu
           int 10h        ; IIpepbIBaHue (BbIIIOJIHeHue BbIBODA)
        
           mov ah, 0eh     
           mov al, 0dh       ;Bo3BpaT KapetKu
           int 10h                           
          
    popa
ret
proc_readln:
    pusha
    cld
    read:
        mov ah, 0
        int 16h
        cmp al, 13
        jz exit_read
        stosb
        jmp read
        exit_read:
        popa       
ret        
 
proc_strlen:
    push si
    cld
    mov si, di
    mov al, 0h
    repne scasb
    jz zero
    mov ax, 0h
    pop si
    ret
    
    zero:
    sub di, si
    mov ax, di
    dec ax
    pop si    
ret

numF:
    mov ax, num
    mov max, ax
    mov ax, num2
    mov min, ax
jmp numRetF 

start:

mov cx, 255

lea di, buf2
call proc_strlen
mov num2, ax

lea di, buf
call proc_strlen
mov num, ax

;;;

lea di, buf2
mov al, [di]
cmp al, 45d
jne notSecondMinus
 
or minus, 1b 
inc di
lea bx, buf2

call ArrCpy

lea di, buf2
dec num2
add di, num2

call NullArr

notSecondMinus:


lea di, buf
mov al, [di]
cmp al, 45d
jne notFirstMinus
 
or minus, 10b
inc di
lea bx, buf

call ArrCpy

lea di, buf
dec num
add di, num

call NullArr

notFirstMinus:

;;;

call proc_compare
mov comp, ax


;;;

mov ax, num
cmp ax, num2
jge numF
mov ax, num2
mov max, ax
mov ax, num
mov min, ax
numRetF:


mov  cx,  min

lea si, buf  
lea bx, buf2
lea di, res
add si,  num
add bx,  num2
add di, max
dec si
dec bx
dec di

cmp minus, 00b
je plusSum


cmp minus, 11b
je  plusTwoMinus

cmp minus, 01b
je PlusOneMinus

cmp minus, 10b
je plusOneMinus

  

ret

plusTwoMinus:
    call plusSum
     
    call drawMinus 
ret

drawMinus:
    lea bx, buf
    lea di, res
    call ArrCpy 
    
    lea bx, res
    lea di, buf
    mov [bx], 45d
    inc bx
    call ArrCpy
ret

plusOneMinus:
    
    mov ax, comp
    cmp ax, 0
    je equalNull
    
    mov ax, comp
    cmp ax, 0
    jg norm 
    
    lea di, tempBuf
    call Nullarr
    
    lea bx, tempBuf
    lea di, buf2
    
    call ArrCpy
    
    lea bx, buf2
    lea di, buf
    
    call ArrCpy 
    
    lea bx, buf
    lea di, tempBuf
    
    call ArrCpy
    
    mov drw, 0
    cmp minus, 01b
    jne norm
    mov drw, 1    
    norm: 
    
    mov ax, comp
    cmp ax, 0
    jl nochg
    mov drw, 0
    cmp minus, 01b
    je nochg
    mov drw, 1 
    
    nochg:
    
    lea di, tempBuf
    call Nullarr
    
    mov cx, max
    sub cx, min
    mov ax, cx
    
    lea di, tempBuf
    
    call writeSomeNulls
    
    lea bx, tempBuf
    add bx, ax
    lea di, buf2
    
    call ArrCpy
    
    
    lea di, res
    lea si, buf
    lea bx, tempBuf
    
    mov cx, max
    dec cx
    
    add si, cx
    add di, cx
    add bx, cx
    
    inc cx
    
    call minusSum
    
    mov ax, drw
    cmp drw, 0
    je notodrw
    call DrawMinus
    
    ;mov di, res
    notodrw:
    
    mov ax, comp
    cmp ax, 0
    jne nequalNull
    
    equalNull:
    lea di, res
    mov [di], '0'
    nequalNull:
    
ret

minusSum:
    
    ;mov dl, 0
    mov al, [si]
    add al, 48d
    ;add ax, dx
    ;inc dx
    sub al, [bx]
    add [di], al
    cmp al, 48d
    jge reflow 
    add [di], 10d
    dec si
    dec [si]
    inc si

    
    reflow:
    dec si
    dec bx
    dec di
   
    loop minusSUm
ret

plusSum:
    mov dl, 0 
    
    call sumMin
    
    mov ax, max
    cmp ax, min
    jz equalLen
    mov cx, max
    sub cx, min
    ;dec si
    ;dec bx
    ;dec di
    mov dl, 0
    call sumMax
    equalLen:           
    inc max           
    mov cx, max
    lea di, res
    add di, max
    cmp dl, 1
    jge call overArr
ret

sumMin:       
    mov dl, 0
    mov al, [si]
    add al, -96d
    ;add ax, dx
    ;inc dx
    add al, [bx]
    add [di], al
    cmp al, 10d
    jge of
    nof: 
    add [di], 48d
    
    dec si
    dec bx
    dec di
    
    add [di], dl
    cmp [di], 58d
    jl lol
    mov dh, 1d
    lol:
    ;mov dl, 0
   
    loop sumMin
ret

sumMax:
    mov ax, num       
    cmp ax, max
    je first
    mov dh, [bx]
    add [di], dh
    dec bx
    firstret:
    add [di], dl
    cmp [di], 58d
    jge of2
    mov dl, 0
    nof2:
    dec di
    loop sumMax
ret

first:
    mov dh, [si]
    add [di], dh
    dec si
jmp firstret

of:
    sub [di], 10d
    mov dl, 1
jmp nof
     
     
of2:
    sub [di], 10d
    mov dl, 1
    cmp cx, 1
    je kek
jmp nof2  


kek:
    mov dh, 1;  
jmp nof2
    
    
overArr:
    cmp cx,1
    je last
    mov al, [di-1] 
    mov [di], al
    retOverArr:
    dec di
    loop overArr
ret

last:
    mov al, [di-1] 
    mov [di], al
    dec di
    add dl, 48d
    mov [di], dl
jmp retOverArr


arrCpy:
;bx - dest, di - source
    ;popa
    ;lea di, tempBuf  
    ;;;lea bx, tempBuf2
    ;call proc_strlen
    ;;;lea di, tempBuf
    ;mov cx, ax
    ;dec cx
    ;add di, cx
    ;add bx, cx
    call proc_cpy
    ;pusha
ret

proc_cpy:
    mov al, [di]
    mov [bx], al
    inc bx
    inc di
    ;dec cx
    cmp [di], 0 
    jne proc_cpy
ret

NullArr:
    mov [di], 0
    inc di
    cmp [di], 0 
    jne NullArr
ret

proc_compare:
   
   mov ax, num
   sub ax, num2
   
   cmp ax, 0
   je endCompare
   
   lea bx, buf
   lea si, buf2
   
   mov ax, [bx]
   sub ax, [si]
   
   cmp ax, 0
   jne endCompare
   
   inc bx
   inc si
   cmp [bx], 0
   jne proc_compare
   
   endCompare:
ret

writeSomeNulls:
    mov [di], 48d
    inc di
    loop writeSomeNulls
ret        

main: 

    mov ax, cs
    mov es, ax
    lea di, buf
    call proc_readln
    
    lea si, buf
    call proc_writeln 
    
    mov ax, cs
    mov es, ax
    lea di, buf2 
    call proc_readln
    
    lea si, buf2
    call proc_writeln
    
    call start 
    
    lea si, res
    call proc_writeln

int 20h
num dw 0
num2 dw 0
max dw 0
min dw 0
comp dw 0
minus dw 0
drw dw 0
buf db MAX_PATH dup(0)
tempBuf db MAX_PATH dup(0) 
buf2 db MAX_PATH dup(0) 
res db MAX_PATH dup(0)