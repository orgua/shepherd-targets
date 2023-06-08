//**************************************************************************************************
//**************************************************************************************************

// helper macros
#define BUILD_CONFIG_Release_FlockLab	1
#define BUILD_CONFIG_IS(x)				(BUILD_CONFIG == BUILD_CONFIG_ ## x)

//**************************************************************************************************
// GPI configuration

#if BUILD_CONFIG_IS(Release_FlockLab)
	#include "config_flocklab.h"
	#define GPI_ARCH_PLATFORM			(GPI_ARCH_BOARD_nRF_PCA10059_FLOCKLAB | GPI_ARCH_CRT_SEGGER2)
	#define GPI_STDOUT_UART_BAUDRATE	FLOCKLAB_UART_BAUDRATE
#else
	#define GPI_ARCH_PLATFORM			(GPI_ARCH_BOARD_nRF_PCA10056 | GPI_ARCH_CRT_SEGGER2)
	#define GPI_STDOUT_UART_BAUDRATE	230400
	#define GPI_ARM_NRF_STDOUT_UART_FLOWCONTROL_MODE	3
	// ATTENTION: 460800 is not totally safe even with flow control
	// (I guess that the DK's interface MCU deactivates CTS too late
	// (not enough buffer space left for data transmitted in between))
#endif

#define GPI_ARM_INTLOCK_PRIORITY			1
#define GPI_ARM_NRF_FAST_CLOCK_TIMER		4

// enable asynchronous stdout with interrupt-driven UART routines
// This increases performance because preparation of (next) transmit data gets parallelized with
// (currently) running UART transmission.
#define GPI_STDOUT_INTERRUPT_ENABLED			1
#define GPI_ARM_NRF_STDIO_INTERRUPT_PRIORITY	4
#define GPI_ARM_NRF_STDOUT_BUFFER_NUM_SLOTS		32
#define GPI_ARM_NRF_STDOUT_BUFFER_SLOT_SIZE		16

// use GPI_TRACE without automatic flushing (i.e. flush manually)
// This is needed because the standard flush routine does not support nested calls,
// which is critical when using preemptive multithreading (as we do). The simple solution
// is to perform flushing in the scheduler's idle loop.
// We use a relatively large trace buffer size to avoid losing messages in high-load situations.
#define GPI_TRACE_MODE						(GPI_TRACE_MODE_TRACE | GPI_TRACE_MODE_FLUSH_NOAUTO)
#define GPI_TRACE_BUFFER_NUM_ENTRIES		512 //128	// 64 bytes each (GPI_TRACE_BUFFER_ENTRY_SIZE)

// limit GPI_TRACE_FLUSH_MAX_ENTRIES_PER_CALL and consequently the runtime of GPI_TRACE_FLUSH()
// (see GPI_TRACE_FLUSH_MAX_ENTRIES_PER_CALL for details)
// ATTENTION: long-running GPI_TRACE_FLUSH() calls can lead to TRX message losses in high-load
// situations (due to intermediate Rx buffer overflow)
#define GPI_TRACE_FLUSH_MAX_ENTRIES_PER_CALL	3

//#if BUILD_CONFIG_IS(Release_FlockLab)
	#define GPI_TRACE_TYPE_FORMAT			1
//#else
	//#define GPI_TRACE_TYPE_FORMAT			3
//#endif

#define GPI_TRACE_BASE_SELECTION			GPI_TRACE_LOG_STANDARD
//#define GPI_TRACE_USER_SELECTION			(GPI_TRACE_MSG_TYPE_ERROR | GPI_TRACE_MSG_TYPE_WARNING | GPI_TRACE_MSG_TYPE_INFO)
#define GPI_TRACE_USER_SELECTION			GPI_TRACE_LOG_USER

#define VA_SIZE_GRANULARITY					4

#define GPI_RESOURCE_CHECK					1

//**************************************************************************************************
// application settings

#if BUILD_CONFIG_IS(Release_FlockLab)
	#define BLE_RADIO_CHANNEL			(FLOCKLAB_RADIO_CHANNEL)
	#define ROOT_NODE_ID				FLOCKLAB_ROOT_NODE
#else
	#define BLE_RADIO_CHANNEL			(-1)
	#define ROOT_NODE_ID				1
#endif

#define RX_QUEUE_SIZE					128 //256		// num. entries 
#define RSSI_SPACE_SIZE					(128 * 1024)	// bytes
#define LOG_BUFFER_SIZE					1024			// bytes

#define	DEFLATE_C2_DIFFERENTIAL_HASH_CHAIN_LENGTH	2048

//**************************************************************************************************
//**************************************************************************************************
