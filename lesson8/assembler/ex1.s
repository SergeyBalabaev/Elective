 .global _start
        .text
_start:
        # write(1, message, 12)
        mov     $1, %rax                # ��������� ����� 1
        mov     $1, %rdi                # ��������� � �������� ������������ 1
        mov     $message, %rsi          # �������� ����� ������
        mov     $12, %rdx               # ������ ������
        syscall                         # ��������� �����

        # exit(0)
        mov     $60, %rax               # ��������� ����� 1
        mov     $0, %rdi                # �������� 0 � ������� ���������
        syscall                         # ��������� �����
        .data
message:
        .ascii  "Hello, MIET\n"
