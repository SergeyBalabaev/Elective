#include <stdio.h> 
#include <unistd.h> 
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include "safe_printf_lib.h"

#ifdef DEBUG
	#define info(... ) safe_printf(__VA_ARGS__)
#else
	#define info(... )
#endif


int has_initialized = 0;	//���� ������������� malloc_init
void* managed_memory_start; //��������� �� ������ ���������� ������
void* last_valid_address;	//��������� �� ��������� ��������� �����

struct mem_control_block {
	int is_available;
	int size;
};

void malloc_init()
{
	last_valid_address = sbrk(0);	// �������� ��������� �� ��������� ��������� �����
	managed_memory_start = last_valid_address; // �.�. ������ ��� �� ���������, �� ������=�����
	has_initialized = 1;			//����������������� ���������� ������������� malloc_init
}


void* malloc(long numbytes) {
	/*
	static int i = 1;
	safe_printf("%d) Malloc %ld bytes\n", i, numbytes);
	i++;
	*/
	void* current_location;							//������� ������������ ���������
	struct mem_control_block* current_location_mcb; //������� ������������ ���������, ����������� � ���� struct
	void* memory_location = NULL;					// ������������ ��������
	if (!has_initialized) {
		malloc_init();
	}
	numbytes = numbytes + sizeof(struct mem_control_block); // ��������� � ���������� ������� ������ ������ ���������
	current_location = managed_memory_start; // �������������� ������� �������� ��������� ��������� �������

	while (current_location != last_valid_address) //��������� �� ������, ���� �� ��������� ���������� ���������� ������
	{
		current_location_mcb =	(struct mem_control_block*)current_location; //������� � current_location_mcb �������� �������� ���������

		if (current_location_mcb->is_available)
		{
			if (current_location_mcb->size >= numbytes)
			{
				current_location_mcb->is_available = 0; // ������� ������. ������� ����
				memory_location = current_location;		// ������������ �������� = �������� ��������
				break;
			}
		}
		current_location = current_location + current_location_mcb->size; //���� ������� ������� �����, �� ��������� �� ������ ������� ������
	}

	if (!memory_location) //���� ��� �������� ���� ���������� �����, �� �� ����� �������� ��������� �������, �� �������� ��� ������
	{
		sbrk(numbytes); //�������� program break �� numbytes
		memory_location = last_valid_address;		// ��������� ����� ��������� �� ���������� ���������� ������
		last_valid_address = last_valid_address + numbytes; // ������� ��������� ��������� �����
		current_location_mcb = memory_location;		//�������������� current_location_mcb
		current_location_mcb->is_available = 0;
		current_location_mcb->size = numbytes;
	}
	info("Allocated:\t from %p to %p\n", memory_location, memory_location + numbytes);
	memory_location = memory_location + sizeof(struct mem_control_block); // ���������� ��������� �� ������������ �������� ����� ���������
	return memory_location; //���������� ���������
}

void free(void* firstbyte) {
	struct mem_control_block* mcb;
	mcb = firstbyte - sizeof(struct mem_control_block); //������� ��������� �� ������  mem_control_block
	mcb->is_available = 1; //�������� ���� ���������
	info("Free:\t\t from %p to %p\n", mcb, firstbyte - sizeof(struct mem_control_block) + mcb->size);
	return;
}

