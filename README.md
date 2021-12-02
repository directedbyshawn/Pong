# Pong

### Description
One of our assignments for my advanced programming class was to recreate an old school video game. I saw on Twitter that it was recently the 49th anniversary
of Atari releasing pong, so I thought it would be cool to recreate it. For those who don't know, pong is a basic digital implementation of ping pong / table tennis. It was the first
video game ever released by Atari, and digital ping pong was the first concept ever used for a video game. I wanted this to feel and look as close to the Atari version as possible. I 
used all the same sounds as Atari did and tried to keep the game play as similar as possible with a few small adjustments. Overall I am very happy with this project, and had fun creating 
it as I have very little experience with game development of any kind.

### Setup instructions
This game requires OpenGL and GLUT. I compiled the project using CMake, if you do the same you just need
to included `freeglut.dll` in your debug folder. I did my best to configure the project to work natively on both Windows and Mac OS (CMakeLists included), 
however I'm not 100% confident it will compile and run on anything other than Windows machines. 

### How to play
When you first run the game, you arrive at the start screen. To begin playing, press the `spacebar`. You then begin the
game and have a few seconds to get ready. The ball will be initially served to either player so both players need
to be ready to recieve the serve. The left player (player1) uses the `w` and `s` keys to move up and down. The right player (player2)
uses the `UP` and `DOWN` arrow keys to move up and down. The game will play until the score limit is reached. To 
adjust the score limit, change the variable `maxScore` that is initialized at the top of `main.cpp`. It is set to 5 by defualt. Once 
the score limit is reached, the game will display the winner, and you can press `esc` to exit. You 
also have the option to toggle sound on and off at any point in the game by pressing `p`.

<img src="https://srodgers.w3.uvm.edu/cs120/pong-images/pong.png" alt="game snapshot" style="width: 500px;">
