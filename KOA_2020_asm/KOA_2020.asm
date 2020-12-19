; Генерация выполнена успешно. Дата: 19.12.2020 07:40:44
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
V_16	 BYTE	"Date: ", 0
V_17	 BYTE	". Time: ", 0
V_18	 BYTE	".", 0
V_20	 BYTE	"-----------------------------------------------", 0
V_23	 BYTE	"Havok", 0
V_24	 BYTE	"Joker", 0
V_26	 DWORD	100
V_27	 DWORD	70
V_28	 DWORD	1
V_29	 DWORD	2
V_30	 DWORD	0
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
V_15	 BYTE	512 DUP(0)
V_19	 DWORD	0
V_21	 BYTE	512 DUP(0)
V_22	 BYTE	0
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
; 13	 ti=@@;
	 push OFFSET _getDate
	 call GetDate
	 push eax
	 pop PV_7
	 invoke CharToUint, PV_7
	 push eax
	 pop V_19
; 14	 ri;
	 ret
GetCurrentTime ENDP
main PROC
; 19	 @@;
	 invoke GetCurrentTime
	 push eax
	 pop PV_7
	 invoke cWriteLine, PV_7
	 push eax
; 20	 l@;
	 push OFFSET V_20
	 pop PV_7
	 invoke cWriteLine, PV_7
	 push eax
; 21	 ti;
; 22	 ti;
; 24	 i=llv;
	 push OFFSET V_23
	 push OFFSET V_24
	 push OFFSET strTemp
	 call Concat
	 push eax
	 push OFFSET V_21
	 call AssignmentString
; 25	 ti=llvll@v;
	 push V_26
	 push V_27
	 pop eax
	 pop ebx
	 add eax, ebx
	 push eax
	 push V_28
	 push V_29
	 pop PV_7
	 pop PV_6
	 invoke GetRandom, PV_7, PV_6
	 push eax
	 pop eax
	 pop ebx
	 add eax, ebx
	 push eax
	 pop V_25
; 27	 rl;
	 push V_30
	 call ExitProcess
main ENDP
end main
