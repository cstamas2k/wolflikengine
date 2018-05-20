# wolflikeengine

simple wolf3d-like engine using only SDL2 and basic c++

no textures (yet), no gui, just the pure wall&sky&ceiling renderer and user control

# usage
game controls: 
              delete: strafe left
              pgdown: strafe right
              arrow keys: move
map editor controls:
                    arrow keys: move selection
                    q: delete block
                    d: door block
                    e: door entry block (from where you can open the door)
                    w: wall block
                    1: open "map1.dat" file
                    2: save to "map1.dat" file

# the game is undergoing redesign at the moment.

you can view a minimalist version of it under the "rewrite" branch (it was writed on debian, so it will work on linux)

meanwhile i want to fully rewrite the master branch, add sprites, textures etc

