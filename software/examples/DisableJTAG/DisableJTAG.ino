
void disable_jtag(void)
{
  __asm__ __volatile__ ( \ 
			 "in __tmp_reg__,__SREG__" "\n\t" \ 
			 "cli" "\n\t"				\
			 "out %1, %0" "\n\t"			\
			 "out __SREG__, __tmp_reg__" "\n\t"\ 
			 "out %1, %0" "\n\t"		\
			 : /* no outputs */		\
			 : "r" ((uint8_t)(1<<JTD)), \ 
			   "M" (_SFR_IO_ADDR(MCUCR)) \ 
			 : "r0");		\
}
  
void enable_jtag(void)
{
  __asm__ __volatile__ ( \ 
			 "in __tmp_reg__,__SREG__" "\n\t" \ 
			 "cli" "\n\t" \ 
			 "out %1, %0" "\n\t" \ 
			 "out __SREG__, __tmp_reg__" "\n\t"\ 
			 "out %1, %0" "\n\t" \ 
			 : /* no outputs */ \ 
			 : "r" ((uint8_t)(0)), \ 
			   "M" (_SFR_IO_ADDR(MCUCR)) \ 
			 : "r0");
}

void setup(void)
{
  Serial.begin(9600);
}


void loop(void)
{
  delay(2000);
  Serial.print("Disabling JTAG, ");
  disable_jtag();
  Serial.print("MCUCR: 0x"); Serial.println(MCUCR, HEX);

  delay(2000);
  Serial.print("Enabling JTAG, ");
  enable_jtag();
  Serial.print("MCUCR: 0x"); Serial.println(MCUCR, HEX);
}
