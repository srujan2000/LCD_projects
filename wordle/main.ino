#include "word.h"

char keys[16] = {'A','B','C','D','E','F','G','H','I','J','M','N','O','P','S','='};
char ans[5];
char *wor = wordle();
char count =0;
void setup() {
  init_port();
  init_lcd();

  char x = 0;
  char w[] = " !!! Wordle !!!";

  for(char i=0;i<16;i++){
    write_lcd(w[i]);
  }
  
  second_line();
  keypad();
}

void init_port(){
  char *ddr1 = (char*)0x30;
  *ddr1 = 0x0F;

  char *ddr2 = (char*)0x107;
  *ddr2 = 0x0F;

  char *ddr3 = (char*)0x10A;
  *ddr3 = 0xFF;
}

void outport_row(char data){
  char *out = (char*)0x31;
  *out = data;
}

void outport_rs_en(char data){
  char *out = (char*)0x108;
  *out = data;
}

void outport_data(char data){
  char *out = (char*)0x10B;
  *out = data;
}

char scan_keypad(){
  char row,col,columns,data;

  for(row=0;row<4;row++){
    outport_row(1<<row);

    for(columns=0;columns<4;columns++){
      col = inport();

      if(col!=0x00){
        delay1();

        for(char column=0;column<4;column++){
          if(col==(1<<column)){
            data = row*4+column+1;
            delay1();
            return data;
          }
        }
      }
    }
  }
  return 0;
}


void keypad(){
   Serial.begin(9600);
   char x=0,c=0;
   while(count<5){
    while(x==0 && count<5){
      x = scan_keypad();
      delay1();
    }
    
    if(keys[x-1]=='='){
      count++;
      check();
    }else{
      write_lcd(keys[x-1]);
      ans[c] = keys[x-1];
      c++;
    }
    x=0;
    delay1();
  }
}

void check(){
  char x=1;
  for(int i=0;i<5;i++){
    if(ans[i]!=wor[i]){
      x=0;
    }
  }
  
  clear_screen();
  if(x){
     won();
  }else{
    try_again();
  }
}

void won(){
  // char str[] = "  !!! WON !!!";
  // for(int i=0;i<16;i++){
  //   write_lcd(str[i]);
  // }
  if(count==1){
    char str[] = " !!! GENIUS !!!";
    for(int i=0;i<16;i++){
    write_lcd(str[i]);
  }
  }else if(count==2){
    char str[] = "!! EXCELLENT !!";
    for(int i=0;i<16;i++){
    write_lcd(str[i]);
  }
  }else if(count==3){
    char str[] = "!! IMPRESSIVE !!";
    for(int i=0;i<17;i++){
    write_lcd(str[i]);
  }
  }else if(count==4){
    char str[] = "!!! SPLENDID !!!";
    for(int i=0;i<16;i++){
    write_lcd(str[i]);
  }
  }else if(count==5){
    char str[] = " !!! GREAT !!!";
    for(int i=0;i<16;i++){
    write_lcd(str[i]);
  }
  }
}

void try_again(){
  char str[] = "Tries left: ";
  char tries = 5-count;
  if(tries){
  for(int i=0;i<12;i++){
    write_lcd(str[i]);
  }
  write_lcd(tries+'0');
  second_line();
  keypad();
  }else{
    char str[] = "   Game Over";
    for(int i=0;i<16;i++){
      write_lcd(str[i]);
  }
  }
}


char inport(){
  char *inp,r,s;
  inp = 0x2F;
  r = (*inp & 0xF0) >>4;
  s = r & 0x0F;
  return s;
}

void init_lcd(){
  outport_data(0x38);
  enable();
  outport_data(0x0F);
  enable();
  // outport_data(0x06);
  // enable();
}

void enable(){
  outport_rs_en(0x01);
  delay1();
  outport_rs_en(0x00);
  delay1();
}

void write_lcd(char data){
  outport_data(data);
  enable_register();
}

void enable_register(){
  outport_rs_en(0x02);
  delay1();
  outport_rs_en(0x03);
  delay1();
}

void second_line(){
  outport_data(0x38);
  enable();
  outport_data(0xC4);
  enable();
}

void clear_screen(){
  outport_data(0x38);
  enable();
  outport_data(0x01);
  enable();
}

void inc_cursor(){
  outport_data(0x38);
  enable();
  outport_data(0x06);
  enable();
}

void dec_cursor(){
  outport_data(0x38);
  enable();
  outport_data(0x04);
  enable();
}

void delay1(){
  volatile long i;
  for(i=0;i<10000;i++);
}

void loop() {
  // put your main code here, to run repeatedly:

}
