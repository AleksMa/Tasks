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

;; Dlina

lea di, buf2
call proc_strlen
add ax, ax
lea di, buf2
mov dl, [di]
shr dl, 4
cmp dl, 0
jne oldR1
dec ax
oldR1:
mov num2, ax

lea di, buf
call proc_strlen
mov num, ax 
add ax, ax
lea di, buf
mov dl, [di]
shr dl, 4
cmp dl, 0
jne oldR2
dec ax
oldR2:
mov num, ax

;; Nahodim max i min

mov ax, num
cmp ax, num2
jge numF
mov ax, num2
mov max, ax
mov ax, num
mov min, ax
numRetF:

;; Cymmipyem min (konec) 

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
buf db MAX_PATH dup(0) 
buf2 db MAX_PATH dup(0) 
res db MAX_PATH dup(0)