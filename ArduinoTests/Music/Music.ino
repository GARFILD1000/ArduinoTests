#include "Notes.cpp"

const class Notes notes;
int second = 2000;
int whole = second;
int half = whole / 2;
int quarter = whole / 4;
int eighth = whole / 8;
int sixteenth = whole / 16;

void playNote(int note, int noteLength){
  tone(A1, note, noteLength - 10);
  delay(noteLength);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, OUTPUT);

  playNote(notes.B_2, eighth);
  playNote(notes.D_3, sixteenth);
  playNote(notes.B_2, sixteenth);
  
  playNote(notes.Fs_2, eighth);
  playNote(notes.B_2, sixteenth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.D_2, eighth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.D_2, sixteenth);
  
  playNote(notes.B_1, quarter);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.B_2, sixteenth);
  playNote(notes.D_3, sixteenth);
  playNote(notes.B_2, sixteenth);
  
  playNote(notes.Cs_3, sixteenth);
  playNote(notes.B_2, sixteenth);
  playNote(notes.Cs_3, sixteenth);
  playNote(notes.B_2, sixteenth);
  playNote(notes.As_2, sixteenth);
  playNote(notes.Cs_3, sixteenth);
  playNote(notes.E_3, sixteenth);
  playNote(notes.Cs_3, sixteenth);
  
  playNote(notes.D_3, eighth);
  playNote(notes.B_2, eighth);
  playNote(notes.B_2, eighth);
  playNote(notes.D_3, sixteenth);
  playNote(notes.B_2, sixteenth);
  
  playNote(notes.Fs_2, eighth);
  playNote(notes.B_2, sixteenth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.D_2, eighth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.D_2, sixteenth);
  
  playNote(notes.B_1, quarter);
  playNote(notes.D_2, sixteenth);
  playNote(notes.Cs_2, sixteenth);
  playNote(notes.D_2, eighth);
  
  playNote(notes.D_2, sixteenth);
  playNote(notes.Cs_2, sixteenth);
  playNote(notes.D_2, eighth);
  playNote(notes.D_2, sixteenth);
  playNote(notes.B_2, sixteenth);
  playNote(notes.D_2, eighth);
  
  playNote(notes.D_2, eighth);
  playNote(notes.Cs_2, eighth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.F_2, sixteenth);
  playNote(notes.Fs_2, eighth);
  
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.F_2, sixteenth);
  playNote(notes.Fs_2, eighth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.D_3, sixteenth);
  playNote(notes.Fs_2, eighth);
  
  playNote(notes.Fs_2, eighth);
  playNote(notes.F_2, eighth);
  playNote(notes.Cs_2, sixteenth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.A_2, sixteenth);
  playNote(notes.Fs_2, sixteenth);
  
  playNote(notes.Gs_2, sixteenth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.Gs_2, sixteenth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.F_2, sixteenth);
  playNote(notes.Gs_2, sixteenth);
  playNote(notes.B_2, sixteenth);
  playNote(notes.Gs_2, sixteenth);

  playNote(notes.A_2, sixteenth);
  playNote(notes.Gs_2, sixteenth);
  playNote(notes.A_2, sixteenth);
  playNote(notes.Gs_2, sixteenth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.A_2, sixteenth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.F_2, sixteenth);
  
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.B_2, sixteenth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.F_2, sixteenth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.Cs_3, sixteenth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.F_2, sixteenth);
  
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.D_3, sixteenth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.F_2, sixteenth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.D_3, sixteenth);
  playNote(notes.Cs_3, sixteenth);
  playNote(notes.B_2, sixteenth);

  playNote(notes.Cs_3, sixteenth);
  playNote(notes.A_2, sixteenth);
  playNote(notes.Gs_2, sixteenth);
  playNote(notes.Fs_2, sixteenth);
  playNote(notes.A_2, eighth);
  playNote(notes.Gs_2, eighth);
  
  playNote(notes.Fs_2, quarter);
  
  
  
  
  
}



void loop() {
  // put your main code here, to run repeatedly:
 
}
