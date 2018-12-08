use16                       
org 100h                    
    jmp start               
;-------------------------------------------------------------------------------
;
file_name db 'number1.bin',0
s_error   db 'Error!',13,10,'$'
s_file    db '----[ file "kek.txt" ]$'
endline   db 13,10,'$'
s_pak     db 'Press any key...$'
buffer    db 255 dup (0)            
handle    rw 1              
;-------------------------------------------------------------------------------
;
start:
    mov ah,3Dh                      ;open file
    xor al,al                       ; read only
    mov dx,file_name                ;filename
    xor cx,cx               
    int 21h                
    jnc @F                  
    call error_msg          
    jmp exit                
@@: mov [handle],ax                 
                                    
    mov bx,ax                       ;descriptor
    mov ah,3Fh                      ;read
    mov dx,buffer                   ;dest
    mov cx,254              
    int 21h                 
    jnc @F                 
    call error_msg          
    jmp close_file          
 
@@: mov bx,buffer
    add bx,ax               
    mov byte[bx],'$'                   
 
    mov ah,9
    mov dx,buffer
    int 21h                
    mov dx,endline
    int 21h                
             
 
close_file:
    mov ah,3Eh             
    mov bx,[handle]        
    int 21h               
    jnc exit               
    call error_msg        
 
exit:
    mov ah,9
    mov dx,s_pak
    int 21h                
    mov ah,8            
    int 21h                
    mov ax,4C00h          
    int 21h                
 
;-------------------------------------------------------------------------------
; 
error_msg:
    mov ah,9
    mov dx,s_error
    int 21h                
    ret
;-------------------------------------------------------------------------------
; 
; CX - 
