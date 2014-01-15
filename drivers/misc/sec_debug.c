/* sec_debug.c
 *
 * Exception handling in kernel by SEC
 *
 * Copyright (c) 2011 Samsung Electronics
 *                http://www.samsung.com/
 */

#ifdef CONFIG_SEC_DEBUG
#include <linux/errno.h>
#include <linux/ctype.h>
#include <linux/vmalloc.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/input.h>

#include <linux/file.h>
#include <mach/hardware.h>

#include <mach/msm_iomap.h>

#include <linux/sec_debug.h>

#include <linux/smp.h>
#include <linux/cpu.h>

#ifdef CONFIG_SEC_DEBUG_DOUBLE_FREE
#include <linux/circ_buf.h>
#endif

#include "../arch/arm/mach-msm/smd_private.h"

#ifdef CONFIG_SEC_SINGLE_CORE
#define CONFIG_NR_CPUS 1
#endif

/********************************
 *  Variable
 *********************************/
 
typedef struct  {
	int SCTLR;
	int TTBR0;
	int TTBR1;
	int TTBCR;
	int DACR;
	int DFSR;
	int DFAR;
	int IFSR;
	int IFAR;
	int DAFSR;
	int IAFSR;
	int PMRRR;
	int NMRRR;
	int FCSEPID;
	int CONTEXT;
	int URWTPID;
	int UROTPID;
	int POTPIDR;
}sec_debug_mmu_reg_t;

/* ARM CORE regs mapping structure */
typedef struct {
	/* COMMON */
	unsigned int r0;
	unsigned int r1;
	unsigned int r2;
	unsigned int r3;
	unsigned int r4;
	unsigned int r5;
	unsigned int r6;
	unsigned int r7;
	unsigned int r8;
	unsigned int r9;
	unsigned int r10;
	unsigned int r11;
	unsigned int r12;

	/* SVC */
	unsigned int r13_svc;
	unsigned int r14_svc;
	unsigned int spsr_svc;

	/* PC & CPSR */
	unsigned int pc;
	unsigned int cpsr;

	/* USR/SYS */
	unsigned int r13_usr;
	unsigned int r14_usr;

	/* FIQ */
	unsigned int r8_fiq;
	unsigned int r9_fiq;
	unsigned int r10_fiq;
	unsigned int r11_fiq;
	unsigned int r12_fiq;
	unsigned int r13_fiq;
	unsigned int r14_fiq;
	unsigned int spsr_fiq;

	/* IRQ */
	unsigned int r13_irq;
	unsigned int r14_irq;
	unsigned int spsr_irq;

	/* MON */
	unsigned int r13_mon;
	unsigned int r14_mon;
	unsigned int spsr_mon;

	/* ABT */
	unsigned int r13_abt;
	unsigned int r14_abt;
	unsigned int spsr_abt;

	/* UNDEF */
	unsigned int r13_und;
	unsigned int r14_und;
	unsigned int spsr_und;
}sec_debug_core_t;

static int save_final_context;
static unsigned int secdbg_paddr;
static unsigned int secdbg_size;


/* klaatu - schedule log */
#ifdef CONFIG_SEC_DEBUG_SCHED_LOG
struct sec_debug_log {
	atomic_t idx_sched[CONFIG_NR_CPUS];
	struct sched_log sched[CONFIG_NR_CPUS][SCHED_LOG_MAX];

	atomic_t idx_irq[CONFIG_NR_CPUS];
	struct irq_log irq[CONFIG_NR_CPUS][SCHED_LOG_MAX];

	atomic_t idx_irq_exit[CONFIG_NR_CPUS];
	struct irq_exit_log irq_exit[CONFIG_NR_CPUS][SCHED_LOG_MAX];

	atomic_t idx_timer[CONFIG_NR_CPUS];
	struct timer_log timer_log[CONFIG_NR_CPUS][SCHED_LOG_MAX];

#ifdef CONFIG_SEC_DEBUG_MSG_LOG
	atomic_t idx_secmsg[CONFIG_NR_CPUS];
	struct secmsg_log secmsg[CONFIG_NR_CPUS][MSG_LOG_MAX];
#endif
#ifdef CONFIG_SEC_DEBUG_DCVS_LOG
	atomic_t dcvs_log_idx ;
	struct dcvs_debug dcvs_log[DCVS_LOG_MAX] ;
#endif
#ifdef CONFIG_SEC_DEBUG_FUELGAUGE_LOG
	atomic_t fg_log_idx;
	struct fuelgauge_debug fg_log[FG_LOG_MAX] ;
#endif
};

struct sec_debug_log *secdbg_log;
struct sec_debug_subsys *secdbg_subsys;
struct sec_debug_subsys_data_krait *secdbg_krait;

