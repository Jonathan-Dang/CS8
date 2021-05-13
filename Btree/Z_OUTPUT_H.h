#pragma once
/*

ALL TESTS VERIFIED

Int Test
=============================================================
Do you want to allow dups?
n

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
rrrrrrrr
Inserted: 41
[41]

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
Inserted: 467
[467]
[41]

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
Inserted: 334
   [467]
[334]
   [41]

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
Inserted: 500
   [500]
   [467]
[334]
   [41]

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
Inserted: 169
   [500]
   [467]
[334]
   [169]
   [41]

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
Inserted: 724
   [724]
[500]
   [467]
[334]
   [169]
   [41]

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
Inserted: 478
   [724]
[500]
   [478]
   [467]
[334]
   [169]
   [41]

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
Inserted: 358
       [724]
   [500]
       [478]
[467]
       [358]
   [334]
       [169]
       [41]

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
i
Input Value: 800
       [800]
       [724]
   [500]
       [478]
[467]
       [358]
   [334]
       [169]
       [41]

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
d
Delete Value: 334
       [800]
       [724]
   [500]
       [478]
[467]
       [358]
   [169]
       [41]

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
d
Delete Value: 500
       [800]
   [724]
       [478]
[467]
       [358]
   [169]
       [41]

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
d
Delete Value: 0
       [800]
   [724]
       [478]
[467]
       [358]
   [169]
       [41]

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
d
Delete Value: 467
   [800]
[724]
   [478]
[358]
   [169]
   [41]

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
d
Delete Value: 724
   [800]
[358]
   [478]
[169]
   [41]

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
s
Size: 5
   [800]
[358]
   [478]
[169]
   [41]

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
c
Search Value: 41
Value 41 is in the tree!
   [800]
[358]
   [478]
[169]
   [41]

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
l

[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it
x
===============================END===========================

----------------------------------------------------------------------------

String Test
=============================================================
Do you want to allow dups?
n

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
i
Input Value: a
[a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
i
Input Value: b
[b]
[a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
i
Input Value: c
   [c]
[b]
   [a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
i
Input Value: d
   [d]
   [c]
[b]
   [a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
i
Input Value: e
   [e]
[d]
   [c]
[b]
   [a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
i
Input Value: f
   [f]
   [e]
[d]
   [c]
[b]
   [a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
i
Input Value: g
       [g]
   [f]
       [e]
[d]
       [c]
   [b]
       [a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
d
Delete Value: d
   [g]
[f]
   [e]
[c]
   [b]
   [a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
i
Input Value: d
   [g]
[f]
   [e]
   [d]
[c]
   [b]
   [a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
l

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
i
Input Value: a
[a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
i
Input Value: b
[b]
[a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it

i
Input Value: c
   [c]
[b]
   [a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
i
Input Value: d
   [d]
   [c]
[b]
   [a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
i
Input Value: e
   [e]
[d]
   [c]
[b]
   [a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
i
Input Value: f
   [f]
   [e]
[d]
   [c]
[b]
   [a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
i
Input Value: g
       [g]
   [f]
       [e]
[d]
       [c]
   [b]
       [a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
c
Search Value: c
Value c is in the tree!
       [g]
   [f]
       [e]
[d]
       [c]
   [b]
       [a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
s
Size: 7
       [g]
   [f]
       [e]
[d]
       [c]
   [b]
       [a]

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
l

[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it
x
===============================END===========================
*/