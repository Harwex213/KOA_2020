; Генерация выполнена успешно. Дата: 30.12.2020 12:47:18
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
GetCurrentTime PROTO
Check PROTO: BYTE, : DWORD
.const
V_0	 BYTE	"DateTime.lib", 0
V_16	 BYTE	"Date: ", 0
V_17	 BYTE	". Time: ", 0
V_18	 BYTE	".", 0
V_22	 BYTE	0
V_23	 DWORD	0
V_24	 BYTE	"------------------------", 0
V_30	 DWORD	2077
V_32	 BYTE	1
V_33	 BYTE	"10", 0
V_35	 DWORD	1444
V_36	 DWORD	2
V_37	 DWORD	10
V_38	 DWORD	213
V_40	 BYTE	"Найти максимальное среди чисел: ", 0
V_41	 BYTE	", ", 0
V_42	 BYTE	" Самое большое число!", 0
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
V_15	 BYTE	512 DUP(0)
V_25	 BYTE	512 DUP(0)
V_26	 BYTE	0
V_27	 BYTE	0
V_28	 BYTE	0
V_29	 DWORD	0
V_31	 DWORD	0
V_34	 DWORD	0
V_39	 BYTE	512 DUP(0)
.code
GetCurrentTime PROC
; 12	 ti=l@vlv@vlv;
	 push OFFSET V_16
	 push OFFSET _getDate
	 call GetDate
	 push eax
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_17
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET _getTime
	 call GetTime
	 push eax
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_18
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_15
	 call AssignmentString
; 13	 ri;
	 mov eax, OFFSET V_15
	 ret
@DIVZERO:
	 push OFFSET _divZeroException
	 call cWriteLine
	 push -1
	 call ExitProcess
GetCurrentTime ENDP
Check PROC, V_20: BYTE, V_21: DWORD
; 18	 i=l;
	 movzx eax, V_22
	 push eax
	 pop eax
	 mov V_20, al
; 19	 i@;
	 push V_21
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 20	 rl;
	 mov eax, V_23
	 ret
@DIVZERO:
	 push OFFSET _divZeroException
	 call cWriteLine
	 push -1
	 call ExitProcess
Check ENDP
main PROC
	call StartRandom
; 25	 @@;
	 invoke GetCurrentTime
	 push eax
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 26	 l@;
	 push OFFSET V_24
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 27	 ti;
; 28	 ti;
; 29	 ti;
; 30	 ti;
; 31	 ti=ll@;
	 push V_23
	 push V_30
	 pop TEMP_V_7
	 pop TEMP_V_6
	 invoke GetRandom, TEMP_V_6, TEMP_V_7
	 push eax
	 pop V_29
; 32	 ti=ll@;
	 movzx eax, V_32
	 push eax
	 push OFFSET V_33
	 pop TEMP_V_7
	 pop eax
	 mov TEMP_V_15, al
	 invoke Check, TEMP_V_15, TEMP_V_7
	 push eax
	 pop V_31
; 33	 ti=llvlvlv;
	 push V_35
	 push V_36
	 pop ebx
	 pop eax
	 cmp ebx, 0h
	 je @DIVZERO
	 cdq
	 div ebx
	 push eax
	 push V_37
	 pop eax
	 pop ebx
	 mul ebx
	 push eax
	 push V_38
	 pop eax
	 pop ebx
	 sub ebx, eax
	 push ebx
	 pop V_34
; 34	 ti=li@vlvi@vlvi@v;
	 push OFFSET V_40
	 push V_29
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_41
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push V_31
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_41
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push V_34
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_39
	 call AssignmentString
; 35	 i@;
	 push OFFSET V_39
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 36	 qiig
	 push V_29
	 push V_31
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_0
; 38	 qiig
	 push V_29
	 push V_34
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_1
; 40	 i=i@;
	 push V_29
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_25
	 call AssignmentString
	 jmp END_BLOCK_1
ELSE_BLOCK_1: 
; 44	 i=i@;
	 push V_34
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_25
	 call AssignmentString
END_BLOCK_1: 
	 jmp END_BLOCK_0
ELSE_BLOCK_0: 
; 49	 qiig
	 push V_31
	 push V_34
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_2
; 51	 i=i@;
	 push V_31
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_25
	 call AssignmentString
	 jmp END_BLOCK_2
ELSE_BLOCK_2: 
; 55	 i=i@;
	 push V_34
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_25
	 call AssignmentString
END_BLOCK_2: 
END_BLOCK_0: 
; 59	 i=ilv;
	 push OFFSET V_25
	 push OFFSET V_42
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_25
	 call AssignmentString
; 60	 i@;
	 push OFFSET V_25
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 61	 rl;
	 push V_23
	 call ExitProcess
@DIVZERO:
	 push OFFSET _divZeroException
	 call cWriteLine
	 push -1
	 call ExitProcess
main ENDP
end main
