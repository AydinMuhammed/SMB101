<!-- ---------------CSS----------- -->
<style>
* {
    font-family: Verdana;
}

</style>
<!-- ---------------CSS----------- -->
<center><h1>SMB101</h1></center>

<h2>Configuration de l'environment de travail: </h2>

<ol>
     <h3><li> Les extensions VS Code à installer :</h3>
            <ul>
                <li>Markdown Preview Github (pour visualiser les notes en .md directement sur vs code</li>
                <li>C/C++ (langage de programmation)</li>
                <li> Code runner (pour debuger) </li>
            </ul>
        </li>
    <h3><li>Le compilateur GCC (avec MingW64) à installer :</h3>
            <ul>
                <li> Se rendre sur ce <a href="https://github.com/niXman/mingw-builds-binaries">lien</a> et télécharger puis executer l'installer
                <img src ="Openclassroom/compilateur.png">
                Pendant l'installation choisir les options : 12.2.0, windows64, posix et rev2.
                 <br>Par la suite il faut préciser le PATH comme variable d'environnement dans Windows et vérifier l'installation du gcc dans le terminal, pour cela suivre cette <a href="https://www.youtube.com/watch?v=8Jc26cmTtKM&ab_channel=GeekyScript">vidéo</a> de à 4:22 à 6:45.
                </li>
            </ul>
        </li>
    <h3><li> Configurer l'extension C/C++</h3>
            <ul>
                <li> Il faut indiquer l'adresse du compilateur à utiliser (chez nous c'est gcc), pour se faire dans VS Code créer un fichier en .c et ajouter le code suivant:
                </li>
            </ul>
        </li>
</ol>

```C
#include <stdio.h>
int main(void){
    printf("Hello World!");
    return 0;
}
```
<p>Une erreure devrait être affiché à la première ligne, faites correction rapide puis première option.
Vous devrez être rediriger vers la page d'option de l'extension C/C++, il faut modifier l'option "Compiler PATH" et mettre la bonne adresse (tel que C:\mingw64\bin\gcc.exe), pour cela voir l'emplacement à laquelle vous avez installer le complilateur.

Un fichier "c_ccp_properties.json" devrait être crée avec vos propres option. Il faut faire attention à ne jamais commit ce fichier.

Afin de vérifier, lancer le programme test en .c "Hello World".</p>

<ul>
    <h3><li> Configurer aussi pour le serveur virtuel Linux Ubuntu </h3>
    </li>
    <p>Le compilateur gcc et l'extension pour visualiser les fichiers md sont déjà installé de base.
    Finalement, il suffit juste d'installer l'extension C/C++ ainsi que Code Runner.</p>
    <h3><li>Commande a éxécuter pour compiler</h3></li>
</ul>

```cmd
gcc fichier.c -o fichier (nom du fichier en sortie en .exe )
```