#endif /* CONFIG_SEC_DEBUG_SCHED_LOG */

struct sec_debug_log *secdbg_log;


#ifdef CONFIG_SEC_DEBUG_DOUBLE_FREE
extern void * high_memory;
#endif


/********************************
 *  Define
 *********************************/
#define LOCKUP_FIRST_KEY KEY_VOLUMEUP
#define LOCKUP_SECOND_KEY KEY_VOLUMEDOWN
#define LOCKUP_THIRD_KEY KEY_HOME

/********************************
 *  Function
 *********************************/
/* core reg dump function*/
__used sec_debug_core_t sec_debug_core_reg;
__used sec_debug_mmu_reg_t sec_debug_mmu_reg;



static void sec_debug_save_core_reg(sec_debug_core_t *core_reg)
{
	asm(
		/* we will be in SVC mode when we enter this function.
		* Collect SVC registers along with cmn registers.
		*/
		"str r0, [%0,#0]\n\t"
		"str r1, [%0,#4]\n\t"
		"str r2, [%0,#8]\n\t"
		"str r3, [%0,#12]\n\t"
		"str r4, [%0,#16]\n\t"
		"str r5, [%0,#20]\n\t"
		"str r6, [%0,#24]\n\t"
		"str r7, [%0,#28]\n\t"
		"str r8, [%0,#32]\n\t"
		"str r9, [%0,#36]\n\t"
		"str r10, [%0,#40]\n\t"
		"str r11, [%0,#44]\n\t"
		"str r12, [%0,#48]\n\t"

		/* SVC */
		"str r13, [%0,#52]\n\t"
		"str r14, [%0,#56]\n\t"
		"mrs r1, spsr\n\t"
		"str r1, [%0,#60]\n\t"

		/* PC and CPSR */
		"sub r1, r15, #0x4\n\t"
		"str r1, [%0,#64]\n\t"
		"mrs r1, cpsr\n\t"
		"str r1, [%0,#68]\n\t"

		/* SYS/USR */
		"mrs r1, cpsr\n\t"
		"and r1, r1, #0xFFFFFFE0\n\t"
		"orr r1, r1, #0x1f\n\t"
		"msr cpsr,r1\n\t"

		"str r13, [%0,#72]\n\t"
		"str r14, [%0,#76]\n\t"

		/*FIQ*/
		"mrs r1, cpsr\n\t"
		"and r1,r1,#0xFFFFFFE0\n\t"
		"orr r1,r1,#0x11\n\t"
		"msr cpsr,r1\n\t"

		"str r8, [%0,#80]\n\t"
		"str r9, [%0,#84]\n\t"
		"str r10, [%0,#88]\n\t"
		"str r11, [%0,#92]\n\t"
		"str r12, [%0,#96]\n\t"
		"str r13, [%0,#100]\n\t"
		"str r14, [%0,#104]\n\t"
		"mrs r1, spsr\n\t"
		"str r1, [%0,#108]\n\t"

		/*IRQ*/
		"mrs r1, cpsr\n\t"
		"and r1, r1, #0xFFFFFFE0\n\t"
		"orr r1, r1, #0x12\n\t"
		"msr cpsr,r1\n\t"

		"str r13, [%0,#112]\n\t"
		"str r14, [%0,#116]\n\t"
		"mrs r1, spsr\n\t"
		"str r1, [%0,#120]\n\t"

		/*MON*/
		"mrs r1, cpsr\n\t"
		"and r1, r1, #0xFFFFFFE0\n\t"
		"orr r1, r1, #0x16\n\t"
		"msr cpsr,r1\n\t"

		"str r13, [%0,#124]\n\t"
		"str r14, [%0,#128]\n\t"
		"mrs r1, spsr\n\t"
		"str r1, [%0,#132]\n\t"

		/*ABT*/
		"mrs r1, cpsr\n\t"
		"and r1, r1, #0xFFFFFFE0\n\t"
		"orr r1, r1, #0x17\n\t"
		"msr cpsr,r1\n\t"

		"str r13, [%0,#136]\n\t"
		"str r14, [%0,#140]\n\t"
		"mrs r1, spsr\n\t"
		"str r1, [%0,#144]\n\t"

		/*UND*/
		"mrs r1, cpsr\n\t"
		"and r1, r1, #0xFFFFFFE0\n\t"
		"orr r1, r1, #0x1B\n\t"
		"msr cpsr,r1\n\t"

		"str r13, [%0,#148]\n\t"
		"str r14, [%0,#152]\n\t"
		"mrs r1, spsr\n\t"
		"str r1, [%0,#156]\n\t"

		/* restore to SVC mode */
		"mrs r1, cpsr\n\t"
		"and r1, r1, #0xFFFFFFE0\n\t"
		"orr r1, r1, #0x13\n\t"
		"msr cpsr,r1\n\t"

	:			/* output */
		: "r"(core_reg) 		/* input */
	: "%r1" 	/* clobbered register */
	);

	return;
}




