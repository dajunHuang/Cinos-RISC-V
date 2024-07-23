#include "psci.h"

#include "printf.h"
#include <errno.h>
#include "tools/macros.h"
#include "smc.h"

typedef unsigned long (psci_fn)(unsigned long, unsigned long,
				unsigned long, unsigned long);
static psci_fn *invoke_psci_fn;


enum psci_function {
	PSCI_FN_CPU_SUSPEND,
	PSCI_FN_CPU_ON,
	PSCI_FN_CPU_OFF,
	PSCI_FN_MIGRATE,
	PSCI_FN_MAX,
};


static uint32_t psci_function_id[PSCI_FN_MAX];


static unsigned long __invoke_psci_fn_smc(unsigned long function_id,
			unsigned long arg0, unsigned long arg1,
			unsigned long arg2)
{
	struct arm_smccc_res res;
	// printf("before smc\n");
	do_smc(function_id, arg0, arg1, arg2,&res);
	return res.a0;
}

static uint32_t psci_get_version(void)
{
	return invoke_psci_fn(PSCI_0_2_FN_PSCI_VERSION, 0, 0, 0);
}
static int psci_to_errno(int errno)
{
	switch (errno) {
	case PSCI_RET_SUCCESS:
		return 0;
	case PSCI_RET_NOT_SUPPORTED:
		return -EOPNOTSUPP;
	case PSCI_RET_INVALID_PARAMS:
	case PSCI_RET_INVALID_ADDRESS:
		return -EINVAL;
	case PSCI_RET_DENIED:
		return -EPERMIT;
	};

	return -EINVAL;
}

int psci_cpu_on(unsigned long cpuid, unsigned long entry_point)
{
	int err;
	uint32_t fn;

	fn = psci_function_id[PSCI_FN_CPU_ON];

	err = invoke_psci_fn(fn, cpuid, entry_point, 0);

	return psci_to_errno(err);
}




static void  psci_0_2_set_functions(void)
{
	printf("Using standard PSCI v0.2 function IDs\n");

	psci_function_id[PSCI_FN_CPU_ON] = PSCI_0_2_FN64_CPU_ON;

	//need to do
	psci_function_id[PSCI_FN_CPU_SUSPEND] = PSCI_0_2_FN64_CPU_SUSPEND;
	psci_function_id[PSCI_FN_CPU_OFF] = PSCI_0_2_FN_CPU_OFF;
	psci_function_id[PSCI_FN_MIGRATE] = PSCI_0_2_FN64_MIGRATE;

}


static int  psci_probe(void){
	uint32_t ver = psci_get_version();

	printf("PSCIv%d.%d detected in firmware.\n",
			PSCI_VERSION_MAJOR(ver),
			PSCI_VERSION_MINOR(ver));

	if (PSCI_VERSION_MAJOR(ver) == 0 && PSCI_VERSION_MINOR(ver) < 2) {
		printf("Conflicting PSCI version detected.\n");
		return -EINVAL;
	}

	psci_0_2_set_functions();

	return 0;
}

//psci spec 1.0
int  psci_init(void){
    invoke_psci_fn = __invoke_psci_fn_smc; // virt use psci v1.1 , method = smc

    int err = psci_probe();
    if(err) {
        printf("psci probe failed\n");
        return err;
    }


    return 0;
}