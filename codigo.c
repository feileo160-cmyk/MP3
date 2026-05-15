#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// ===== BOTÕES =====
const int botaoS = 8; // subir
const int botaoD = 9; // descer
const int botaoV = 7; // confirmar / sair
const int botaoPause = 6; // pause

// ===== BUZZER =====
int buzzer = 13;

// ===== CONTROLE =====
int escolha = 1;
bool tocando = false;
bool pausado = false;

// ===== NOTAS =====
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_E2 82
#define NOTE_G3 196

// ===== SETUP =====
void setup() {
pinMode(botaoS, INPUT_PULLUP);
pinMode(botaoD, INPUT_PULLUP);
pinMode(botaoV, INPUT_PULLUP);
pinMode(botaoPause, INPUT_PULLUP);
pinMode(buzzer, OUTPUT);

lcd.begin(16, 2);
lcd.print("MP3 Arduino");
delay(1000);
lcd.clear();
}

// ===== LOOP =====
void loop() {

if (!tocando) {

// SUBIR  
if (digitalRead(botaoS) == LOW) {  
  escolha++;  
  if (escolha > 3) escolha = 1;  
  lcd.clear();  
  delay(250);  
}  

// DESCER  
if (digitalRead(botaoD) == LOW) {  
  escolha--;  
  if (escolha < 1) escolha = 3;  
  lcd.clear();  
  delay(250);  
}  

// MENU  
lcd.setCursor(0, 0);  
lcd.print("Escolha:");  

lcd.setCursor(0, 1);  
if (escolha == 1) lcd.print("Star Wars   ");  
if (escolha == 2) lcd.print("DOOM        ");  
if (escolha == 3) lcd.print("Silent Night");  

// CONFIRMAR  
if (digitalRead(botaoV) == LOW) {  
  tocando = true;  
  pausado = false;  
  lcd.clear();  
  delay(300);  
}

}

// ===== TOCAR =====
if (tocando) {
if (escolha == 1) tocarStarWars();
if (escolha == 2) tocarDoom();
if (escolha == 3) tocarSilent();
}
}

// ===== FUNÇÃO BASE COM PAUSE =====
void tocarMusica(int melody[], int tamanho) {

int notes = tamanho / 2;

for (int i = 0; i < notes * 2; i += 2) {

int duracao = 1000 / melody[i + 1];  

// ===== PAUSADO =====  
while (pausado) {  

  lcd.setCursor(0, 1);  
  lcd.print("PAUSADO      ");  
  noTone(buzzer);  

  // SAIR MESMO PAUSADO  
  if (digitalRead(botaoV) == LOW) {  
    tocando = false;  
    pausado = false;  
    lcd.clear();  
    return;  
  }  

  // DESPAUSAR  
  if (digitalRead(botaoPause) == LOW) {  
    pausado = false;  
    lcd.clear();  
    delay(300);  
  }  
}  

// ATIVAR PAUSE  
if (digitalRead(botaoPause) == LOW) {  
  pausado = true;  
  delay(300);  
  i -= 2; // volta nota  
  continue;  
}  

// TOCAR NOTA  
tone(buzzer, melody[i], duracao);  
delay(duracao * 1.3);  
noTone(buzzer);  

// SAIR  
if (digitalRead(botaoV) == LOW) {  
  tocando = false;  
  lcd.clear();  
  return;  
}

}

tocando = false;
}

// ===== STAR WARS =====
int melodyStar[] = {
NOTE_A4,4, NOTE_A4,4, NOTE_A4,4,
NOTE_F4,8, NOTE_C4,16,
NOTE_A4,4, NOTE_F4,8, NOTE_C4,16, NOTE_A4,2
};

void tocarStarWars() {
lcd.setCursor(0,0);
lcd.print("Star Wars");
tocarMusica(melodyStar, sizeof(melodyStar));
}

// ===== DOOM =====
int melodyDoom[] = {
NOTE_E2,8, NOTE_E2,8, NOTE_E2,8,
NOTE_G3,8, NOTE_E2,8
};

void tocarDoom() {
lcd.setCursor(0,0);
lcd.print("DOOM");
tocarMusica(melodyDoom, sizeof(melodyDoom));
}

// ===== SILENT NIGHT =====
int melodySilent[] = {
NOTE_G4,4, NOTE_A4,4, NOTE_G4,4,
NOTE_E4,2
};

void tocarSilent() {
lcd.setCursor(0,0);
lcd.print("Silent Night");
tocarMusica(melodySilent, sizeof(melodySilent));
}
