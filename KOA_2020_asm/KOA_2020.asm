; ----- Start -----
.586
.model flat, stdcall
includelib kernel32.lib
includelib libucrt.lib
ExitProcess PROTO: DWORD
; ----- End Start -----
; ----- Function Protos -----
FindMax PROTO : DWORD, : DWORD
; ----- End Function Protos -----
.stack 4096
.const
L0 db	"date.lib"
L1 dd	10
L2 dd	900
L3 dd	310
L4 dd	100
L5 dd	1
L6 dd	20
L7 dd	9
.data
arr_FindMax dd	0
i_FindMax dd	0
k_FindMax dd	0
j_I0 dd	0
k_main dd	0
; ----- Code -----
.code
end main; ----- End Code -----
