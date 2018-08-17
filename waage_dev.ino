String command = "";
int laufendeNummer = 1;

String randomWeight()
{
    int number = random(10000, 50000);
    return "   " + String(number);
}

String datum()
{
    return String("17.08.18");
}

String zeit()
{
    return String(random(10, 24)) + ":" + String(random(10, 59));
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
    Serial.println("<" + String("00") + String("00") + datum() + zeit() + (sendIdent ? IdentNummer() : String("   1")) + String("1") + weight + String("       0") + weight + String("kg") + String("PT") + String(" ") + String("001") + String("   12348") + ">");
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
        else
        {
            Serial.println("<32>");
        }
    }
}