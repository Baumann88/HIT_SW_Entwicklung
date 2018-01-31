CFLAGS    = -O2 -Wall -Wno-parentheses \
	    -fno-strict-aliasing \
	    -DPF_CAN=29 \
	    -DAF_CAN=PF_CAN\
	    -Bstatic
	 

CC	= ${CROSS_COMPILE}gcc ${CFLAGS}
GCC     = ${CROSS_COMPILE}g++ 


MAKEFLAGS = -k

PROGRAMS = Beeper_demo_application Motion_demo_application Temperature_demo_application\
	LED_demo_application CANopen_demo_application IN_OUT_demo_application CAN_demo_application SMS_demo_application
	   
all: ${PROGRAMS}

clean:
	rm -f $(PROGRAMS) *.o

install:
	cp -f $(PROGRAMS) ../result

distclean:
	rm -f $(PROGRAMS) *.o *~

Beeper_demo_application:	beeper.c
		${CC} beeper.c -o Beeper_demo_application
Motion_demo_application:	motion.c
		${CC} motion.c -o Motion_demo_application
Temperature_demo_application:	temperature.c
		${CC} temperature.c -o Temperature_demo_application
LED_demo_application:		LED.c
		${CC} LED.c -o LED_demo_application
CANopen_demo_application:	CANopen.c
		${CC}  CANopen.c -o CANopen_demo_application -lcol2_ppc -lyiox_ppc -lydios_ppc
IN_OUT_demo_application:        in_out.c
		${CC}  in_out.c -o IN_OUT_demo_application
CAN_demo_application:           CAN.c
		${CC}  CAN.c -o CAN_demo_application
SMS_demo_application:           SMSHandler.c
		${CC}  SMSHandler.c -o SMS_demo_application	
		
