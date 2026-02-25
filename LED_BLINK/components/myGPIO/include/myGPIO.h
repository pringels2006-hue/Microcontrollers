//LED

void myGPIO_LED_aan(int pin);
void myGPIO_LED_uit(int pin);
void myGPIO_LED_toggle(int pin);
void myGPIO_LED_setup(int pin);
void myGPIO_LED_write_value(int pin, int value);

//INPUT KNOP

void myGPIO_knop_setup(int pin);
int myGPIO_knop_read_value(int pin);
int myGPIO_knop_edge(int pin);