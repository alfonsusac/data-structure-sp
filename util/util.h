#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h> // https://stackoverflow.com/questions/30033582/what-is-the-symbol-for-whitespace-in-c/30033598#30033598

// ************************ LINES SHORTCUT: INPUT AND OUTPUT
#define clr() printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")
#define get(PROMPT, FORMAT, ...)                  \
    {                                             \
        while (1)                                 \
        {                                         \
            printf(PROMPT);                       \
            fflush(stdin);                        \
            if (scanf(FORMAT, ##__VA_ARGS__) > 0) \
            {                                     \
                fflush(stdin);                    \
                break;                            \
            }                                     \
        }                                         \
    }
#define getline(PROMPT, OUTPUT)                    \
    {                                              \
        while (1)                                  \
        {                                          \
            printf(PROMPT);                        \
            fflush(stdin);                         \
            if (scanf("%255[^\n]%*c", OUTPUT) > 0) \
            {                                      \
                fflush(stdin);                     \
                break;                             \
            }                                      \
        }                                          \
    }
#define getint(PROMPT, OUTPUT)            \
    {                                     \
        while (1)                         \
        {                                 \
            printf(PROMPT);               \
            fflush(stdin);                \
            if (scanf("%d", &OUTPUT) > 0) \
            {                             \
                fflush(stdin);            \
                break;                    \
            }                             \
        }                                 \
    }
#define validate(GET, MUST_BE) \
    do                         \
    {                          \
        GET;                   \
    } while (!(MUST_BE))
#define validate_catch(GET, MUST_BE, CATCH) \
    while (1)                               \
    {                                       \
        GET;                                \
        if (MUST_BE)                        \
        {                                   \
            break;                          \
        }                                   \
        else                                \
        {                                   \
            CATCH;                          \
        }                                   \
    }

int strcasecmpnew(const char *s1, const char *s2)
{
    // Copy first to make it non destructive
    const unsigned char *us1 = (const unsigned char *)s1,
                        *us2 = (const unsigned char *)s2;

    // Lower it
    while (tolower(*us1) == tolower(*us2++))
        if (*us1++ == '\0')
            return (0);
    return (tolower(*us1) - tolower(*--us2));
}

#define validate_int_from_choices(PROMPT, OUTPUT, NUM_OF_CHOICE, ...) \
    {                                                                 \
        OUTPUT = -1;                                                  \
        char input_choice[256];                                       \
        const char *__choices[] = {__VA_ARGS__};                      \
        do                                                            \
        {                                                             \
            get(PROMPT, "%255[^\n]%*c", input_choice);                \
            for (range(NUM_OF_CHOICE))                                \
            {                                                         \
                if (strcmp(input_choice, __choices[i]) == 0)          \
                {                                                     \
                    OUTPUT = i;                                       \
                    break;\
                }                                            \
            }                                                \
        } while (OUTPUT == -1);                              \
    }
#define scmp_case(OUTPUT, STR1, STR2)\
    {\
        const unsigned char *us1 = (const unsigned char *)STR1;\
        const unsigned char *us2 = (const unsigned char *)STR2;\
        while (tolower(*us1) == tolower(*us2++))\
        {\
            if (*us1++ == '\0')\
            {\
                OUTPUT = 0;\
                break;\
            }\
        }\
        OUTPUT = tolower(*us1) - tolower(*--us2);\
    }
#define validate_int_from_choices_case(PROMPT, OUTPUT, NUM_OF_CHOICE, ...) \
    {                                                                      \
        OUTPUT = -1;                                                       \
        char input_choice[256];                                            \
        const char *__choices[] = {__VA_ARGS__};                           \
        do                                                                 \
        {                                                                  \
            get(PROMPT, "%255[^\n]%*c", input_choice);                     \
            for (range(NUM_OF_CHOICE))                                     \
            {                                                              \
                int cmp;                                                   \
                scmp_case(cmp, input_choice, __choices[i]);                \
                if (cmp == 0)                                              \
                {                                                          \
                    OUTPUT = i;                                            \
                    break;                                                 \
                }                                                          \
            }                                                              \
        } while (OUTPUT == -1);                                            \
    }
#define validate_int_from_array(PROMPT, OUTPUT, CHOICE_COUNT, CHOICE_ARRAY) \
    { /**C     C     C                  ARRAY **/                        \
        char input_choice[256];                                          \
        OUTPUT = -1;                                                     \
        do                                                               \
        {                                                                \
            get(PROMPT, "%255[^\n]%*c", input_choice);                   \
            for (range(CHOICE_COUNT))                                    \
            {                                                            \
                if (strcmp(input_choice, CHOICE_ARRAY[i]) == 0)             \
                {                                                        \
                    OUTPUT = i;                                          \
                    break;                                               \
                }                                                        \
            }                                                            \
        } while (OUTPUT == -1);                                          \
    }

#define validate_str_from_choices(PROMPT, OUTPUT, NUM_OF_CHOICE, ...) \
    {                                                       \
        const char *__choices[] = {__VA_ARGS__};            \
        do                                                  \
        {                                                   \
            get(PROMPT, "%255[^\n]%*c", OUTPUT);            \
            for (range(NUM_OF_CHOICE))                                \
            {                                               \
                if (strcmp(OUTPUT, __choices[i]) == 0)      \
                {                                           \
                    break;                                  \
                }                                           \
            }                                               \
        } while (1);                                        \
    }
#define validate_yn(PROMPT, OUTPUT_BOOL, ...)       \
    {                                               \
        char input_choice[256];                     \
        do                                          \
        {                                           \
            put(PROMPT __VA_OPT__(, ) __VA_ARGS__); \
            get(" ", "%3[^\n]%*c", input_choice);   \
            if (len(input_choice) == 1)             \
            {                                       \
                if (input_choice[0] == 'n')         \
                {                                   \
                    OUTPUT_BOOL = false;            \
                    break;                          \
                }                                   \
                else if (input_choice[0] == 'y')    \
                {                                   \
                    OUTPUT_BOOL = true;             \
                    break;                          \
                }                                   \
            }                                       \
        } while (1);                                \
    }
#define getenter(...)    \
    printf(__VA_ARGS__); \
    getchar();
#define putl(...)        \
    printf(__VA_ARGS__); \
    printf("\n");

// ************************ LINES SHORTCUT: OTHERS
#define len(STR)                strlen(STR)
#define new_struct(TYPE, NAME)  TYPE *NAME = (TYPE *)malloc(sizeof(TYPE))
#define break_if_numeric(STR)   int len = strlen(STR); for( range(len) ) if( !isdigit(STR[i])) continue; break;
#define loop(DOWHAT)            while(true){DOWHAT}
#define CONST_STRING_ARRAY(NAME,COUNTNAME, NUM, ...)        const int COUNTNAME = NUM; const char *const NAME[] = {__VA_ARGS__};

// ************************ ALIASES
#define put     printf
#define is      ==
#define isnot   !=
#define and     &&
#define or      ||
#define STRUCT  typedef struct
#define exists  isnot NULL
#define isempty is NULL

// ************************ EXPRESSIONS
#define _range1(end) \
    int i = 0;       \
    i < end;         \
    i++
#define _range2(start, end) \
    int i = start;          \
    i < end;                \
    i++
#define _range3(start, end, hop) \
    int i = start;               \
    i < end;                     \
    i = i + hop
#define range_get_macro(_1, _2, _3, name, ...) name
#define range(...) range_get_macro(__VA_ARGS__, _range3, _range2, _range1)(__VA_ARGS__)
#define seq(A, B)                           strcmp(A, B) == 0
#define scmp(A,B,C)                         strcmp(A,C) B 0
#define between(what, from, to)             what >= from && what <= to
#define traverse(what, to)                  what = what->to
#define starts_with(INPUT,STARTS_WITH)      strncmp(STARTS_WITH,INPUT,strlen(STARTS_WITH)) == 0
#define ends_with(INPUT,ENDS_WITH)          strlen(INPUT) > strlen(ENDS_WITH) && !strcmp(INPUT + strlen(INPUT) - strlen(ENDS_WITH), ENDS_WITH)
#define betweenstr(STRING, FROM, TO)        between(strlen(STRING), FROM, TO)
#define max(A,B)                            A > B ? A : B

// ******************************** PERSONAL LIMITS
#define MAX_STR_LENGTH 256
