/* ?ｿｽ?ｿｽ?ｿｽ闕橸ｿｽﾝ関係 */

#include "bootpack.h"
#include <stdio.h>

void init_pic(void)
/* PIC?ｿｽﾌ擾ｿｽ?ｿｽ?ｿｽ?ｿｽ?ｿｽ */
{
	io_out8(PIC0_IMR,  0xff  ); /* ?ｿｽS?ｿｽﾄの奇ｿｽ?ｿｽ闕橸ｿｽﾝゑｿｽ?ｿｽ?ｯ付?ｿｽ?ｿｽ?ｿｽﾈゑｿｽ */
	io_out8(PIC1_IMR,  0xff  ); /* ?ｿｽS?ｿｽﾄの奇ｿｽ?ｿｽ闕橸ｿｽﾝゑｿｽ?ｿｽ?ｯ付?ｿｽ?ｿｽ?ｿｽﾈゑｿｽ */

	io_out8(PIC0_ICW1, 0x11  ); /* ?ｿｽG?ｿｽb?ｿｽW?ｿｽg?ｿｽ?ｿｽ?ｿｽK?ｿｽ?ｿｽ?ｿｽ[?ｿｽh */
	io_out8(PIC0_ICW2, 0x20  ); /* IRQ0-7?ｿｽﾍ、INT20-27?ｿｽﾅ受けゑｿｽ */
	io_out8(PIC0_ICW3, 1 << 2); /* PIC1?ｿｽ?ｿｽIRQ2?ｿｽﾉて接托ｿｽ */
	io_out8(PIC0_ICW4, 0x01  ); /* ?ｿｽm?ｿｽ?ｿｽ?ｿｽo?ｿｽb?ｿｽt?ｿｽ@?ｿｽ?ｿｽ?ｿｽ[?ｿｽh */

	io_out8(PIC1_ICW1, 0x11  ); /* ?ｿｽG?ｿｽb?ｿｽW?ｿｽg?ｿｽ?ｿｽ?ｿｽK?ｿｽ?ｿｽ?ｿｽ[?ｿｽh */
	io_out8(PIC1_ICW2, 0x28  ); /* IRQ8-15?ｿｽﾍ、INT28-2f?ｿｽﾅ受けゑｿｽ */
	io_out8(PIC1_ICW3, 2     ); /* PIC1?ｿｽ?ｿｽIRQ2?ｿｽﾉて接托ｿｽ */
	io_out8(PIC1_ICW4, 0x01  ); /* ?ｿｽm?ｿｽ?ｿｽ?ｿｽo?ｿｽb?ｿｽt?ｿｽ@?ｿｽ?ｿｽ?ｿｽ[?ｿｽh */

	io_out8(PIC0_IMR,  0xfb  ); /* 11111011 PIC1?ｿｽﾈ外?ｿｽﾍ全?ｿｽﾄ禁止 */
	io_out8(PIC1_IMR,  0xff  ); /* 11111111 ?ｿｽS?ｿｽﾄの奇ｿｽ?ｿｽ闕橸ｿｽﾝゑｿｽ?ｿｽ?ｯ付?ｿｽ?ｿｽ?ｿｽﾈゑｿｽ */

	return;
}

#define PORT_KEYDAT		0x0060

struct FIFO8 keyfifo;

void inthandler21(int *esp)
{
	unsigned char data;
	io_out8(PIC0_OCW2, 0x61);	/* IRQ-01?ｿｽ?ｿｽt?ｿｽ?ｿｽ?ｿｽ?ｿｽ?ｿｽ?ｿｽPIC?ｿｽﾉ通知 */
	data = io_in8(PORT_KEYDAT);
	fifo8_put(&keyfifo, data);
	return;
}

struct FIFO8 mousefifo;

void inthandler2c(int *esp)
/* PS/2?ｿｽ}?ｿｽE?ｿｽX?ｿｽ?ｿｽ?ｿｽ?ｿｽﾌ奇ｿｽ?ｿｽ闕橸ｿｽ?ｿｽ */
{
	unsigned char data;
	io_out8(PIC1_OCW2, 0x64);
	io_out8(PIC0_OCW2, 0x62);
	data = io_in8(PORT_KEYDAT);
	fifo8_put(&mousefifo, data);
	return;
}

void inthandler27(int *esp)
{
	io_out8(PIC0_OCW2, 0x67); /* IRQ-07?ｿｽ?ｿｽt?ｿｽ?ｿｽ?ｿｽ?ｿｽ?ｿｽ?ｿｽPIC?ｿｽﾉ通知 */
	return;
}
