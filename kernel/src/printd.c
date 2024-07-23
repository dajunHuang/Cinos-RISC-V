#include "printd.h"
#include "k_stdarg.h"
#include "k_stdio.h"
#include "k_string.h"


const char info_assert     = 'a';
const char info_error      = 'e';
const char info_warning    = 'w';
const char info_info       = 'i';
const char info_debug      = 'd';
const char info_verbose    = 'v';

LOG_DECLARE()
const char printd_level[] = "aewidv";
static struct level_info s_level_info[6] = {
    {.info = info_assert,  .color = COLOR_RED   },
    {.info = info_error,   .color = COLOR_RED   },
    {.info = info_warning, .color = COLOR_YELLOW},
    {.info = info_info,    .color = COLOR_WHITE },
    {.info = info_debug,   .color = COLOR_GREEN },
    {.info = info_verbose, .color = COLOR_BLUE  }
};

void printd_write(const char *str)
{
#ifdef CONFIG_PRINTD_ENABLE_UART
    puts(str);
#endif // CONFIG_PRINTD_ENABLE_UART
}

/**
 * @brief   日志打印
 *
 * @param   level           等级
 * @param   config_level    配置的等级
 * @param   module          模块
 * @param   format          omit
 * @param   ...             omit
 */
void _printd(int level, int config_level, char *module, const char *format, ...)
{
    int tmp = 0;
    int state = 0;
    char log[CONFIG_PRINTD_STRING_LEN + 30];
    struct printd_cache this;

    if (level > config_level) {                             // 如果打印等级不够, 就退出
        return;
    }

    /**
     * @brief   打印等级, 小写kernel, 大写rootserver
     *
     */
    this.head.level = printd_level[level];
    log[state++]      = printd_level[level];

    /**
     * @brief   模块
     *
     */
    log[state++] = '|';
    PRINTD_MEMCPY(this.head.module, module, 10);
    this.head.module[9] = 0;
    tmp = strlen(module);
    PRINTD_MEMCPY(&log[state], module, tmp);
    state += tmp;
    PRINTD_MEMCPY(this.head.module, module, 10);

    /**
     * @brief   可选信息
     *
     */
#ifdef CONFIG_PRINTD_TIME                                                       // 时间戳
    log[state++] = '|';
    char tmp_buf[20];
    this.head.time = 0;
    sprintf(tmp_buf, "%08X| ", this.head.time);
    PRINTD_MEMCPY(&log[state], tmp_buf, 8);
    state += 8;
#endif

    log[state++] = '|';
    log[state++] = ' ';

    /* info */
    va_list ap;
    va_start(ap, format);
    vsnprintf(this.str, CONFIG_PRINTD_STRING_LEN, format, ap);
    va_end(ap);
    PRINTD_MEMCPY(&log[state], this.str, CONFIG_PRINTD_STRING_LEN);

    PRINTD_LOCK;
    printf("%s", s_level_info[level].color);        // 打印颜色
    printd_write(log);                              // 打印信息
    printf("%s", COLOR_RESET);                      // 打印颜色
    log_in(&this);
    PRINTD_UNLOCK;
}

/******************************************************************************/

struct log_cache log_cache_kernel_t = {.in = 1, .out = 1};
struct log_cache *log_cache_kernel = &log_cache_kernel_t;

/**
 * @brief   初始化 log_cache
 *
 */
void log_cache_init(void)
{
    // log_cache_kernel->in = 0;
    // log_cache_kernel->out = 0;
}

/**
 * @brief   入队, kernel 和 rootserver 都会调用
 *
 * @param   data            omit
 */
void log_in(struct printd_cache* data)
{
    unsigned int in;
    unsigned int out;
    if (!data) {
        return;
    }

    // 临界区, [rootserver加互斥锁], [kernel 加自旋锁]
    in = log_cache_kernel->in;
    out = log_cache_kernel->out;
    log_cache_kernel->in++;                      // 先把坑位占着, 如果要加锁, 就加这儿
    if (in - out == LOG_CACHE_LEN) {        // 满了, 覆盖
        log_cache_kernel->out++;
    }

    // 临界区
    PRINTD_MEMCPY(&log_cache_kernel->cache[(in & LOG_CACHE_MASK)], data, sizeof(struct printd_cache));  // 临界区访问, TODO 如果被高优先级的打断了会怎么样
}

void ksync_log_cache(unsigned long a0)
{
    log_cache_kernel = (struct log_cache *)a0;
    PRINTD_MEMCPY((void*)a0, &log_cache_kernel_t, sizeof(struct log_cache));
}
