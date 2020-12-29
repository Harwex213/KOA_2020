; Генерация выполнена успешно. Дата: 29.12.2020 21:00:46
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
; User Functions:
GetCurrentTime PROTO
.const
V_0	 BYTE	"DateTime.lib", 0
V_14	 BYTE	"Date: ", 0
V_15	 BYTE	". Time: ", 0
V_16	 BYTE	".", 0
V_17	 BYTE	"-----------------------", 0
V_23	 DWORD	0
V_24	 DWORD	2077
V_27	 DWORD	100
V_29	 BYTE	"Найти максимальное среди чисел: ", 0
V_30	 BYTE	", ", 0
V_31	 DWORD	10
V_32	 BYTE	" Самое большое число!", 0
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
V_13	 BYTE	512 DUP(0)
V_18	 BYTE	512 DUP(0)
V_19	 BYTE	0
V_20	 BYTE	0
V_21	 BYTE	0
V_22	 DWORD	0
V_25	 DWORD	0
V_26	 DWORD	0
V_28	 BYTE	512 DUP(0)
.code
GetCurrentTime PROC
; 11	 ti=l@vlv@vlv;
	 push OFFSET V_14
	 push OFFSET _getDate
	 call GetDate
	 push eax
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_15
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET _getTime
	 call GetTime
	 push eax
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_16
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_13
	 call AssignmentString
; 12	 ri;
	 mov eax, OFFSET V_13
	 ret
GetCurrentTime ENDP
main PROC
; 17	 @@;
	 invoke GetCurrentTime
	 push eax
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 18	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 19	 ti;
; 20	 ti;
; 21	 ti;
; 22	 ti;
; 23	 ti=ll@;
	 push V_23
	 push V_24
	 pop TEMP_V_7
	 pop TEMP_V_6
	 invoke GetRandom, TEMP_V_6, TEMP_V_7
	 push eax
	 pop V_22
; 24	 ti=l;
	 push V_24
	 pop V_25
; 25	 ti=l;
	 push V_27
	 pop V_26
; 26	 ti=li@vlvi@vlvi@v;
	 push OFFSET V_29
	 push V_22
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_30
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push V_25
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_30
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push V_26
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_28
	 call AssignmentString
; 27	 i@;
	 push OFFSET V_28
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 28	 qill@vig
	 push V_22
	 push V_27
	 push V_31
	 pop TEMP_V_7
	 pop TEMP_V_6
	 invoke GetRandom, TEMP_V_6, TEMP_V_7
	 push eax
	 pop eax
	 pop ebx
	 add eax, ebx
	 push eax
	 push V_25
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jb ELSE_BLOCK_0
; 30	 qiig
	 push V_22
	 push V_26
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jb ELSE_BLOCK_1
; 32	 i=i@;
	 push V_22
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_18
	 call AssignmentString
	 jmp END_BLOCK_1
ELSE_BLOCK_1: 
; 36	 i=i@;
	 push V_26
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_18
	 call AssignmentString
END_BLOCK_1: 
	 jmp END_BLOCK_0
ELSE_BLOCK_0: 
; 41	 qiig
	 push V_25
	 push V_26
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jb ELSE_BLOCK_2
; 43	 i=i@;
	 push V_25
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_18
	 call AssignmentString
	 jmp END_BLOCK_2
ELSE_BLOCK_2: 
; 47	 i=i@;
	 push V_26
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_18
	 call AssignmentString
END_BLOCK_2: 
END_BLOCK_0: 
; 51	 i=ilv;
	 push OFFSET V_18
	 push OFFSET V_32
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_18
	 call AssignmentString
; 52	 i@;
	 push OFFSET V_18
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 53	 rl;
	 push V_23
	 call ExitProcess
main ENDP
end main
