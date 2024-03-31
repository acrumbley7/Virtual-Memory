#include "stats.h"
#include "va_splitting.h"
/* The stats. See the definition in stats.h. */
stats_t stats;

/**
 * --------------------------------- PROBLEM 10 --------------------------------------
 * Checkout PDF section 10 for this problem
 * 
 * Calulate the total average time it takes for an access
 * 
 * HINTS:
 * 		- You may find the #defines in the stats.h file useful.
 * 		- You will need to include code to increment many of these stats in
 * 		the functions you have written for other parts of the project.
 * -----------------------------------------------------------------------------------
 */
void compute_stats(void) {
    uint64_t mem_time = (double) stats.accesses * MEMORY_ACCESS_TIME;
    uint64_t fault_time = (double) stats.page_faults * DISK_PAGE_READ_TIME;
    uint64_t writeback_time = (double) stats.writebacks * DISK_PAGE_WRITE_TIME;
    stats.amat = (double) ((mem_time + fault_time + writeback_time + (double) get_disk_reads()) / stats.accesses);
}