static void sec_debug_save_mmu_reg(sec_debug_mmu_reg_t *mmu_reg)
{
	asm("mrc    p15, 0, r1, c1, c0, 0\n\t"	/* SCTLR */
		"str r1, [%0]\n\t"
		"mrc    p15, 0, r1, c2, c0, 0\n\t"	/* TTBR0 */
		"str r1, [%0,#4]\n\t"
		"mrc    p15, 0, r1, c2, c0,1\n\t"	/* TTBR1 */
		"str r1, [%0,#8]\n\t"
		"mrc    p15, 0, r1, c2, c0,2\n\t"	/* TTBCR */
		"str r1, [%0,#12]\n\t"
		"mrc    p15, 0, r1, c3, c0,0\n\t"	/* DACR */
		"str r1, [%0,#16]\n\t"
		"mrc    p15, 0, r1, c5, c0,0\n\t"	/* DFSR */
		"str r1, [%0,#20]\n\t"
		"mrc    p15, 0, r1, c6, c0,0\n\t"	/* DFAR */
		"str r1, [%0,#24]\n\t"
		"mrc    p15, 0, r1, c5, c0,1\n\t"	/* IFSR */
		"str r1, [%0,#28]\n\t"
		"mrc    p15, 0, r1, c6, c0,2\n\t"	/* IFAR */
		"str r1, [%0,#32]\n\t"
		/*Dont populate DAFSR and RAFSR */
		"mrc    p15, 0, r1, c10, c2,0\n\t"	/* PMRRR */
		"str r1, [%0,#44]\n\t"
		"mrc    p15, 0, r1, c10, c2,1\n\t"	/* NMRRR */
		"str r1, [%0,#48]\n\t"
		"mrc    p15, 0, r1, c13, c0,0\n\t"	/* FCSEPID */
		"str r1, [%0,#52]\n\t"
		"mrc    p15, 0, r1, c13, c0,1\n\t"	/* CONTEXT */
		"str r1, [%0,#56]\n\t"
		"mrc    p15, 0, r1, c13, c0,2\n\t"	/* URWTPID */
		"str r1, [%0,#60]\n\t"
		"mrc    p15, 0, r1, c13, c0,3\n\t"	/* UROTPID */
		"str r1, [%0,#64]\n\t"
		"mrc    p15, 0, r1, c13, c0,4\n\t"	/* POTPIDR */
		"str r1, [%0,#68]\n\t"
		:			/* output */
	    : "r"(mmu_reg)			/* input */
	: "%r1", "memory"	/* clobbered register */
	);
	return 0;
}


void sec_save_final_context(void)
{
	samsung_vendor1_id *smem_vendor1 = NULL;
	unsigned size;

	if (save_final_context) {
		printk(KERN_EMERG"(sec_save_final_context) already saved.\n");
		return;
	}

    sec_debug_save_mmu_reg(&sec_debug_mmu_reg);
	sec_debug_save_core_reg(&sec_debug_core_reg);
	printk(KERN_EMERG "(%s) sec_save_final_context (CPU:%d)\n", __func__,
		smp_processor_id());

	smem_vendor1 = (samsung_vendor1_id *)smem_get_entry(SMEM_ID_VENDOR1,\
				&size);
	memcpy(&(smem_vendor1->apps_dump.apps_regs),
		&sec_debug_mmu_reg, sizeof(sec_debug_mmu_reg));

	save_final_context = 1;
}
EXPORT_SYMBOL(sec_save_final_context);

