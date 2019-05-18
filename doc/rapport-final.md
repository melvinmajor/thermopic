---
title: Rapport final - ThermoPIC
author: 
    - Melvin Campos Casares
    - Maxime De Cock
    - Guillaume Vanden Herrewegen
    - Hubert Van De Walle
date: 20 mai 2019
titlepage: true
---

Rapport final - ThermoPIC
=========================

Introduction
------------

ThermoPIC est un projet consistant en l’application d’une sonde de température envoyant au PIC une mesure analogique de la température ambiante d’une pièce.

Une intégration digitale et un signal d’alerte sont tous deux requis afin de prévenir l’utilisateur de l’éventuel dépassement d’un seuil critique défini par l’utilisateur.
L’intégration digitale est l’affichage de la température sur un afficheur intégré au circuit, tout comme d’un indicateur sur le programme lancé sur l’ordinateur relié au PIC.
Le signal d’alerte n’est autre que l’enclenchement d’une LED de couleur rouge et un message d’alerte sur l’ordinateur relié.

Ce projet est à construire de A à Z, dans le sens où il nous faut schématiser, simuler, mais également programmer l’intégralité du circuit électronique choisi.

### Contraintes

_Certaines contraintes nous ont été imposée._
Tout d’abord, la communication entre le circuit et l’ordinateur doit se faire par le biais d’une application écrite en Java.
De plus, certains composants du circuit sont prédéfinis comme le PIC, la sonde de température, les afficheurs 7 segments et des LED (une rouge et une verte).
La sonde température doit fonctionner dans la gamme de 0°C à 100°C **minimum**, les afficheurs 7 segments doivent servir à l’affichage de la température et les LED aux alertes (LED rouge clignotante si alerte, LED verte continue si aucune alerte en cours).

La programmation du PIC est possible via l’interface RS232 ou via l’utilisation d’un module FTDI permettant la conversion du port série en port mini-USB.

### Matériel nécessaire

1. PIC 18F458
2. Sonde température LM35
3. Amplificateur LM324
4. Crystal XTALS
5. Port série et convertisseur série MAX232
6. Deux afficheurs 7 segments à cathodes communes HD-1103
7. Alimentation 5V
8. Pin Header PINHD-1X3
9. Résistances, bouton poussoir 10-XX, LED rouge et verte LED3MM et/ou LED5MM

### Performance

Nous avons pensé en groupe qu'il serait intéressant de réduire la consommation électrique et le besoin en composants de notre prototype afin que celui-ci respecte au mieux les désires de chacun.
Pour respecter cet engagement, nous avons utilisé un affichage simultané sur deux afficheurs 7 segments et en n'utilisant qu'un seul décodeur à 7 segments.

Grâce à deux transistors, nous parvenons à choisir sur quel afficheur afficher un chiffre.
Si on transite rapidement entre les deux afficheurs, l'impact visuel sera inexistant.
Cette manipulation à permis de réduire de 50% la consommation électrique de l'affichage et l'utilisation d'un seul décodeur 7 segments.

Une autre solution possible, mais plus difficile à mettre en place, serait d'allumer les segments de l'afficheur un par un.
Seulement, cette option n'utiliserait pas un décodeur et donc nous devrions utiliser 7 sorties du PIC.
Cette option n'était donc pas envisageable étant donné la taille de la plaque et la place à prévoir pour toutes les connexions ainsi que tous les composants.

Partie technique
----------------

### Fonctionnement

Le fonctionnement de ce circuit repose sur un programme tournant en boucle, qui va à chaque instant donné, récupérer la valeur de la sonde de température et comparer cette valeur à la température maximale entrée par l'utilisateur via une application Java.
Ce programme va aussi vérifier si une donnée est reçue via son RX envoyée depuis l'application Java vers l'entrée Serial du PIC.

