MAX_PATH EQU 255
;ds:si - source
;es:di - dest
jmp main

;ds:si - input buf
proc_writeln:
    pusha
    cld
    mov ah, 0Eh
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
    ;es:di - output buf 
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

main: 
    mov ax, cs
    mov ds, ax
    lea si, Str
    call proc_writeln
    
    mov ax, cs
    mov es, ax
    lea di, buf
    call proc_readln
    
    lea si, buf
    call proc_writeln  
                     
    mov cx, 255
    lea di, buf                 
    call proc_strlen
   

int 20h
Str db 'Enter string:', 0
buf db MAX_PATH dup(0)