/*
 * Automatically generated by ./mkgetopt.py [v1.0.2]
 * Input file: example.in
 *
 * DO NOT EDIT THIS FILE!
 *
 * Make all changes in example.in.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>
#include <errno.h>


#include "getopt_long.h"
#include "error.h"

#include "example.h"

static const struct option Long_options[] =
{
      {"help",                            no_argument,       0, 300}
    , {"version",                         no_argument,       0, 301}
    , {"jobs",                            required_argument, 0, 302}
    , {"use-proxy",                       no_argument,       0, 303}
    , {"foreground",                      no_argument,       0, 304}
    , {"debug",                           required_argument, 0, 305}
    , {"log-level",                       optional_argument, 0, 306}
    , {"little-endian",                   no_argument,       0, 307}
    , {"big-endian",                      no_argument,       0, 308}
    , {"disk-size",                       required_argument, 0, 313}
    , {"delay",                           required_argument, 0, 314}

    , {0, 0, 0, 0}
};

static const char Short_options[] = "hVj:fl::LBd:D:";

static unsigned long grok_int(const char * str, const char * option, char * present, int * err, unsigned long limit, int has_limit);
static uint64_t grok_size(const char * str, const char * option, char * present, int * err);
static char* dupstr(const char*);
static void show_version(void);
static void show_help(void);



/*
 * Parse command line options.
 * Return:
 *    0 on success
 *    > 0 on error (number of errors encountered)
 */
int
fulcrum_parse(fulcrum_option * opt, int argc, char * const *argv)
{
    int c,
        errs = 0;

    /*
     * Assume that getopt library has been used before this call;
     * and reset explicitly.
     */
    optind = 0;

    opt->help = 0;
    opt->version = 0;
    opt->njobs = 1;
    opt->use_proxy_p = 0;
    opt->fg_p = 0;
    opt->debug = dupstr("syslog");
    opt->loglevel = 0;
    opt->somevar = 0;
    opt->somevar2 = 1;
    opt->somevar3 = dupstr("");
    opt->somevar4 = 4.1458132e-3;
    opt->disksize = 1048576;
    opt->delay = 3.32;

    opt->help_present = 0;
    opt->version_present = 0;
    opt->njobs_present = 0;
    opt->use_proxy_p_present = 0;
    opt->fg_p_present = 0;
    opt->debug_present = 0;
    opt->loglevel_present = 0;
    opt->little_end_cb_present = 0;
    opt->big_end_cb_present = 0;
    opt->disksize_present = 0;
    opt->delay_present = 0;


    opt->argv_inputs = 0;
    opt->argv_count  = 0;

    if (argc == 0)
        return 0;

    if (argc < 0 || !argv || !argv[0])
        return 0;

    while ((c = getopt_long(argc, argv, Short_options, Long_options, 0)) != EOF)
    {
        switch (c)
        {
        case 300:  /* help */
        case 'h':  /* help */
            opt->help = 1;
            opt->help_present = 1;
            fflush(stdout);
            fflush(stderr);
            show_help();
            break;

        case 301:  /* version */
        case 'V':  /* version */
            opt->version = 1;
            opt->version_present = 1;
            fflush(stdout);
            fflush(stderr);
            show_version();
            break;

        case 302:  /* jobs */
        case 'j':  /* jobs */
            if (optarg && *optarg)
            {
                opt->njobs = (int)grok_int(optarg, "jobs",
                                    &opt->njobs_present, &errs,
                                    INT_MAX, 1);
            }
            break;

        case 303:  /* use-proxy */
            opt->use_proxy_p = 1;
            opt->use_proxy_p_present = 1;
            break;

        case 304:  /* foreground */
        case 'f':  /* foreground */
            opt->fg_p = 1;
            opt->fg_p_present = 1;
            break;

        case 305:  /* debug */
            opt->debug_present = 1;
            if (optarg && *optarg)
                opt->debug = dupstr(optarg);
            break;

        case 306:  /* log-level */
        case 'l':  /* log-level */
            if (optarg && *optarg)
            {
                opt->loglevel = (int)grok_int(optarg, "log-level",
                                    &opt->loglevel_present, &errs,
                                    INT_MAX, 1);
            }
            else
            {
                opt->loglevel_present = 1;
                ++opt->loglevel;
            }
            break;

        case 307:  /* little-endian */
        case 'L':  /* little-endian */
            opt->little_end_cb_present = 1;
            assert(opt->little_end_cb);
            if (optarg && *optarg)
                (*opt->little_end_cb)(opt, optarg);
            else
                (*opt->little_end_cb)(opt, 0);
            break;

        case 308:  /* big-endian */
        case 'B':  /* big-endian */
            opt->big_end_cb_present = 1;
            assert(opt->big_end_cb);
            if (optarg && *optarg)
                (*opt->big_end_cb)(opt, optarg);
            else
                (*opt->big_end_cb)(opt, 0);
            break;

        case 313:  /* disk-size */
        case 'd':  /* disk-size */
            if (optarg && *optarg)
                opt->disksize = grok_size(optarg, "disk-size",
                                    &opt->disksize_present, &errs);
            break;

        case 314:  /* delay */
        case 'D':  /* delay */
            if (optarg && *optarg)
            {
                char* xxptr  = 0;
                double xxdbl = strtod(optarg, &xxptr);

                if (xxptr)
                {
                    if (xxptr == optarg)
                    {
                        ++errs;
                        error(0, 0, "Invalid characters '%s' for floating point value in option 'delay'", xxptr);
                    }
                    else if (*xxptr)
                        error(0, 0, "Ignoring trailing characters '%s' for option 'delay'", xxptr);
                    else
                    {
                        opt->delay = xxdbl;
                        opt->delay_present = 1;
                    }
                }
            }
            break;



        default:
            ++errs;
            break;
        }
    }

    opt->argv_inputs = &argv[optind];
    opt->argv_count  = argc - optind;

    /*
     * Reset getopt library for next use.
     */
    optind = 0;

    return errs;
}


