        global  _call_c_method

        section .text



; =============================================================================
;
; unsigned long int _call_c_method( void* method_pointer, unsigned char num_params, unsigned long int method_params[] )
;
;   void* method_point
;      A pointer to the method to be called.
;
;   unsigned char num_params
;      The number of arguments.  gnu c might allow for only 64 arguments.
;
;   unsigned long nt method_params[]
;      An array, in first-to-last order, containing our arguments.
;
; Returns whatever was returned by the call to *method_pointer.
;
_call_c_method:
        push    ebp             ;save parent stack frame.
        mov     ebp, esp        ;set current stack frame to our current scope.

      ;load up our method's params from the array passed in, if any.
        cmp     dword [ebp+12],0    ;are there any parameters at all?
        je      @call_the_method
        mov     ecx,dword [ebp+12]  ;load the second param: number of params.

      ;we gotta load our params in reverse order, "__cdecl"-style.
        mov     edx,ecx
        shl     edx,2
        add     edx,dword [ebp+16]  ;load the third param: pointer to array of params.
      @push_params_loop_start:
        sub    edx,4           ;move on to the next param.
        push    dword [edx]     ;push our param onto the stack...
        loop    @push_params_loop_start

       @call_the_method:        ;make it so!
        call    [ebp+8]         ;first param: method pointer.
        mov     ebx,eax         ;preserve our called method's returned value.

      ;cleanup: discard any params after method call.
        cmp     dword [ebp+12],0    ;are there any parameters at all?
        je      @end_of_call_c_method
        mov     ecx,dword [ebp+12]    ;reload our second param: number of params.
      @pop_params_loop_start:
        pop     dword edx             ;throwaway old params...
        loop    @pop_params_loop_start

      @end_of_call_c_method:
        pop     ebp             ;restore parent stack frame.
        mov     eax,ebx         ;return our called method's returned value.
        ret


; =============================================================================
;
; void _memcpy( void* dest_ptr, void* src_ptr, unsigned long int len ))
;
;   void* dest_ptr
;      A pointer to the destination to copy to.
;
;   unsigned char num_params
;      A pointer to the source to copy from.
;
;   unsigned long nt method_params[]
;      An integer indication the size, in bytes, of the block to be copied.
;
; Returns the destination pointer value passed in.
;
;
; TODO: This method REALLY needs to be optimized:
;   * use of movs and it's variants is a GOOD possibility.
;   * it might also be wise to have a separate copy method for null-terminated strings.
;   * how about taking advantage of cpu optmizations (SSE, MMX, etc.)
;   * how about copying data 64bit bits at a time?
;
_memcpy:
        push    ebp             ;save parent stack frame.
        mov     ebp, esp        ;set current stack frame to our current scope.

        mov     ebx,[ebp+8]     ;first param: destination pointer.
        mov     edx,[ebp+12]    ;first param: source pointer.
        mov     ecx,[ebp+16]    ;block size to be copied.

      @copy_the_block_32bits_at_a_time:
        cmp     ecx,4
        jge     @copy_the_block_16bits_at_a_time
      @copy_dword_loop_start:
        mov     dword eax,[edx+ecx]
        mov     [ebx+ecx],dword eax
        sub     ecx,4
        cmp     ecx,4
        jge     @copy_dword_loop_start

      @copy_the_block_16bits_at_a_time:
        cmp     ecx,2
        jge     @copy_the_block_8bits_at_a_time
      @copy_word_loop_start:
        mov     word ax,[edx+ecx]
        mov     [ebx+ecx],word ax
        sub     ecx,2
        cmp     ecx,2
        jge     @copy_word_loop_start

      @copy_the_block_8bits_at_a_time:
        jecxz   @end_of_memcpy
      @copy_byte_loop_start:
        mov     byte al,[edx+ecx]
        mov     [ebx+ecx],byte al
        dec     ecx
        jecxz   @copy_byte_loop_start

      @end_of_memcpy:
        pop     ebp             ;restore parent stack frame.
        mov     eax,[ebp+8]     ;memcpy should return the destination pointer.
        ret


;===============================================================================
;
;
;
;
;
_peekb:
        push    ebp         ;save parent stack frame.
        mov     ebp,esp     ;set current stack frame to our current scope.
        xor     eax,eax

        pop     ebp             ;restore parent stack frame.
        mov     ebx,[ebp+8]     ;first param: source pointer.
      @end_of_peekb:
        pop     ebp             ;restore parent stack frame.
        mov     al,[ebx]
        ret

_peekw:
        push    ebp         ;save parent stack frame.
        mov     ebp,esp     ;set current stack frame to our current scope.
        xor     eax,eax

        pop     ebp             ;restore parent stack frame.
        mov     ebx,[ebp+8]     ;first param: source pointer.
      @end_of_peekw:
        pop     ebp             ;restore parent stack frame.
        mov     ax,[ebx]
        ret

_peekd:
        push    ebp         ;save parent stack frame.
        mov     ebp,esp     ;set current stack frame to our current scope.
        xor     eax,eax

        pop     ebp             ;restore parent stack frame.
        mov     ebx,[ebp+8]     ;first param: source pointer.
      @end_of_peekd:
        pop     ebp             ;restore parent stack frame.
        mov     eax,[ebx]
        ret


_pokeb:
        push    ebp         ;save parent stack frame.
        mov     ebp,esp     ;set current stack frame to our current scope.
        xor     eax,eax

        pop     ebp             ;restore parent stack frame.
        mov     ebx,[ebp+8]     ;first param: dest pointer.
        mov     al,[ebp+12]     ;second param: byte value.
        mov     [ebx], al
      @end_of_pokeb:
        pop     ebp             ;restore parent stack frame.
        ret

_pokew:
        push    ebp         ;save parent stack frame.
        mov     ebp,esp     ;set current stack frame to our current scope.
        xor     eax,eax

        pop     ebp             ;restore parent stack frame.
        mov     ebx,[ebp+8]     ;first param: dest pointer.
        mov     ax,[ebp+12]     ;second param: byte value.
        mov     [ebx], ax
      @end_of_pokew:
        pop     ebp             ;restore parent stack frame.
        ret

_poked:
        push    ebp         ;save parent stack frame.
        mov     ebp,esp     ;set current stack frame to our current scope.
        xor     eax,eax

        pop     ebp             ;restore parent stack frame.
        mov     ebx,[ebp+8]     ;first param: dest pointer.
        mov     eax,[ebp+12]     ;second param: byte value.
        mov     [ebx], eax
      @end_of_poked:
        pop     ebp             ;restore parent stack frame.
        ret

