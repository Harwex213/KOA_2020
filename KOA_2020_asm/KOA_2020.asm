; Генерация выполнена успешно. Дата: 30.12.2020 01:52:14
.586
.model flat, stdcall
.stack 4096
includelib kernel32.lib
includelib libucrt.lib
includelib StandartLib.lib
includelib	 "DateTime.lib"
ExitProcess	 PROTO : DWORD
Concat	 PROTO : DWORD, : DWORD, : DWORD
AssignmentString	 PROTO : DWORD, : DWORD
cWrite PROTO : DWORD
cWriteLine PROTO : DWORD
GetRandom PROTO : DWORD, : DWORD
GetDate PROTO : DWORD
GetTime PROTO : DWORD
BoolToChar PROTO : DWORD, : DWORD
UintToChar PROTO : DWORD, : DWORD
CharToBool PROTO : DWORD
CharToUint PROTO : DWORD
StartRandom PROTO
; User Functions:
.const
V_0	 BYTE	"DateTime.lib", 0
V_13	 DWORD	10
V_15	 DWORD	30
V_16	 BYTE	"Amigo", 0
V_17	 BYTE	"joker", 0
V_18	 DWORD	0
.data
TEMP_V_0	 DWORD	?
TEMP_V_1	 DWORD	?
TEMP_V_2	 DWORD	?
TEMP_V_3	 DWORD	?
TEMP_V_4	 DWORD	?
TEMP_V_5	 DWORD	?
TEMP_V_6	 DWORD	?
TEMP_V_7	 DWORD	?
TEMP_V_8	 BYTE	?
TEMP_V_9	 BYTE	?
TEMP_V_10	 BYTE	?
TEMP_V_11	 BYTE	?
TEMP_V_12	 BYTE	?
TEMP_V_13	 BYTE	?
TEMP_V_14	 BYTE	?
TEMP_V_15	 BYTE	?
strTemp	 BYTE	 512 DUP(0)
strConvert	 BYTE	 512 DUP(0)
_getDate	 BYTE	 512 DUP (0)
_getTime	 BYTE	 512 DUP(0)
_divZeroException	 BYTE	 "Division by zero was detected!", 0
V_12	 DWORD	0
V_14	 DWORD	0
.code
main PROC
	call StartRandom
; 11	 ti=l;
	 push V_13
	 pop V_12
; 12	 ti=l;
	 push V_15
	 pop V_14
; 13	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_0
; 15	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 16	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_1
; 18	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_1
ELSE_BLOCK_1: 
; 22	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 23	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_2
; 25	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_2
ELSE_BLOCK_2: 
; 29	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 30	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_3
; 32	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_3
ELSE_BLOCK_3: 
; 36	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
END_BLOCK_3: 
; 38	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_4
; 40	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_4
ELSE_BLOCK_4: 
; 44	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 45	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_5
; 47	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_5
ELSE_BLOCK_5: 
; 51	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
END_BLOCK_5: 
END_BLOCK_4: 
END_BLOCK_2: 
; 55	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_6
; 57	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_6
ELSE_BLOCK_6: 
; 61	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 62	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_7
; 64	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_7
ELSE_BLOCK_7: 
; 68	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
END_BLOCK_7: 
END_BLOCK_6: 
END_BLOCK_1: 
; 72	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_8
; 74	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_8
ELSE_BLOCK_8: 
; 78	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 79	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_9
; 81	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_9
ELSE_BLOCK_9: 
; 85	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 86	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_10
; 88	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_10
ELSE_BLOCK_10: 
; 92	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 93	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_11
; 95	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 96	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_12
; 98	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_12
ELSE_BLOCK_12: 
; 102	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
END_BLOCK_12: 
	 jmp END_BLOCK_11
ELSE_BLOCK_11: 
; 107	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 108	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_13
; 110	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_13
ELSE_BLOCK_13: 
; 114	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 115	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_14
; 117	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_14
ELSE_BLOCK_14: 
; 121	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
END_BLOCK_14: 
END_BLOCK_13: 
END_BLOCK_11: 
END_BLOCK_10: 
END_BLOCK_9: 
END_BLOCK_8: 
	 jmp END_BLOCK_0
ELSE_BLOCK_0: 
; 131	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 132	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_15
; 134	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 135	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_16
; 137	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_16
ELSE_BLOCK_16: 
; 141	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 142	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_17
; 144	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_17
ELSE_BLOCK_17: 
; 148	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 149	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_18
; 151	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_18
ELSE_BLOCK_18: 
; 155	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 156	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_19
; 158	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 159	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_20
; 161	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_20
ELSE_BLOCK_20: 
; 165	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
END_BLOCK_20: 
	 jmp END_BLOCK_19
ELSE_BLOCK_19: 
; 170	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
END_BLOCK_19: 
END_BLOCK_18: 
END_BLOCK_17: 
END_BLOCK_16: 
	 jmp END_BLOCK_15
ELSE_BLOCK_15: 
; 178	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 179	 qiig
	 push V_14
	 push V_12
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_21
; 181	 l@;
	 push OFFSET V_16
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
	 jmp END_BLOCK_21
ELSE_BLOCK_21: 
; 185	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
END_BLOCK_21: 
END_BLOCK_15: 
END_BLOCK_0: 
; 189	 rl;
	 push V_18
	 call ExitProcess
@DIVZERO:
	 push OFFSET _divZeroException
	 call cWriteLine
	 push -1
	 call ExitProcess
main ENDP
end main
