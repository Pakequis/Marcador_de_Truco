/*******************************************************
        Contador marcador para jogo de Truco
        
        Rodrigo Feliciano (www.pakequis.com.br)
                   Novembro de 2015
ATENCAO: Utiliza o shield de LCD 2x16 com teclado!!!
********************************************************/
#include <LiquidCrystal.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

//variaveis...
int dupla1 = 0; 	//Pontos da dupla 1
int dupla2 = 0;		//Pontos da dupla 2
int l_select = 0;	//selecao de linha

// read the buttons
int read_LCD_buttons()
{
	adc_key_in = analogRead(0);      // read the value from the sensor 

	if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
	// For V1.1 us this threshold
	//if (adc_key_in < 50)   return btnRIGHT;  
	//if (adc_key_in < 250)  return btnUP; 
	//if (adc_key_in < 450)  return btnDOWN; 
	//if (adc_key_in < 650)  return btnLEFT; 
	//if (adc_key_in < 850)  return btnSELECT;  

	//Meu Shield eh versao 1.0
	if (adc_key_in < 50)   return btnRIGHT;  
	if (adc_key_in < 195)  return btnUP; 
	if (adc_key_in < 380)  return btnDOWN; 
	if (adc_key_in < 555)  return btnLEFT; 
	if (adc_key_in < 790)  return btnSELECT;   

	return btnNONE;  // when all others fail, return this...
}

void setup()
{
	lcd.begin(16, 2); 
	lcd.setCursor(0,0);
}
 
void loop()
{
	delay(100);

	//Tela do contador
	lcd.setCursor(0,0);	      
	lcd.print("  Dupla 1 = ");
	lcd.setCursor(0,1);
	lcd.print("  Dupla 2 = ");
 
	lcd.setCursor(12,0);
	lcd.print(dupla1);	//Mostra pontos da dupla 1
	lcd.print(" ");
	lcd.setCursor(12,1);
	lcd.print(dupla2);	//Mostra pontos da dupla 2
	lcd.print(" ");
        
	//Qual contador estah selecionado
	if(!l_select)
	{
		lcd.setCursor(0,0);
		lcd.print(">");
		lcd.setCursor(15,0);
		lcd.print("<");
		lcd.setCursor(0,1);
		lcd.print(" ");
		lcd.setCursor(15,1);
		lcd.print(" "); 	 
	}else
	{
		lcd.setCursor(0,0);
		lcd.print(" ");
		lcd.setCursor(15,0);
		lcd.print(" ");
		lcd.setCursor(0,1);
		lcd.print(">");
		lcd.setCursor(15,1);
		lcd.print("<"); 	  
	}

	//Condicao 12/0: Regra do truco de churraso 
	//onde o perdedor tem que passar debaixo da mesa
	if((dupla1 == 12) && (dupla2 == 0))
	{
		lcd.setCursor(0,0);
		lcd.print("Dupla 2: Passa  ");
		lcd.setCursor(0,1);
		lcd.print("debaixo da mesa!");
		dupla1 = 0;
		dupla2 = 0;
		l_select = 0;
		while(read_LCD_buttons() != btnSELECT)
		{
			//espera a tecla ser pressionada
		}
	}
	//Condicao 12/0: Regra do truco de churraso 
	//onde o perdedor tem que passar debaixo da mesa
	if ((dupla1 == 0) && (dupla2 == 12))
	{
		lcd.setCursor(0,0);
		lcd.print("Dupla 1: Passa  ");
		lcd.setCursor(0,1);
		lcd.print("debaixo da mesa!");
		dupla1 = 0;
		dupla2 = 0;
		l_select = 0;
		while (read_LCD_buttons() != btnSELECT)
		{
			//espera a tecla ser pressioanada
		}
	} 
	
	//Dupla 1 chegou a 12
	if ((dupla1 == 12) && (dupla2 > 0))
	{
		dupla1 = 0;
		dupla2 = 0;
		l_select = 0;
		lcd.setCursor(0,0);
		lcd.print("Dupla 1: Ganhou!");
		lcd.setCursor(0,1);
		lcd.print("Dupla 2: Perdeu!");
		while(read_LCD_buttons() != btnSELECT)
		{
			//espera a tecla ser pressionada
		}
	}

	//Dupla 2 chegou a 12
	if ((dupla1 > 0) && (dupla2 == 12))
	{
		dupla1 = 0;
		dupla2 = 0;
		l_select = 0;
		lcd.setCursor(0,0);
		lcd.print("Dupla 2: Ganhou!");
		lcd.setCursor(0,1);
		lcd.print("Dupla 1: Perdeu!");
		while(read_LCD_buttons() != btnSELECT)
		{
			//espera a tecla ser pressionada
		}
	}
 	
	lcd_key = read_LCD_buttons();
	
	//Atualizacao de variaveis quando uma
	//tecla for pressionada
	switch (lcd_key)          
	{
		case btnRIGHT:
		{
			if(!l_select)
			{
				if(dupla1 < 12) dupla1++;	//soma 1 ponto para a dupla 1
			}else
			{
				if(dupla2 < 12) dupla2++;	//soma 1 ponto para a dupla 2
			}
			delay(100);
			break;
		}
   		case btnLEFT:
   			{
   				if(!l_select)
   				{
   					if(dupla1) dupla1--;	//diminui 1 ponto para a dupla 1
   				}else
   				{
   					if(dupla2) dupla2--;	//diminui 1 ponto para a dupla 2
   				}
   				delay(100);
   				break;
   			}
   		case btnUP:
   		{
   			if(l_select) l_select--;	//vai para a primeira linha
   			delay(100);
   			break;
   		}
   		case btnDOWN:
   		{
   			if(!l_select) l_select++;	//vai para a segunda linha
   			delay(100);
   			break;
   		}
		//zera os contadores e limpa o display
   		case btnSELECT:
   		{
   			dupla1 = 0;
   			dupla2 = 0;
   			l_select = 0;
   			delay(100);
   			lcd.setCursor(0,0);
   			lcd.print("                ");
   			lcd.setCursor(0,1);
   			lcd.print("                ");
   			break;
   		}
    		case btnNONE:
    		{
    			//vazio!!!
    			break;
    		}
    	}
}