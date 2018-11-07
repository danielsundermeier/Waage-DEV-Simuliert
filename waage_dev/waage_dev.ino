String command = "";
int laufendeNummer = 1;
int stunde = 10;
int minute = 10;
String datum = "07.11.18";

String randomWeight()
{
    int number = random(10000, 50000);
    return "   " + String(number);
}

String getDatum()
{
    return datum;
}

String zeit()
{
    minute++;
    if (minute == 60) {
      stunde++;
      if (stunde == 24) {
        stunde = 10;
      }
      minute = 10;
    }
    return String(stunde) + ":" + String(minute);
}

String IdentNummer()
{
    String nummer = String(laufendeNummer);

    String leerzeichen = "";
    for(unsigned int i=0; i<(4-nummer.length()); i++){
        leerzeichen += " ";
    }
    leerzeichen += nummer;

    laufendeNummer++;

    return leerzeichen;
}

void antwortGewicht(bool sendIdent = true)
{
    String weight = randomWeight();
    Serial.println("<" + String("00") + String("00") + getDatum() + zeit() + (sendIdent ? IdentNummer() : String("   1")) + String("1") + weight + String("       0") + weight + String("kg") + String("PT") + String(" ") + String("001") + String("   12348") + ">");
}

void setup()
{
    Serial.begin(4800);
    Serial.println("Starte...");
}

void loop()
{
    if (Serial.available() > 0) {
        // read the incoming byte:
        command = Serial.readString();
        command.trim();

        if (command == "<RN>")
        {
            antwortGewicht();
        }
        else if (command == "<RM>") {
            antwortGewicht(false);
        }
        else if (command == "<TA>")
        {
            Serial.println("<00>");
        }
        else if (command == "<TC>") {
            Serial.println("<00>");
        }
        else if (command == "<SZ>") {
            Serial.println("<00>");
        }
        else if (command.startsWith("<PR")) {
            Serial.println("<00>");
        }
        else if (command.startsWith("SETDATE")) {
          command.remove(0, 8);
          datum = command;
          Serial.println("<00>");
        }
        else
        {
            Serial.println("<32>");
        }
    }
}
