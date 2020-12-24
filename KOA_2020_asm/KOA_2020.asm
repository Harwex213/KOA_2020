; Генерация выполнена успешно. Дата: 19.12.2020 12:36:19
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
; ----- User and Libs Function Protos -----
GetCurrentTime PROTO
; ----- End User and Libs Function Protos -----
.const
V_0	 BYTE	"DateTime.lib", 0
V_14	 BYTE	"Date: ", 0
V_15	 BYTE	". Time: ", 0
V_16	 BYTE	".", 0
V_17	 BYTE	"-----------------------------------------------", 0
V_22	 DWORD	0
V_23	 DWORD	2077
V_26	 BYTE	"Найти максимальное среди чисел: ", 0
V_27	 BYTE	", ", 0
V_28	 BYTE	1
V_29	 BYTE	"Самое большое число!", 0
.data
PV_0	 DWORD	?
PV_1	 DWORD	?
PV_2	 DWORD	?
PV_3	 DWORD	?
PV_4	 DWORD	?
PV_5	 DWORD	?
PV_6	 DWORD	?
PV_7	 DWORD	?
PV_8	 BYTE	?
PV_9	 BYTE	?
PV_10	 BYTE	?
PV_11	 BYTE	?
PV_12	 BYTE	?
PV_13	 BYTE	?
PV_14	 BYTE	?
PV_15	 BYTE	?
strTemp	 BYTE	 512 DUP(0)
strConvert	 BYTE	 512 DUP(0)
_getDate	 BYTE	 512 DUP (0)
_getTime	 BYTE	 512 DUP(0)
V_13	 BYTE	512 DUP(0)
V_18	 BYTE	512 DUP(0)
V_19	 BYTE	0
V_20	 BYTE	0
V_21	 DWORD	0
V_24	 DWORD	0
V_25	 BYTE	512 DUP(0)
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
	 pop PV_7
	 invoke cWriteLine, PV_7
; 18	 l@;
	 push OFFSET V_17
	 pop PV_7
	 invoke cWriteLine, PV_7
; 19	 ti;
; 20	 ti;
; 21	 ti;
; 22	 ti=ll@;
	 push V_22
	 push V_23
	 pop PV_7
	 pop PV_6
	 invoke GetRandom, PV_6, PV_7
	 push eax
	 pop V_21
; 23	 ti=ll@;
	 push V_22
	 push V_23
	 pop PV_7
	 pop PV_6
	 invoke GetRandom, PV_6, PV_7
	 push eax
	 pop V_24
; 24	 ti=li@vlvi@v;
	 push OFFSET V_26
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
	 push V_24
	 push OFFSET strConvert
	 call UintToChar
	 push eax
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_25
	 call AssignmentString
; 25	 i@;
	 push OFFSET V_25
	 pop PV_7
	 invoke cWriteLine, PV_7
; 26	 qiig
	 push V_21
	 push V_24
	 pop eax
	 pop ebx
	 cmp eax, ebx
	 ja BODY_BLOCK1
	 jmp END_BLOCK1
BODY_BLOCK1:
	 movzx eax, V_19
	 push eax
	 movzx eax, V_28
	 push eax
	 movzx eax, V_19
	 push eax
	 movzx eax, V_28
	 push eax
END_BLOCK1:
; 36	 qi{i=i(i);}
	 movzx eax, V_19
	 push eax
	 pop eax
	 cmp eax, 0	 
	 je BODY_BLOCK2
	 jmp END_BLOCK2
BODY_BLOCK2:
	 push OFFSET V_18
	 push OFFSET V_7
	 push V_21
END_BLOCK2:
; 37	 qi{i=i(i);}
	 movzx eax, V_20
	 push eax
	 pop eax
	 cmp eax, 0h	 
	 je BODY_BLOCK3
	 jmp END_BLOCK3
BODY_BLOCK3:
	 push OFFSET V_18
	 push OFFSET V_7
	 push V_24
END_BLOCK3:
; 39	 i=ilv;
	 push OFFSET V_18
	 push OFFSET V_29
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_18
	 call AssignmentString
; 40	 i@;
	 push OFFSET V_18
	 pop PV_7
	 invoke cWriteLine, PV_7
; 41	 rl;
	 push V_22
	 call ExitProcess
main ENDP
end main
