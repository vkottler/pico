/* internal */
#include "App.h"

bool led_state_val = true;

void do_led(CommandLine &cli)
{
    (void)cli;

    led_state_val = not led_state_val;

    // add LED code soon?
    // led1_state(led_state_val);

    printf("Toggling LED %s.\n", led_state_val ? "on" : "off");
}

void register_commands(CommandLineApp &app)
{
    app.add_handler("led", do_led, "toggle the LED on or off");
}

char input[BUFSIZ];

int main(void)
{
    App app(register_commands);

    while (true)
    {
        app.poll_stdin(input);
    }

    return 0;
}