static int __init __init_sec_debug_log(void)
{
	int i;
	struct sec_debug_log *vaddr;
	int size;

	if (secdbg_paddr == 0 || secdbg_size == 0) {
		pr_info("%s: sec debug buffer not provided. Using kmalloc..\n",
			__func__);
		size = sizeof(struct sec_debug_log);
		vaddr = kmalloc(size, GFP_KERNEL);
	} else {
		size = secdbg_size;
		vaddr = ioremap_nocache(secdbg_paddr, secdbg_size);
	}

	pr_info("%s: vaddr=0x%x paddr=0x%x size=0x%x "
		"sizeof(struct sec_debug_log)=0x%x\n", __func__,
		(unsigned int)vaddr, secdbg_paddr, secdbg_size,
		sizeof(struct sec_debug_log));

	if ((vaddr == NULL) || (sizeof(struct sec_debug_log) > size)) {
		pr_info("%s: ERROR! init failed!\n", __func__);
		return -EFAULT;
	}

	for (i = 0; i < CONFIG_NR_CPUS; i++) {
		atomic_set(&(vaddr->idx_sched[i]), -1);
		atomic_set(&(vaddr->idx_irq[i]), -1);
		atomic_set(&(vaddr->idx_irq_exit[i]), -1);
		atomic_set(&(vaddr->idx_timer[i]), -1);
#ifdef CONFIG_SEC_DEBUG_MSG_LOG
		atomic_set(&(vaddr->idx_secmsg[i]), -1);
#endif
	}
#ifdef CONFIG_SEC_DEBUG_DCVS_LOG
		atomic_set(&(vaddr->dcvs_log_idx), -1);
#endif
#ifdef CONFIG_SEC_DEBUG_FUELGAUGE_LOG
		atomic_set(&(vaddr->fg_log_idx), -1);
#endif

	secdbg_log = vaddr;

	pr_info("%s: init done\n", __func__);

	return 0;
}


__init int sec_debug_init(void)
{


	#ifdef CONFIG_SEC_DEBUG_SCHED_LOG
	__init_sec_debug_log();
	#endif
	#if CONFIG_SEC_DEBUG_SEMAPHORE_LOG
	debug_semaphore_init();
	#endif
}



static int __init sec_dbg_setup(char *str)
{
	unsigned size = memparse(str, &str);

	pr_emerg("%s: str=%s\n", __func__, str);

	if (size && (size == roundup_pow_of_two(size)) && (*str == '@')) {
		secdbg_paddr = (unsigned int)memparse(++str, NULL);
		secdbg_size = size;
		}

	pr_emerg("%s: secdbg_paddr = 0x%x\n", __func__, secdbg_paddr);
	pr_emerg("%s: secdbg_size = 0x%x\n", __func__, secdbg_size);

	return 1;
}
__setup("sec_dbg=", sec_dbg_setup);

#ifdef CONFIG_SEC_DEBUG_SCHED_LOG
void __sec_debug_task_sched_log(int cpu, struct task_struct *task,
						char *msg)
{
	unsigned i;

	if (!secdbg_log)
		return;

	if (!task && !msg)
		return;

	i = atomic_inc_return(&(secdbg_log->idx_sched[cpu]))
		& (SCHED_LOG_MAX - 1);
	secdbg_log->sched[cpu][i].time = cpu_clock(cpu);
	if (task) {
		strncpy(secdbg_log->sched[cpu][i].comm, task->comm,
			sizeof(secdbg_log->sched[cpu][i].comm));
		secdbg_log->sched[cpu][i].pid = task->pid;
	} else {
		strncpy(secdbg_log->sched[cpu][i].comm, msg,
			sizeof(secdbg_log->sched[cpu][i].comm));
		secdbg_log->sched[cpu][i].pid = -1;
	}
}

void sec_debug_task_sched_log_short_msg(char *msg)
{
	__sec_debug_task_sched_log(smp_processor_id(), NULL, msg);
}

void sec_debug_task_sched_log(int cpu, struct task_struct *task)
{
	__sec_debug_task_sched_log(cpu, task, NULL);
}

void sec_debug_timer_log(unsigned int type, int int_lock, void *fn)
{
	int cpu = smp_processor_id();
	unsigned i;

	if (!secdbg_log)
		return;

	i = atomic_inc_return(&(secdbg_log->idx_timer[cpu]))
			& (SCHED_LOG_MAX - 1);
	secdbg_log->timer_log[cpu][i].time = cpu_clock(cpu);
	secdbg_log->timer_log[cpu][i].type = type;
	secdbg_log->timer_log[cpu][i].int_lock = int_lock;
	secdbg_log->timer_log[cpu][i].fn = (void *)fn;
}

void sec_debug_irq_sched_log(unsigned int irq, void *fn, int en)
{
	int cpu = smp_processor_id();
	unsigned i;

	if (!secdbg_log)
		return;

	i = atomic_inc_return(&(secdbg_log->idx_irq[cpu]))
			& (SCHED_LOG_MAX - 1);
	secdbg_log->irq[cpu][i].time = cpu_clock(cpu);
	secdbg_log->irq[cpu][i].irq = irq;
	secdbg_log->irq[cpu][i].fn = (void *)fn;
	secdbg_log->irq[cpu][i].en = en;
	secdbg_log->irq[cpu][i].preempt_count = preempt_count();
	secdbg_log->irq[cpu][i].context = &cpu;
}

