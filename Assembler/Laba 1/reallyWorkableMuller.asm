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

;CJIOJIIEHUE

numF:
    mov ax, bufNum
    mov max, ax
    mov ax, bufNum2
    mov min, ax
jmp numRetF 

start:
mov cx, 255

lea di, tempBuf2
call proc_strlen
mov bufNum2, ax

lea di, tempBuf
call proc_strlen
mov bufNum, ax
mov ax, bufNum
cmp ax, bufNum2
jge numF
mov ax, bufNum2
mov max, ax
mov ax, bufNum
mov min, ax
numRetF:

mov  cx,  min

lea si, tempBuf  
lea bx, tempBuf2
lea di, res
add si,  bufNum
add bx,  bufNum2
add di, max
dec si
dec bx
dec di


mov dl, 0 

call sumMin

mov ax, max
cmp ax, min
je equalLen
mov cx, max
sub cx, min
;dec si
;dec bx
;dec di
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
    ;mov dl, 0
    mov al, [si]
    sub al, 96d  ;;2 * 48
    ;add ax, dx
    ;inc dx
    add al, [bx]
    add [di], al
    ;cmp al, 10d
    ;jge of
    ;nof: 
    add [di], 48d
    
    add [di], dl  
    mov dl, 0
    cmp [di], 58d
    jl notMinOf
    mov dl, 1d
    sub [di], 10d
    notMinOf:
    
    dec si
    dec bx
    dec di
   
    loop sumMin
ret

sumMax:
    mov ax, bufNum       
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

;of:
;    sub [di], 10d
;    mov dl, 1
;jmp nof
     
     
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

;CJIO}I{EHuE KOHEC

;yMHO}I{EHuE  

startMul:
mov cx, 255

lea di, buf2
call proc_strlen
mov num2, ax

lea di, buf
call proc_strlen
mov num, ax
;mov ax, num

mov cx, num2
mov index, cx
;mov dp, 0
;dec cx
;dec num2

lea di, res
mov [di], 48d

call Muller

;lea di, res

;call removeSomeNulls


;lea di, res
;call NullArr
;lea di, tempBuf
;lea bx, res

call arrCpy


ret  

Muller:

    push cx
    ;push num
       
    mov acc, 0   
    
    ;COMMENT *
    lea di, res
    lea bx, tempBuf2
    call arrCpy
    
       
    lea di, res
    call NullArr
    
    
    
    mov  cx,  num

    lea si, buf  
    lea bx, buf2
    
    lea di, tempBuf
    call NullARr
    
    
    
    lea di, tempBuf
    add si,  num
    add bx,  num2
    add di, num
    dec si
    dec bx
    dec di
    
    call mulOneDigit 
    
    dec num2
    
          
    ;DopuCbIBaHue 00000      
          
    lea di, tempBuf
    call proc_strlen
    
    lea di, tempBuf
    
    add di, ax
    
    mov cx, index
    sub cx, num2
    dec cx
    cmp cx, 1
    jl noToNulls
    call writeSomeNulls        
        
        
    noToNulls:
    
           
           
    ;call arrCpy
    
    pusha
    
    call start
    
    popa
    
    ;pop num
    pop cx 
    
    loop Muller

ret

mulOneDigit:
    call oneDigitMuller

    ;inc num           
    mov cx, num
    inc cx
    lea di, tempBuf
    add di, cx
    mov dl, acc
    cmp dl, 0
    jg call overArr

ret 

oneDigitMuller: 
    mov ah, acc
    mov curAcc, ah
    mov acc, 0
    mov ax, num
    mov al, [si]
    sub al, 48d
    mov dh, [bx]
    sub dh, 48d
    mul dh
    add [di], al
    mov al, curAcc
    add [di], al
    cmp [di], 10d
    jl endMul
    mov al, [di]
    mov ah, 0
    mov dh, 10d
    div dh
    mov acc, al
    ;mov al, acc
    mul dh
    sub [di], al
    endMul:
    add [di], 48d
    dec di
    dec si 
    mov curAcc, 0
    loop oneDigitMuller
ret 


writeSomeNulls:
    mov [di], 48d
    inc di
    loop writeSomeNulls
ret

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


; bx - dest, di - source
proc_cpy:
    mov al, [di]
    mov [bx], al
    inc bx
    inc di
    cmp [di], 0 
    jne proc_cpy
ret

NullArr:
    mov [di], 0
    inc di
    cmp [di], 0 
    jne NullArr
ret 

removeSomeNulls:
    
    push di
    lea di, tempBuf
    call NullArr
    pop di
    ;push di
    lea bx, tempBuf
    ;lea di, res
    mov ax, 0
    countNulls:
        cmp [di], '0'
        jne stopCountNulls
        inc ax
        inc di
        jmp countNulls 
    
    stopCountNulls:
    cmp [di], 0
    jne notDecNulls
    dec di
    notDecNulls:
    call ArrCpy

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
    
    call startMul
    
    lea si, res
    call proc_writeln

int 20h
num dw 0
num2 dw 0
bufNum dw 0
bufNum2 dw 0
max dw 0
min dw 0
dp dw 0
acc db 0
curAcc db 0
index dw 0
keklol dw 0
buf db MAX_PATH dup(0) 
buf2 db MAX_PATH dup(0)
tempBuf db MAX_PATH dup(0)
tempBuf2 db MAX_PATH dup(0) 
res db MAX_PATH dup(0)