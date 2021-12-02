# Pong
## Created by Shawn Rodgers

### Description
Pong is an old game that is essentially a 2d version of ping pong. Each player has a paddle, and the players have to
deflect the ball to their opponent. I tried to make my implementation feel as much like the Atari version as possible. 
I even included the original sounds in the Atari pong game. 

### Setup instructions
This game only uses OpenGL and GLUT which we have been using in class, you need nothing else to run it. As long as 
`freeglut.dll` is in your debug folder and you properly configure `CMakeLists.txt` for your machine you should be able 
to run it with no problems. I did my best to make this work for apple machines but I'm not 100% confident it will 
compile for Mac OS users. If it won't, checkout my demo video linked below.

### How to play
When you first run the game, you arrive at the start screen. To begin playing, press the `spacebar`. You then begin the
game and have a few seconds to get ready. The ball will be initially served to either player so both players need
to be ready to hit it. The left player (player1) uses the `w` and `s` keys to move up and down. The right player (player2)
uses the `UP` and `DOWN` arrow keys to move up and down. The game will play until the score limit is reached. To 
adjust the score limit, change the variable `maxScore` that is declared at the top of `main.cpp`. It is initally
set to 5. Once the score limit is reached, the game will display the winner, and you can press `esc` to exit. You 
also have the option to toggle sound on and off at any point in the game by pressing `p`. 

Demo: https://www.youtube.com/watch?v=y6IxROSGxzc