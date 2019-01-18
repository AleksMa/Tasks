format PE GUI 4.0
entry start
 
include 'win32a.inc'
 
BUFFER_SIZE     = 257
 
 
section '.data' data readable writeable
        base db BUFFER_SIZE dup(?)
        power db BUFFER_SIZE dup(?)
        res db BUFFER_SIZE dup(?)
        modul db BUFFER_SIZE dup(?)
 
        pwSwap db BUFFER_SIZE dup(?)
        pwBase db BUFFER_SIZE dup(?)
        pwExp db BUFFER_SIZE dup(?)
 
        baseFileName db 'C:\Users\Fujitsu\PycharmProjects\ASM\RSA\RSASM\base.txt',0
        powerFileName db 'C:\Users\Fujitsu\PycharmProjects\ASM\RSA\RSASM\power.txt',0
        resFileName db 'C:\Users\Fujitsu\PycharmProjects\ASM\RSA\RSASM\res.txt',0
        modFileName db 'C:\Users\Fujitsu\PycharmProjects\ASM\RSA\RSASM\mod.txt',0
 
        lpBytesBase dd ?
        lpBytesPower dd ?
        lpBytesRes dd ?
        lpBytesMod dd ?
        hFile dd ?
 
section '.code' code readable executable
        proc OpenAndRead, fn,buf,bufSize,bytesRead
             push    eax
             invoke CreateFile, [fn], GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0
             mov [hFile], eax
 
             ;invoke  GetFileSize, [hFile], 0
             ;mov [fSize], eax
 
             invoke ReadFile, [hFile], [buf], [bufSize], [bytesRead], 0
             invoke CloseHandle, [hFile]
 
             pop     eax
             ret
        endp
 
        proc OpenAndWrite, fn,buf,bufSize,bytesRead
             push    eax
             invoke CreateFile, [fn], GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
             mov [hFile], eax
 
             ;invoke  GetFileSize, [hFile], 0
             ;mov [fSize], eax
 
             invoke WriteFile, [hFile], [buf], [bufSize], [bytesRead], 0
             invoke CloseHandle, [hFile]
 
             pop     eax
             ret
        endp
 
        proc Memset mem, memLen, set_byte
             push eax ecx edi
             pushf
             cld
             mov eax, [set_byte]
             mov edi, [mem]
             mov ecx, [memLen]
             rep stosb
             popf
             pop edi ecx eax
             ret
        endp
 
 
        proc ByteMul base, res, numberLen, mul_byte
             push eax bx edi ecx
             pushf
             xor bx, bx
             cld
 
             mov al,  byte[mul_byte]
             mov ecx, [numberLen]
             mov edi, [base]
             .loop:
                push ax
                mul byte[edi]
                add al, bl
                mov bl, ah
                mov ah, 0
                stdcall ByteAdd, [res], [numberLen], eax
 
                jnc .not_over
                inc bl
                .not_over:
                  inc [res]
                  inc edi
                  pop ax
             loop .loop
             popf
             pop ecx edi bx eax
             ret
        endp
 
 
        proc ByteAdd, res, numberLen, add_byte
             push eax edi ecx
             pushf
             cld
             clc
             mov ah, byte[add_byte]
 
             mov ecx, [numberLen]
             mov edi, [res]
             .loop:
                mov al, ah
                add al, [edi]
                jc .over
                stosb
                jmp .end
             .over:
                mov ah, 1
                stosb
             loop .loop
             .end:
                popf
                pop ecx edi eax
             ret
        endp
       
 
        proc Mult, number1, number2, result, numberLen
            push eax ecx edi
            cld
            clc
 
            xor eax, eax
            mov ecx, [numberLen]
            .loop:
                mov edi, [number1]
                mov al, [edi]
                mov ah, 0
                stdcall ByteMul, [number2], [result], [numberLen], eax
                inc [number1]
                inc [result]
            loop .loop
            pop edi ecx eax
            ret
        endp
 
 
        proc Sum, number1, number2, result, numberLen
             push ax edi ecx
             cld
             clc
             mov ecx, [numberLen]
             .loop:
                mov edi, [number1]
                mov al,  [edi]
                mov edi, [number2]
                jc .over
                add al, [edi]
                jmp .save_digit
              .over:
                add al, 1
                jc .over_again
                add al, [edi]
                jmp .save_digit
              .over_again:
                mov al, [edi]
              .save_digit:
                mov edi, [result]
                mov [edi], al
                inc [number1]
                inc [number2]
                inc [result]
             loop .loop
 
 
             pop ecx edi ax
             ret
        endp
 
        proc ShiftRight, number, numberLen
             push esi ecx eax
             pushf
             cld
             clc
             mov ecx, [numberLen]
             mov esi, [number]
             lodsb
             shr al, 1
             mov [esi-1], al
             dec ecx
             .loop:
                lodsb
                mov ah, al
                shr al, 1
                mov [esi-1], al
                and ah, 1
                cmp ah, 0
                jz .not_zero
                add [esi-2], BYTE 80h
                .not_zero:
             loop .loop
             popf
             pop eax ecx esi
             ret
        endp
 
        proc ShiftLeft, number, numberLen
             push esi ecx eax
             pushf
             cld
             clc
             mov ecx, [numberLen]
             mov esi, [number]
             lodsb
             mov ah, al
             shr ah, 7
             shl al, 1
             mov [esi-1], al
             dec ecx
             .loop:
                 lodsb
                 mov [esi-1], ah
                 mov ah, al
                 shr ah, 7
                 shl al, 1
                 add [esi-1], al
             loop .loop
             popf
             pop eax ecx esi
             ret
        endp
 
        proc InverseNum, num, res, numberLen
             push eax ecx edi esi
             mov edi, [res]
             mov esi, [num]
             mov ecx, [numberLen]
 
             .loop:
               lodsb
               xor al, BYTE 255
               stosb
             loop .loop
             mov ah, 00h
             mov al, 01h
             stdcall ByteAdd, [res], [numberLen], eax
 
             pop esi edi ecx eax
             ret
        endp
 
        proc Subs, number1, number2, result, numberLen
             push eax edi ecx
             stdcall InverseNum, [number2], [result], BUFFER_SIZE
             stdcall Sum, [number1], [result], [result], BUFFER_SIZE
             pop ecx edi eax
             ret
        endp
 
        proc Less, number1, number2, numberLen
             push edi esi ecx ebx
             pushf
             mov ecx, [numberLen]
             mov edi, [number1]
             add edi, [numberLen]
             dec edi
 
             mov esi, [number2]
             add esi, [numberLen]
             dec esi
             .loop:
                mov bl, [edi]
                mov bh, [esi]
                cmp bl, bh
                jb .end_true
                ja .end_false
                dec edi
                dec esi
             loop .loop
             .end_false: ;;equal or greater
             mov eax, 00h
             jmp .exit
             .end_true:
             mov eax, 01h
             .exit:
             popf
             pop ebx ecx esi edi
             ret
        endp
 
        proc FindLen, number, numberLen
             push edi edx eax
             mov ecx, [numberLen]
             mov edi, [number]
             add edi, [numberLen]
             dec edi
             mov ebx, 0 ;start init
             .loop:
                cmp [edi], BYTE 0
                jne .find_bit_shift
                dec edi
             loop .loop
             jmp .exit
             .find_bit_shift:
             mov edx, 128
             mov ebx, 7
             .bit_loop:
                mov eax, [edi]
                and eax, edx
                cmp eax, 0
                jne .exit
                shr edx, 1
                dec ebx
             jmp .bit_loop
             .exit:
             pop eax edx edi
             ret
        endp
 
        proc MultMod, number1, number2, result, module, numberLen
                push edi eax ebx ecx edx
                stdcall Memset, [result], [numberLen], 0
                stdcall FindLen, [number1], [numberLen]
                cmp ecx, 0
                je .break
 
                mov edi, [number1]
                add edi, ecx
                dec edi
 
                dec ecx
                shl ecx, 3
                add ecx, ebx
                inc ecx
 
                push ecx
                mov edx, 1
                mov cl, bl
                shl edx, cl
                pop ecx
                .loop:
                        stdcall ShiftLeft, [result], [numberLen]
                        stdcall Less, [result], [module], [numberLen]
                        cmp eax, 0
                        jne .less1
                            stdcall InverseNum, [module], [module], [numberLen]
                            stdcall Sum, [result], [module], [result], [numberLen]
                            stdcall InverseNum, [module], [module], [numberLen]
                        .less1:
                        mov eax, [edi]
                        and eax, edx
                        cmp eax, 0
                        je .no_add
                            stdcall Sum, [result], [number2], [result], [numberLen]
                        .no_add:
                        stdcall Less, [result], [module], [numberLen]
                        cmp eax, 0
                        jne .less2
                            stdcall InverseNum, [module], [module], [numberLen]
                            stdcall Sum, [result], [module], [result], [numberLen]
                            stdcall InverseNum, [module], [module], [numberLen]
                        .less2:
                        cmp edx, 1
                        je .correct_edx
                        shr edx, 1
                        jmp .continue
                        .correct_edx:
                        mov edx, 128
                        dec edi
                        .continue:
                        dec ecx
                        jz .break
                jmp .loop
                .break:
                pop edx ecx ebx eax edi
                ret
        endp
 
        proc PowMod, number1, number2, result, module, numberLen
             push edi
             invoke RtlMoveMemory, pwBase, [number1], [numberLen]
             invoke RtlMoveMemory, pwExp, [number2], [numberLen]
             mov edi, [result]
             mov [edi], BYTE 1
             mov edi, pwExp
             .loop:
                stdcall FindLen, pwExp, [numberLen]
                cmp ecx, 0
                je .exit
                   mov eax, 1
                   and eax, [edi]
                   cmp eax, 1
                   jne .zero
                       stdcall MultMod, [result],pwBase,pwSwap,[module], [numberLen]
                       invoke RtlMoveMemory, [result], pwSwap, [numberLen]
                   .zero:
                   stdcall MultMod, pwBase,pwBase,pwSwap,[module], [numberLen]
                   invoke RtlMoveMemory, pwBase, pwSwap, [numberLen]
                   stdcall ShiftRight, pwExp, [numberLen]
             jmp .loop
             .exit:
             pop edi
             ret
        endp
 
        start:
             stdcall OpenAndRead, baseFileName, base, BUFFER_SIZE, lpBytesBase
             stdcall OpenAndRead, powerFileName, power, BUFFER_SIZE, lpBytesPower
             stdcall OpenAndRead, modFileName, modul, BUFFER_SIZE, lpBytesMod
 
             stdcall PowMod, base,power,res,modul, BUFFER_SIZE
             stdcall FindLen, res, BUFFER_SIZE
             stdcall OpenAndWrite, resFileName, res, ecx, lpBytesRes
             invoke ExitProcess, 0
 
section '.idata' import data readable writeable
 
        library kernel,'KERNEL32.DLL'
 
        import  kernel,\
                RtlMoveMemory, 'RtlMoveMemory',\
                CreateFile, 'CreateFileA',\
                WriteFile, 'WriteFile',\
                ReadFile, 'ReadFile',\
                CloseHandle, 'CloseHandle',\
                ExitProcess,'ExitProcess'