/**
 * @memo Grok a integer in any base (auto detect)
 *
 * @param str     String containing an integer (possibly signed)
 * @param option  The corresponding option string (for emitting errors)
 * @param present Output value -- true if there are no errors, false otherwise
 * @param err     Output value -- incremented on errors
 * @param limit   The maximum permissible limit for this integer
 * @param has_limit   Set if the corresponding option had a size limitation
 *                (e.g., a short integer etc.)
 * @return Converted string value.
 */
static unsigned long
grok_int(const char * str, const char * option, char * present, int * err,
            unsigned long limit, int has_limit)
{
    char * xxend = 0;
    long lim_pos = (long) limit,
         lim_neg = -lim_pos - 1;
    int isneg = 0;
    union
    {
        long l;
        unsigned long ul;
    } un;

    if (*str == '-')
    {
        ++str;
        isneg = 1;
    }

    un.ul = strtoul(str, &xxend, 0);
    if (xxend && *xxend)
        error(0, 0, "Ignoring trailing characters '%s' for option '%s'", xxend, option);

    if (isneg)
    {
        un.l *= -1;
    }

    if (has_limit)
    {
        if (isneg && un.l < lim_neg)
        {
            *err += 1;
            error(0, 0, "Integer value '-%s' underflow for option '%s' (min %ld)",
                    str, option, lim_neg);
        }
        else if (!isneg && un.ul > (unsigned long)lim_pos)
        {
            *err += 1;
            error(0, 0, "Integer value '%s' overflow for option '%s' (max %lu)",
                    str, option, lim_pos);
        }
    }
    else
        *present = 1;

    return un.ul;
}

