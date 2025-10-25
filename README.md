Producer–Consumer Problem (C / Linux)

README Contents (short summary for GitHub)

Files in this repository:
- producer.c        : Source code for producer process
- consumer.c        : Source code for consumer process
- Documentation.txt : Detailed documentation and explanations (matches rubric)
- results.png       : Screenshot of example program output
- .gitignore        : Ignored files (executables, objects)

Usage (compile and run) — tested on Kent State server wasp.cs.kent.edu (VS Code Remote):
1. Compile:
   gcc producer.c -o producer -pthread -lrt -Wall
   gcc consumer.c -o consumer -pthread -lrt -Wall

2. Run both concurrently (single terminal background execution):
   ./producer & ./consumer 

