#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<avr/eeprom.h>
void LCD_Init(void);
void dt(char data);/*lcd*/
void loc(char com);
void str(char *str);
void num(int ch);
unsigned char keypad();
void ini();   /*rfid*/
void send(char send);
char rec(void);

void main() 

{DDRB=0xf0;
DDRA=0xff;
DDRC=0xff;
DDRD=0xff;
PORTB=0B11111111;


int x,X,Y,y,z,i,j,k,p;                                    /*rfid part */
char a[1][12],b[20][12]={{0,0,0,0},
               {1,1,1,1,1,1,1,1,1,1,1,1},
               {2,2,2,2,2,2,2,2,2,2,2,2}},
	 d[4],c[4]={0,0,0,0},/*password*/
	 e[1][4],f[1][4],g[20][4]={{0,0,0,0},/*money*/
	                   {0,1,0,0},
					   {0,2,0,0}};
						   
						   

LCD_Init();
while(1)
{while(1)
{
/*for(i=0;i<=3;i++)             
 {for(j=0;j<=3;j++)
  {eeprom_write_byte((i*4)+j+240,g[i][j]);
}}*/
	
loc(0x01);
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0x94);
str("Customer Service");
loc(0xd4);
str("Admin login");
_delay_ms(100);

int q;
q=keypad();
if(q==22)
      {loc(0x01);
      _delay_ms(10);
	  loc(0x83);
      str("Down Town Cafe");
       loc(0x94);
       str("Welcome Sir");
       loc(0xd4);
       str("Enter Password:-");
	   
    for(i=0;i<=3;i++)
     {x=keypad();
      d[i]=x;
	  str("*");
     }
	 _delay_ms(30);
z=0;
    for(j=0;j<=3;j++)
      {if(c[j]!=d[j])
	   {z=1;
	   break;
	   }
      }
if(z==1)
  {loc(0x01);
  _delay_ms(10);
  loc(0x83);
  str("Down Town Cafe");
  loc(0x94);
  str("Incorrect Password");
  _delay_ms(200);
  break;
  }
 
  else if(z==0)
  {while(1)
    {while(1)
  {loc(0x01);
  _delay_ms(10);
  loc(0x83);
  str("Down Town Cafe");
  loc(0x94);
  str("Add Money");
  loc(0xd4);
  str("Add New card");
  
  X=keypad();

if(X==11)
{loc(0x01);/*to read card*/
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0x94);
str("Insert Card");

for(i=0;i<=3;i++)                
{
x=keypad();
a[0][i]=x;
str(".");
_delay_ms(10);
}


for(i=0;i<=20;i++)              /*match the card in data*/
 {y=0;
  for(j=0;j<=3;j++)
   {int l=eeprom_read_byte((i*12)+j);
if(l!=a[0][j])
	 {y=1;
	 break;
	 }
	}
	if(y!=1)
	 {break;}
  }

if(y==0)
{loc(0x01);
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0x94);
str("Enter Amount");
loc(0xc4);
str("*upto 5000*");
loc(0xd4);
str("Add");

int I,K;
for(I=0,K=0xa1;I<=4&&K<=0xa6;I++,K++)
{Y=keypad();
 if(Y!=22)
  {e[0][I]=Y;
   loc(K);
   num(Y);	
	}
 else if(Y==22&&i==0)		
  {e[0][0]=0;}
 else if(Y==22)
  {loc(K);
   str("/");
   loc(++K);
   str("-");
   _delay_ms(100);
   loc(0x01);
   _delay_ms(10);
   loc(0x83);
   str("Down Town Cafe");
   loc(0xd4);
   str("processing...");
   _delay_ms(200);

int w,r,t,m;
if(I==4){w=1000;}
else if(I==3){w=100;}
else if(I==2){w=10;}
else if(I==1){w=1;}
	
	for(j=0;j<=3;j++)
	 {f[0][j]=eeprom_read_byte(240+(i*4)+j);
	 }
	
	r=w*e[0][0]+w/10*e[0][1]+w/100*e[0][2]+w/1000*e[0][3];
	t=1000*f[0][0]+100*f[0][1]+10*f[0][2]+1*f[0][3];
	
if(r<=5000)
{m=t+r;
	
loc(0x01);
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0x94);
str("New Balance :-");
loc(0xa5);
num(m);
int M[4],k=3;
while(m!=0)
{ M[k]=m%10;
  k--;
	m=m/10;
}
for(j=0;j<=3;j++)
{eeprom_write_byte((i*4)+j+240,M[j]);
}
_delay_ms(400);
break;
}
else
{loc(0x01);
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0x94);
str("Enter Valid Amount");
_delay_ms(300);
break;
}
}
}
}

else
{loc(0x01);
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0x94);
str("Invalid card");
_delay_ms(200);
break;
}
}

else if(X==22)
{loc(0x01);
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0x94);
str("Insert New Card");
for(i=0;i<=3;i++)                
{
x=keypad();
a[0][i]=x;
str(".");
_delay_ms(10);}


for(i=1;i<=20;i++)              /*match the card in data*/
 {y=0;
  for(j=0;j<=3;j++)
   {int l=eeprom_read_byte((i*12)+j);
if(l!=b[0][j])
	 {y=1;
	 break;
	 }
	}
	if(y!=1)
	 {break;}
  }




 /*for(i=0;i<=20;i++)
   {int l=eeprom_read_byte(i*12);
if(l!='\0')
   {   }
	else
    { break;}	   
   }*/
loc(0x01);
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0x94);
str("Saving Your Card");

