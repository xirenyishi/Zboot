.text
.global mem_init
mem_init:
	@����uboot ELFIN_MEM_SYS_CFG
	@оƬ�ֲ�������MEM_SYS_CFGP
	@��7λ����Ϊ0��Ϊ������
	
	ldr r0, =0x7e001004  @�ڴ��������Ĵ���
	mov r1, #0x4         @�����ֲ��֪��Ҫ�Ƚ�������ģʽP193
	str r1, [r0]
	
	ldr r0, =0x7e001010   @ˢ�¼Ĵ�����ַ
	                         @����ˢ��ʱ��
	str r1, [r0] 
	
	ldr r0, =0x7e001014   @CAS latency�Ĵ���
	mov r1, #0x6          @(3<<1)
	str r1, [r0]
	
	ldr r0, =0x7e001018    @t_DQSS�Ĵ��� 
	mov r1, #0x1           @��ʼֵ
	str r1, [r0]
	
	ldr r0, =0x7e00101c    @T_MRD�Ĵ���
	mov r1, #0x2           @��ʼֵ
	str r1, [r0]
	
	ldr r0, =0x7e001020    @t_RAS�Ĵ���
	
	str r1, [r0]
	
	ldr r0, =0x7e001024   @t_RC�Ĵ���
	
	str r1, [r0]
	
	ldr r0, =0x7e001028   @t_RCD�Ĵ���
	
    	str r1, [r0]
    	
    	ldr r0, =0x7e00102c   @t_RFC�Ĵ���
    	
    	str r1, [r0]
    	
    	ldr r0, =0x7e001030   @t_RP�Ĵ���
    	
    	str r1, [r0]
    	
    	ldr r0, =0x7e001034   @t_rrd�Ĵ���
    	
    	str r1, [r0]
    	
    	ldr r0, =0x7e001038   @t_wr�Ĵ���
   	
 @  	ldr r2, [r0]
    	str r1, [r0]
    	
    	ldr r0, =0x7e00103c   @t_wtr�Ĵ���
    	mov r1, #0x07
    	str r1, [r0]
    	
    	ldr r0, =0x7e001040   @t_xp�Ĵ���
   	mov r1, #0x02
    	str r1, [r0]
    	
    	ldr r0, =0x7e001044   @t_xsr�Ĵ���
    	
    	str r1, [r0]
    	
    	ldr r0, =0x7e001048   @t_esr�Ĵ���
    	
    	str r1, [r0]
    	
    	ldr r0, =0x7e00100c   @�ڴ�������üĴ���
    	ldr r1, =0x00010012   @���ÿ�����
    	str r1, [r0]

    	ldr r0, =0x7e00104c   @32λDRAM���ÿ��ƼĴ���
    	ldr r1, =0x0b45
    	str r1, [r0]

    	ldr r0, =0x7e001200   @Ƭѡ�Ĵ���
    	ldr r1, =0x150f8
    	str r1, [r0]

    	ldr r0, =0x7e001304   @�û����üĴ���
    	mov r1, #0x0
    	str r1, [r0]
    	
    	ldr r0, =0x7e001008    @�ڴ��ʼ������
    	ldr r1, =0x000c0000    @'NOP' memory command
    	str r1, [r0]
    	
    	ldr r1, =0x00000000    @'Prechargeall' memory
    	str r1, [r0]
    	
    	ldr r1, =0x00040000     @'Autorefresh' memory
    	str r1, [r0]
    	
    	ldr r1, =0x00040000     @'Autorefresh' memory
    	str r1, [r0]
    	
    	ldr r1, =0x000a0000     @��uboot��DMC_mDDR_EMR0
    	str r1, [r0]

    	ldr r1, =0x00080032     @��uboot��DMC_mDDR_MR0
    	str r1, [r0]

	ldr r0, =0x7e001004    @����DRAM����������Ready
    	mov r1, #0x0
    	str r1, [r0]
    	
    	
check_dmc1_ready:              @���memory״̬ΪReady
	ldr r0, =0x7e001000 
	ldr r1, [r0]
	mov r2, #0x3
	and r1, r1, r2
	cmp r1, #0x1
	bne check_dmc1_ready
	nop
	mov pc, lr
    	
	
	