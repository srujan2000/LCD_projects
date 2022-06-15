void init();
void delay1();
char scan_keypad();
char inp_col();
void init_lcd();
void write_data(char);
void lcd_control();
void outport_keypad(char);
void outport_rs_end(char);
void outport_lcd_data(char);
void first_num(char);
void second_num(char);
void second_line();
void setup_numbers();
void addition(char[],char[],int);
void subraction(char [],char[],int);
void multiplication(char [],char [],int);
void division(char [],char [], int len);
char *div_subraction(char [],char[],int len);
void operation(char[],char[],int);
void clear_screen();
int find_len(char[]);
void quotient(int);
void reset();

char n1[15],n2[15];
char total[15],sub[15],mul[15],div1[15],div2[15],copy[15],k,l,oper;

void first_num(char c){
    n1[k] = c;
    write_data(n1[k]);
}

void second_num(char c){
    n2[l] = c;
    write_data(n2[l]);
}

void second_line(){
   outport_lcd_data(0x80);
   lcd_control();
   outport_lcd_data(0xC0);
   lcd_control();
   delay1();
}

char *div_subraction(char *s1,char *s2,int len){
  char difference,k=0;

  for(int i=len-1;i>=0;i--){
    difference = s1[i]-s2[i];
    if(i==0 && (difference<0)){
      return 0;
    }
    
    if(difference<0){
        div1[k] = ((s1[i]+10)-s2[i])+'0';
        s1[i-1] = s1[i-1]-1;
    }else{
        div1[k] = difference+'0';
    }
    k++;
  }

  char m=0;
  for(int j=len-1;j>=0;j--){
      div2[m] = div1[j];
      m++;
  }
  return div2;
}

int find_len(char *str)
{
    int c = 0;
    while (str[c] != '\0')
    {
        c++;
    }
    return c;
}

void addition(char *s1,char *s2,int len){
  char sum,m=0;
  for(int i=len-1;i>=0;i--){
    sum = (s1[i]-'0')+(s2[i]-'0');
    if(sum>9){
      total[m] = total[m] + sum%10 +'0';
      total[m+1] = total[m+1] + sum/10;
    }else{
      total[m] = total[m] + sum+'0';
    }
    m++;
  }
  if(total[m]>0){
     total[m] = total[m]+'0';
     len = m;
  }else{
    len = m-1;
  }
  
  // write_data(' ');
  second_line();
  for(int i=len;i>=0;i--){
    write_data(total[i]);
    delay1();
  }
}

void subraction(char *s1,char *s2,int len){
      char diff,m=0;
      for(int i=len-1;i>=0;i--){
        diff = s1[i] - s2[i];
        if(diff<0){
          sub[m] = ((s1[i]+10)-s2[i])+'0';
          s1[i-1] = s1[i-1]-1;
        }else{
          sub[m] = diff+'0';
        }
        m++;
      }

     char x=0;
    //  write_data(' ');
     second_line();
     for(int j=m-1;j>=0;j--){
      //  Serial.println(j);
       if(sub[j]!='0'){
        x=1;
       }
       if(x){
         write_data(sub[j]);
         delay1();
       }
     }
     if(x==0){
       write_data('0');
     }
}

void multiplication(char *s1,char *s2,int len){
    char product,m;
    for(int i=len-1;i>=0;i--){
      m= (len-1)-i;
      for(int j=len-1;j>=0;j--){
        product = (s1[i]-'0')*(s2[j]-'0');
        if(product>9){
          mul[m] = mul[m]+product%10;
          mul[m+1] = mul[m+1]+product/10;
          if(mul[m]>9){
            int g = mul[m];
            mul[m+1] = mul[m+1]+g/10;
            mul[m] = g%10;
          }
        }else{
           mul[m] = mul[m]+product;
           if(mul[m]>9){
            int g = mul[m];
            mul[m+1] = mul[m+1]+g/10;
            mul[m] = g%10;
          }
        }
        m++;
      }
    }

    if(mul[m]!=0){
      len = m;
    }else{
      len = m-1;
    }
    
    // write_data(' ');
    second_line();

    char x=0;
    for(int j=len;j>=0;j--){
      if(mul[j]!=0){
        x=1;
      }
      if(x){
        write_data(mul[j]+'0');
        delay1();
      }
    }
    if(x==0){
      write_data('0');
    }
}

void quotient(int n){
   int number=n,i=0;
   char quo[10];
   while(number!=0){
      quo[i] = (number%10)+'0';
      i++;
      number = number/10; 
   }

   for(int j=i-1;j>=0;j--){
     write_data(quo[j]);
   }
}

void division(char *s1,char *s2, int len){
      char *s,l,*r;
      int count=0;
      s = div_subraction(s1,s2,len);
      while(s){
        count++;
        l = find_len(s);
        for(int i=0;i<l;i++){
          copy[i] = s[i];
        }
        r = s;
        s = div_subraction(copy,s2,len);
      }
      
      write_data(' ');
      second_line();
      quotient(count);
      write_data(' ');

      char x=0;
      for(int i=0;i<len;i++){
        if(r[i]!='0'){
          x=1;
        }
        if(x){
          write_data(r[i]);
        }
      }
      
      if(x==0){
        write_data('0');
      }

}

