.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/SDL_Lib.lib
ExitProcess PROTO : DWORD
_compare PROTO : DWORD, :DWORD
_strln PROTO : DWORD
_out PROTO : DWORD
_outInt PROTO : DWORD


.stack 4096
.const
	_DIVISION_BY_ZERO_ERROR BYTE 'Ошибка выполнения: деление на ноль', 0
	L0 BYTE 'unknown', 0
	L1 DWORD 10
	L2 DWORD 5
	L3 BYTE 'numone more then numtwo', 0
	L4 BYTE 'numone equal numtwo', 0
	L5 BYTE 'numone not equal numtwo', 0
	L6 BYTE 'sum of operations is', 0
	L7 BYTE 'dmitriy', 0
	L8 BYTE 'not dmitriy', 0
	L9 BYTE 'dmitriy equal dmitriy', 0
	L10 BYTE 'dmitriy equal not dmitriy', 0
	L11 BYTE 'length of dmitriy', 0
	L12 DWORD 0
.data
	_operationssumresult		DWORD 0 ; bzint
	_mainnameone		DWORD 0 ; str
	_mainnametwo		DWORD 0 ; str
	_maintemp		DWORD 0 ; str
	_mainnumone		DWORD 0 ; bzint
	_mainnumtwo		DWORD 0 ; bzint
	_maincomp		DWORD 0 ; bzint
	_mainstrlength		DWORD 0 ; bzint
	_mainlessorequal		DWORD 0 ; bzint
	_mainmoreorequal		DWORD 0 ; bzint
	_mainless		DWORD 0 ; bzint
	_mainnotequal		DWORD 0 ; bzint
	_mainsum		DWORD 0 ; bzint

.code
_operationssum PROC _m: DWORD, _z: DWORD, _y: DWORD, _x: DWORD
	push		_x
	push		_y

	pop		eax
	pop		ebx
	add		eax, ebx
	push		eax

	push		_z

	pop		eax
	pop		ebx
	add		eax, ebx
	push		eax

	push		_m

	pop		eax
	pop		ebx
	add		eax, ebx
	push		eax

	pop			_operationssumresult

	mov		eax, _operationssumresult
	ret		16
_operationssum ENDP

main PROC
	push		offset L0
	pop			_maintemp

	push		L1
	pop			_mainnumone

	push		L2
	pop			_mainnumtwo

	push		_mainnumone
	push		_mainnumtwo
	pop		ebx
	pop		eax
	cmp		eax, ebx
	jna		FALSE23
	push		offset L3
	pop			_maintemp

	push		_maintemp
	call		_out

FALSE23: 
	push		_mainnumone
	push		_mainnumtwo
	pop		ebx
	pop		eax
	cmp		eax, ebx
	jne		FALSE28
	je		TRUE28
TRUE28: 
	push		offset L4
	pop			_maintemp

	push		_maintemp
	call		_out

	jmp		IFOUT28
FALSE28: 
	push		offset L5
	pop			_maintemp

	push		_maintemp
	call		_out

IFOUT28: 
	push		_mainnumone
	push		_mainnumtwo

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jbe		LESSOREQUALS38
	push		0
	jna		MORE38
LESSOREQUALS38:
	push		1
MORE38:
	pop			_mainlessorequal

	push		_mainnumone
	push		_mainnumtwo

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jae		MOREOREQUAL39
	push		0
	jnb		LESS39
MOREOREQUAL39:
	push		1
LESS39:
	pop			_mainmoreorequal

	push		_mainnumone
	push		_mainnumtwo

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jb		LESS40
	push		0
	ja		MORE40
LESS40:
	push		1
MORE40:
	pop			_mainless

	push		_mainnumone
	push		_mainnumtwo

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jne		NOTEQUAL41
	push		0
	je		EQUAL41
NOTEQUAL41:
	push		1
EQUAL41:
	pop			_mainnotequal

	push		offset L6
	pop			_maintemp

	push		_mainlessorequal
	push		_mainmoreorequal
	push		_mainless
	push		_mainnotequal
	call		_operationssum
	push		eax
	pop			_mainsum

	push		_maintemp
	call		_out

	push		_mainsum
	call		_outInt

	push		offset L7
	pop			_mainnameone

	push		offset L8
	pop			_mainnametwo

	push		_mainnameone
	push		_mainnameone
	call		_compare
	push		eax
	pop			_maincomp

	push		offset L9
	pop			_maintemp

	push		_maintemp
	call		_out

	push		_maincomp
	call		_outInt

	push		_mainnameone
	push		_mainnametwo
	call		_compare
	push		eax
	pop			_maincomp

	push		offset L10
	pop			_maintemp

	push		_maintemp
	call		_out

	push		_maincomp
	call		_outInt

	push		offset L11
	pop			_maintemp

	push		_maintemp
	call		_out

	push		_mainnameone
	call		_strln
	push		eax
	pop			_mainstrlength

	push		_mainstrlength
	call		_outInt

	push		L12
	call		ExitProcess
main ENDP
end main
