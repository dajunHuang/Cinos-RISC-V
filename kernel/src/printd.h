#ifndef _PRINTD_H_
#define _PRINTD_H_
#include "autoconf.h"

#include "k_stdarg.h"


/************************* color **************************/
#define COLOR_RESET   "\033[0m"
#define COLOR_BLACK   "\033[30m"   // Black 黑色
#define COLOR_RED     "\033[31m"   // Red 红色
#define COLOR_GREEN   "\033[32m"   // Green 绿色
#define COLOR_YELLOW  "\033[33m"   // Yellow 黄色
#define COLOR_BLUE    "\033[34m"   // Blue 蓝色
#define COLOR_MAGENTA "\033[35m"   // Magenta 洋红
#define COLOR_CYAN    "\033[36m"   // Cyan 青色
#define COLOR_WHITE   "\033[37m"   // White 白色

/**********************************************************/
#define CONFIG_PRINTD_STRING_LEN    256 // 设置 str 的最大长度

#define CONFIG_PRINTD_TIME          1   // 可选
#define CONFIG_PRINTD_UID           1   // 可选
#define CONFIG_PRINTD_XXX           1   // 可选

#define CONFIG_PRINTD_ENABLE_UART   1   // 打印到串口
#define CONFIG_PRINTD_ENABLE_FUNC   1   // 打印函数信息
#define CONFIG_PRINTD_ENABLE_LINE   1   // 打印行信息

#define PRINTD_OFF                 -1   // 一个都不打印
#define PRINTD_ASSERT               0   // 红色 最好不要屏蔽
#define PRINTD_ERR                  1   // 洋红 错误, 用户在正常使用一不会触发的打印
#define PRINTD_WARNING              2   // 黄色 警告, 用户在错误使用的情况下会触发的打印
#define PRINTD_INFO                 3   // 白色 信息. 打印一般信息
#define PRINTD_DEBUG                4   // 绿色 调试, 调试的信息
#define PRINTD_VERBOSE              5   // 蓝色 调试, 调试的信息
#define PRINTD_ALL                  6   // 全都打印

struct level_info {
    const char info;
    const char *color;
};

struct printd_head {
    char level;                             // 等级, 小写表示 kernel, 大写表示 rootserver
    char module[10];                        // 日志类型 内存管理, caps, etc.
#ifdef CONFIG_PRINTD_TIME
    unsigned int time;                      // 日志产生时间
#endif
    // int file;                           // 日志所在文件
    // int fun;                            // 日志所在函数
    // int line;                           // 日志所在行数
};

struct printd_cache {
    struct printd_head head;                // 可选信息
    char str[CONFIG_PRINTD_STRING_LEN];     // 日志主体
};

/******************************************************************************/

#define LOG_CACHE_LEN   64
#define LOG_CACHE_MASK  (LOG_CACHE_LEN - 1)

struct log_cache {
    unsigned int magic;                         // 魔术字 ( 取反 )
    unsigned int in;                            // 入列的时候增加的位置
    unsigned int out;                           // 出列的时候增加的位置
    struct printd_cache cache[LOG_CACHE_LEN];   // 日志缓存区大小是确定的
};

#ifdef CONFIG_KERNEL
#define PRINTD_MEMCPY   memcpy
#define PRINTD_LOCK     spin_lock(&print_lock);
#define PRINTD_UNLOCK   spin_unlock(&print_lock);
void ksync_log_cache(unsigned long a0);
#else
#define PRINTD_MEMCPY   memcpy
#define PRINTD_LOCK
#define PRINTD_UNLOCK
int pre_log_out(void);
int log_out_rootserver(void);
int log_out_kernel(void);
#endif

void _printd(int level, int config_level, char *module, const char *format, ...);

void log_cache_init(void);
void log_in(struct printd_cache* data);

typedef struct log_type {
    char module[10];                    // 模块名
    int level;                          // 基准打印等级
} log_type_t;

#define printd(level, format, ...) _printd(level, CONFIG_PRINTD_LEVEL, "...", format, ##__VA_ARGS__)
#define LOGA(type, format, ...)    _printd(PRINTD_ASSERT, type.level, type.module, format, ##__VA_ARGS__)
#define LOGE(type, format, ...)    _printd(PRINTD_ERR, type.level, type.module, format, ##__VA_ARGS__)
#define LOGW(type, format, ...)    _printd(PRINTD_WARNING, type.level, type.module, format, ##__VA_ARGS__)
#define LOGI(type, format, ...)    _printd(PRINTD_INFO, type.level, type.module, format, ##__VA_ARGS__)
#define LOGD(type, format, ...)    _printd(PRINTD_DEBUG, type.level, type.module, format, ##__VA_ARGS__)
#define LOGV(type, format, ...)    _printd(PRINTD_VERBOSE, type.level, type.module, format, ##__VA_ARGS__)
#define LOGPOINT(type)             _printd(PRINTD_WARNING, type.level, type.module, "%s : %s : %d", __FILE__, __FUNCTION__, __LINE__)

/*********************** 自己设置模块 **********************/

/**
 * @brief   用于头文件声明
 *
 */
#define LOG_TYPE(var, lev, n)      extern log_type_t var;

/**
 * @brief   根据实际情况添加自己的模块
 *          1. 模块的名称
 *          2. 打印显示的名称
 *          3. 打印的等级
 *
 */
#define LOG_DECLARE()                                    \
    LOG_TYPE(LOGOTHER, PRINTD_WARNING, "...")            \
    LOG_TYPE(LOGELF, PRINTD_WARNING, "ELF")              \
    LOG_TYPE(LOGSOURCE, PRINTD_DEBUG, "SOURCE")          \
    LOG_TYPE(LOGMUTEX, PRINTD_DEBUG, "MUTEX")            \
    LOG_TYPE(LOGCOND, PRINTD_VERBOSE, "COND")            \
    LOG_TYPE(LOGRWLOCK, PRINTD_WARNING, "RWLOCK")        \
    LOG_TYPE(LOGDEV, PRINTD_WARNING, "DEV")              \
    LOG_TYPE(LOGENV, CONFIG_PRINTD_LEVEL, "ENV")         \
    LOG_TYPE(LOGPROC, PRINTD_ALL, "PROC")                \
    LOG_TYPE(LOGAS, PRINTD_ALL, "AS")                    \
    LOG_TYPE(LOGVFS, CONFIG_PRINTD_LEVEL, "VFS")         \
    LOG_TYPE(LOGEXBUDDY, CONFIG_PRINTD_LEVEL, "EXBUDDY") \
    LOG_TYPE(LOGMEM, CONFIG_PRINTD_LEVEL, "MEM")         \
    LOG_TYPE(LOGCSYS, CONFIG_PRINTD_LEVEL, "CSYS")       \
    LOG_TYPE(LOGFAULT, CONFIG_PRINTD_LEVEL, "FAULT")

LOG_DECLARE();

/**
 * @brief   用于源文件定义
 *
 */
#undef LOG_TYPE
#define LOG_TYPE(var, lev, n) log_type_t var = {.level = lev, .module = n};

/******************************************************************************/

#endif