void operation(char *s1,char *s2,int len){
   if (oper == '+')
    {
        addition(s1, s2, len);
    }
    else if (oper == '-')
    {
        subraction(s1, s2, len);
    }
    else if (oper == '*')
    {
        multiplication(s1, s2, len);
    }
    else if (oper == '/')
    {
      division(s1,s2,len);
    }
}

void clear_screen(){
  outport_lcd_data(0x38);
  lcd_control();
  outport_lcd_data(0x01);
  lcd_control();
}

void setup_numbers(){
    char new_num[10];
    if(k>l){
       int diff = k-l,i;
       for (i = 0; i < diff; i++)
        {
            new_num[i] = '0';
        }
        for(int j=0;j<l;j++){
            new_num[i] = n2[j];
            i++;
        }
        operation(n1,new_num,k);
        // if(oper=='+'){
        //      addition(n1,new_num,k);
        // }else if(oper == '-'){
        //     subraction(n1,new_num,k);
        // }else if(oper == '*'){

        // }else if(oper == '/'){

        // }
    }else if(k<l){
      int diff = l-k,i;
       for (i = 0; i < diff; i++)
        {
            new_num[i] = '0';
        }
        for(int j=0;j<k;j++){
            new_num[i] = n1[j];
            i++;
        }
        operation(n2,new_num,l);
        // if(oper=='+'){
        //     addition(n2,new_num,l);
        // }else if(oper == '*'){

        // }else if(oper == '/'){
          
        // }
    }else{
        operation(n1,n2,k);
        //  if(oper=='+'){
        //   subraction(n1,n2,k);
        // }else if(oper == '-'){
        //     subraction(n1,n2,k);
        // }else if(oper == '*'){

        // }else if(oper == '/'){
          
        // }
    }
}

void reset(){
  for(int i=0;i<16;i++){
    // n1[i]='0';
    // n2[i]='0';
    total[i]=0;
    sub[i]=0;
    mul[i]=0;
    div1[i]=0;
    div2[i]=0;
    copy[i]=0;
  }
  k=0,l=0;
}

void setup() {
  reset();
  Serial.begin(9600);
  char keypad[16] = {'1','2','3','+','4','5','6','-','7','8','9','*','C','0','=','/'};
  init_lcd();
  char x=0,y=1;
  while(1){

    while(x==0){
      x = scan_keypad();

      if(x==13){
        clear_screen();
        // write_data(k+'0');
        // write_data(' ');
        // write_data(l+'0');
        x=0;
        y=1;
        continue;
      }

      if(x==15){
        setup_numbers();
        x=0;
        // write_data(' ');
        // write_data(k+'0');
        // write_data(' ');
        // write_data(l+'0');
        reset();
        continue;
      }

      delay1();
      if(x){
      char z = keypad[x-1];


      if(z=='+' || z=='-'||z=='*'||z=='/'){
        y=0;
        // Serial.println("hello");
        oper = z;
        write_data(oper);
        continue;
      }

      if(y==1){
        first_num(z);
        // write_data(k+'0');
        k++;
      }
      
      else{
        second_num(z);
        // write_data(l+'0');
        l++;
      }
      }
    }
    x =0;
  }
}

void init(){
  char *ddr_key,*ddr_rs_en,*ddr_data;

  ddr_key = 0x30;
  *ddr_key = 0x0F;

  ddr_rs_en = 0x107;
  *ddr_rs_en =0x0F;

  ddr_data = 0x10A;
  *ddr_data = 0xFF;
}

void init_lcd(){
    outport_lcd_data(0x38);
    lcd_control();
    outport_lcd_data(0x0F);
    lcd_control();
    outport_lcd_data(0x01);
    lcd_control();
    outport_lcd_data(0x06);
    lcd_control();
}

void write_data(char data){
   outport_lcd_data(data);
   outport_rs_en(0x02);
   delay1();
   outport_rs_en(0x03);
   delay1();
   outport_rs_en(0x02);
   delay1();
}

void outport_keypad(char data){
  char *out;
  out = 0x31;
  *out = data;
}

void outport_rs_en(char data){
  char *out;
  out = 0x108;
  *out = data;
}

void outport_lcd_data(char data){
  char *out;
  out = 0x10B;
  *out = data;
}

void lcd_control(){
   outport_rs_en(0x01);
   delay1();
   outport_rs_en(0x00);
   delay1();
}


char scan_keypad(){
   char row,column,data,col_no;

   for(row=0;row<4;row++){
    outport_keypad(1<<row);

    for(column=0;column<4;column++){
      col_no = inp_col(); 

      delay1();
      if(col_no!=0x00){
        delay1();

        for(char col=0;col<4;col++){
          if(col_no == (1<<col)){
             data = row*4+col+1;
             delay1();
             return data;
          }
        }
      }
    }
   }
   return 0;
}

char inp_col(){
    char *inp,inp_out,s;
    inp = 0x2F;
    s = (*inp & 0xF0)>>4;
    inp_out = s & 0x0F;
    return (inp_out);
}

void delay1(){
  volatile long i;
  for(i=0;i<10000;i++);
}

void loop() {
  // put your main code here, to run repeatedly:

}
