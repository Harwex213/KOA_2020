.586
.model flat, stdcall
.stack 4096
includelib kernel32.lib
includelib libucrt.lib
includelib "date.lib"
ExitProcess PROTO: DWORD
; ----- User Function Protos -----
FindMax PROTO : DWORD, : DWORD
; ----- End User Function Protos -----
.const
V_0 BYTE	"date.lib"
V_5 DWORD	10
V_6 DWORD	900
V_7 DWORD	310
V_9 BYTE	1
V_11 DWORD	20
V_12 DWORD	9
.data
PV_0 DWORD	?
PV_1 DWORD	?
PV_2 DWORD	?
PV_3 DWORD	?
PV_4 DWORD	?
PV_5 DWORD	?
PV_6 DWORD	?
PV_7 DWORD	?
PV_8 BYTE	?
PV_9 BYTE	?
PV_10 BYTE	?
PV_11 BYTE	?
PV_12 BYTE	?
PV_13 BYTE	?
PV_14 BYTE	?
PV_15 BYTE	?
V_2 DWORD	0
V_3 DWORD	0
V_4 DWORD	0
V_8 BYTE	0
V_10 DWORD	0
.code
FindMax PROC, i: DWORD, arr: DWORD
; ti=lllvlvvlv;
	 push V_5
	 push V_6
	 push V_7
	 pop eax
	 pop ebx
	 mul ebx
	 push eax
	 push V_5
	 pop eax
	 pop ebx
	 add eax, ebx
	 push eax
	 pop eax
	 pop ebx
	 add eax, ebx
	 push eax
	 push V_5
	 pop eax
	 pop ebx
	 or  eax, ebx
	 push eax
	 pop V_4
; =l;
	 movzx eax, V_9
	 push eax
	 pop eax
	 mov V_8, al
; l;
	 push V_5
	 push V_11
	 push V_12
	 pop eax
	 pop ebx
	 add eax, ebx
	 push eax
	 pop PV_7
	 pop PV_6
	 invoke FindMax, PV_8, PV_7
	 pop V_10
	ret
FindMax ENDP
main PROC
; =lllv@;
	 push V_5
	 push V_11
	 push V_12
	 pop eax
	 pop ebx
	 add eax, ebx
	 push eax
	 pop PV_7
	 pop PV_6
	 invoke FindMax, PV_8, PV_7
	 pop V_10
	push 0
	call ExitProcess
main ENDP
end main
