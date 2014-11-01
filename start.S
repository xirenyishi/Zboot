@****************************
@File:start.S
@
@�������µĿ�ʼ�������������Լ�ȱ�ٵģ�����
@****************************

.text
.global	_start
_start:
	b reset
	ldr pc, undefined_instruction_addr
	ldr pc, software_interrupt_addr
	ldr pc, prefetch_abort_addr
	ldr pc, data_abort_addr
	ldr pc, not_used_addr
	ldr pc, irq_addr
	ldr pc, fiq_addr
	
undefined_instruction_addr: .word undefined_instruction
software_interrupt_addr: .word software_interrupt
prefetch_abort_addr: .word prefetch_abort
data_abort_addr: .word data_abort
not_used_addr: .word not_used
irq_addr: .word irq
fiq_addr: .word fiq

undefined_instruction:
	nop
software_interrupt:
	nop
prefetch_abort:
	nop
data_abort:
	nop
not_used:
	nop
irq:
	nop
fiq:
	nop

reset:
	bl set_svc
	bl set_peri_port
	bl disable_watchdog
	bl disable_interrupt
	bl disable_mmu
	bl init_clock
	bl init_stack
	bl clean_bss
	bl mem_init
	bl copy_to_ram
	bl light_led
	ldr pc, =zboot_main
	
set_peri_port:
	ldr r0, =0x70000000     @���ǻ���ַ��������S3C6410�ֲ���������70000000��P208
	orr r0, r0, #0x13       @����Size�Ĵ�СΪ256M����b10011 = 256MB
	mcr p15,0,r0,c15,c2,4   @����ο�P150ҳд��CP15
	mov pc, lr
	
set_svc:
	mrs r0, cpsr
	bic r0, r0, #0x1f
	orr r0, r0, #0xd3  @�����رտ����жϣ���ͨ�ж�
	msr cpsr, r0 
	mov pc, lr
	
#define WTCON 0x7e004000
disable_watchdog:
	ldr r0, =WTCON
	mov r1, #0x0
	str r1, [r0]
	mov pc, lr
	
disable_interrupt:
	ldr r0, =0x71200014
	mov r1, #0xffffffff
	str r1, [r0]
	
	ldr r0, =0x71300014
	str r1, [r0]
	mov pc, lr
	
disable_mmu:
	mcr p15,0,r0,c7,c7,0
	mrc p15,0,r0,c1,c0,0
	bic r0, r0, #0x00000007
	mcr p15,0,r0,c1,c0,0
	mov pc, lr

#define CLK_DIV0 0x7e00f020	
#define OTHERS 0x7e00f900
#define APLL_CON 0x7e00f00c
#define MPLL_CON 0x7e00f010
#define CLK_SRC 0x7e00f01c
#define DIV_VAL ((0x0<<0)|(0x1<<9)|(0x1<<8)|(0x3<<12))
#define PLL_VAL ((1<<31)|(266<<16)|(3<<8)|(1<<0))	
init_clock:
	ldr r0, =CLK_DIV0   //��Ƶ������
	ldr r1, =DIV_VAL
	str r1, [r0]
	
	ldr r0, =OTHERS    //����Ϊ�첽����ģʽ
	ldr r1, [r0]
	bic r1,r1,#0xc0
	str r1, [r0]
	
	ldr r0, =APLL_CON  //����APLLʱ��
	ldr r1, =PLL_VAL
	str r1, [r0]
	
	ldr r0, =MPLL_CON  //����MPLLʱ��
	ldr r1, =PLL_VAL
	str r1, [r0]
	
	ldr r0, =CLK_SRC   //����APLL��MPLL����������ʱ��
	mov r1, #0x7
	str r1, [r0]
	
	mov pc, lr

 

copy_to_ram:
	ldr r0, =0x0
	ldr r1, =0x50008000
	add r3, r0,#1024*4

copy_loop:
	ldr r2,[r0],#4
	str r2,[r1],#4
	cmp r0, r3
	bne copy_loop	
	
	mov pc, lr
		
init_stack:
	ldr sp, =0x54000000
	mov pc, lr
	
clean_bss:
	ldr r0, =bss_start
	ldr r1, =bss_end
	cmp r0, r1
	moveq pc, lr
clean_loop:
	mov r2, #0x0
	str r2, [r0], #4
	cmp r0, r1
	bne clean_loop
	mov pc, lr
		
#define GPKCON0 0x7f008800
#define GPKDAT 0X7F008808
light_led:
	ldr r0, =GPKCON0
	ldr r1, =0x11110000
	str r1, [r0]
	
	ldr r0, =GPKDAT
	ldr r1, =0xa0    @led1 led3����led2 led4��
	str r1, [r0]
	mov pc, lr