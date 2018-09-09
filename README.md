# Tris-Brute-Force-Solver
Generate all possible board positions in the game Tris. Calculate win rates for each board.
Tris is about the simplest meaningful game there is.\
There are 362880 (9!) board positions.\
This program uses inefficient recursion to create a tree that contains every possible position.\
Once the tree is created, the program propagates backward the outcome of the position, from the leaves to the root.\
The program than computes winrates for 'O' and 'X', creates a list, sort it and save it to file.\
The output is the database "tris.log" that contains boards and winrates.\
This 16MB log file contains about 550K board positions and is meant to be used as database to train a neural network.\
Tris obviously does not require a neural network to be solved. simple rules allow perfect play already.\
The Tris neural network is meant as an excercise.\
\
Sample output:\
//Tris game statistic\
//number of boards\
549946\
//Structure\
//&int[1] &<&char[9]&> &int[4]\
0,         ,58.5,28.8,362880,46080,212256,104544,\
1,    O    ,69.3,19.3,40320,4608,27936,7776,\
1,O        ,60.7,26.4,40320,5184,24480,10656,\
1,        O,60.7,26.4,40320,5184,24480,10656,\
1,      O  ,60.7,26.4,40320,5184,24480,10656,\
1,  O      ,60.7,26.4,40320,5184,24480,10656,\
1,     O   ,53.6,33.6,40320,5184,21600,13536,\
1,   O     ,53.6,33.6,40320,5184,21600,13536,\
1,       O ,53.6,33.6,40320,5184,21600,13536,\
1, O       ,53.6,33.6,40320,5184,21600,13536,\
2,    OX   ,72.9,15.7,5040,576,3672,792,\
2, X  O    ,72.9,15.7,5040,576,3672,792,\
2,    O  X ,72.9,15.7,5040,576,3672,792,\
2,   XO    ,72.9,15.7,5040,576,3672,792,\
2, X    O  ,68.6,25.7,5040,288,3456,1296,\
2,O      X ,68.6,25.7,5040,288,3456,1296,\
2,     XO  ,68.6,25.7,5040,288,3456,1296,\
2,  OX     ,68.6,25.7,5040,288,3456,1296,\
2,   X    O,68.6,25.7,5040,288,3456,1296,\
2,O    X   ,68.6,25.7,5040,288,3456,1296,\
2, X      O,68.6,25.7,5040,288,3456,1296,\
2,  O    X ,68.6,25.7,5040,288,3456,1296,\
2,  X O    ,65.7,22.9,5040,576,3312,1152,\
2,X   O    ,65.7,22.9,5040,576,3312,1152,\
2,    O X  ,65.7,22.9,5040,576,3312,1152,\
2,    O   X,65.7,22.9,5040,576,3312,1152,\
2, XO      ,64.3,18.6,5040,864,3240,936,\
2,       XO,64.3,18.6,5040,864,3240,936,\
2,O  X     ,64.3,18.6,5040,864,3240,936,\
2,     X  O,64.3,18.6,5040,864,3240,936,\
2,   X  O  ,64.3,18.6,5040,864,3240,936,\
2,  O  X   ,64.3,18.6,5040,864,3240,936,\
2,OX       ,64.3,18.6,5040,864,3240,936,\
2,      OX ,64.3,18.6,5040,864,3240,936,\
2, O X     ,60.0,28.6,5040,576,3024,1440,\
2, X   O   ,60.0,28.6,5040,576,3024,1440,\
2,     O X ,60.0,28.6,5040,576,3024,1440,\
2,   O   X ,60.0,28.6,5040,576,3024,1440,

<!DOCTYPE html>
    <head lang="en">
    <title>Sample document</title>
    <meta charset="utf-8">
    <style>
    body {
      margin: 2em auto;
      width: 90%;
      max-width: 30em;
      font-family: Verdana, Helvetica, sans-serif;
      }
    p {
      color: red;
      font-family: Georgia, "Times New Roman", serif;
      }
    </style>
    </head>
    <body>
    
    <h1>Sample Pages for Fun and Profit</h1>
    <p>This paragraph is red and in a different
    font! Woo-hoo!
    
    </body>
    </html>
