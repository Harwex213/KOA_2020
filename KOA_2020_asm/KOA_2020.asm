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
V_8 DWORD	100
V_10 DWORD	1
V_12 DWORD	20
V_13 DWORD	9
.data
V_2 DWORD	0
V_3 DWORD	0
V_4 DWORD	0
V_9 DWORD	0
V_11 DWORD	0
.code
FindMax PROC, i: DWORD, arr: DWORD
	ret
FindMax ENDP
main PROC
	push 0
	call ExitProcess
main ENDP
end main
