        .global _start
        .text
_start:
        mov     $0, %rax                # ��������� ����� 1
        mov     $0, %rdi                # ��������� � �������� ������������ 1
        mov     $x, %rsi          # �������� ����� ������
        mov     $5, %rdx                # ������ ������
        syscall                         # ��������� �����

        # write(1, message, 12)
        mov     $1, %rax                # ��������� ����� 1
        mov     $1, %rdi                # ��������� � �������� ������������ 1
        mov     $x, %rsi          # �������� ����� ������
        mov     $12, %rdx               # ������ ������
        syscall                         # ��������� �����

        # exit(0)
        mov     $60, %rax               # ��������� ����� 1
        mov     $0, %rdi                # �������� 0 � ������� ���������
        syscall                         # ��������� �����
        
        .bss
x:      .fill    10

        .data
message:
        .ascii  "123456789"