#ifdef CONFIG_SEC_DEBUG_IRQ_EXIT_LOG
void sec_debug_irq_enterexit_log(unsigned int irq,
						unsigned long long start_time)
{
	int cpu = smp_processor_id();
	unsigned i;

	if (!secdbg_log)
		return;

	i = atomic_inc_return(&(secdbg_log->idx_irq_exit[cpu]))
			& (SCHED_LOG_MAX - 1);
	secdbg_log->irq_exit[cpu][i].time = start_time;
	secdbg_log->irq_exit[cpu][i].end_time = cpu_clock(cpu);
	secdbg_log->irq_exit[cpu][i].irq = irq;
	secdbg_log->irq_exit[cpu][i].elapsed_time =
		secdbg_log->irq_exit[cpu][i].end_time - start_time;
	}
#endif

#ifdef CONFIG_SEC_DEBUG_MSG_LOG
asmlinkage int sec_debug_msg_log(void *caller, const char *fmt, ...)
{
	int cpu = smp_processor_id();
	int r = 0;
	int i;
	va_list args;

	if (!secdbg_log)
		return 0;

	i = atomic_inc_return(&(secdbg_log->idx_secmsg[cpu]))
		& (MSG_LOG_MAX - 1);
	secdbg_log->secmsg[cpu][i].time = cpu_clock(cpu);
	va_start(args, fmt);
	r = vsnprintf(secdbg_log->secmsg[cpu][i].msg,
		sizeof(secdbg_log->secmsg[cpu][i].msg), fmt, args);
	va_end(args);

	secdbg_log->secmsg[cpu][i].caller0 = __builtin_return_address(0);
	secdbg_log->secmsg[cpu][i].caller1 = caller;
	secdbg_log->secmsg[cpu][i].task = current->comm;

	return r;
}
#endif
#endif /* CONFIG_SEC_DEBUG_SCHED_LOG */

/* klaatu - semaphore log */
#ifdef CONFIG_SEC_DEBUG_SEMAPHORE_LOG
void debug_semaphore_init(void)
{
	int i = 0;
	struct sem_debug *sem_debug = NULL;

	spin_lock_init(&sem_debug_lock);
	sem_debug_free_head_cnt = 0;
	sem_debug_done_head_cnt = 0;

	/* initialize list head of sem_debug */
	INIT_LIST_HEAD(&sem_debug_free_head.list);
	INIT_LIST_HEAD(&sem_debug_done_head.list);

	for (i = 0; i < SEMAPHORE_LOG_MAX; i++) {
		/* malloc semaphore */
		sem_debug = kmalloc(sizeof(struct sem_debug), GFP_KERNEL);

		/* add list */
		list_add(&sem_debug->list, &sem_debug_free_head.list);
		sem_debug_free_head_cnt++;
	}

	sem_debug_init = 1;
}

void debug_semaphore_down_log(struct semaphore *sem)
{
	struct list_head *tmp;
	struct sem_debug *sem_dbg;
	unsigned long flags;

	if (!sem_debug_init)
		return;

	spin_lock_irqsave(&sem_debug_lock, flags);
	list_for_each(tmp, &sem_debug_free_head.list) {
		sem_dbg = list_entry(tmp, struct sem_debug, list);
		sem_dbg->task = current;
		sem_dbg->sem = sem;
		sem_dbg->pid = current->pid;
		sem_dbg->cpu = smp_processor_id();
		list_del(&sem_dbg->list);
		list_add(&sem_dbg->list, &sem_debug_done_head.list);
		sem_debug_free_head_cnt--;
		sem_debug_done_head_cnt++;
		break;
	}
	spin_unlock_irqrestore(&sem_debug_lock, flags);
}

void debug_semaphore_up_log(struct semaphore *sem)
{
	struct list_head *tmp;
	struct sem_debug *sem_dbg;
	unsigned long flags;

	if (!sem_debug_init)
		return;

	spin_lock_irqsave(&sem_debug_lock, flags);
	list_for_each(tmp, &sem_debug_done_head.list) {
		sem_dbg = list_entry(tmp, struct sem_debug, list);
		if (sem_dbg->sem == sem && sem_dbg->pid == current->pid) {
			list_del(&sem_dbg->list);
			list_add(&sem_dbg->list, &sem_debug_free_head.list);
			sem_debug_free_head_cnt++;
			sem_debug_done_head_cnt--;
			break;
		}
	}
	spin_unlock_irqrestore(&sem_debug_lock, flags);
}

