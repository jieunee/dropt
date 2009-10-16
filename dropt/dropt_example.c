/** dropt_example.c
  *
  *     A simple dropt example.
  *
  * Written by James D. Lin and assigned to the public domain.
  *
  * The latest version of this file can be downloaded from:
  * <http://www.taenarum.com/software/dropt/>
  */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "dropt.h"


typedef enum { unknown, heads, tails } face_t;


/** handle_face
  *
  *     An example of a custom option handler.  Usually the stock callbacks
  *     (e.g. dropt_handle_bool, dropt_handle_int, dropt_handle_string,
  *     etc.) should be sufficient for most purposes.
  */
static dropt_error_t
handle_face(dropt_context_t* context, const dropt_char_t* optionArgument, void* handlerData)
{
    dropt_error_t err = dropt_error_none;
    face_t* face = handlerData;
    assert(face != NULL);

    /* Option handlers should handle 'optionArgument' being NULL (if the
     * option's argument is optional) or being the empty string (if a user
     * explicitly passed an empty string (e.g. --face="").
     */
    if (optionArgument == NULL || optionArgument[0] == '\0')
    {
        err = dropt_error_insufficient_arguments;
    }
    else if (strcmp(optionArgument, "heads") == 0)
    {
        *face = heads;
    }
    else if (strcmp(optionArgument, "tails") == 0)
    {
        *face = tails;
    }
    else
    {
        /* Reject the value as being inappropriate for this handler. */
        err = dropt_error_mismatch;
    }

    return err;
}


int
main(int argc, char** argv)
{
    dropt_bool_t showHelp = 0;
    dropt_bool_t showVersion = 0;
    int i = 0;
    face_t face = unknown;

    /* Each option is defined by a row in a table, containing properties
     * such as the option's short name (e.g. -h), its long name (e.g.
     * --help), its help text, its handler callback, and its callback data
     * (for typical handlers, the data is usually the address of a variable
     * for the handler to modify).
     *
     * See the dropt_option_t documentation in dropt.h for a complete list
     * of option properties.
     */
    dropt_option_t options[] = {
        { 'h',  "help", "Shows help.", NULL, dropt_handle_bool, &showHelp, dropt_attr_halt },
        { '?', NULL, NULL, NULL, dropt_handle_bool, &showHelp, dropt_attr_halt | dropt_attr_hidden },
        { '\0', "version", "Shows version information.", NULL, dropt_handle_bool, &showVersion, dropt_attr_halt },
        { 'i',  "int", "Sample integer option.", "value", dropt_handle_int, &i },
        { 'f',  "face", "Sample custom option.", "{heads, tails}", handle_face, &face },
        { 0 } /* Sentinel value. */
    };

    dropt_context_t* droptContext = dropt_new_context(options);
    if (droptContext != NULL)
    {
        dropt_char_t** rest = dropt_parse(droptContext, -1, &argv[1]);
        if (dropt_get_error(droptContext) != dropt_error_none)
        {
            fprintf(stderr, "dropt_example: %s\n", dropt_get_error_message(droptContext));
        }
        else if (showHelp)
        {
            printf("Usage: dropt_example [options] [--] [operands]\n\n"
                   "Options:\n");
            dropt_print_help(stdout, options, NULL);
        }
        else if (showVersion)
        {
            printf("dropt_example 1.0\n");
        }
        else
        {
            printf("int value: %d\n", i);
            printf("face value: %d\n", face);

            printf("Operands: ");
            while (*rest != NULL)
            {
                printf("%s ", *rest);
                rest++;
            }
            printf("\n");
        }

        dropt_free_context(droptContext);
    }

    return 0;
}
