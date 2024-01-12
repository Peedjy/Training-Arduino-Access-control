/* 
Contrôle d’accès 
Description:
Ce programme est un exercice d’initiation à la programmation
Il a pour fonction d’autoriser ou de refuser un accès en fonction d’un code secret reçu par le port série
 
Circuit:
Arduino Duemilanove 
           LED rouge sur Pin 13
           LED verte sur Pin 12
          Buzzer sur Pin 11

Revision: V1.3
Ajout des mots de passe avec plusieurs caractères sous forme de strng et 
nouvelle methode de test basée sur des if/else plutôt que switch/case qui ne supporte que les int.
+ Double BIP en cas d'accès refusé!
V1.2: Ajout des fonctions Clignote, AccesOk, AccesNoOK
created by CROZEMARIE J.Pierre
Janvier 2012

*/
//-----------------------------------------  
// FONCTIONS
//-----------------------------------------
   void Clignote()
   {
digitalWrite(13, HIGH);     // On allume la LED rouge
  delay(1000);              // On attend 1 sec
  digitalWrite(13, LOW);    // On eteind la LED rouge
  delay(1000);             // On attend 1 sec
}             
//--------------------------------------
void AccesOK ()
{
     digitalWrite(12, HIGH);   //On allume la LED Vert
     digitalWrite(13, LOW);    //On éteind la LED rouge
     digitalWrite(11, HIGH);   //On fait BIP pendant 0.3 seconde
     delay(300);              
     digitalWrite(11, LOW);    // On arrete le BIP
     delay(500);               // On laisse la LED Verte allumée un peu plus longtemps
     digitalWrite(12, LOW);   // On eteind la LED Verte
}
//------------------------------------
void AccesNoOK ()
{
digitalWrite(13, HIGH);       //On allume la LED Rouge
digitalWrite(12, LOW);         //On éteind la LED Verte
digitalWrite(11, HIGH);       //On fait BIP-Bip pendant 0.3 seconde
delay(100);   
digitalWrite(11, LOW);       
delay(100); 
digitalWrite(11, HIGH);       
delay(100);  
digitalWrite(11, LOW);
digitalWrite(13, LOW);       //On re-éteind la LED Rouge
}
//------------------------------------------------
/*String LireCode () //Fonction qui retour un string, void ne retourn rien!
{
String Code;

Serial.println("Debut Fct readstring");
  	  while (Serial.available()) {
	  delay(10);
	    if (Serial.available() >0) {
	  char c = Serial.read();
	  Code = Code + c; }
	  }

	if (Code.length() >0) {
Serial.println("Code recu =");	
  Serial.println(Code);
return Code;
	//Code="";
	}}*/
//-------------------------
boolean CodeOK = false;
int Pwd1 ;
int Pwd2;
int PwdTot;

void setup() 
{
Serial.begin(9600);
Serial.println("Connexion etablie"); // permet de vérifier la connexion

  pinMode(13, OUTPUT); // LED Rouge
  pinMode(12, OUTPUT); // LED Verte
  pinMode(11, OUTPUT); // Buzzer

}

void loop() 
{
  String Code;
  Clignote ();
          //Serial.println("Debut lecture");
  	  while (Serial.available()) {
	  delay(10);
	    if (Serial.available() >0) {
	  char c = Serial.read();
	  Code = Code + c; }
	  }

	if (Code.length() >0) // Siquelque chose reçu
            {
              Serial.println("Code recu =");	
              Serial.println(Code);
  
               if (Code == "farnell")
                  {
                    Serial.println("****** est valide");
                    Pwd1 = 1;
                  } 
                else
                   {
                     Serial.println("code non valide");
                     Pwd1 = 0;
                   }
//---------------------------- 
if (Code == "jp")
{
  Serial.println("** est valide");
  Pwd2 = 1;
  //Code= "";
} 
else
{
  Serial.println("code non valide");
  Pwd2 = 0;
  //Code= "";
} 
PwdTot = Pwd1+Pwd2;
Serial.println(PwdTot); 
//-------------------------
Serial.println("fin test code recu...."); 
   if (PwdTot != 0)
{
  Serial.println("code valide");
  AccesOK ();
  //Code= "";
} 
else
{
  Serial.println("code non valide");
  AccesNoOK ();
  //Code= "";
} 
}// fin du test si code recu
} // fin de loop

