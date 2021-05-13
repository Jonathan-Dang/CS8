#pragma once
/*
================================================
BEGIN TREE NODE FUNCTION TESTS!~
Initialized tree noded
            [30]
                [20]
                    [9]
        [9]
            [6]
    [5]
        [4]
 [4]
        [1]
    [-20]
Searching for number 1!
FOUND: |1|
Searching for -50!
FOUND: 00000000
if 0, then its not in the tree!
Removing the right most leaf node!
MAX VALUE: 30|
            [20]
                [9]
        [9]
            [6]
    [5]
        [4]
 [4]
        [1]
    [-20]
Removing number 20!
SUCCESS!
            [9]
        [9]
            [6]
    [5]
        [4]
 [4]
        [1]
    [-20]
Removing number 20!
FAIL!
            [9]
        [9]
            [6]
    [5]
        [4]
 [4]
        [1]
    [-20]
Copying t to temp!
This is T
================================
            [9]
        [9]
            [6]
    [5]
        [4]
 [4]
        [1]
    [-20]
===============================
This is Temp
================================
            [9]
        [9]
            [6]
    [5]
        [4]
 [4]
        [1]
    [-20]
================================
Tree_ADD function!
NEW T:
================================
                    [9]
                [9]
            [9]
        [9]
                [6]
            [6]
                [5]
    [5]
                [4]
            [4]
        [4]
 [4]
            [1]
        [1]
            [-20]
    [-20]
================================
CLEARING BOTH TREES!
This is T
================================
===============================
This is Temp
================================
================================
TREE FROM SORTED LIST!
            [9]
        [8]
    [7]
            [6]
        [5]
 [4]
            [3]
        [2]
    [1]
        [0]

END OF TESTING
END OF TREE NODE FUNCTION TESTS!
================================================
BEGIN TREE CLASS TESTING!
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
r
 [41]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
r
    [67]
 [41]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
r
    [67]
 [41]
    [34]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
r
    [67]
 [41]
    [34]
        [0]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
r
        [69]
    [67]
 [41]
    [34]
        [0]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
r
        [69]
    [67]
 [41]
    [34]
            [24]
        [0]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
r
            [78]
        [69]
    [67]
 [41]
    [34]
            [24]
        [0]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
r
            [78]
        [69]
    [67]
        [58]
 [41]
    [34]
            [24]
        [0]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
r
            [78]
        [69]
    [67]
            [62]
        [58]
 [41]
    [34]
            [24]
        [0]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
r
            [78]
        [69]
    [67]
                [64]
            [62]
        [58]
 [41]
    [34]
            [24]
        [0]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
i
Please enter a number to Insert: 100
                [100]
            [78]
        [69]
    [67]
                [64]
            [62]
        [58]
 [41]
    [34]
            [24]
        [0]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
i
Please enter a number to Insert: -100
                [100]
            [78]
        [69]
    [67]
                [64]
            [62]
        [58]
 [41]
    [34]
            [24]
        [0]
            [-100]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
i
Please enter a number to Insert: 57
                [100]
            [78]
        [69]
    [67]
                [64]
            [62]
        [58]
            [57]
 [41]
    [34]
            [24]
        [0]
            [-100]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
s
Please Enter a number to Search: -100
FOUND!
 Input found at Height: 0
                [100]
            [78]
        [69]
    [67]
                [64]
            [62]
        [58]
            [57]
 [41]
    [34]
            [24]
        [0]
            [-100]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
s
Please Enter a number to Search: 34
FOUND!
 Input found at Height: 2
                [100]
            [78]
        [69]
    [67]
                [64]
            [62]
        [58]
            [57]
 [41]
    [34]
            [24]
        [0]
            [-100]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
s
Please Enter a number to Search: 78
FOUND!
 Input found at Height: 1
                [100]
            [78]
        [69]
    [67]
                [64]
            [62]
        [58]
            [57]
 [41]
    [34]
            [24]
        [0]
            [-100]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
e
Please Enter a number to Erase: 69
            [100]
        [78]
    [67]
                [64]
            [62]
        [58]
            [57]
 [41]
    [34]
            [24]
        [0]
            [-100]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
e
Please Enter a number to Erase: 57
            [100]
        [78]
    [67]
        [58]
 [41]
    [34]
            [24]
        [0]
            [-100]
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
c
[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it:
x
END OF TREE CLASS TESTING!
=========================END====================

*/