; Генерация выполнена успешно. Дата: 30.12.2020 13:09:52
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
.const
V_0	 BYTE	"DateTime.lib", 0
V_16	 BYTE	"Date: ", 0
V_17	 BYTE	". Time: ", 0
V_18	 BYTE	".", 0
V_19	 BYTE	"------------------------", 0
V_25	 DWORD	0
V_26	 DWORD	2077
V_28	 DWORD	102
V_30	 DWORD	1444
V_31	 DWORD	2
V_32	 DWORD	10
V_33	 DWORD	213
V_34	 DWORD	10000
V_35	 DWORD	123
V_36	 DWORD	3120
V_37	 DWORD	132103
V_38	 DWORD	100000
V_39	 DWORD	78888
V_41	 BYTE	"Найти максимальное среди чисел: ", 0
V_42	 BYTE	", ", 0
V_43	 BYTE	" Самое большое число!", 0
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
V_20	 BYTE	512 DUP(0)
V_21	 BYTE	0
V_22	 BYTE	0
V_23	 BYTE	0
V_24	 DWORD	0
V_27	 DWORD	0
V_29	 DWORD	0
V_40	 BYTE	512 DUP(0)
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
main PROC
	call StartRandom
; 18	 @@;
	 invoke GetCurrentTime
	 push eax
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 19	 l@;
	 push OFFSET V_19
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 20	 ti;
; 21	 ti;
; 22	 ti;
; 23	 ti;
; 24	 ti=ll@;
	 push V_25
	 push V_26
	 pop TEMP_V_7
	 pop TEMP_V_6
	 invoke GetRandom, TEMP_V_6, TEMP_V_7
	 push eax
	 pop V_24
; 25	 ti=l;
	 push V_28
	 pop V_27
; 26	 ti=llvlvllvlvvllvvll@lvvlv;
	 push V_30
	 push V_31
	 pop ebx
	 pop eax
	 cmp ebx, 0h
	 je @DIVZERO
	 cdq
	 div ebx
	 push eax
	 push V_32
	 pop eax
	 pop ebx
	 mul ebx
	 push eax
	 push V_33
	 push V_34
	 pop eax
	 pop ebx
	 mul ebx
	 push eax
	 push V_35
	 pop eax
	 pop ebx
	 mul ebx
	 push eax
	 pop eax
	 pop ebx
	 sub ebx, eax
	 push ebx
	 push V_36
	 push V_37
	 pop eax
	 pop ebx
	 mul ebx
	 push eax
	 pop eax
	 pop ebx
	 add eax, ebx
	 push eax
	 push V_25
	 push V_38
	 pop TEMP_V_7
	 pop TEMP_V_6
	 invoke GetRandom, TEMP_V_6, TEMP_V_7
	 push eax
	 push V_31
	 pop ebx
	 pop eax
	 cmp ebx, 0h
	 je @DIVZERO
	 cdq
	 div ebx
	 push eax
	 pop eax
	 pop ebx
	 add eax, ebx
	 push eax
	 push V_39
	 pop eax
	 pop ebx
	 add eax, ebx
	 push eax
	 pop V_29
; 27	 ti=li@vlvi@vlvi@v;
	 push OFFSET V_41
	 push V_24
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_42
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push V_27
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_42
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push V_29
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_40
	 call AssignmentString
; 28	 i@;
	 push OFFSET V_40
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 29	 qiig
	 push V_24
	 push V_27
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_0
; 31	 qiig
	 push V_24
	 push V_29
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_1
; 33	 i=i@;
	 push V_24
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_20
	 call AssignmentString
	 jmp END_BLOCK_1
ELSE_BLOCK_1: 
; 37	 i=i@;
	 push V_29
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_20
	 call AssignmentString
END_BLOCK_1: 
	 jmp END_BLOCK_0
ELSE_BLOCK_0: 
; 42	 qiig
	 push V_27
	 push V_29
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jle ELSE_BLOCK_2
; 44	 i=i@;
	 push V_27
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_20
	 call AssignmentString
	 jmp END_BLOCK_2
ELSE_BLOCK_2: 
; 48	 i=i@;
	 push V_29
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_20
	 call AssignmentString
END_BLOCK_2: 
END_BLOCK_0: 
; 52	 i=ilv;
	 push OFFSET V_20
	 push OFFSET V_43
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_20
	 call AssignmentString
; 53	 i@;
	 push OFFSET V_20
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 54	 rl;
	 push V_25
	 call ExitProcess
@DIVZERO:
	 push OFFSET _divZeroException
	 call cWriteLine
	 push -1
	 call ExitProcess
main ENDP
end main
