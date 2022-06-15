void init_port();
void lcd_setup();
void outport_reg_en(char);
void outport_data(char);
void lcd_setup();
void lcd_enable();
char scan_keypad();
char inport();



void setup() {
  Serial.begin(9600);
  init_port();
  lcd_setup();
  // write_data('S');
  // write_data('R');
  // write_data('S');
  char x;
  x = scan_keypad();
  while(1){
    while(x==0){
      x = (char) scan_keypad();
      delay1();
      if(x!=0x00){
        write_data(48 + x);
        // Serial.println(x,DEC);
      }
    }
    x=0;
  }
}

char scan_keypad(){
  int row,col,column;
  char data;
  for(row=0;row<4;row++){
    outport_l(1<<row);

    for(col=0;col<4;col++){
      column = inport();

      if(column!=0x00){
        delay1();
        for(col=0;col<4;col++){
          if(column == (1<<col)){
            data = row*4+col+1;
            delay2();
            return data;
          }
        }
      }
    }
  }
  return 0;
}

void outport_l(char data){
  char *out;
  out = 0x10B;
  *out = data;
}

char inport(){
   char *inp,inp_data,x;
   inp = 0x109;
   x = (*inp & 0xF0) >> 4;
   inp_data = x & 0x0F;
   return(inp_data);
}

void init_port(){
  char *out,*en,*keypad;
  out = 0x107;
  *out = 0xFF;

  en = 0x30;
  *en = 0x0F;

  keypad = 0x10A;
  *keypad = 0x0F;
}



void outport_reg_en(char data){
   char *reg_en;
   reg_en = 0x31;
   *reg_en = data;
}

void outport(char data){
  char *out_data;
  out_data = 0x108;
  *out_data = data;
}

void write_data(char write_data){
  outport(write_data);
  outport_reg_en(0x02);
  delay1();
  outport_reg_en(0x03);
  delay1();
  outport_reg_en(0x02);
}

void lcd_setup(){
   outport(0x38);
   lcd_enable();
   outport(0x0F);
   lcd_enable();
   outport(0x06);
   lcd_enable();
}

void lcd_enable(){
  outport_reg_en(0x01);
  delay1();
  outport_reg_en(0x00);
  delay1();
}

void delay1(){
  volatile long i;
  for(i=0;i<1000;i++);
}

void delay2(){
  volatile long i;
  for(i=0;i<100000;i++);
}

void loop() {
  // put your main code here, to run repeatedly:

}
