

*************IMPLEMENTATION***********************

At the start of the project Liam and I spent the first class deciding who did
what, our plan for implementation etc. As the project progressed we ended up modifying 
our plan here and there, and helping eachother get over problems we encountered. Our game
logic is quite simple, we just scan the 2-d array for available slots in correspondence to
the rules of the game. We expand our scan based on moves made to scan a larger area where
possible moves could arrive. We have quite a few functions working together to achieve this 
and we re-use that data to help change the disks once a move is made. We also re-use the 
scanned data to count our disks and print them at the end with the game result!


*********WORK DIVIDE****************************
Liam worked on Legal moves, selecting moves and disk placement.
Kevin worked on flipping disks, input/output and the game setup/startup.

FOR TECHNICAL COMMENTS SEE SOURCE CODE