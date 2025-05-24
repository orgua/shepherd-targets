
	TRX_begin			transmitter=NODE(SHP_ID_PLACEHOLDER), tx_delay=2000, timeout=5000
		// payload content:
		TRX_data_fixed			0x01, 0x02, 0x03, 0x04		// 4 bytes with fixed content
		TRX_data_random			len=4						// 4 bytes with random content
		TRX_data_checkpoint									// checkpoint ~ 12 byte
		TRX_data_fixed			0x05, 0x06, 0x07, 0x08		// some more content
		TRX_data_checkpoint_marker							// checkpoint marker
		// ATTENTION: TRX_data_checkpoint_marker is mandatory and must match
		// TRX_CHECKPOINT_MARKER_POS (also if packet does not contain a checkpoint)
		// Bluetooth 1MBit, ~ 10 Byte overhead
	TRX_end

	// sleep a second
	SLEEP		1000000
