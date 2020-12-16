TP3


////////////////////////////////////////////////////////////////////////////////

Architecture :                          x86_64

Mode(s) opératoire(s) des processeurs : 32-bit, 64-bit

Boutisme :                              Little Endian

Processeur(s) :                         2

Liste de processeur(s) en ligne :       0,1

Thread(s) par cœur :                    1

Cœur(s) par socket :                    2

Socket(s) :                             1

Nœud(s) NUMA :                          1

Identifiant constructeur :              GenuineIntel

Famille de processeur :                 6

Modèle :                                158

Nom de modèle :                         Intel(R) Core(TM) i5-8300H CPU @ 2.30GHz

Révision :                              10

Vitesse du processeur en MHz :          2304.000

BogoMIPS :                              4608.00

Constructeur d'hyperviseur :            KVM

Type de virtualisation :                complet

Cache L1d :                             32K

Cache L1i :                             32K

Cache L2 :                              256K

Cache L3 :                              8192K

Nœud NUMA 0 de processeur(s) :          0,1

////////////////////////////////////////////////////////////////////////////////

PRODUIT SCALAIRE

N = 100 000
nbSamples = 1024

TEMPS DE CALCUL = temps assemblage vecteurs + temps produits scalaires + temps sommation

OMP_NUM_THREADS | TEMPS DE CALCUL | ACCELERATION

      1         |      0.74       |      1     
 
      2         |      0.72       |      1.03

      4         |      0.82       |      0.90

      8         |      0.82       |      0.90

L'accélération ne change presque pas, elle devient même inférieure à 1

La parallélisation ne fonctionne pas

OMP_NUM_THREADS | TEMPS DE CALCUL | ACCELERATION

      1         |      0.82       |      1    
      
      2         |      0.84       |      0.98
      
      4         |      0.81       |      1.01
      
      8         |      0.83       |      0.99

L'accélération reste à 1

Je ne sais pas pourquoi la parallélisation ne fonctionne pas

////////////////////////////////////////////////////////////////////////////////
