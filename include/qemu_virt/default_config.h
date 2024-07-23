/**
 * @file    default_config.h
 * @brief   根据 autoconf.h 自动设置的一些config
 */
#ifndef _DEFAULT_CONFIG_H_
#define _DEFAULT_CONFIG_H_

/**
 * @brief   配置arm位数 32位/64位
 *
 */
#ifdef CONFIG_ARCH_ARM
#define CONFIG_ARCH_32      // arm 32位 相关设置 =========================================

// 页表比特位配置，平台用
#define PAGE_ORDER              (8)
#define PAGE_SHIFT              (12)
#define L0_INDEX_SHIFT          ((1 * PAGE_ORDER) + PAGE_SHIFT)
#define L1_INDEX_SHIFT          ((0 * PAGE_ORDER) + PAGE_SHIFT)

// 任何有mmp的架构都应当有大小页区分，内核代码用
#define CONFIG_PAGE_SHIFT       L1_INDEX_SHIFT
#define CONFIG_SEGMENT_SHIFT    L0_INDEX_SHIFT
#define LNPT_SIZE               (sizeof(long) << PAGE_ORDER)
                            // arm 32位 相关设置 =========================================
#else
#define CONFIG_ARCH_64      // arm 64位 相关设置 =========================================

// 页表比特位配置，平台用
#define PAGE_ORDER              (9)
#define PAGE_SHIFT              (12)
#define L0_INDEX_SHIFT          ((3 * PAGE_ORDER) + PAGE_SHIFT)
#define L1_INDEX_SHIFT          ((2 * PAGE_ORDER) + PAGE_SHIFT)
#define L2_INDEX_SHIFT          ((1 * PAGE_ORDER) + PAGE_SHIFT)
#define L3_INDEX_SHIFT          ((0 * PAGE_ORDER) + PAGE_SHIFT)

// 任何有mmp的架构都应当有大小页区分，内核代码用
#define CONFIG_PAGE_SHIFT       L3_INDEX_SHIFT
#define CONFIG_SEGMENT_SHIFT    L2_INDEX_SHIFT
#define LNPT_SIZE               (sizeof(long) << PAGE_ORDER)
                            // arm 64位 相关设置 =========================================
#endif

/**
 * @brief   调试的宏
 *
 */
#ifndef CONFIG_DEBUG
#define NDEBUG
#endif

/**
 * @brief   线程的名字字节数
 *
 */
#define CONFIG_TASK_NAMELEN (32)

/**
 * @brief   如果不使能多核, 则核数设置为1
 *
 */
#ifndef CONFIG_SMP
#define CONFIG_NR_CPUS      (1)
#endif

/**
 * @brief   页大小
 *
 */
#define CONFIG_PAGE_SIZE        (1 << CONFIG_PAGE_SHIFT)
#define CONFIG_SEGMENT_SIZE     (1 << CONFIG_SEGMENT_SHIFT)

/**
 * @brief   栈大小
 *
 */
#define CONFIG_STACK_SIZE   (CONFIG_STACK_PAGES << CONFIG_PAGE_SHIFT)

/**
 * @brief   域相关的配置
 *
 */
#define CONFIG_DOM_NUMBER   1 // the max number of domains exists; min value is 1.
#define CONFIG_DOM_START    0 // the id of which domain can run fisrt.

#endif
