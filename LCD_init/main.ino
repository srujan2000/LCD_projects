void init_port(void);
void outport(char);
void outportc(char);
void delay1(int);
void init_lcd(void);
void write_data(char);
void lcd_control_write(void);

void setup() {
  init_port();
  init_lcd();
  char y= 48;
  for(char i=0;i<10;i++){
    write_data('A');
    delay1(1);
  }
}

void init_port()
{
  char *portb_dir  = (char *)0x107;
  char *portc_dir  = (char *)0x30;
  *portb_dir = 0xFF;
  *portc_dir = 0x0F;
}

void outport( char out_data)
{
  char *portb_data = (char *)0x108;  
  *portb_data = out_data;
}

void outportc( char out_data)
{
  char *portc_data = (char *)0x31; 
  *portc_data = out_data;
}

void init_lcd( void )
{
  outport(0x38);   // 8bit 2 line
  lcd_control_write();
  outport(0x0F);   // Display on Cursor Blinking
  lcd_control_write();
  outport(0x01);   // Clear Display
  lcd_control_write();
  outport(0x06);   // Auto Increment
  lcd_control_write();
}

void write_data(char wr_data)
{
  outport(wr_data);
  outportc(0x04);
  delay1(1);
  outportc(0x05);
  delay1(1);
  outportc(0x04);
  delay1(1);
}

void lcd_control_write( void )
{
  outportc(0x01);
  delay1(1);
  outportc(0x00);
  delay1(1);
}

void delay1(int count)
{
  volatile long i;
  while(count)
  {
    for(i=0; i<1000; i++);
    count--;
  }
}

void loop() {

}
