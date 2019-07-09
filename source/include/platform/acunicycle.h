// SPDX-License-Identifier: MIT

#include <stdint.h>
#include "kalloc.h"
#include "lock.h"
#include "mem.h"
#include "string.h"


#ifdef __LP64__
#define ACPI_MACHINE_WIDTH      64
#else
#define ACPI_MACHINE_WIDTH      32
#endif

#define COMPILER_DEPENDENT_INT64        int64_t
#define COMPILER_DEPENDENT_UINT64       uint64_t

#define ACPI_UINTPTR_T      uintptr_t


#define ACPI_USE_DO_WHILE_0
#define ACPI_USE_NATIVE_DIVIDE
#define ACPI_USE_NATIVE_MATH64
#define ACPI_USE_SYSTEM_CLIBRARY

#define ACPI_MUTEX_TYPE     ACPI_OSL_MUTEX
// cache is a really size of bucket
#define ACPI_CACHE_T		size_t
#define ACPI_MUTEX          lock_t*
#define ACPI_SPINLOCK       lock_t*

// Redefine AcpiOsFree as our macro
#define ACPI_USE_ALTERNATE_PROTOTYPE_AcpiOsFree
#define AcpiOsFree(ptr) kfree(ptr)
#define AcpiOsFreeSize(ptr, Size) kfree_size(ptr, Size)