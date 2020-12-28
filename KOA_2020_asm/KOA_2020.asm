; Генерация выполнена успешно. Дата: 28.12.2020 15:43:58
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
V_16	 BYTE	"Date: ", 0
V_17	 BYTE	". Time: ", 0
V_18	 BYTE	".", 0
V_19	 BYTE	"-----------------------------------------------", 0
V_22	 BYTE	"10", 0
V_23	 DWORD	10
V_24	 DWORD	20
V_26	 DWORD	100
V_27	 BYTE	" Самое большое число!", 0
V_28	 DWORD	0
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
V_15	 BYTE	512 DUP(0)
V_20	 BYTE	512 DUP(0)
V_21	 DWORD	0
V_25	 DWORD	0
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
GetCurrentTime ENDP
main PROC
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
; 21	 ti=l@llvv;
	 push OFFSET V_22
	 pop TEMP_V_7
	 invoke CharToUint, TEMP_V_7
	 push eax
	 push V_23
	 push V_24
	 pop eax
	 pop ebx
	 mul ebx
	 push eax
	 pop eax
	 pop ebx
	 add eax, ebx
	 push eax
	 pop V_21
; 22	 ti=l;
	 push V_26
	 pop V_25
; 23	 i=ii@vlv;
	 push OFFSET V_20
	 push V_21
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_27
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_20
	 call AssignmentString
; 24	 i@;
	 push OFFSET V_20
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 25	 i=ll@;
	 push V_23
	 push V_26
	 pop TEMP_V_7
	 pop TEMP_V_6
	 invoke GetRandom, TEMP_V_6, TEMP_V_7
	 push eax
	 pop V_25
; 26	 i=i@;
	 push V_25
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET V_20
	 call AssignmentString
; 27	 i@;
	 push OFFSET V_20
	 pop TEMP_V_7
	 invoke cWriteLine, TEMP_V_7
; 28	 rl;
	 push V_28
	 call ExitProcess
main ENDP
end main
