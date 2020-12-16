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
V_0 db	"date.lib"
V_5 dd	10
V_6 dd	900
V_7 dd	310
V_8 dd	100
V_10 dd	1
V_12 dd	20
V_13 dd	9
.data
V_2 dd	0
V_3 dd	0
V_4 dd	0
V_9 dd	0
V_11 dd	0
.code
FindMax PROC, i: dd, arr: dd
FindMax ENDP
main PROC
main ENDP
end main
