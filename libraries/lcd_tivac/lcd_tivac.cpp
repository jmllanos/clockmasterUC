#include <Arduino.h>
#include <Wire.h>
#include <lcd_tivac.h>

lcd_tivac::lcd_tivac(void){
}

uint8_t lcd_tivac::start(uint8_t addr){
  Wire.beginTransmission(addr);
  Wire.write(0x00);//Comsend = 0x00
  Wire.write(0x38);
  delay(10);
  Wire.write(0x39);
  delay(10);
  Wire.write(0x14);
  Wire.write(0x78);
  Wire.write(0x5E);
  Wire.write(0x6D);
  Wire.write(0x0C);
  Wire.write(0x01);
  Wire.write(0x06);
  delay(10);
  uint8_t error = Wire.endTransmission();

  writing(addr, 0x00, 0x02);//Set cursor on 0,0
  return error;
}
void lcd_tivac::text(char input[]){//, int n) {
  int n = strlen(input)-1;
  uint8_t addr = 0x3c;
  for (int i = 0; i <= n; i++)
  {
    writing(addr, 0x40, input[i]);//(write on DDRAM command, ASCII code for character)
  }
}
/*
void lcd_tivac::text(char input[]){
  //Tener en cuenta que el texto a ingresar puede tener una longitud maxima de 20 caracteres
  // Y se deben mandar 20 caracteres por serial, si se mandan menos los siguientes comandos
  // se detectaran como caracteres, lo cual generara visualizaciones extrañas
  int n = strlen(input);

  Wire.beginTransmission(0x3C);

  Wire.write(0x40);


  for (int i=0;i<n;i++){
    Wire.write(input[i]);
  }

  Wire.endTransmission(0x3C);

}
*/
void lcd_tivac::put_num(byte number){
  char *cad;
  cad = (char*)malloc(sizeof(char)*4);// Solo necesita 3 caracteres para un byte, el otro es para el fin de cadena
  sprintf(cad,"%d",number);
  text(cad);
  free(cad);/////---------########################################################################
}

void lcd_tivac::writing(byte my_addr, byte cmd, byte data) {
  Wire.beginTransmission(my_addr);
  Wire.write(cmd);
  Wire.write(data);
  Wire.endTransmission();
}

void lcd_tivac::position(int row, int col){
  byte addr = 0x3c;
  byte a = 0x00;
  if (col < 20){
  if (row == 1)
    a = 0x00+col;
  else if (row == 2)
    a = 0x40+col;
  writing(addr, 0x00, 0x80|a);
  }


}

lcd_tivac LCD;
