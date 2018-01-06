SECTIONS {
	/* The kernel starts at 1M */
	. = 0x100000;

	_start = .;

	.text : {
		*(.text)
	}

	.data : {
		*(.data)

		_edata  =  .;
	}

	.bss : {
		*(.bss)
		__bss_end = .;
	}

	_end = .; /* same as __bss_end (cf `man end`) */

	/* Beginning of kernel memory heap */
	mem_heap = _end;

	/* End of kernel memory heap */
	mem_heap_end = 0x1000000;
}
