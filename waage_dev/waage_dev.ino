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

String IdentNummer(unsigned int stellen = 4)
{
    String nummer = String(laufendeNummer);

    String leerzeichen = "";
    for(unsigned int i = 0; i < (stellen - nummer.length()); i++) {
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

void antwortGewichtTell() {
    String weight = randomWeight();
    Serial.println(String("1;") + IdentNummer(10) + String(";") + getDatum() + String(";") + zeit() + String(";1;1;       0;") + String("kg") + weight + String(";") + weight + String(";") + weight + String(";111"));
}

void antwortGewichtPfister() {
    Serial.println("OK");
    String weight = randomWeight();
    Serial.println(String("$MP") + IdentNummer(6) + String("  ") + weight + String("kg"));
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
        else if (command == "<FP0>") {
            antwortGewichtTell();
        }
        else if (command == "MP") {
            antwortGewichtPfister();
        }
        else if (command.startsWith("<PR")) {
            Serial.println("<00>");
        }
        else if (command.startsWith("ST")) {
          command.remove(0, 2);
          command.remove(8);
          datum = command;
          Serial.println("<00>");
        }
        else
        {
            Serial.println("<32>");
        }
    }
}
