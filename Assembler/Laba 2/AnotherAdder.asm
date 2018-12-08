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
mov num2, ax

lea di, buf
call proc_strlen
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
    ;sub al, 96d  ;;2 * 48
    ;add ax, dx
    ;inc dx
    add al, [bx]
    add [di], al
    ;cmp al, 10d
    ;jge of
    ;nof: 
    ;add [di], 48d
    
    add [di], dl
    mov dl, 0  
    jnc NotC1
    mov dl, 1
    NotC1:
    ;cmp [di], 58d
    ;jl notMinOf
    ;mov dl, 1d
    ;sub [di], 10d
    ;notMinOf:
    
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
    mov dl, 0  
    jnc NotC2
    mov dl, 1
    NotC2:
    ;cmp [di], 58d
    ;jge of2
    ;mov dl, 0
    ;nof2:
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
     
COMMENT *     
of2:
    sub [di], 10d
    mov dl, 1
    cmp cx, 1
    je kek
jmp nof2  


kek:
    mov dh, 1;  
jmp nof2
*    
    
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

proc_write:
    create_file:
        pusha
        mov ah, 3ch ;create file
        mov dx, offset output_file
        xor cx, cx  ;file without attributes
        int 21h
        jc error
    go_write:
        mov [handle], ax
        mov bx, ax
        mov dx, offset byte_buf
        mov cx, 1
        lea si, max
        mov di, [si]
        lea bp, byte_buf
    write_byte:
        cmp di, -1
        je exit_writeln
        mov ah, 40h ;write to file
        mov al, res[di-1]
        mov [bp], al
        int 21h
        jc error
        dec di
        jmp write_byte
    exit_writeln:
        call close_file
        popa
ret      


;in bp - addr of num
;in si - size of num
;in bx - addr of file_name
proc_read:
    open_file:
        pusha
        mov ah, 3dh ;open file
        xor al, al  ;only reading mode
        mov dx, bx 
        xor cx, cx  ;file without attributes
        int 21h
        jc error
    go_read: 
        mov [handle], ax
        mov bx, ax
        ;mov dx, offset byte_buf
        mov cx, 1 ;read 1 byte
        push 0
    read_byte:
        mov ah, 3fh ;read from file
        int 21h
        jc error
        cmp ax, 0
        je create_number
        mov [bp], dl
        inc bp
        jmp read_byte
    create_number:
        exit_readln:
            call close_file
            popa
            ret

close_file:
    pusha
    mov ah, 3eh ;close file
    mov bx, [handle]
    int 21h
    jc error
    popa
    ret

error:
    mov ah, 9
    mov dx, offset error_str
    int 21h
    jmp exit_program

exit_program:   
    int 20h

main: 

    lea bp, buf
    lea si, num
    lea bx, file_name1
    call proc_read

    lea bp,buf2
    lea si, num2
    lea bx, file_name2
    call proc_read
  
    call start
    
    lea di, res
    call proc_strlen
    mov max, ax
    
    call proc_write

int 20h
num dw 0
num2 dw 0
max dw 0
min dw 0
buf db MAX_PATH dup(0) 
buf2 db MAX_PATH dup(0) 
res db MAX_PATH dup(0) 
file_name1  db 'number1.bin', 0
file_name2  db 'number2.bin', 0
output_file db 'output.bin', 0
error_str   db 'Error!', 13, 10, '$'
byte_buf    db 0 
handle      dw ?       
         
         

