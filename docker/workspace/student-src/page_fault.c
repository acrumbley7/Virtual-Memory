#include "mmu.h"
#include "pagesim.h"
#include "swapops.h"
#include "stats.h"
#include "va_splitting.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

uint64_t disk_reads = 0;
uint64_t get_disk_reads(void);

/**
 * --------------------------------- PROBLEM 6 --------------------------------------
 * Checkout PDF section 7 for this problem
 * 
 * Page fault handler.
 * 
 * When the CPU encounters an invalid address mapping in a page table, it invokes the 
 * OS via this handler. Your job is to put a mapping in place so that the translation 
 * can succeed.
 * 
 * @param addr virtual address in the page that needs to be mapped into main memory.
 * 
 * HINTS:
 *      - You will need to use the global variable current_process when
 *      altering the frame table entry.
 *      - Use swap_exists() and swap_read() to update the data in the 
 *      frame as it is mapped in.
 * ----------------------------------------------------------------------------------
 */
void page_fault(vaddr_t addr) {
   // TODO: Get a new frame, then correctly update the page table and frame table
   stats.page_faults++;

   vpn_t vpn = vaddr_vpn(addr);
   pfn_t new_pfn = free_frame();

   pte_t *pte = (pte_t*) (mem + (PTBR * PAGE_SIZE) + (vpn * sizeof(pte_t)));

   if (swap_exists(pte)) {
      swap_read(pte, (void*) (mem + (new_pfn * PAGE_SIZE)));
      disk_reads++;
   } else {
      memset((void*) (mem + (new_pfn * PAGE_SIZE)), 0, (size_t) PAGE_SIZE);
   }
   pte->valid = 1;
   pte->pfn = new_pfn;
   frame_table[new_pfn].mapped = 1;
   frame_table[new_pfn].vpn = vpn;
   frame_table[new_pfn].process = current_process;
}



#pragma GCC diagnostic pop

uint64_t get_disk_reads(void) {
    return disk_reads;
}
