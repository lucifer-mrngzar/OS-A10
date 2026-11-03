# Operating Systems Lab — Assignment 10

**Indian Institute of Technology Patna (IIT Patna)**  
**Name:** Ranveer Gupta  
**Roll Number:** 2401MC20  
**Platform:** xv6-riscv

## Overview

This repository contains the implementation of Assignment 10 for the Operating Systems Lab. The assignment explores memory management and page replacement mechanisms by extending the xv6-riscv operating system.

The work covers four major components:

1. Physical Memory Tracking
2. Virtual-to-Physical Address Translation
3. Page-Table Inspection and Protection
4. Page Replacement Algorithms (FIFO, LRU, and Optimal)

## Implementations

### 1. Physical Memory Tracking

Extended the physical memory allocator in `kernel/kalloc.c` to track:

- Total allocated physical pages
- Total freed physical pages
- Currently allocated pages
- Available physical pages

Implemented a `memstats()` function and exposed it through the `memstats` system call.

**Test program:** `user/memtest.c`

The test allocates and releases three pages using `sbrk()` and displays memory statistics at each stage.

### 2. Virtual-to-Physical Address Translation

Implemented `vtop()` in `kernel/vm.c` to translate a user virtual address into its corresponding physical address.

The implementation:
- Walks the current process's page table.
- Checks whether the page is valid and user-accessible.
- Extracts the physical frame address.
- Preserves the page offset during translation.
- Rejects invalid or unmapped addresses.

**System call:** `vtop()`  
**Test program:** `user/vttest.c`

### 3. Page-Table Inspection and Protection

Implemented two functions in `kernel/vm.c`:

- `pageinfo()`: Displays the physical frame address and page permission flags: Present (P), Writable (W), and User (U).
- `setreadonly()`: Removes write permission from a mapped user page by clearing the `PTE_W` bit.

Both functions were exposed through system calls.

**System calls:** `pageinfo()`, `setreadonly()`  
**Test program:** `user/pagetest.c`

The test verifies that write permission is removed and that an attempted write triggers the expected page fault.

### 4. Page Replacement Algorithms

Implemented three page replacement algorithms in `user/pagereplace.c`:

- **FIFO (First-In First-Out):** Replaces the page that entered memory earliest.
- **LRU (Least Recently Used):** Replaces the page that has not been accessed for the longest time.
- **Optimal:** Replaces the page whose next use is farthest in the future.

**Reference String:**

```text
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
```

Each algorithm was tested with 3, 4, and 5 frames. The program displays the frame contents after each reference, identifies hits and faults, and calculates their respective ratios.

#### Results

| Frames | Algorithm | Hits | Faults | Hit Ratio | Fault Ratio |
|---:|---|---:|---:|---:|---:|
| 3 | FIFO | 5 | 15 | 25% | 75% |
| 3 | LRU | 8 | 12 | 40% | 60% |
| 3 | Optimal | 11 | 9 | 55% | 45% |
| 4 | FIFO | 10 | 10 | 50% | 50% |
| 4 | LRU | 12 | 8 | 60% | 40% |
| 4 | Optimal | 12 | 8 | 60% | 40% |
| 5 | FIFO | 11 | 9 | 55% | 45% |
| 5 | LRU | 13 | 7 | 65% | 35% |
| 5 | Optimal | 13 | 7 | 65% | 35% |

**Observation:** Optimal produced the fewest page faults for all tested frame counts. LRU also outperformed FIFO for the given reference string.

## System Calls Added

| System Call | Functionality |
|---|---|
| `memstats()` | Displays physical memory statistics |
| `vtop(va)` | Translates a virtual address into a physical address |
| `pageinfo(va)` | Displays page-table information and permission flags |
| `setreadonly(va)` | Removes write permission from a user page |

## Repository Structure

```text
.
├── kernel/
│   ├── kalloc.c
│   ├── vm.c
│   ├── syscall.c
│   ├── syscall.h
│   ├── sysproc.c
│   └── defs.h
│
├── user/
│   ├── memtest.c
│   ├── vttest.c
│   ├── pagetest.c
│   ├── pagereplace.c
│   ├── user.h
│   └── usys.pl
│
├── Makefile
│
├── Report/
│   └── Assignment_10_Report.pdf
│
└── Screenshots/
    ├── Q1_memtest.png
    ├── Q2_vttest.png
    ├── Q3_pagetest.png
    ├── Q4_page_replacement.png
    └── Q4_comparison_table.png
```

## Building and Running

This project uses the xv6-riscv environment.

1. Clone the repository:

```bash
git clone <repository-url>
cd <repository-directory>
```

2. Build and start xv6:

```bash
make qemu
```

3. Run the test programs at the xv6 shell prompt:

```text
memtest
vttest
pagetest
pagereplace
```

**Note:** The test programs are included in the `UPROGS` list in the Makefile.

## Conclusion

This assignment provided practical experience with physical memory allocation, page-table traversal, virtual memory protection, system call implementation, and page replacement strategies in xv6-riscv.

All four implementations were compiled and tested successfully.

---

**Course:** Operating Systems Lab  
**Institution:** Indian Institute of Technology Patna
