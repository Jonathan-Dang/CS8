#pragma once
/*

ALL TESTS VERIFIED
===========================================================
PREVIEW TO HEAP
-----------------------------------------------------
|25| |13| |17| |8| |10| |14| |15|
-----------------------------------------------------

     [15]

  [17]

     [14]

[25]

     [10]

  [13]

     [8]

===========================================================
-----------------------------------------------------

-----------------------------------------------------
[R]andom  [I]nsert  [P]op     e[X]it:
r
Inserting 41
-----------------------------------------------------
|41|
-----------------------------------------------------

[41]
[R]andom  [I]nsert  [P]op     e[X]it:
r
Inserting 467
-----------------------------------------------------
|467| |41|
-----------------------------------------------------

[467]

  [41]
[R]andom  [I]nsert  [P]op     e[X]it:
r
Inserting 334
-----------------------------------------------------
|467| |41| |334|
-----------------------------------------------------

  [334]

[467]

  [41]
[R]andom  [I]nsert  [P]op     e[X]it:
r
Inserting 500
-----------------------------------------------------
|500| |467| |334| |41|
-----------------------------------------------------

  [334]

[500]

  [467]

     [41]
[R]andom  [I]nsert  [P]op     e[X]it:
r
Inserting 169
-----------------------------------------------------
|500| |467| |334| |41| |169|
-----------------------------------------------------

  [334]

[500]

     [169]

  [467]

     [41]
[R]andom  [I]nsert  [P]op     e[X]it:
r
Inserting 724
-----------------------------------------------------
|724| |467| |500| |41| |169| |334|
-----------------------------------------------------

  [500]

     [334]

[724]

     [169]

  [467]

     [41]
[R]andom  [I]nsert  [P]op     e[X]it:
rr
Inserting 478
-----------------------------------------------------
|724| |467| |500| |41| |169| |334| |478|
-----------------------------------------------------

     [478]

  [500]

     [334]

[724]

     [169]

  [467]

     [41]
[R]andom  [I]nsert  [P]op     e[X]it:
Inserting 358
-----------------------------------------------------
|724| |467| |500| |358| |169| |334| |478| |41|
-----------------------------------------------------

     [478]

  [500]

     [334]

[724]

     [169]

  [467]

     [358]

        [41]
[R]andom  [I]nsert  [P]op     e[X]it:
r
Inserting 962
-----------------------------------------------------
|962| |724| |500| |467| |169| |334| |478| |41| |358|
-----------------------------------------------------

     [478]

  [500]

     [334]

[962]

     [169]

  [724]

        [358]

     [467]

        [41]
[R]andom  [I]nsert  [P]op     e[X]it:
r
Inserting 464
-----------------------------------------------------
|962| |724| |500| |467| |464| |334| |478| |41| |358| |169|
-----------------------------------------------------

     [478]

  [500]

     [334]

[962]

     [464]

        [169]

  [724]

        [358]

     [467]

        [41]
[R]andom  [I]nsert  [P]op     e[X]it:
r
Inserting 705
-----------------------------------------------------
|962| |724| |500| |467| |705| |334| |478| |41| |358| |169| |464|
-----------------------------------------------------

     [478]

  [500]

     [334]

[962]

        [464]

     [705]

        [169]

  [724]

        [358]

     [467]

        [41]
[R]andom  [I]nsert  [P]op     e[X]it:
r
Inserting 145
-----------------------------------------------------
|962| |724| |500| |467| |705| |334| |478| |41| |358| |169| |464| |145|
-----------------------------------------------------

     [478]

  [500]

     [334]

        [145]

[962]

        [464]

     [705]

        [169]

  [724]

        [358]

     [467]

        [41]
[R]andom  [I]nsert  [P]op     e[X]it:
p
POPED: 962
-----------------------------------------------------
|145| |724| |500| |467| |705| |334| |478| |41| |358| |169| |464|
-----------------------------------------------------

     [478]

  [500]

     [334]

[145]

        [464]

     [705]

        [169]

  [724]

        [358]

     [467]

        [41]
[R]andom  [I]nsert  [P]op     e[X]it:
p
POPED: 145
-----------------------------------------------------
|464| |724| |500| |467| |705| |334| |478| |41| |358| |169|
-----------------------------------------------------

     [478]

  [500]

     [334]

[464]

     [705]

        [169]

  [724]

        [358]

     [467]

        [41]
[R]andom  [I]nsert  [P]op     e[X]it:
p
POPED: 464
-----------------------------------------------------
|169| |724| |500| |467| |705| |334| |478| |41| |358|
-----------------------------------------------------

     [478]

  [500]

     [334]

[169]

     [705]

  [724]

        [358]

     [467]

        [41]
[R]andom  [I]nsert  [P]op     e[X]it:
p
POPED: 169
-----------------------------------------------------
|358| |724| |500| |467| |705| |334| |478| |41|
-----------------------------------------------------

     [478]

  [500]

     [334]

[358]

     [705]

  [724]

     [467]

        [41]
[R]andom  [I]nsert  [P]op     e[X]it:
p
POPED: 358
-----------------------------------------------------
|41| |724| |500| |467| |705| |334| |478|
-----------------------------------------------------

     [478]

  [500]

     [334]

[41]

     [705]

  [724]

     [467]
[R]andom  [I]nsert  [P]op     e[X]it:
p
POPED: 41
-----------------------------------------------------
|478| |724| |500| |467| |705| |334|
-----------------------------------------------------

  [500]

     [334]

[478]

     [705]

  [724]

     [467]
[R]andom  [I]nsert  [P]op     e[X]it:
p
POPED: 478
-----------------------------------------------------
|334| |724| |500| |467| |705|
-----------------------------------------------------

  [500]

[334]

     [705]

  [724]

     [467]
[R]andom  [I]nsert  [P]op     e[X]it:
p
POPED: 334
-----------------------------------------------------
|705| |724| |500| |467|
-----------------------------------------------------

  [500]

[705]

  [724]

     [467]
[R]andom  [I]nsert  [P]op     e[X]it:
p
POPED: 705
-----------------------------------------------------
|467| |724| |500|
-----------------------------------------------------

  [500]

[467]

  [724]
[R]andom  [I]nsert  [P]op     e[X]it:
p
POPED: 467
-----------------------------------------------------
|500| |724|
-----------------------------------------------------

[500]

  [724]
[R]andom  [I]nsert  [P]op     e[X]it:
p
POPED: 500
-----------------------------------------------------
|724|
-----------------------------------------------------

[724]
[R]andom  [I]nsert  [P]op     e[X]it:
p
POPED: 724
-----------------------------------------------------

-----------------------------------------------------
[R]andom  [I]nsert  [P]op     e[X]it:
i
Please enter a number to Insert: 100
-----------------------------------------------------
|100|
-----------------------------------------------------

[100]
[R]andom  [I]nsert  [P]op     e[X]it:
i
Please enter a number to Insert: 1
-----------------------------------------------------
|100| |1|
-----------------------------------------------------

[100]

  [1]
[R]andom  [I]nsert  [P]op     e[X]it:
i
Please enter a number to Insert: 120
-----------------------------------------------------
|120| |1| |100|
-----------------------------------------------------

  [100]

[120]

  [1]
[R]andom  [I]nsert  [P]op     e[X]it:
p
POPED: 120
-----------------------------------------------------
|100| |1|
-----------------------------------------------------

[100]

  [1]
[R]andom  [I]nsert  [P]op     e[X]it:
p
POPED: 100
-----------------------------------------------------
|1|
-----------------------------------------------------

[1]
[R]andom  [I]nsert  [P]op     e[X]it:
p
POPED: 1
-----------------------------------------------------

-----------------------------------------------------
[R]andom  [I]nsert  [P]op     e[X]it:
x
==============================END==========================




*/