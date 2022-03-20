#ifndef ERR_H
#define ERR_H
#include <stdarg.h>

#if defined(__cplusplus)
extern "C" {
#endif
void err(int eval, const char *fmt, ...);
void errx(int eval, const char *fmt, ...);
void warn(const char *fmt, ...);
void warnx(const char *fmt, ...);
void verr(int eval, const char *fmt, va_list args);
void verrx(int eval, const char *fmt, va_list args);
void vwarn(const char *fmt, va_list args);
void vwarnx(const char *fmt, va_list args);
#if defined(__cplusplus)
}
#endif

  
#endif // #ifndef ERR_H
