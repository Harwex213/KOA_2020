; ��������� ��������� �������. ����: 29.12.2020 23:53:01
.586
.model flat, stdcall
.stack 4096
includelib kernel32.lib
includelib libucrt.lib
includelib StandartLib.lib
includelib	 "DateTime.lib"
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
V_14	 BYTE	"Date: ", 0
V_15	 BYTE	". Time: ", 0
V_16	 BYTE	".", 0
V_17	 BYTE	"-----------------------", 0
V_23	 DWORD	0
V_24	 DWORD	2077
V_27	 DWORD	1444
V_29	 BYTE	"����� ������������ ����� �����: ", 0
V_30	 BYTE	", ", 0
V_31	 DWORD	100
V_32	 DWORD	10
V_33	 BYTE	" ����� ������� �����!", 0
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
; 12	 ti=l@vlv@vlv;
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
; 13	 ri;
	 mov eax, OFFSET V_13
	 ret
GetCurrentTime ENDP
main PROC
	call StartRandom
; 18	 @@;
	 invoke GetCurrentTime
	 push eax
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 19	 l@;
	 push OFFSET V_17
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 20	 ti;
; 21	 ti;
; 22	 ti;
; 23	 ti;
; 24	 ti=ll@;
	 push V_23
	 push V_24
	 pop TEMP_V_7
	 pop TEMP_V_6
	 invoke GetRandom, TEMP_V_6, TEMP_V_7
	 push eax
	 pop V_22
; 25	 ti=ll@;
	 push V_23
	 push V_24
	 pop TEMP_V_7
	 pop TEMP_V_6
	 invoke GetRandom, TEMP_V_6, TEMP_V_7
	 push eax
	 pop V_25
; 26	 ti=l;
	 push V_27
	 pop V_26
; 27	 ti=li@vlvi@vlvi@v;
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
; 28	 i@;
	 push OFFSET V_28
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 29	 qill@vig
	 push V_22
	 push V_31
	 push V_32
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
; 31	 qiig
	 push V_22
	 push V_26
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jb ELSE_BLOCK_1
; 33	 i=i@;
	 push V_22
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_18
	 call AssignmentString
	 jmp END_BLOCK_1
ELSE_BLOCK_1: 
; 37	 i=i@;
	 push V_26
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_18
	 call AssignmentString
END_BLOCK_1: 
	 jmp END_BLOCK_0
ELSE_BLOCK_0: 
; 42	 qiig
	 push V_25
	 push V_26
	 pop ebx
	 pop eax
	 cmp eax, ebx
	 jb ELSE_BLOCK_2
; 44	 i=i@;
	 push V_25
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_18
	 call AssignmentString
	 jmp END_BLOCK_2
ELSE_BLOCK_2: 
; 48	 i=i@;
	 push V_26
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_18
	 call AssignmentString
END_BLOCK_2: 
END_BLOCK_0: 
; 52	 i=ilv;
	 push OFFSET V_18
	 push OFFSET V_33
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_18
	 call AssignmentString
; 53	 i@;
	 push OFFSET V_18
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 54	 rl;
	 push V_23
	 call ExitProcess
main ENDP
end main
