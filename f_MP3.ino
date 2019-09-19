void initializeMP3(){
  pinMode(MP3, FUNCTION_3);
  pinMode(MP3, OUTPUT);
}

void startMP3(){
  digitalWrite(MP3,HIGH);
}

void stopMP3(){
  digitalWrite(MP3,LOW);
}
