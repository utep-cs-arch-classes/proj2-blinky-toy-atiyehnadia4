	.arch msp430g2553
	.p2align 1,0
	.text

	.global change

change:
	call #change_state
