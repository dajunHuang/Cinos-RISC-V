#include "k_stdint.h"
#include "smp.h"
#include "psci.h"
#include "platsmp.h"
#include "printf.h"
#include "allocate.h"
#include "psci.h"

#include "scr.h"
void smp_boot_secondary_cpu(void)
{
#ifdef CONFIG_SMP
    extern uint64_t _start;
    uint64_t i;
    uint32_t initialcores = smp_current_cores();  //init 1.
    uint64_t entry = allocator_pbase((uint64_t)&_start);  //let the secondary cpus run codes in _start in entry.S.

    printf("psci init start\n");
    int err = psci_init();
    if (err) {
        printf("psci init failed\n");
        return;
    }

    printf("Setup entrys for secondary cores to %x!\n", entry);

    for(i = 1; i < CONFIG_NR_CPUS; i++){
        printf("Start to wakeup Core#%d...\n",i);
        word_t mpidr = scr_read_MPIDR();
        mpidr = (mpidr & ~0xFF) | (i & 0xFF);
        printf("core%d,mpidr : %x\n",i,mpidr);
        int err = psci_cpu_on(mpidr,entry);

        if(err){
            printf("enable Core#%d failed,ret code is %x \n",i,err);
            return ;
        }
        else
            printf("enable Core#%d \n",i);
        printf("smp_current_cores():%d\n",smp_current_cores());
        while(smp_current_cores() != (initialcores + i)){
        }
        printf("Core#%d is ready!\n", i);
    }
    printf("Secondary cores enable finished!\n");
    //scu_dump_info();
#endif
}
