void init_port();
void init_lcd();
void clear();
void out_data(char);
void out_control(char);
void register_enable();
void write_lcd();
void enable();
void delay1();

void setup(){
  init_port();
  init_lcd();
  char smiley[8] = {0x00,0x00,0x0A,0x00,0x11,0x0E,0x00,0x00}; //5x8 pattern
  char custom1[8] = {0x1F,0x15,0x15,0x15,0x15,0x15,0x15,0x1F};
  char custom2[8] = {0x11,0x11,0x11,0x0A,0x04,0x04,0x04,0x1F};
  char custom3[8] = {0x0E,0x11,0x1B,0x11,0x15,0x11,0x11,0x0E};
  char telugu1[8] = {0x00,0x1C,0x17,0x1F,0x13,0x1F,0x11,0x1F};

  for(int i=0;i<8;i++){
    write_lcd(smiley[i]);//writing into the CGRAM memory location 0x40
  }

  for(int i=0;i<8;i++){
    write_lcd(custom1[i]);//writing into the CGRAM memory location 0x48;
  }

  for(int i=0;i<8;i++){
    write_lcd(custom2[i]);//writing into the CGRAM memory location 0x56;
  }

  for(int i=0;i<8;i++){
    write_lcd(custom3[i]);//writing into the CGRAM memory location 0x64;
  }

  for(int i=0;i<8;i++){
    write_lcd(telugu1[i]);//writing into the CGRAM memory location 0x64;
  }

  clear();
  for(char i=0;i<5;i++){
    write_lcd(i);  //displaying custom characters on screen using command
    write_lcd(' ');
  }
}

void init_port(){
  char *ddr1 = (char *)0x30;
  *ddr1 = 0x0F;

  char *ddr2 = (char *)0x107;
  *ddr2 = 0xFF;
}

void out_data(char data){
  char *out = (char *)0x108;
  *out = data;
}

void out_control(char data){
  char *out = (char *)0x31;
  *out = data;
}

void clear(){
  out_data(0x38);
  enable();
  out_data(0x01);
  enable();
}

void enable(){
  out_control(0x01);
  delay1();
  out_control(0x00);
  delay1();
}

void register_enable(){
  out_control(0x02);
  delay1();
  out_control(0x03);
  delay1();
  out_control(0x00);
  delay1();
}

void init_lcd(){
  out_data(0x38);
  enable();
  out_data(0x0F);
  enable();
  out_data(0x06);
  enable();
  out_data(0x40); //choosing CGRAM location 0x40
  enable();
}

void write_lcd(char data){
  out_data(data);
  register_enable();
}


void delay1(){
  volatile long i;
  for(i=0;i<1000;i++); 
}

void loop(){

}
