/*
.--.       .  .           .--.      .          .
|   )     _|_ |           |   )     |         _|_
|--:  .-.  |  | .  . ____ |--'  .-. |.-.  .-.  |
|   )(   ) |  | |  |      |  \ (   )|   )(   ) |
'--'  `-'  `-'`-`--|      '   ` `-' '`-'  `-'  `-'
                   ;
                `-'
* [foo description]
* Librairie principale des robots Botly et Scott
* @date         2018-11-22
* @author       Jules T. / Adrien B. / Alexandre P.
* @entreprise   La Machinerie
* @version      V2.0.3
*/

#ifndef Botly_h
#define Botly_h
#define LIBRARY_VERSION	2.0.3

#define SCOTT_V4 1 // Version Scott V4 du robot
#define BOTLY_V1 2 // Version Botly V1 du robot

#include "BotlySteppers.h"


/*********************************
     Constantes de calibrations
 *********************************/

#define SCOTT_MM_TO_STEP 260.76
#define SCOTT_RAD_TO_STEP 1210
#define SCOTT_DELTA_ARC 47.5

#define BOTLY_MM_TO_STEP 345
#define BOTLY_RAD_TO_STEP 1861
#define BOTLY_DELTA_ARC 47


/*********************
	 Dependances
*********************/
#include <Servo.h>
#include <Arduino.h>

#include <IRremote.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include "BotlySteppers.h"

void pin2_isr();

class Botly{
public:

  Servo crayon;
  IRsend irsend;
  decode_results results;

  int pin = 9;
  IRrecv irrecv = new IRrecv(pin);

  Botly();

  Botly(int version);

  void init();

  void setCalibration(int distance, int rotation);

  void run();

  void stop(long temps);

  void stop();

  void gauche(long pas);

  void tournerGauche(long angleDegree);

  void droite(long pas);

  void tournerDroite(long angleDegree);

  void avant(long pas);

  void avancer(long distanceMillimeter);

  void arriere(long pas);

  void reculer(long distanceMillimeter);

  void setSpeed(float vitesse);

  void setSpeed(float vitesseD, float vitesseG);

  void logSpeed();

  void turnGo(float angle, long ligne);

  void turnGoDegree(float angle, long ligne);

  void polygone(unsigned int nbrCote, unsigned int longueur);

  void rectangle(unsigned int largeur, unsigned int longueur);

  void carre(unsigned int longueur);

  void cercle(unsigned int diametre);

  void arc(float rayon,float angle);

  void leverCrayon();

  void poserCrayon();

  void bougerCrayon(int angle);

  // ----------------------------
  // Fonctions dédiées à ScottV4
  // ----------------------------

  unsigned int lectureDistance();

  unsigned int lectureLigne();

  unsigned int lectureLumiere();

  unsigned char lectureContact();

  // ----------------------------
  // Fonctions dédiées à BotlyV1
  // ----------------------------

  void isIRDataReceived();

  void initIRcom();

  void sonyCode(byte data);

  bool proximite(int i = 10, int seuil = 5);

  int mesureBatterie();

  void sleepNow();

  void sleepWakeup();

private:

  int _version = 1;

  int _pinBotlyServo= 11  ; // Pin servo pour BotlyV1
  int _pinScottServo= 3   ; // Pin servo pour ScottV4

  // Définition des pins à partir de la version BotlyV1
  int _pinTsop = 9;
  int _pinBotlyIrEmetteur = 13 ;
  int _pinMesureBatterie = A5;
  int _pinBuzzer = 7;
  BotlySteppers *Steppers;

  // Définition des pins à partir de la version ScottV4
  int _pinSwitchDroite = 4 ;
  int _pinSwitchGauche = 5 ;
  int _pinLigneDroite = A1 ;
  int _pinLigneGauche = A0 ;
  int _pinLumiereDroite = A7 ;
  int _pinLumiereGauche = A6 ;
  int _pinDistDroite = A2 ;
  int _pinDistGauche = A3 ;
  int _pinScottIrEmetteur = 2 ;

  // Variable capteur de distance
  int _distDroite;
  int _distGauche;

  // Variable Crayon
  // Version Botly
  int _botlyBas = 90;
  int _botlyHaut = 50;

  // Version Scott
  int _scottBas = -35; // A modifier
  int _scottHaut = 10;

  // Variables de calibration des deplacements
  int _mmToStep = 0;
  int _radToStep = 0;
  int _deltaArc = 0;

  int servoAction = 0;

};
#endif
