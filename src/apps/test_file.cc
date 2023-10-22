/* internal */
#include "testing.h"

/* toolchain */
#include <cstdio>
#include <cstring>

/*
 * Must be set by a debugger.
 */
volatile bool enable_cli = false;

int main(void)
{
    bool led_state_val = true;
    int iterations = 0;

    initialize_semihosting();

    char input[BUFSIZ];

    while (true)
    {
        if (enable_cli and gets(input) != NULL)
        {
            if (!input[0])
            {
                printf(prompt);
                continue;
            }

            if (strcmp(input, "led") == 0)
            {
                led_state_val = not led_state_val;

                // add LED code soon?
                // led1_state(led_state_val);

                printf("Toggling LED %s.\n", led_state_val ? "on" : "off");
            }
            else if (strcmp(input, "cli") == 0)
            {
                /* Toggle CLI. */
                enable_cli = not enable_cli;
            }
            else
            {
                printf("input: '%s'\n", input);
            }

            printf(prompt);
        }

        iterations++;
    }

    return 0;
}
