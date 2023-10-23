/* internal */
#include "testing.h"

/* toolchain */
#include <cstdio>
#include <cstring>

/* third-party */
#include "coral/cli/StringCommandProcessor.h"

/*
 * Must be set by a debugger.
 */
volatile bool enable_cli = false;

using Processor = Coral::StringCommandProcessor<BUFSIZ>;

bool led_state_val = true;

void handle_input(const char **args, std::size_t num_args)
{
    for (std::size_t i = 0; i < num_args; i++)
    {
        printf("(%zu) %s\n", i, args[i]);
    }

    if (strcmp(args[0], "led") == 0)
    {
        led_state_val = not led_state_val;

        // add LED code soon?
        // led1_state(led_state_val);

        printf("Toggling LED %s.\n", led_state_val ? "on" : "off");
    }
    else if (strcmp(args[0], "cli") == 0)
    {
        /* Toggle CLI. */
        enable_cli = not enable_cli;
        printf("Toggling CLI %s.\n", enable_cli ? "on" : "off");
    }
    else
    {
        printf("not handled\n");
    }
}

int main(void)
{
    int iterations = 0;

    initialize_semihosting();

    Processor::Buffer buf;
    Processor processor(buf, handle_input, true /* auto_poll */);
    char input[BUFSIZ];

    while (true)
    {
        if (enable_cli and gets(input) != NULL)
        {
            /* Publish command data. */
            buf.push_n_blocking(input, strlen(input));
            buf.push_blocking('\n');

            /* Emit prompt. */
            printf(prompt);
        }

        iterations++;
    }

    return 0;
}