for(j=0;j<=3;j++)                
{eeprom_write_byte((i*12)+j,a[0][j]);
str(".");
_delay_ms(40);
}

loc(0x01);
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0x94);
str("Successfully Saved");
_delay_ms(300);
}

else if(X==44)
break;
}

if(X==44)
break;
}
}
}

else if(q==11)
{
while (1)
{
loc(0x01);
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0xc6);
str("Welcome");
loc(0x94);
str("Insert Card");

for(j=0;j<=3;j++)                /*to read card*/
{
x=keypad();
a[0][j]=x;
str(".");
}

for(i=0;i<=20;i++)              /*match the card in data*/
{y=0;
 for(j=0;j<=3;j++)
   {int l=eeprom_read_byte((i*12)+j);
    if(l!=a[0][j])
	 {y=1;
	 break;
	 }
	}
	 if(y!=1)
	 {break;}
   }
while (1)
{
if(y==0)
{
loc(0x01);
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0x94);
str("Check Balance");
loc(0xd4);
str("Proceed Payment");

X=keypad();

if(X==11)
{loc(0x01);
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0x94);
str("Your Card Balance");
for(j=0;j<=3;j++)
	{f[0][j]=eeprom_read_byte(240+(i*4)+j);}
	int t=1000*f[0][0]+100*f[0][1]+10*f[0][2]+1*f[0][3];
loc(0xd9);
num(t);
_delay_ms(300);		
}
else if(X==44)
break;	
else if(X==22)
{
loc(0x01);
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0x94);
str("Enter Bill Amount");
loc(0xd4);
str("Pay");

int I,K;
for(I=0,K=0xe0;I<=4&&K<=0xe5;I++,K++)
{Y=keypad();
   
 if(Y!=22)
   {e[0][I]=Y;
    loc(K);
    num(Y);	
	}
	
 else if(Y==22&&i==0)		
 {e[0][0]=0;
  loc(0xa0);
  num(0);}
	 
else if(Y==22)
{loc(K);
str("/");
loc(++K);
str("-");
_delay_ms(100);
loc(0x01);
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0xd4);
str("processing...");
_delay_ms(150);

int w,r,t,m;
if(I==4){w=1000;}
else if(I==3){w=100;}
else if(I==2){w=10;}
else if(I==1){w=1;}

for(j=0;j<=3;j++)
	{f[0][j]=eeprom_read_byte(240+(i*4)+j);}
		
	r=w*e[0][0]+w/10*e[0][1]+w/100*e[0][2]+w/1000*e[0][3];
	t=1000*f[0][0]+100*f[0][1]+10*f[0][2]+1*f[0][3];

if(t>=r)
{m=t-r;	
loc(0x01);
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0x94);
str("Bill paid");
loc(0xd4);
str("Amount left");
loc(0xe4);
num(m);
int M[4],k=3;
while(m!=0)
{ M[k]=m%10;
  k--;
	m=m/10;
}
for(j=0;j<=3;j++)
{eeprom_write_byte((i*4)+j+240,M[j]);
}
_delay_ms(400);
p=0;
break;
}

else
{loc(0x01);
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0x94);
str("Payment failed");
loc(0xd5);
str("*Not Enough Money*");
_delay_ms(400);
p=0;
break;
}
}
}
if(p==0)
break;
}
}

