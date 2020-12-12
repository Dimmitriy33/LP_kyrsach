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
	L0 BYTE 'as', 0
	L1 BYTE '1234567890', 0
	L2 DWORD 10
	L3 BYTE '2 more then 1 is', 0
	L4 DWORD 2
	L5 DWORD 1
	L6 BYTE '2 less then 1 is', 0
	L7 BYTE '2 less or equal 1 is', 0
	L8 BYTE '2 more or equal 1 is', 0
	L9 BYTE '2 equal 1 is', 0
	L10 BYTE '2 not equal 1 is', 0
	L11 DWORD 5
	L12 BYTE 'zashel v if v ifelse', 0
	L13 BYTE 'zashel v else v ifelse', 0
	L14 BYTE 'zashel v if v if', 0
	L15 BYTE 'контрольный пример', 0
	L16 DWORD 0
.data
	_sumz		DWORD 0 ; bzint
	_myfunce		DWORD 0 ; str
	_mainx		DWORD 0 ; bzint
	_mainy		DWORD 0 ; bzint
	_mainz		DWORD 0 ; bzint
	_mainv		DWORD 0 ; bzint
	_mainsa		DWORD 0 ; str
	_mainsb		DWORD 0 ; str
	_mainsc		DWORD 0 ; str
	_mainsd		DWORD 0 ; str

.code
_sum PROC _y: DWORD, _x: DWORD
	push		_x
	push		_y

	pop		eax
	pop		ebx
	add		eax, ebx
	push		eax

	pop			_sumz

	mov		eax, _sumz
	ret		8
_sum ENDP

_myfunc PROC _b: DWORD, _a: DWORD
	push		offset L0
	pop			_myfunce

	mov		eax, _myfunce
	ret		8
_myfunc ENDP

main PROC
	push		offset L1
	pop			_mainsa

	push		offset L1
	pop			_mainsb

	push		L2
	pop			_mainv

	push		_mainsa
	push		_mainsb
	call		_compare
	push		eax
	pop			_mainx

	push		_mainsa
	call		_strln
	push		eax
	pop			_mainx

	push		_mainx
	call		_outInt

	push		offset L3
	pop			_mainsd

	push		L4
	push		L5

	pop		ebx
	pop		eax
	cmp		eax, ebx
	ja		MORE32
	push		0
	jb		LESS32
MORE32:
	push		1
LESS32:
	pop			_mainv

	push		_mainsd
	call		_out

	push		_mainv
	call		_outInt

	push		offset L6
	pop			_mainsd

	push		L4
	push		L5

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jb		LESS36
	push		0
	ja		MORE36
LESS36:
	push		1
MORE36:
	pop			_mainv

	push		_mainsd
	call		_out

	push		_mainv
	call		_outInt

	push		offset L7
	pop			_mainsd

	push		L4
	push		L5

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jbe		LESSOREQUALS40
	push		0
	jna		MORE40
LESSOREQUALS40:
	push		1
MORE40:
	pop			_mainv

	push		_mainsd
	call		_out

	push		_mainv
	call		_outInt

	push		offset L8
	pop			_mainsd

	push		L4
	push		L5

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jae		MOREOREQUAL44
	push		0
	jnb		LESS44
MOREOREQUAL44:
	push		1
LESS44:
	pop			_mainv

	push		_mainsd
	call		_out

	push		_mainv
	call		_outInt

	push		offset L9
	pop			_mainsd

	push		L4
	push		L5

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jne		NOTEQUAL48
	push		0
	je		EQUAL48
EQUAL48:
	push		1
NOTEQUAL48:
	pop			_mainv

	push		_mainsd
	call		_out

	push		_mainv
	call		_outInt

	push		offset L10
	pop			_mainsd

	push		L4
	push		L5

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jbe		LESSOREQUALS52
	push		0
	jna		MORE52
LESSOREQUALS52:
	push		1
MORE52:
	pop			_mainv

	push		_mainsd
	call		_out

	push		_mainv
	call		_outInt

	push		L2
	push		L11
	pop		ebx
	pop		eax
	cmp		eax, ebx
	jnb		FALSE55
	jna		TRUE55
TRUE55: 
	push		offset L12
	pop			_mainsd

	push		_mainsd
	call		_out

	jmp		IFOUT55
FALSE55: 
	push		offset L13
	pop			_mainsd

	push		_mainsd
	call		_out

IFOUT55: 
	push		L2
	push		L11
	pop		ebx
	pop		eax
	cmp		eax, ebx
	jb		FALSE65
	push		offset L14
	pop			_mainsd

	push		_mainsd
	call		_out

FALSE65: 
	push		L11
	pop			_mainy

	push		_mainx
	push		_mainy
	call		_sum
	push		eax
	pop			_mainz

	push		_mainsa
	push		_mainsb
	call		_myfunc
	push		eax
	pop			_mainsc

	push		offset L15
	call		_out

	push		_mainsc
	call		_out

	push		_mainsc
	call		_out

	push		L16
	call		ExitProcess
main ENDP
end main
