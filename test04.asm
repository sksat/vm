00000000  55                push ebp
00000001  89E5              mov ebp,esp
00000003  83EC18            sub esp,byte +0x18
00000006  C745F400000A00    mov dword [ebp-0xc],0xa0000
0000000D  C745F040010000    mov dword [ebp-0x10],0x140
00000014  C745ECC8000000    mov dword [ebp-0x14],0xc8
0000001B  83EC04            sub esp,byte +0x4
0000001E  6A78              push byte +0x78
00000020  6A78              push byte +0x78
00000022  6A14              push byte +0x14
00000024  6A14              push byte +0x14
00000026  6A01              push byte +0x1
00000028  FF75F0            push dword [ebp-0x10]
0000002B  FF75F4            push dword [ebp-0xc]
0000002E  E812000000        call dword 0x45
00000033  83C420            add esp,byte +0x20
00000036  EBFE              jmp short 0x36
00000038  55                push ebp
00000039  89E5              mov ebp,esp
0000003B  8B5508            mov edx,[ebp+0x8]
0000003E  8B450C            mov eax,[ebp+0xc]
00000041  01D0              add eax,edx
00000043  5D                pop ebp
00000044  C3                ret
00000045  55                push ebp
00000046  89E5              mov ebp,esp
00000048  83EC14            sub esp,byte +0x14
0000004B  8B4510            mov eax,[ebp+0x10]
0000004E  8845EC            mov [ebp-0x14],al
00000051  8B4518            mov eax,[ebp+0x18]
00000054  8945F8            mov [ebp-0x8],eax
00000057  EB33              jmp short 0x8c
00000059  8B4514            mov eax,[ebp+0x14]
0000005C  8945FC            mov [ebp-0x4],eax
0000005F  EB1F              jmp short 0x80
00000061  8B45F8            mov eax,[ebp-0x8]
00000064  0FAF450C          imul eax,[ebp+0xc]
00000068  89C2              mov edx,eax
0000006A  8B45FC            mov eax,[ebp-0x4]
0000006D  01D0              add eax,edx
0000006F  89C2              mov edx,eax
00000071  8B4508            mov eax,[ebp+0x8]
00000074  01C2              add edx,eax
00000076  0FB645EC          movzx eax,byte [ebp-0x14]
0000007A  8802              mov [edx],al
0000007C  8345FC01          add dword [ebp-0x4],byte +0x1
00000080  8B45FC            mov eax,[ebp-0x4]
00000083  3B451C            cmp eax,[ebp+0x1c]
00000086  7ED9              jng 0x61
00000088  8345F801          add dword [ebp-0x8],byte +0x1
0000008C  8B45F8            mov eax,[ebp-0x8]
0000008F  3B4520            cmp eax,[ebp+0x20]
00000092  7EC5              jng 0x59
00000094  90                nop
00000095  C9                leave
00000096  C3                ret
