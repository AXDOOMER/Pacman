# Pacman
Projet de fin de session à ma première session de CEGEP. Un simple Pacman en C++. 

Je l'ai codé en décembre 2013 comme projet de fin de session. Onze mois après, en 2014, je l'ai porté vers Linux. Le code source du jeu est maintenant disponible sous la license GNU GPL version 2. Les graphismes du jeu sont aussi distribués sous cette version de la GNU GPL, sous les mêmes termes que le code source. Veuillez noter que je n'ai pas écrit "SDLCLG" et que les fichiers sources correspondants ne sont pas distribués sous cette license, car elle m'a été donné par mes professeurs et correspond à une blibliothèque. 

Vous pouvez utiliser Visual Studio 2012 pour compiler ce projet. Si vous utilisez Linux, vous pouvez le compiler à partir du terminal avec les commandes suivantes: 
`g++ -o PacmanAX main.cpp Fonctions.cpp sdlclg.cpp -lSDL -lSDL_mixer`

Note: Vous devez vous assurer que les paquets suivants sont installés: `g++ libsdl1.2-dev libsdl-mixer1.2-dev` et aussi les paquets correspondants pour l'exécution du programme. 

![screenshot at 2016-09-23 11_04_50](https://cloud.githubusercontent.com/assets/6194072/18793261/e78e80c2-8187-11e6-8595-bf63733eac18.png)

Distribué sous la GNU GPL v2.