Lors du fonctionnement du circuit, si la température est inférieure à la valeur maximale désirée, une LED verte sera allumée pour signaler que tout va bien.
Si cette température dépasse la valeur maximale, une LED rouge clignotera pour signaler l'utilisateur que la température maximale a été dépassée.
L'interface de l'application Java signalera aussi cette alerte.

#### Mode d'emploi

L'utilisation du prototype est extraimement simple. Il suffit d'alimenter en 5v et relier le prototype à un ordinateur via un câble sérial.
Ensuite il faut lancer l'application Java qui permettra de surveiller et de configurer l'alarme à distance.

### Schéma électronique

#### Logique

![Schéma du circuit réalisé sur Proteus](schema-proteus.png)

![Schéma du circuit réalisé sur Eagle](schema.png)

#### PCB

![Plaque de tirage PCB réalisé sur Eagle](pcb.png)

![Plaque de tirage PCB, avec isolation, réalisé sur Eagle](pcb-isolated.png)

### Code C

#### main.h

```C
#include <18F458.h>
#device ADC=10

#FUSES NOWDT                    /*No Watch Dog Timer*/

#use delay(crystal=20000000)

#define LED PIN_D4
#define DELAY 1000

```

#### code.c

```C
/*================================================================
Code from:
- Maxime De Cock
- Melvin Campos
- Hubert Van De Walle
- Guillaume Vanden Herrewegen

Used for Thermopic project with 18f458 microship
==================================================================*/

#include <main.h>
#use rs232(baud=57600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

char buffer[1];

#int_rda
void isr(){
   disable_interrupts(INT_RDA);
   gets(buffer);
}

/*
   Cette fonction permet de sortir un nombre sur 4 pins au lieu de 8
*/
void sortie(int nbr){
   switch(nbr){
         case 0 :  output_low(pin_d0);
                   output_low(pin_d1);
                   output_low(pin_d2);
                   output_low(pin_d3);
                   break;
         case 1 :  output_high(pin_d0);
                   output_low(pin_d1);
                   output_low(pin_d2);
                   output_low(pin_d3);
                   break;
         case 2 :  output_low(pin_d0);
                   output_high(pin_d1);
                   output_low(pin_d2);
                   output_low(pin_d3);
                   break;
         case 3 :  output_high(pin_d0);
                   output_high(pin_d1);
                   output_low(pin_d2);
                   output_low(pin_d3);
                   break;
         case 4 :  output_low(pin_d0);
                   output_low(pin_d1);
                   output_high(pin_d2);
                   output_low(pin_d3);
                   break;
         case 5 :  output_high(pin_d0);
                   output_low(pin_d1);
                   output_high(pin_d2);
                   output_low(pin_d3);
                   break;
         case 6 :  output_low(pin_d0);
                   output_high(pin_d1);
                   output_high(pin_d2);
                   output_low(pin_d3);
                   break;
         case 7 :  output_high(pin_d0);
                   output_high(pin_d1);
                   output_high(pin_d2);
                   output_low(pin_d3);
                   break;
         case 8 :  output_low(pin_d0);
                   output_low(pin_d1);
                   output_low(pin_d2);
                   output_high(pin_d3);
                   break;
         case 9 :  output_high(pin_d0);
                   output_low(pin_d1);
                   output_low(pin_d2);
                   output_high(pin_d3);
                   break;
   }
}

/*
   Cette fonction permet d'afficher sur 2 afficheurs 7 segments à cathodes communes un nombre à 2 chiffres décimaux
*/
void affiche(int nbr){
   int nbr1 = nbr/10;
   int nbr2 = nbr%10;
   output_high(pin_d4);
   output_low(pin_d5);
   sortie(nbr1);
   delay_ms(10);
   output_high(pin_d5);
   output_low(pin_d4);
   sortie(nbr2);
   delay_ms(10);
   delay_ms(10);   
}

void ledRedOn(){
   output_high(pin_d6);
}

void ledRedOff(){
   output_low(pin_d6);
}

void ledGreenOn(){
   output_high(pin_d7);
}

void ledGreenOff(){
   output_low(pin_d7);
}

void main(){
   unsigned long temp;
   long affTemp;
   
   setup_adc(ADC_CLOCK_DIV_32); //configure analog to digiral converter
   setup_adc_ports(ALL_ANALOG); 
   set_adc_channel(0);
   output_high(pin_e0);
   
   int temperatureAlerte = 25;   // température maximale
   
   while(TRUE){
      set_adc_channel(0);//set the pic to read from AN0
      delay_us(10);//delay 10 microseconds to allow PIC to switch to analog channel 0
      temp=read_adc()/10; //read input from pin AN0: 0<=photo<=255
      
      affTemp = temp;
      
      if(temp>25 && temp<69){
         affTemp = temp - 1;
         affiche(affTemp);
         if(affTemp > temperatureAlerte){
            ledRedOn();
            ledGreenOff(); 
         //printf("%c", buffer[0]);
         }
         else{
            ledRedOff();
            ledGreenOn();
         //printf("%c", buffer[0]);
         }
      }
      else if(temp>69){
         affTemp = temp - 2;
         affiche(affTemp);
         if(affTemp > temperatureAlerte){
            ledRedOn();
            ledGreenOff(); 
         //printf("%c", buffer[0]);
         }
         else{
            ledRedOff();
            ledGreenOn();
         //printf("%c", buffer[0]);
         }
      }
      else{
         affiche(affTemp);
         if(affTemp > temperatureAlerte){
            ledRedOn();
            ledGreenOff();
         //printf("%c", buffer[0]);            
         }
         else{
            ledRedOff();
            ledGreenOn();
         //printf("%c", buffer[0]);
         }
      }
      delay_ms(10);
   }
}
```