/* rwsemaphore logging */
void debug_rwsemaphore_init(void)
{
	int i = 0;
	struct rwsem_debug *rwsem_debug = NULL;
	spin_lock_init(&rwsem_debug_lock);
	rwsem_debug_free_head_cnt = 0;
	rwsem_debug_done_head_cnt = 0;

	/* initialize list head of sem_debug */
	INIT_LIST_HEAD(&rwsem_debug_free_head.list);
	INIT_LIST_HEAD(&rwsem_debug_done_head.list);

	for (i = 0; i < RWSEMAPHORE_LOG_MAX; i++) {
		/* malloc semaphore */
		rwsem_debug =
			kmalloc(sizeof(struct rwsem_debug), GFP_KERNEL);
		/* add list */
		list_add(&rwsem_debug->list, &rwsem_debug_free_head.list);
		rwsem_debug_free_head_cnt++;
	}

	rwsem_debug_init = 1;
}

void debug_rwsemaphore_down_log(struct rw_semaphore *sem, int dir)
{
	struct list_head *tmp;
	struct rwsem_debug *sem_dbg;
	unsigned long flags;

	if (!rwsem_debug_init)
		return;

	spin_lock_irqsave(&rwsem_debug_lock, flags);
	list_for_each(tmp, &rwsem_debug_free_head.list) {
		sem_dbg = list_entry(tmp, struct rwsem_debug, list);
		sem_dbg->task = current;
		sem_dbg->sem = sem;
		sem_dbg->pid = current->pid;
		sem_dbg->cpu = smp_processor_id();
		sem_dbg->direction = dir;
		list_del(&sem_dbg->list);
		list_add(&sem_dbg->list, &rwsem_debug_done_head.list);
		rwsem_debug_free_head_cnt--;
		rwsem_debug_done_head_cnt++;
		break;
	}
	spin_unlock_irqrestore(&rwsem_debug_lock, flags);
}

void debug_rwsemaphore_up_log(struct rw_semaphore *sem)
{
	struct list_head *tmp;
	struct rwsem_debug *sem_dbg;
	unsigned long flags;

	if (!rwsem_debug_init)
		return;

	spin_lock_irqsave(&rwsem_debug_lock, flags);
	list_for_each(tmp, &rwsem_debug_done_head.list) {
		sem_dbg = list_entry(tmp, struct rwsem_debug, list);
		if (sem_dbg->sem == sem && sem_dbg->pid == current->pid) {
			list_del(&sem_dbg->list);
			list_add(&sem_dbg->list, &rwsem_debug_free_head.list);
			rwsem_debug_free_head_cnt++;
			rwsem_debug_done_head_cnt--;
			break;
		}
	}
	spin_unlock_irqrestore(&rwsem_debug_lock, flags);
}
#endif	/* CONFIG_SEC_DEBUG_SEMAPHORE_LOG */

#ifdef CONFIG_SEC_DEBUG_USER
extern int dump_enable_flag;
void sec_user_fault_dump(void)
{
#if 0
	if (sec_debug_level.en.kernel_fault == 1
	    && sec_debug_level.en.user_fault == 1)
#else
	if ( dump_enable_flag == 2 ) // debug level HIGH
#endif
		panic("User Fault");
}

static int sec_user_fault_write(struct file *file, const char __user * buffer,
				size_t count, loff_t * offs)
{
	char buf[100];

	if (count > sizeof(buf) - 1)
		return -EINVAL;
	if (copy_from_user(buf, buffer, count))
		return -EFAULT;
	buf[count] = '\0';

	if (strncmp(buf, "dump_user_fault", 15) == 0)
		sec_user_fault_dump();

	return count;
}

static const struct file_operations sec_user_fault_proc_fops = {
	.write = sec_user_fault_write,
};

static int __init sec_debug_user_fault_init(void)
{
	struct proc_dir_entry *entry;

	entry = proc_create("user_fault", S_IWUSR | S_IWGRP, NULL,
			    &sec_user_fault_proc_fops);
	if (!entry)
		return -ENOMEM;
	return 0;
}

device_initcall(sec_debug_user_fault_init);
#endif

#ifdef CONFIG_APPLY_GA_SOLUTION
extern void dump_all_task_info();
extern void dump_cpu_stat();
#endif

