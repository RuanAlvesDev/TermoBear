#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT22

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

const int ledVerde = 9;
const int ledAmarelo = 6;
const int ledVermelho = 3;

void setup() {

  Serial.begin(9600);
  Serial.println("Inicializando DHT22...");

  dht.begin();

  lcd.init();
  lcd.backlight();

  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  // Texto fixo no LCD
  lcd.setCursor(0,0);
  lcd.print("Temp: ");

  lcd.setCursor(0,1);
  lcd.print("Umid: ");
}

void loop() {

  float humidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  if (isnan(temperatura) || isnan(humidade)) {
    Serial.println("Erro ao ler DHT22");
    delay(2000);
    return;
  }

  // Atualiza temperatura
  lcd.setCursor(6,0);
  lcd.print("      "); // limpa área
  lcd.setCursor(6,0);
  lcd.print(temperatura,1);
  lcd.print("C");

  // Atualiza humidade
  lcd.setCursor(6,1);
  lcd.print("      ");
  lcd.setCursor(6,1);
  lcd.print(humidade,1);
  lcd.print("%");

  // Serial monitor
  Serial.print("Temp: ");
  Serial.print(temperatura);
  Serial.print(" C | Umid: ");
  Serial.print(humidade);
  Serial.println(" %");

  // Controle dos LEDs
  if (temperatura < 15) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
  } 
  else if (temperatura <= 30) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
  } 
  else {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
  }

  delay(2000);
}
