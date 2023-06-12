//**************************************************************************************************
//**************************************************************************************************

// This file contains the basic FlockLab setup.
// It is used in config.h (i.e., C code) as well as flocklab_config.xml (i.e., XML config file).
// The latter defines _XML_, which can be used for format-specific handling.

#ifdef _XML_
  #define comma
#else
  #define comma ,
#endif

#define FLOCKLAB_TEST_NAME TrafficBench
#define FLOCKLAB_TEST_DESCRIPTION                                                                  \
  tutorial schedule;                                                                               \
  channel   = FLOCKLAB_RADIO_CHANNEL;                                                              \
  nodes     = FLOCKLAB_OBSERVERS;                                                                  \
  root node = FLOCKLAB_ROOT_NODE

#define FLOCKLAB_IMAGE_NAME        FLOCKLAB_TEST_NAME
#define FLOCKLAB_IMAGE_DESCRIPTION FLOCKLAB_TEST_DESCRIPTION

#define FLOCKLAB_TEST_DURATION     120 // in seconds

#define FLOCKLAB_RADIO_CHANNEL     41
#define FLOCKLAB_ROOT_NODE         1

#define FLOCKLAB_UART_BAUDRATE     230400
// 460800 causes problems at some nodes/observers (e.g. 1, 2)
// increasing drive strength (S0S1 -> H0H1) causes even more problems

// observers to be used in the test
// say ALL if you want to use all available observers (instead of listing all IDs)
#if 1
  #define FLOCKLAB_OBSERVERS 1 comma 2 comma 8 comma 27
#else
  #define FLOCKLAB_OBSERVERS                                                                       \
    1 comma 2 comma 3 comma 4 comma 5 comma 6 comma 7 comma 8 comma 9 comma 10 comma 11 comma 12 comma 13 comma 16 comma 19 comma 20 comma 21 comma 22 comma 23 comma 24 comma 26 comma 27 comma 29 comma 31
#endif

// optional user-defined node IDs. use observer IDs if not specified.
// num entries must match FLOCKLAB_OBSERVERS
#if 0
  #define FLOCKLAB_NODES                                                                           \
    1 comma 2 comma 3 comma 4 comma 6 comma 7 comma 8 comma 10 comma 11 comma 13 comma 14 comma 15 comma 16 comma 17 comma 18 comma 19 comma 20 comma 22 comma 23 comma 24 comma 25 comma 26 comma 27 comma 28 comma 31 comma 32 comma 33 comma /*	200		comma	\
	201		comma	\
	202 	comma	\
	204
*/
#endif

//**************************************************************************************************
//**************************************************************************************************