void sec_check_crash_key(int keycode, u8 keypress)
{
	static enum {NONE, STEP1, STEP2, STEP3, STEP4, STEP5, STEP6,\
			STEP7, STEP8} state = NONE;

	switch (state) {
	case NONE:
		if ((keycode == LOCKUP_FIRST_KEY) && keypress)
			state = STEP1;
		else
			state = NONE;
		break;
	case STEP1:
		if ((keycode == LOCKUP_FIRST_KEY) && !keypress)
			state = STEP2;
		else
			state = NONE;
		break;
	case STEP2:
		if ((keycode == LOCKUP_SECOND_KEY) && keypress)
			state = STEP3;
		else
			state = NONE;
		break;
	case STEP3:
		if ((keycode == LOCKUP_SECOND_KEY) && !keypress)
			state = STEP4;
		else
			state = NONE;
		break;
	case STEP4:
		if ((keycode == LOCKUP_THIRD_KEY) && keypress)
			state = STEP5;
		else
			state = NONE;
		break;
	case STEP5:
		if ((keycode == LOCKUP_THIRD_KEY) && !keypress)
			state = STEP6;
		else
			state = NONE;
		break;
	case STEP6:
		if ((keycode == LOCKUP_FIRST_KEY) && keypress)
			state = STEP7;
		else
			state = NONE;
		break;
	case STEP7:
		if ((keycode == LOCKUP_FIRST_KEY) && !keypress)
			state = STEP8;
		else
			state = NONE;
		break;
	case STEP8:
		if ((keycode == LOCKUP_THIRD_KEY) && keypress)
		{
#ifdef CONFIG_APPLY_GA_SOLUTION
			printk("Force Key DUMP\n");
		//	dump_all_task_info();
		//	dump_cpu_stat();
#endif
			panic("[Crash Key] LOCKUP CAPTURED!!!");
		}
		else
			state = NONE;
		break;
	default:
		break;
	}
}
EXPORT_SYMBOL(sec_check_crash_key);

#if defined(CONFIG_DEBUG_FS) && defined(CONFIG_DEBUG_PANIC_TEST)
#include <linux/debugfs.h>

static struct dentry *debug_panic_dent;
static spinlock_t debug_panic_spinlock;

struct debug_panic_type {
	void (*func)(void);
	char *desc;
};

void debug_panic_dabort(void)
{
	int *p = 0;
	*p = 0;
}

void debug_panic_pabort(void)
{
	void (*p)(void) = 0;
	p();
}
void debug_panic_lockup(void)
{
	unsigned long flags;
	spin_lock_irqsave(&debug_panic_spinlock, flags);
	while (1)
		;
	spin_unlock_irqrestore(&debug_panic_spinlock, flags);
}

void debug_panic_spinlock_bug(void)
{
	spin_lock(&debug_panic_spinlock);
	spin_lock(&debug_panic_spinlock);

	spin_unlock(&debug_panic_spinlock);
}

void debug_panic_sched_while_atomic(void)
{
	spin_lock(&debug_panic_spinlock);
	msleep(20);
	spin_unlock(&debug_panic_spinlock);
}

void debug_panic_sched_with_irqoff(void)
{
	unsigned long flags;

	raw_local_irq_save(flags);
	msleep(20);
}

struct debug_panic_type debug_panic_scenario[] = {
	[0] = {
		.func = debug_panic_dabort,
		.desc = "data abort\n"
	},
	[1] = {
		.func = debug_panic_pabort,
		.desc = "prefetch abort\n"
	},
	[2] = {
		.func = debug_panic_lockup,
		.desc = "lockup\n"
	},
	[3] = {
		.func = debug_panic_spinlock_bug,
		.desc = "spinlock bug\n"
	},
	[4] = {
		.func = debug_panic_sched_while_atomic,
		.desc = "schedule while atomic\n"
	},
	[5] = {
		.func = debug_panic_sched_with_irqoff,
		.desc = "schedule with irq disabled\n"
	},

};

static int debug_panic_open(struct inode *inode, struct file *file)
{
	file->private_data = inode->i_private;
	return 0;
}

static ssize_t debug_panic_read(struct file *file, char __user *buf,
			  size_t count, loff_t *ppos)
{
	struct debug_panic_type *panic_type = file->private_data;
	ssize_t rc;

	rc = simple_read_from_buffer((void __user *) buf, count,\
		ppos, (void *) panic_type->desc,\
		strlen(panic_type->desc));

	return rc;
}
static ssize_t debug_panic_write(struct file *file, const char __user *buf,
			   size_t count, loff_t *ppos)
{
	struct debug_panic_type *panic_type = file->private_data;

	pr_info("@@ %s %s\n", __func__, panic_type->desc);
	msleep(500);

	panic_type->func();

	return count;
}

static const struct file_operations debug_panic_ops = {
	.open =         debug_panic_open,
	.read =         debug_panic_read,
	.write =        debug_panic_write,
};

#define DEBUG_MAX_FNAME 16
void debug_panic_init(void)
{
	int i;
	char name[DEBUG_MAX_FNAME];

	spin_lock_init(&debug_panic_spinlock);

	debug_panic_dent = debugfs_create_dir("panic", NULL);
	if (IS_ERR(debug_panic_dent)) {
		pr_err("panic debugfs_create_dir fail, error %ld\n",
		       PTR_ERR(debug_panic_dent));
		return;
	}

	for (i = 0; i < ARRAY_SIZE(debug_panic_scenario); i++) {
		snprintf(name, DEBUG_MAX_FNAME-1, "panic-%d", i);
		if (debugfs_create_file(name, 0644, debug_panic_dent,\
			&debug_panic_scenario[i], &debug_panic_ops) == NULL) {
			pr_err("pmic8058 debugfs_create_file %s failed\n",\
				name);
		}
	}
}