/**
 * @memo Grok a size specification string.
 *
 * @doc Handles suffixes of 'k', 'M', 'G', 'T', 'P'
 *
 * @param str     String containing size like '36k' or '14M'
 * @param option  The corresponding option string (for emitting errors)
 * @param present Output value -- true if there are no errors, false otherwise
 * @param err     Output value -- incremented on errors
 *
 * @return Converted value of the size
 */
static uint64_t
grok_size(const char * str, const char * option, char * present, int * err)
{
    int errs = 0;
    uint64_t   xxbase = 0,
               xxmult = 1,
               xxval  = 0;

    char * xxend = 0;

    /* MS is weird. They deliberately chose NOT to use names that the rest
     * of the world uses. */
#ifdef _MSC_VER
#define strtoull(a,b,c,)  _strtoui64(a,b,c)
#define _ULLCONST(n) n##ui64
#else
#define _ULLCONST(n) n##ULL
#endif

#define UL_MAX__    _ULLCONST(18446744073709551615)
#define _kB         _ULLCONST(1024)
#define _MB         (_kB * 1024)
#define _GB         (_MB * 1024)
#define _TB         (_GB * 1024)
#define _PB         (_TB * 1024)

    *present = 1;
    xxbase = strtoull(str, &xxend, 0);

    if ( xxend && *xxend )
    {
        switch (*xxend)
        {
            case 'b': case 'B':
                break;
            case 'k': case 'K':
                xxmult = _kB;
                break;
            case 'M':
                xxmult = _MB;
                break;
            case 'G':
                xxmult = _GB;
                break;
            case 'T':
                xxmult = _TB;
                break;
            case 'P':
                xxmult = _PB;
                break;
            default:
                errs++;
                error(0, 0, "Unknown multilplier constant '%c'  for option '%s'",
                        *xxend, option);
                *present = 0;
                break;
        }

        xxval = xxbase * xxmult;
        if ((xxbase == UL_MAX__ && errno == ERANGE) || 
            (xxval < xxbase))
        {
            errs++;
            error(0, 0, "Size value overflow for option '%s' (base %lu, multiplier %lu)",
                    option, xxbase, xxmult);
            *present = 0;
        }
    }
    else
        xxval = xxbase;

    *err += errs;
    return xxval;
}


/*
 * Duplicate a string. Many systems don't have strdup().
 */
static char*
dupstr(const char* s)
{
    int n    = 1 + strlen(s);
    char * x = (char *)calloc(1, n);
    if (x)
        memcpy(x, s, n);

    return x;
}

static void
show_version(void)
{
    const char * ver = fulcrum_version ();

    fflush(stdout);
    fflush(stderr);
    printf("%s -- %s\n", program_name, ver);
    fflush(stdout);
    fflush(stderr);
    exit(0);
}

static void
show_help(void)
{
    const char* desc =
"Example program to show mkgetopt.pl.\n\n"
"This is a hello world program that is too long in the number of words it\n"
"uses. And this sentence has entirely too many words with continuations and\n"
"such.\n"
;
    const char* usage = get_prog_usage();
    const char* options = 
"\nOptions (defaults within '[ ]'):\n"
"    --help, -h           Print this help and exit [false]\n"
"    --version, -V        Print version information and exit [false]\n"
"    --jobs=j, -j j       Use 'J' jobs simultaneously [1]\n"
"    --use-proxy          Use the default proxy server [false]\n"
"    --foreground, -f     Run in the foreground [false]\n"
"    --debug=d            Send debug messages to 'D' [syslog]\n"
"    --log-level=l, -l l  Default log level [0]\n"
"    --little-endian, -L  Use little-endian format\n"
"    --big-endian, -B     Use big-endian format\n"
"    --disk-size=d, -d d  Disk size of the emulated rootfs [1M]\n"
"    --delay=d, -D d      Wait for D millisecs [3.32]\n"
;

    fflush(stdout);
    fflush(stderr);
    printf("%s: %s", program_name, desc);
    fputs(usage, stdout);
    fputs(options, stdout);
    fflush(stdout);
    fflush(stderr);
    exit(0);
}
