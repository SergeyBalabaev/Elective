.data
printf_format:
        .string "%d\n"
 
.text
.global main
main:
        movl  $0, %eax          /* � %eax ����� ���������, ������� � 
                                   ������ ��� ����� ��������         */
        movl  $10, %ecx         /* 10 ����� �����                    */
 
sum:
        addl  %ecx, %eax        /* %eax = %eax + %ecx                */
        loop  sum
 
        /* %eax = 55, %ecx = 0 */
 
/*
 * ��������� ��� ������� ����� � %eax �� ����� � ��������� ���������
 */
        pushl %eax
        pushl $printf_format
        call  printf
        addl  $8, %esp
 
        movl  $0, %eax
        ret