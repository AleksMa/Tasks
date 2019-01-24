format PE GUI 4.0
entry start

include 'C:\fasmw17304\INCLUDE\win32a.inc'

BUFFER_SIZE     EQU 257

section '.data' data readable writeable
        num1 db BUFFER_SIZE dup(?)
        num2 db BUFFER_SIZE dup(?)
        res db BUFFER_SIZE dup(0)
        temp db BUFFER_SIZE dup(0)
        modul db BUFFER_SIZE dup(?)
        outp db BUFFER_SIZE dup(?)

        num1FileName db 'C:\RSA\c.txt',0
        num2FileName db 'C:\RSA\d.txt',0
        resFileName db 'C:\RSA\menc.txt',0
        modFileName db 'C:\RSA\mod.txt',0

        outSize dd BUFFER_SIZE
        lpBytesNum1 dd ?
        lpBytesNum2 dd ?
        lpBytesMod dd ?
        lpBytesRes dd ?
        hFile dd ?

section '.code' code readable executable

        proc OpenAndRead, fn, buf, bufSize, bytesRead
             push    eax
             ;Создает/открывает файл, кидает в еах хендл (это CreateFileA)
             invoke CreateFile, [fn], GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0
             mov [hFile], eax

             ;Читает из файла в массив
             invoke ReadFile, [hFile], [buf], [bufSize], [bytesRead], 0
             invoke CloseHandle, [hFile]

             pop     eax
             ret
        endp

        proc OpenAndWrite, fn, buf, bufSize, bytesRead
             push    eax
             invoke CreateFile, [fn], GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
             mov [hFile], eax

             ;Читает из массива в файл
             invoke WriteFile, [hFile], [buf], [bufSize], [bytesRead], 0
             invoke CloseHandle, [hFile]

             pop     eax
             ret
        endp

        ;Сумма

        proc Sum, number1, number2, result, numberLen
             push ax edi ecx
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

        ; СДВИГ ВЛЕВО  (*2)

       proc ShiftLeft, number, numberLen
             push esi ecx eax
             pushf
             cld
             clc
             mov ecx, [numberLen]
             mov esi, [number]
             lodsb   ; es:si -> al
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

        ;Вычитание (мемное)

        proc TrueSub, number1, number2, result, numberLen
        pusha

        xor cx, cx
        sub1:
            mov eax, [numberLen]
            cmp cx, ax
            jz exit_sub
            xor ax, ax

        sub_1:
            mov dx, 256
            sub dx, ax

            mov ax, dx
            mov edi, [number1]
            mov dl, [edi]
            add ax, dx
            mov edi, [number2]
            mov dl, [edi]
            sub ax, dx
            cmp ax, 255
            ja sub_2

            mov edi, [result]
            mov [edi], al
            inc cx
            inc [number1]
            inc [number2]
            inc [result]

            jmp sub2
        sub_2:                ;Не занимаем следующий разряд
            mov edi, [result]
            mov [edi], al
            inc cx
            inc [number1]
            inc [number2]
            inc [result]

            jmp sub1
        sub2:                ;Занимаем
            mov ax, 1d
            jmp sub_1
        exit_sub:
        popa
        ret
        endp


        ; Школьное умножение по модулю
        proc ModularMul, number1, number2, result, numberLen, modulus
 
             push eax edi ecx
             pushf
             stdcall SetArray, [result], [numberLen], 0
             stdcall Remodulate, [number1], [numberLen], [modulus]
             stdcall Remodulate, [number2], [numberLen], [modulus]
             mov ecx, [numberLen]
             mov edi, [number1]
             add edi, [numberLen]
             dec edi
 
             .loop:   ;Обход по всем байтам
                cmp ecx, 0
                je .exit_loop
                push ecx
                mov ecx, 8d
 
                .loopa:      ;По битам байта
                    stdcall ShiftLeft, [result], [numberLen]

                    stdcall Less, [result], [modulus], [numberLen]
                    cmp eax, 0
                    jne .less
                    stdcall TrueSub, [result], [modulus], [result], [numberLen]
                    .less:

                    xor ax, ax
                    mov al, [edi]
 
                    mov bx, 1
                    shl bx, cl
                    shr bx, 1
                    test ax, bx


                    jz .endif
                    ;Если в текущем байте единичка
                    stdcall Sum, [result], [number2], [result], [numberLen]
                    .endif:

                    stdcall Less, [result], [modulus], [numberLen]
                    cmp eax, 0
                    jne .less2
                    stdcall TrueSub, [result], [modulus], [result], [numberLen]
                    .less2:
 
                loop .loopa
 
                pop ecx
                dec edi
                dec ecx
             jmp .loop
 
             .exit_loop:
 
             popf
             pop ecx edi eax
             ret
 
        endp

        ;Вычет по модулю number от modulus

        proc Remodulate, number, numberLen, modulus
             pusha
             .loop:
                stdcall Less, [number], [modulus], [numberLen]
                cmp eax, 0
                jne .exit   ; <
                stdcall TrueSub, [number], [modulus], [number], [numberLen]
                jmp .loop
             .exit:
             popa
             ret
        endp

        ;Удаление незначащих нулей с конца (мы же в LE)

        proc RemoveNils number, numberLen
            pusha
            mov edi, [number]
            mov ecx, [numberLen]
            add edi, ecx
            dec edi
            .go_destroy:
                cmp ecx, 1
                je .exit_destroy
                cmp [edi], BYTE 0
                jne .exit_destroy
                dec [outSize]
                dec edi
                dec ecx
                jmp .go_destroy
            .exit_destroy:
            popa
            ret
        endp

        proc SetArray array, numberLen, val
             pusha
             mov ecx, [numberLen]
             mov edi, [array]
             .loop:
                 mov ebx, [val]
                 mov [edi], bl
                 inc edi
             loop .loop
             popa
             ret
        endp

        proc CopyArray source, dest, numberLen
            pusha

            mov ecx, [numberLen]
            .copyloop:
                mov edi, [source]
                mov al, [edi]
                mov edi, [dest]
                mov [edi], al
                inc [source]
                inc [dest]
            loop .copyloop

            popa
            ret
        endp

        ;Возведение в степень по модулю
        proc ModularExponentiation number1, number2, result, numberLen, modulus, buffer

           push eax edi ecx
             pushf

             mov ecx, [numberLen]
             mov edi, [number2]
             add edi, [numberLen]
             dec edi
             mov [res], 1


 
             .loop:
                cmp ecx, 0
                je .exit_loop
                push ecx
                mov ecx, 8d
 
                .loopa:
                    stdcall ModularMul, [result], [result], [buffer], [numberLen], [modulus]
                    stdcall CopyArray, [buffer], [result], [numberLen]

                    xor ax, ax
                    mov al, [edi]
 
                    mov bx, 1
                    shl bx, cl
                    shr bx, 1
                    test ax, bx

                    jz .endif
                    stdcall ModularMul, [result], [number1], [buffer], [numberLen], [modulus]
                    stdcall CopyArray, [buffer], [result], [numberLen]
                    .endif:
 
                loop .loopa
 
                pop ecx
                dec edi
                dec ecx
             jmp .loop
 
             .exit_loop:
 
             popf
             pop ecx edi eax

             stdcall RemoveNils, [result], BUFFER_SIZE

             ret


        endp


       ; Кладет в eax 1, если number1 < number2 , иначе 0

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
             .end_false:
             mov eax, 0
             jmp .exit
             .end_true:
             mov eax, 1
             .exit:
             popf
             pop ebx ecx esi edi
             ret
        endp

        proc Len, number, numberLen
             push edi esi ecx ebx
             pushf
             mov eax, [numberLen]
             mov edi, [number]
             add edi, [numberLen]
             dec edi
             .loop:
                mov bl, [edi]
                cmp bl, 0
                jne .exit_loop
                dec edi
                dec eax
             jmp .loop
             .exit_loop:
             popf
             pop ebx ecx esi edi
        ret
        endp



        start:
             stdcall OpenAndRead, num1FileName, num1, BUFFER_SIZE, lpBytesNum1
             stdcall OpenAndRead, num2FileName, num2, BUFFER_SIZE, lpBytesNum2
             stdcall OpenAndRead, modFileName, modul, BUFFER_SIZE, lpBytesMod


             stdcall ModularExponentiation, num1, num2, res, BUFFER_SIZE, modul, temp

             stdcall OpenAndWrite, resFileName, res, [outSize], lpBytesRes
             invoke ExitProcess, 0

section '.idata' import data readable writeable

        library kernel,'KERNEL32.DLL'

        import  kernel,\
                CreateFile, 'CreateFileA',\
                WriteFile, 'WriteFile',\
                ReadFile, 'ReadFile',\
                CloseHandle, 'CloseHandle',\
                ExitProcess,'ExitProcess'