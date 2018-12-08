;es:di - buf
;cx - memsize
;al - symbol        
proc_memset:
    cld
    zero_loop:
        stosb
        loop zero_loop
    ret

;ds:si - src    
;es:di - dest
;cx - memsize        
proc_memcpy:
    push ax
    cld
    cpy_loop:
        lodsb
        stosb
        loop cpy_loop
         
    pop ax
    ret
;ds:si - src    
;es:di - dest
;cx - memsize        
proc_memcpy:
    cld
    cpy_loop:
        movsb
        loop cpy_loop
         
    ret
    
;ds:si - src    
;es:di - dest
;cx - memsize        
proc_memcpy:
    cld
    rep movsb      
    ret