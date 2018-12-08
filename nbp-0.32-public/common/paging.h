/* 
 * Copyright holder: Invisible Things Lab
 * 
 * This software is protected by domestic and International
 * copyright laws. Any use (including publishing and
 * distribution) of this software requires a valid license
 * from the copyright holder.
 *
 * This software is provided for the educational use only
 * during the Black Hat training. This software should not
 * be used on production systems.
 *
 */

#pragma once

#include <ntddk.h>
#include "common.h"

#define AP_PAGETABLE	1  //��ʾ����������ҳ��
#define AP_PT		2      //*****************//
#define AP_PD		4      //�ֱ��ʾ��Ϊ
#define AP_PDP		8      //����ҳ����ڴ�ҳ
#define AP_PML4		16     //*****************//

typedef enum
{
  PAT_DONT_FREE = 0, //��ʾ����ڴ�ҳ�治�ǵ�������ģ�����һ��������ڴ���м�λ�ã����ܱ��ͷ�
  PAT_POOL,//��ʾ����ڴ�ҳ����ͨ������ExAllocatePoolWithTag()�ӷǷ�ҳ���з���ĵ�һ��ҳ��
  PAT_CONTIGUOUS //��ʾ����ڴ�ҳ����ͨ������MmAllocateContiguousMemorySpecifyCache()����ĵ�һ��ҳ��
} PAGE_ALLOCATION_TYPE;

//����MmSavePage�������½ṹ�屣�������ַ�������������ַ�Ϳͻ��������ַ�Ķ�Ӧ��ϵ
typedef struct _ALLOCATED_PAGE
{

  LIST_ENTRY le; //����ͷ�����ӵ�g_PageTableList

  ULONG Flags; //��־

  PAGE_ALLOCATION_TYPE AllocationType; //��������(����)
  ULONG uNumberOfPages;         // for PAT_CONTIGUOUS only�����ڴ�ҳ��

  PHYSICAL_ADDRESS PhysicalAddress; //�����ַ
  PVOID HostAddress; //�����������ַ
  PVOID GuestAddress; //�ͻ��������ַ

} ALLOCATED_PAGE,*PALLOCATED_PAGE;

NTSTATUS NTAPI MmCreateMapping (
  PHYSICAL_ADDRESS PhysicalAddress,
  PVOID VirtualAddress,
  BOOLEAN bLargePage
);

PVOID NTAPI MmAllocateContiguousPages (
  ULONG uNumberOfPages,
  PPHYSICAL_ADDRESS pFirstPagePA
);

PVOID NTAPI MmAllocateContiguousPagesSpecifyCache (
  ULONG uNumberOfPages,
  PPHYSICAL_ADDRESS pFirstPagePA,
  ULONG CacheType
);

PVOID NTAPI MmAllocatePages (
  ULONG uNumberOfPages,
  PPHYSICAL_ADDRESS pFirstPagePA
);

NTSTATUS NTAPI MmMapGuestPages (
  PVOID FirstPage,
  ULONG uNumberOfPages
);

NTSTATUS NTAPI MmMapGuestKernelPages (
);

NTSTATUS NTAPI MmMapGuestTSS64 (
  PVOID Tss64,
  USHORT Tss64Limit
);

NTSTATUS NTAPI MmInitManager (
);

NTSTATUS NTAPI MmShutdownManager (
);

NTSTATUS NTAPI MmInitIdentityPageTable (
);
