    #include <SoftwareSerial.h>

    #define SIM800_TX 10
    #define SIM800_RX 11

    SoftwareSerial sim800(SIM800_TX,SIM800_RX); // DECLARADOS OS PINOS RX(11) E TX(10) QUE SERÁ USADO

    const int pinoResetGSM = 2; //PINO DIGITAL UTILIZADO PARA RESETAR O SIM800
    const int pinoSinal = 6; //PINO DIGITAL UTILIZADO PARA SINAL DE SAÍDA
    const int pinoCadeira = 7; //PINO DIGITAL UTILIZADO PELA CHAVE FIM DE CURSO
    const int pinoIgn = 8; //PINO DIGITAL UTILIZADO PELA CHAVE DE IGNIÇÃO

void setup()
{
      Serial.begin(9600);//INICIA A BIBLIOTECA SERIAL
      sim800.begin(19200);
      delay(2000);
    
      Serial.println("Inicializando...");//EXIBE NO MONITOR SERIAL O TEXTO INFORMADO
    
      pinMode(pinoSinal, OUTPUT); //DEFINE O PINO COMO SAÍDA
      pinMode(pinoCadeira, INPUT_PULLUP); //DEFINE O PINO COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)
      pinMode(pinoIgn, INPUT_PULLUP); //DEFINE O PINO COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)
}

void loop()
{
  Serial.println("Iniciando a verificação...");//EXIBE NO MONITOR SERIAL O TEXTO INFORMADO
  delay(1000);
    
    digitalWrite(pinoSinal, LOW);// EMITE O SINAL LOW NO PINO DE SAÍDA
    
    if(digitalRead(pinoIgn) == LOW){ //SE A LEITURA DO PINO IGNIÇÃO FOR IGUAL A LOW, FAZ:
      Serial.println("Chave ligada");}//EXIBE NO MONITOR SERIAL O TEXTO INFORMADO
    else{
      Serial.println("Chave desligada");//EXIBE NO MONITOR SERIAL O TEXTO INFORMADO
  digitalWrite(pinoSinal, LOW);// EMITE O SINAL LOW NO PINO DE SAÍDA
        
    if(digitalRead(pinoCadeira) == LOW){ //SE A LEITURA DO PINO FOR IGUAL A LOW, FAZ:
      Serial.println("Enviando SMS");//EXIBE NO MONITOR SERIAL O TEXTO INFORMADO
      sim800.write("AT+CMGF=1\r"); // Ativa SMS em modo texto
      delay(1000);
        
      sim800.write("AT + CMGS = \"+5534991958864\""); // DEFINE O CELULAR A RECEBER O SMS (VER COMO COLOCAR EM STRING IGUAL O TEXTO)
      delay(1000);
        
      sim800.write("Criança no carro, voltar urgentemente"); // CORPO DO SMS DEFINIDO NA STRING texto
      delay(1000);
        
      sim800.write((char)26); // Caractere de FIM de texto e ENVIO
	Serial.println("SMS Enviado");//EXIBE NO MONITOR SERIAL O TEXTO INFORMADO    
      delay(1000);
                  
      Serial.println("Criança no carro, voltar urgentemente");//EXIBE NO MONITOR SERIAL O TEXTO ARMAZENADO
       }
    else{
      Serial.println("Sem criança no carro");}//EXIBE NO MONITOR SERIAL O TEXTO INFORMADO
        
  Serial.println("Verificação finalizada");//EXIBE NO MONITOR SERIAL INFORMANDO QUE FINALIZOU O PROCESSO
  }
delay(1000);
}
