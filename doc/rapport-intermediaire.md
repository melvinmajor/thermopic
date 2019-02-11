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
4. Port série
5. Deux afficheurs 7 segments à cathodes communes
6. Alimentation 5V
7. Résistances
8. LED rouge et verte

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

### Estimation du travail à faire

Objectifs personnels et attente
-------------------------------
### Melvin Campos Casares

### Maxime De Cock

### Guillaume Vanden Herrewegen

### Hubert Van De Walle

Conclusion
----------