else
{loc(0x01);
_delay_ms(10);
loc(0x83);
str("Down Town Cafe");
loc(0x94);
str("Invalid card");
_delay_ms(300);
p=0;
break;
}
}
if(X==44||p==0)
break;
}
}
}
}
}



unsigned char keypad()
{
while(1)
{
PORTC=0B00001110;
_delay_ms(5);
if(PINB==0b11111110)
{
while(PINB==0b11111110);
return 1;
}
else if(PINB==0B11111101)
{
while(PINB==0b11111101);
return 4;
}
else if(PINB==0B11111011)
{
while(PINB==0B11111011);
return 7;
}
else if(PINB==0B11110111)
{
while(PINB==0B11110111);
return '#';
}

PORTC=0B00001101;
_delay_ms(5);
if(PINB==0b11111110)
{
while(PINB==0b11111110);
return 2;
}
else if(PINB==0B11111101)
{
while(PINB==0b11111101);
return 5;
}
else if(PINB==0B11111011)
{
while(PINB==0B11111011);
return 8;
}
else if(PINB==0B11110111)
{
while(PINB==0B11110111);
return 0;
}

PORTC=0B00001011;
_delay_ms(5);
if(PINB==0b11111110)
{
while(PINB==0b11111110);
return 3;
}
else if(PINB==0B11111101)
{
while(PINB==0b11111101);
return 6;
}
else if(PINB==0B11111011)
{
while(PINB==0B11111011);
return 9;
}
else if(PINB==0B11110111)
{
while(PINB==0B11110111);
return '*';
}

PORTC=0B00000111;
_delay_ms(5);
if(PINB==0b11111110)
{
while(PINB==0b11111110);
return 11;
}
else if(PINB==0B11111101)
{
while(PINB==0b11111101);
return 22;
}
else if(PINB==0B11111011)
{
while(PINB==0B11111011);
return 33;
}
else if(PINB==0B11110111)
{
while(PINB==0B11110111);
return 44;
}
}
}

void LCD_Init(void)	/* LCD Initialize function */
{   loc(0x02);         /* to take lcd at home screen */
    loc(0x28);  	/* Initialization of 16X2 LCD in 8bit mode */
	loc(0x0C);	        /* Display ON Cursor OFF */
	   	/* Auto Increment cursor */
  }

void dt(char data)      /*to send data in 4 bite mode*/
     {
	  PORTA=((data&0xF0)|0x05);
	  _delay_us(10);
      PORTA=PORTA-0x04;
	  _delay_us(10);
	  PORTA=(((data<<4)&0xF0)|0x05);
	   _delay_us(10); 
	  PORTA=PORTA-0x04;
	  }

void loc(char com)      /*to send location in 4 bite mode*/
    {
	  PORTA=((com&0xF0)|0x04);
	  _delay_us(10);
      PORTA=PORTA-0x04;
	  _delay_us(10);
	  PORTA=(((com<<4)&0xF0)|0x04); 
	   _delay_us(10);
	  PORTA=PORTA-0x04;
	}

void str(char *str)      /*to print string on lcd*/
{int i=0;
while(str[i]!='\0')
{dt(str[i]);	
i++;
}
}

void num(int ch)              /*to print number on lcd*/
{
int x;
if(ch==0)
 dt(48);
  while(ch!=0)
   {loc(0x04);
     x=ch%10;
    dt(48+x);
	ch=ch/10;
}
}

void ini()
{UBRRL=51;
 UBRRH=0;
 UCSRB=0x18;
 UCSRC=0x8e;
}

void send(char send)
{while((UCSRA & 0x20)==0);
 UDR=send;
}


char rec(void)
{while((UCSRA & 0x80)==0);
 return UDR;
}
