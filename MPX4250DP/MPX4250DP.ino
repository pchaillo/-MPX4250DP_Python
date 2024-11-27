int sensorA = A0;    // select the input pin for the potentiometer
int sensorB = A1;    // select the input pin for the potentiometer
int sensorC = A2;    // select the input pin for the potentiometer


int sensorValueA, sensorValueB, sensorValueC;  // variable to store the value coming from the sensor
float tensionMesA, tensionMesB, tensionMesC ; // Tension mesurée
float tensionCorA, tensionCorB, tensionCorC ; // Tension après correction de l'offset
float pressionMesA, pressionMesB, pressionMesC; // Pression mesurée
int myTime = 0 ; //temps écoulé, en ms

float coef_v = 0.0049; // Constante de conversion de l'indice à la tension correspondante (5V / 1023 indices arduino)
int init_value_A = 0 ; // valeur renvoyé par le capteur déconnecté du système pneumatique ou avant la mise sous pression (état repos)
int init_value_B = 0 ; // valeur renvoyé par le capteur déconnecté du système pneumatique ou avant la mise sous pression (état repos)
int init_value_C = 0 ; // valeur renvoyé par le capteur déconnecté du système pneumatique ou avant la mise sous pression (état repos)

float seuil_max = 4.9 ; // Maximum de tension en sortie de capteur
float pres_coef = 18.8/1000 ; // 18.8mV/kPa
//float pres_coef = 0.045 ; // 45mV/kPa
//float pres_coef = 0.00226 ; // 0.00226V/kPa soit 2.26mv/kPa
int stop_time = 10 ; // temps de latence entre deux prises de mesures

void setup() {
  Serial.begin(115200);  //Pour afficher à l'écran du PC

  Serial.println("Pression mesurée MPX4250DP :");
  delay(500);   //Attendre l'initialisation du module MAX

  init_value_A = analogRead(sensorA);
  init_value_B = analogRead(sensorB);
  init_value_C = analogRead(sensorC);

}

void loop() {
  // read the value from the sensor:
  sensorValueA = analogRead(sensorA);
  sensorValueB = analogRead(sensorB);
  sensorValueC = analogRead(sensorC);

  tensionMesA = sensorValueA*coef_v;
  tensionMesB = sensorValueB*coef_v;
  tensionMesC = sensorValueC*coef_v;

  if ( tensionMesA > seuil_max || tensionMesB > seuil_max || tensionMesC > seuil_max ) {
    Serial.print("\n Attention valeur proche du maximum => ne pas appliquer plus de pression pour ne pas abimer le capteur !!!! \n \n");
  }
  
  tensionCorA = tensionMesA - coef_v*init_value_A;
  tensionCorB = tensionMesB - coef_v*init_value_B;
  tensionCorC = tensionMesC - coef_v*init_value_C;


  pressionMesA = tensionCorA/pres_coef ; 
  pressionMesB = tensionCorB/pres_coef ; 
  pressionMesC = tensionCorC/pres_coef ; 


  myTime = millis();
  
  Serial.print(" ; ");
  Serial.print(pressionMesA);
  Serial.print(" ; ");
  Serial.print(pressionMesB);
  Serial.print(" ; ");  
  Serial.print(pressionMesC);
  Serial.print(" ; ");
  Serial.print(myTime);
  Serial.print("\n"); 

/*
  //Serial.print("Valeur Capteur - Tension mesurée - Tension corrigée - Pression mesurée \n");
  Serial.print(sensorValue);
  Serial.print(" ; ");
  Serial.print(tensionMes);
  Serial.print(" ; ");
  Serial.print(tensionCor);
  Serial.print(" ; ");
  Serial.print(pressionMes);
  Serial.print(" ; ");
  Serial.print(myTime);
  Serial.print("\n"); */

 // Serial.println(sensorValue);
  delay(stop_time);  // 2 mesures par seconde (dépend de la variable stop_time)
}
