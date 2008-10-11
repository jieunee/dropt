#ifndef DROPT_STRING_H
#define DROPT_STRING_H

#include <stdarg.h>
#include "dropt.h"

#if defined _UNICODE || defined UNICODE
    #define dropt_strlen wcslen
    #define dropt_strcmp wcscmp
    #define dropt_strchr wcschr
    #define dropt_strtol wcstol
    #define dropt_strtoul wcstoul
    #define dropt_strtod wcstod
    #define dropt_tolower towlower
    #define dropt_fputs fputws
#else
    #define dropt_strlen strlen
    #define dropt_strcmp strcmp
    #define dropt_strchr strchr
    #define dropt_strtol strtol
    #define dropt_strtoul strtoul
    #define dropt_strtod strtod
    #define dropt_tolower tolower
    #define dropt_fputs fputs
#endif


dropt_char_t* dropt_strdup(const dropt_char_t* s);
int dropt_stricmp(const dropt_char_t* s, const dropt_char_t* t);

#ifndef DROPT_NO_STRING_BUFFERS
typedef struct dropt_stringstream dropt_stringstream;

dropt_char_t* dropt_vaprintf(const dropt_char_t* fmtP, va_list args);
dropt_char_t* dropt_aprintf(const dropt_char_t* fmtP, ...);

dropt_stringstream* dropt_ssopen(void);
void dropt_ssclose(dropt_stringstream* ssP);

void dropt_ssclear(dropt_stringstream* ssP);
dropt_char_t* dropt_ssfinalize(dropt_stringstream* ssP);
const dropt_char_t* dropt_ssgetstring(const dropt_stringstream* ssP);

int dropt_vssprintf(dropt_stringstream* ssP, const dropt_char_t* fmtP, va_list args);
int dropt_ssprintf(dropt_stringstream* ssP, const dropt_char_t* fmtP, ...);
#endif /* DROPT_NO_STRING_BUFFERS */

#endif /* DROPT_STRING_H */
