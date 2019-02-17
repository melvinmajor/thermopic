---
title: Rapport intermédiaire - ThermoPIC
author: 
    - Melvin Campos Casares
    - Maxime De Cock
    - Guillaume Vanden Herrewegen
    - Hubert Van De Walle
date: 11 mars 2019
titlepage: true
---

Rapport intermédiaire - ThermoPIC
=================================

Objectifs du projet
-------------------

### Introduction

ThermoPIC est un projet consistant en l'application d'une sonde température envoyant au PIC une mesure analogique de la température ambiante d'une pièce.

Une intégration digitale et un signal d'alerte sont tous deux requis afin de prévenir l'utilisateur de l'éventuel dépassement d'un seuil critique défini par l'utilisateur.
L'intégration digitale est l'affichage de la température sur un afficheur intégré au circuit, tout comme d'un indicateur sur le programme lancé sur l'ordinateur relié. Le signal d'alerte n'est d'autres que l'enclenchement d'une LED de couleur rouge et un message d'alerte sur l'ordinateur relié.

Ce projet est à construire de A à Z, dans le sens où il nous faut schématiser, simuler, mais également programmer l'intégralité du circuit électronique choisi.

#### Contraintes

_Certaines contraintes nous ont été imposée._
Tout d'abord, la communication entre le circuit et l'ordinateur doit se faire par le biais d'une application écrite en Java.
De plus, certains composants du circuits sont prédéfini comme le PIC, la sonde température, les afficheurs 7 segments et les LED rouge et verte. La sonde température doit fonctionner dans la gamme de 0°C à 100°C **minimum**, les afficheurs 7 segments doivent servir à l'affichage de la température et les LED aux alertes (LED rouge clignotante si alerte, LED verte continue si aucune alerte en cours).

La programmation du PIC est possible via l'interface RS232 ou via l'utilisation d'un module FTDI permettant la conversion du port série en port mini-USB.

### Matériel nécessaire

1. PIC 18F458
2. Sonde température LM35
3. Amplificateur LM324
4. Crystal XTALS
5. Port série
6. Convertisseur série MAX232
7. Deux afficheurs 7 segments à cathodes communes HD-1103
8. Alimentation 5V
9. Pin Header PINHD-1X3
10. Résistances
11. LED rouge et verte LED3MM et/ou LED5MM
12. Bouton poussoir 10-XX

### Application

### Fonctionnement

Etat d'avancement
-----------------

### Général

### Simulation

### Programmation

Schéma
------

Répartition du travail
----------------------

Nous nous sommes réparti le travail par le biais de la plateforme Trello.
Il s'agit d'un outil collaboratif de gestion de projets qui nous a été conseillé lors de la prise de connaissance du cahier des charges de ce projet.

Certains membres du groupe en ont déjà précédemment entendu parlé par d'étudiants de la section comptabilité de l'EPHEC.

### Planning et échéances

#### Création d'un groupe de discussion sur Signal (Melvin Campos Casares & Hubert Van de Walle)

_**Créé le 4 février à 17h34**_

Afin de faciliter la communication entre les membres du groupe, nous avons décidé de créer un groupe de discussion sur l'application Signal, développée par Open Whisper Systems.
Il nous permet également de passer des appels groupés tant en vocal qu'en visio-conférence.

L'avantage de Signal est son cryptage accru de bout en bout, sa gratuité (sans publicité et pas de collecte d'informations, le développement est maintenu sur base de dons et subventions de la communauté) et le fait qu'il soit Open Source.

#### Création du repository GitHub (Melvin Campos Casares)

_**Créé le 4 février à 18h05**_

Par soucis de facilité avec la synchronisation des fichiers, nous utilisons un repository GitHub où nous sommes tous contributeurs.

Le repository est public et accessible à l'adresse suivante : [https://github.com/melvinmajor/thermopic](https://github.com/melvinmajor/thermopic)

#### Création du tableau de planification Trello (Guillaume Vanden Herrewegen)

_**Créé le 5 février à 19h51**_

Afin de mieux coordonner notre plannification et de suivre au plus près nos deadline, nous utilisons la plateforme Trello qui nous à été conseillé lors de la présentation du projet et du cahier des charges.

Le Trello _"ThermoPic project"_ étant privé, il n'y a pas de lien disponible afin d'y accéder à moins d'être invité à le rejoindre.

#### API de gestion de communication sur le port série (Hubert Van de Walle)

_**Finalisé le 6 février**_

Lors de la présentation du projet et du cahier des charges, il nous à été proposé du'itiliser l'API **RxTx** pour gérer la communication sur le port série.
En analysant un peu cette API, nous avons pu remarquer qu'elle n'a plus été mise à jour depuis 6 ans et avons donc préféré trouver une autre API, plus récente, et pouvant convenir au projet.

Hubert à trouvé l'API [jSerialComm](https://github.com/Fazecast/jSerialComm), disponible sur GitHub et permettant d'[utiliser des évènements](https://github.com/Fazecast/jSerialComm/wiki/Event-Based-Reading-Usage-Example).

#### Schéma technique sur Proteus et Eagle (Maxime de Cock & Guillaume Vanden Herrewegen)

_**Echéance le 8 février à 19h**_ - _**Finalisé le 17 février**_

Le délai ne fut pas respecté, entre autre car nous ne savions pas encore clairement quels composants utiliser plus précisément dans notre circuit mais également par la difficulté de trouver une version propre de Proteus (sans virus et disposant des librairies de base).
Le schéma technique sur _Eagle_ fut achevé le 16 février en courant de journée par Maxime.
Pour ce qui concerne le schéma sur _Proteus_, nous attendions la fin du schéma sur Eagle pour pouvoir l'achever.
Quelques dernières retouches ont été réalisé le 17 février sur Eagle tout comme la finalisation de Proteus, par Maxime.

#### Sélection des composants nécessaires au projet (groupe entier)

_**Finalisé le 17 février**_

Bien qu'un point très important, nous avions fini de choisir les composants nécessaires au projet lorsque nous avions terminé le schéma technique sur Eagle.
Lors des cours, nous avons pu remarquer l'intérêt de certains composants et reprendre ces derniers dans notre schéma afin de finaliser correctement la partie technique de l'électronique du projet.

#### Rapport intermédiaire (groupe entier)

_**Echéance le 11 mars à 17h**_

Le rapport intermédiaire fut commencé le 8 février et complété au fur et à mesure de l'avancement du projet.
Il a été tenu à jour par tout le groupe et principalement écrit par Melvin sur base des retours des autres membres du groupes.

#### Fichier EAGLE (*.brd) pour tirage PCB (Melvin Campos Casares)

_**Echéance le 11 mars à 17h**_

Avec le schéma achevé le 16 février, il n'y a plus qu'à réaliser le fichier de carte de circuit imprimé (_**.brd**_).

### Estimation du travail à faire

Objectifs personnels et attente
-------------------------------
### Melvin Campos Casares

### Maxime De Cock

### Guillaume Vanden Herrewegen

### Hubert Van De Walle

Conclusion
----------