### Code Java

### Tests

Voici les tests effectués et leurs résultats :

### Conformité par rapport au cahier des charges

Tous les composants précisé dans le cahier des charges ont été tenu en compte et sont présent sur ThermoPIC.

La programmation C, en mode simulation, fonctionne sans le moindre problème.

### Caractéristiques techniques

#### Sonde

#### PIC

#### Modules

#### ...

Partie projet
-------------

### Planning du projet

Dans le tableau ci-dessous, la personne principalement en charge est celle indiqué en **gras**.

Date | Description | Personne en charge
-----|-------------|-------------------
04/02/2019 | _Création du groupe de discussion sur Signal_ | **Hubert** & Melvin
04/02/2019 | _Création du [repository GitHub](https://github.com/melvinmajor/thermopic)_ | **Melvin**
05/02/2019 | _Création du [tableau de planification privé Trello](https://trello.com/b/enrK0mAl/thermopic-project)_ | **Guillaume**
06/02/2019 | _Choix de l'API de communication sur port série_ | **Hubert**
08/02/2019 > 21/02/2019 | _Schéma technique Proteus et Eagle_ | **Maxime** & Guillaume
17/02/2019 | _Sélection des composants électronique_ | Groupe entier (**Maxime**)
28/02/2019 | _Fichier EAGLE (.brd) pour tirage PCB_ | **Melvin**
06/03/2019 > 19/05/2019 | _Programmation Java_ | Groupe entier (**Hubert**)
09/03/2019 > 14/05/2019 | _Programmation C_ | Groupe entier (**Guillaume**)
11/03/2019 | _Rapport intermédiaire_ | Groupe entier (**Melvin**)
26/03/2019 > 30/04/2019 | _Soudures de plaque PCB_ | **Guillaume**, Maxime, **Melvin**
20/05/2019 | _Rapport final_ | Groupe entier (**Melvin**)

#### Création d’un groupe de discussion sur Signal (Melvin Campos Casares & Hubert Van de Walle)

_**Créé le 4 février à 17h34**_

Afin de faciliter la communication entre les membres du groupe, nous avons décidé de créer un groupe de discussion sur l’application Signal, développée par Open Whisper Systems.
Il nous permet également de passer des appels groupés tant en vocal qu’en visioconférence.

L’avantage de Signal est son cryptage accru de bout en bout, sa gratuité (sans publicité et pas de collecte d’informations, le développement est maintenu sur base de dons et subventions de la communauté) et le fait qu’il soit Open Source.

#### Création du repository GitHub (Melvin Campos Casares)

_**Créé le 4 février à 18h05**_

Par souci de facilité avec la synchronisation des fichiers, nous utilisons un repository GitHub où nous sommes tous contributeurs.

Le repository est public et accessible à l’adresse suivante : [https://github.com/melvinmajor/thermopic](https://github.com/melvinmajor/thermopic)

#### Création du tableau de planification privé Trello (Guillaume Vanden Herrewegen)

_**Créé le 5 février à 19h51**_

Afin de mieux coordonner notre planification et de suivre au plus près nos deadlines, nous utilisons la plateforme Trello qui nous a été conseillée lors de la présentation du projet et du cahier des charges.

Le Trello [_"ThermoPic project"_](https://trello.com/b/enrK0mAl/thermopic-project) étant privé, il n’y a pas de lien disponible à moins d’être invité à le rejoindre.

#### API de gestion de communication sur le port série (Hubert Van de Walle)

_**Finalisé le 6 février**_

Lors de la présentation du projet et du cahier des charges, il nous a été proposé d’utiliser l’API **RxTx** pour gérer la communication sur le port série.
En analysant un peu cette API, nous avons pu remarquer qu’elle n’a plus été mise à jour depuis 6 ans et avons donc préféré trouver une autre API, plus récente, et pouvant convenir au projet.

Hubert à trouvé l’API [jSerialComm](https://github.com/Fazecast/jSerialComm), disponible sur GitHub, et permettant d’[utiliser des évènements](https://github.com/Fazecast/jSerialComm/wiki/Event-Based-Reading-Usage-Example).

#### Schéma technique sur Proteus et Eagle (Maxime de Cock & Guillaume Vanden Herrewegen)

_**Echéance le 8 février à 19h**_ - _**Finalisé le 21 février**_

Le délai ne fut pas respecté, entre autres car nous ne savions pas encore clairement quels composants utiliser plus précisément dans notre circuit, mais également par la difficulté de trouver une version propre de Proteus sans virus et disposant des librairies de base.
Le schéma technique sur _Eagle_ fut achevé le 16 février en courant de journée par Maxime.
Pour ce qui concerne le schéma sur _Proteus_, nous attendions la fin du schéma sur Eagle pour pouvoir l’achever.
Quelques dernières retouches ont été réalisées le 21 février sur Eagle tout comme la finalisation de Proteus, par Maxime.

Quelques modifications mineures ont été apportées par la suite afin d'optimiser au mieux notre plaque de tirage et améliorer quelque peu notre schéma technique.

#### Sélection des composants nécessaires au projet (groupe entier)

_**Finalisé le 17 février**_

Bien qu’un point très important, nous avions fini de choisir les composants nécessaires au projet lorsque nous avions terminé la partie principale du schéma technique sur Eagle.
Lors des cours, nous avons pu remarquer l’intérêt de certains composants et reprendre ces derniers dans notre schéma afin de finaliser correctement la partie technique de l’électronique du projet.

#### Fichier EAGLE (.brd) pour tirage PCB (Melvin Campos Casares)

_**Echéance le 11 mars à 17h**_ - _**Finalisé le 28 février**_ - _**Modifications mineures le 12 mars avant impression**_

Avec le schéma achevé le 16 février, il n’y avait plus qu’à réaliser le fichier de carte de circuit imprimé (_**.brd**_).
Pour ce faire, nous sommes partis du schéma Eagle et nous nous sommes rendu compte de certaines modifications à apporter au niveau du schéma afin que notre plaque d'impressions soit correcte.
De plus, lors du commencement de la programmation du code C, nous avons pu remarquer également certaines modifications à apporter au niveau des résistances choisies, n'entrainant heureusement pas de nouveaux changements au niveau du fichier servant au tirage PCB.

Quelques modifications mineures ont été apportées par la suite afin d'optimiser au mieux notre plaque de tirage et améliorer quelque peu notre schéma technique suite aux retours données par Eurocircuit.

#### Rapport intermédiaire (groupe entier)

_**Echéance le 11 mars à 17h**_

Le rapport intermédiaire fut commencé le 8 février et complété au fur et à mesure de l’avancement du projet.
Il a été tenu à jour par tout le groupe et principalement écrit par Melvin sur base des retours des autres membres du groupe.

#### Programmation du code Java (groupe entier)

_**Commencement prévu le 6 mars**_ - _**Commencé le 17 mai**_ - _**Finalisé le 19 mai**_

La programmation du code Java de ce projet est principalement géré par Hubert Van De Walle.
Cela n'empêche que nous nous échangions des informations au fur et à mesure de l'évolution afin de pouvoir avancer lorsque nous rencontrons un problème.

Hubert ayant mis en avant l'intérêt pour l'utilisation d'une API plus pertinente dans le cadre de l'intéraction entre la programmation C et la programamtion Java, il est la personne idéale pour gérer la programmation Java.
Malheureusement, _Hubert a préféré attendre la fin de la programmation du code C avant de commencer la programmation du code Java_, entraînant un retard conséquent malgré les nombreux avertissements des autres membres du groupe et de le désir de chacun de déjà entamer cette partie.
Cela dit, malgré les quelques jours restants avant la fin du projet, nous mettons tout en place afin de terminer cette partie et commencer les simulations et tests.

#### Programmation du code C (Groupe entier)

_**Commencé le 9 mars**_ - _**Finalisé le 14 mai**_

La programmation du code C de ce projet est principalement géré par Guillaume Vanden Herrewegen.
Cela n'empêche que nous nous échangions des informations au fur et à mesure de l'évolution afin de pouvoir avancer lorsque nous rencontrons un problème.

Maxime De Cock à soulevé des points pertinents concernant la partie électronique à devoir tenir compte pour la programmation en C alors que Hubert Van De Walle et Melvin Campos Casares ont plus aidé concernant les choix et directives à prendre afin de contrecarrer certains problèmes rencontrés.
Guillaume Vanden Herrewegen est la personne principale ayant écrit le code C et ayant réalisé les tests préalables permettant de s'assurer du bon fonctionnement.

Initialement prévu le 24 février, le commencement de la programmation C fut le 9 mars suite à un retard occasionné par le schéma Proteus à finaliser.

#### Soudures de plaque PCB (groupe entier)

_**Commencé le 26 mars**_ - _**Finalisé le 30 avril**_

Guillaume Vanden Herrewegen et Melvin Campos Casares sont les personnes principalement en charge des soudures sur la plaque PCB.

Nous avons réalisé les soudures principalement lors de moments prévu dans le cadre des cours pratique d'_électronique digital et analyse des signaux_.

Maxime De Cock, Guillaume Vanden Herrewegen et Melvin Campos Casares se sont organisé pour se voir pendant les vacances de Pâques afin d'avancer encore un peu dans le cadre des soudures et réaliser une première étape des vérifications des soudures déjà réalisée.

Melvin à par ailleurs finalisé les vérifications des soudures chez lui après l'entrevue avec Maxime et Guillaume.

Le groupe au complet à refait une dernière vérification après les dernières soudures le 30 avril et nous nous sommes rendu compte d'une connexion ne se réalisant pas.
Cela à impliqué le besoin de mettre en place un câble en cuivre afin que la connexion puisse se faire entre la puce RS232 et un des condensateurs.

#### Rapport final (groupe entier)

_**Echéance le 20 mai**_

Le rapport final fut commencé après la remise du rapport intermédiaire.
Nous sommes parti du rapport intermédiaire et avons supprimé les parties qui n'étaient plus pertinent et avons ajouté au fur et à mesure les nouveaux éléments demandés.

Il a été tenu à jour et écrit par Melvin sur base des retours des autres membres du groupe.

### Problèmes rencontrés et solutions apportées

#### Programmation

Pour la partie programmation, nous avons décidé de partir d'un circuit vide.
Nous avons ajouté les différentes parties du circuit au fur et à mesure que le code avançait.
La première partie était l’affichage de la température sur les afficheurs 7 segments.
Une fois cette partie fonctionnelle, nous avons travaillé sur l’entrée analogique de la sonde de température.

Nous avons eu quelques difficultés concernant cette partie du code car nous n’arrivions pas à visualiser quelle type de valeur le convertisseur analogique numérique sortait.
Une fois cette valeur « maitrisée », nous l’avons convertie pour qu’elle puisse représenter la température relevée.
Nous avons ensuite pu afficher aisément la température sur les afficheurs 7 segments.

#### Diminution du nombre de résistances

Nous utilisions au départ 7 résistances pour les afficheurs 7 segments.
En ne mettant qu'une seule résistance sur la cathode commune des afficheurs 7 segments, cela permets de réduire le nombre de résistances utilisées, réduire les coûts mais malgré tout garder un minimum de protection.
Etant donné que nous n'envoyons pas de valeurs excessives, cette solution à été appliquée lors de la création de la plaque de tirage PCB.

#### Soudures de la plaque PCB

Le groupe au complet à fait une dernière vérification après les dernières soudures le 30 avril et nous nous sommes rendu compte d'une connexion ne se réalisant pas.
Cela a impliqué le besoin de mettre en place un câble en cuivre afin que la connexion puisse se faire entre la puce RS232 et un des condensateurs.

Nous avons également rajouté 2 connexions par un câble de cuivre car nous avions un soupçon concernant la fiabilité des soudures concernées. 

#### Court-circuit dans la plaque PCB

Nous avons détecté un court-circuit au niveau de la plaque PCB bien que toutes les soudures soient correctes et vérifiées.
Cela explique l'impossibilité de flasher le PIC et également de tester concrètement et hors simulation notre projet fini.

Pour tenter de trouver la solution, voici les différentes étapes réalisées :

    * Vérification de toutes les soudures via un test de connectivité.
    * Mise en place de câbles pour remplacer des soudures imparfaites.
    * Vérification du fonctionnement de chaque composant du circuit.
    * Vérification de tous les circuits sur base du schéma Eagle.
    * Vérification de tous les circuits sur base de la simulation Proteus.

Aucune solution n'a été trouvé suite à toutes ces recherches.

Conclusion
==========

Limites du systèmes et améliorations possibles
----------------------------------------------

### Rendre la plaque moins énergivore

En ajoutant une puce LM555 connectée à la LED rouge, la LED clignote sans pour autant éteindre le signal de base.
Une interprétation sur base d'une fonction dans la puce permet, sur base d'une valeur simple envoyée à la LM555, de gérer l'intéraction avec la LED.
Par conséquent, l'envoi d'un signal constant permet de réduire la consommation énergétique puisque la LM555 enverra le signal rapide afin de faire clignoter la LED.

Nous aurions pu également utiliser la LM555 pour les afficheurs 7 segments afin d'envoyer un signal constant et, par ce biais, faire en sorte que cette puce gère l'affichage des valeurs sur les afficheurs.

### Amélioration liée à la LM324

En utilisant une autre puce que la LM324, nous aurions pu éviter le fait que la LM324 renvoie une valeur entre 0 et 4V impliquant une conversion dans le code insérée dans le PIC 18F458.
Cela aurait pu donc alléger la programmation C.