static void debug_panic_exit(void)
{
	debugfs_remove_recursive(debug_panic_dent);
}

#else
static void debug_panic_init(void) { }
static void debug_panic_exit(void) { }
#endif

#ifdef CONFIG_SEC_DEBUG_DOUBLE_FREE
#define KFREE_HOOK_BYPASS_MASK 0x1
#define KFREE_CIRC_BUF_SIZE (1<<15)
#define KFREE_FREE_MAGIC 0xf4eef4ee
static DEFINE_SPINLOCK(circ_buf_lock);
struct kfree_info_entry {
	void *addr;
	void *caller;
};

struct kfree_circ_buf {
	int head;
	int tail;
	struct kfree_info_entry entry[KFREE_CIRC_BUF_SIZE];
};

struct kfree_circ_buf kfree_circ_buf;

static void *circ_buf_lookup(struct kfree_circ_buf *circ_buf, void *addr)
{
	int i;
	for (i = circ_buf->tail; i != circ_buf->head ;
		i = (i + 1) & (KFREE_CIRC_BUF_SIZE - 1)) {
		if (circ_buf->entry[i].addr == addr)
			return &circ_buf->entry[i];
	}

	return NULL;
}

static void *circ_buf_get(struct kfree_circ_buf *circ_buf)
{
	void *entry;
	entry = &circ_buf->entry[circ_buf->tail];
	smp_rmb();
	circ_buf->tail = (circ_buf->tail + 1) &
		(KFREE_CIRC_BUF_SIZE - 1);
	return entry;
}

static void *circ_buf_put(struct kfree_circ_buf *circ_buf,
				struct kfree_info_entry *entry)
{
	memcpy(&circ_buf->entry[circ_buf->head], entry, sizeof(*entry));
	smp_wmb();
	circ_buf->head = (circ_buf->head + 1) &
		(KFREE_CIRC_BUF_SIZE - 1);
	return entry;
}

void *kfree_hook(void *p, void *caller)
{
	unsigned int flags;
	struct kfree_info_entry *match = NULL;
	void *tofree = NULL;
	unsigned int addr = (unsigned int)p;

	if (!virt_addr_valid(addr)) {
		/* there are too many NULL pointers so don't print for NULL */
		if (addr)
			pr_debug("%s: trying to free an invalid addr %x from %pS\n",
				__func__, addr, caller);
		return NULL;
	}

	if (addr&0x1) {
		/* return original address to free */
		return (void *)(addr&~(KFREE_HOOK_BYPASS_MASK));
	}

	spin_lock_irqsave(&circ_buf_lock, flags);

	if (kfree_circ_buf.head == 0)
		pr_debug("%s: circular buffer head rounded to zero.", __func__);

	if (*(unsigned int *)p == KFREE_FREE_MAGIC) {
		/* memory that is to be freed may originally have had magic
		 * value, so search the whole circ buf for an actual match */
		match = circ_buf_lookup(&kfree_circ_buf, p);
	}

	if (match) {
		pr_err("%s: 0x%08x was already freed by %pS()\n",
			__func__, p, match->caller);
		spin_unlock_irqrestore(&circ_buf_lock, flags);
		panic("double free detected!");
		return NULL;
	} else {
		struct kfree_info_entry entry;

		/* mark free magic on the freeing node */
		*(unsigned int *)p = KFREE_FREE_MAGIC;

		/* do an actual kfree for the oldest entry
		 * if the circular buffer is full */
		if (CIRC_SPACE(kfree_circ_buf.head, kfree_circ_buf.tail,
			KFREE_CIRC_BUF_SIZE) == 0) {
			struct kfree_info_entry *pentry;
			pentry = circ_buf_get(&kfree_circ_buf);
			if (pentry)
				tofree = pentry->addr;
		}

		/* add the new entry to the circular buffer */
		entry.addr = p;
		entry.caller = caller;
		circ_buf_put(&kfree_circ_buf, &entry);
		if (tofree) {
			spin_unlock_irqrestore(&circ_buf_lock, flags);
			kfree((void *)((unsigned int)tofree |
				KFREE_HOOK_BYPASS_MASK));
			return NULL;
		}
	}

	spin_unlock_irqrestore(&circ_buf_lock, flags);
	return NULL;
}
#endif

#endif /* CONFIG_SEC_DEBUG */
