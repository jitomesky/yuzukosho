#include "rpi_lib/rpi.h"
#include <stdio.h>
#include <stdint.h>

typedef struct {
	// do not change define order

	// // monitor
	// uint32_t sp_mon;
	// uint32_t lr_mon;

	// // hypervisor
	// uint32_t sp_hyp;
	// uint32_t elr_hyp;

	// IRQ
	uint32_t sp_irq;
	uint32_t lr_irq;
	// SVC
	uint32_t sp_svc;
	uint32_t lr_svc;
	// Abort
	uint32_t sp_abt;
	uint32_t lr_abt;
	// Undefined
	uint32_t sp_und;
	uint32_t lr_und;

	// FIQ
	uint32_t r8_fiq;
	uint32_t r9_fiq;
	uint32_t r10_fiq;
	uint32_t r11_fiq;
	uint32_t r12_fiq;
	uint32_t sp_fiq;
	uint32_t lr_fiq;

	// User
	uint32_t r8_usr;
	uint32_t r9_usr;
	uint32_t r10_usr;
	uint32_t r11_usr;
	uint32_t r12_usr;
	uint32_t sp_usr;
	uint32_t lr_usr;

	uint32_t r0_usr;
	uint32_t r1_usr;
	uint32_t r2_usr;
	uint32_t r3_usr;
	uint32_t r4_usr;
	uint32_t r5_usr;
	uint32_t r6_usr;
	uint32_t r7_usr;

} BANKED_REG;


void swi_hello(uint32_t *reg){
	int i;
	uint8_t *r;
	BANKED_REG *br = (BANKED_REG *)reg;

	printf("swi called\n");
	printf("swi_hello: cpsr = 0x%08x\n",getmode());

	// // Hypervisor
	// printf("elr_hyp: 0x%08x\n", br->elr_hyp);
	// printf("sp_hyp: 0x%08x\n", br->sp_hyp);

	// // Monitor
	// printf("lr_mon: 0x%08x\n", br->lr_mon);
	// printf("sp_mon: 0x%08x\n", br->sp_mon);

	// Undefined
	printf("lr_und: 0x%08x\n", br->lr_und);
	printf("sp_und: 0x%08x\n", br->sp_und);
	printf("\n");

	// Abort
	printf("lr_abt: 0x%08x\n", br->lr_abt);
	printf("sp_abt: 0x%08x\n", br->sp_abt);
	printf("\n");

	// SVC
	printf("lr_svc: 0x%08x\n", br->lr_svc);
	printf("sp_svc: 0x%08x\n", br->sp_svc);
	printf("\n");

	// IRQ
	printf("lr_irq: 0x%08x\n", br->lr_irq);
	printf("sp_irq: 0x%08x\n", br->sp_irq);
	printf("\n");

	// FIQ
	printf("lr_fiq: 0x%08x\n", br->lr_fiq);
	printf("sp_fiq: 0x%08x\n", br->sp_fiq);
	printf("r12_fiq: 0x%08x\n", br->r12_fiq);
	printf("r11_fiq: 0x%08x\n", br->r11_fiq);
	printf("r10_fiq: 0x%08x\n", br->r10_fiq);
	printf("r9_fiq: 0x%08x\n", br->r9_fiq);
	printf("r8_fiq: 0x%08x\n", br->r8_fiq);
	printf("\n");

	// User
	printf("lr_usr: 0x%08x\n", br->lr_usr);
	printf("sp_usr: 0x%08x\n", br->sp_usr);
	printf("r12_usr: 0x%08x\n", br->r12_usr);
	printf("r11_usr: 0x%08x\n", br->r11_usr);
	printf("r10_usr: 0x%08x\n", br->r10_usr);
	printf("r9_usr: 0x%08x\n", br->r9_usr);
	printf("r8_usr: 0x%08x\n", br->r8_usr);
	printf("r7_usr: 0x%08x\n", br->r7_usr);
	printf("r6_usr: 0x%08x\n", br->r6_usr);
	printf("r5_usr: 0x%08x\n", br->r5_usr);
	printf("r4_usr: 0x%08x\n", br->r4_usr);
	printf("r3_usr: 0x%08x\n", br->r3_usr);
	printf("r2_usr: 0x%08x\n", br->r2_usr);
	printf("r1_usr: 0x%08x\n", br->r1_usr);
	printf("r0_usr: 0x%08x\n", br->r0_usr);

	// while(1);
}

int main(void){
	int regdump = 1;
	rpi_init();

	// JTAG用設定
	// 3.3V			: ARM_VREF 
	// GPIO22 (ALT4): ARM_TRST
	// GPIO4  (ALT5): ARM_TDI
	// GPIO27 (ALT4): ARM_TMS
	// GPIO25 (ALT4): ARM_TCK
	// GPIO24 (ALT4): ARM_TDO
	// GND			: ARM_GND
	pinMode(22, ALT4);
	pinMode(4, ALT5);
	pinMode(27, ALT4);
	pinMode(25, ALT4);
	pinMode(24, ALT4);

	// LED init
	pinMode(47,OUTPUT);

	printf("main: cpsr = %08x\n",getmode());

	while(1){
		digitalWrite(47, HIGH);
		delay(1000);
		digitalWrite(47, LOW);
		delay(1000);

		if(regdump){
			regdump = 0;
			_swi_caller(10);
		}
	}

	return 0;
}
