# 42-fractol  
Software computed fractals with pretty rainbow colors

Grade: 125/100

This is the code as it was upon closing the project and correcting it. There are a few minor issues that I have decided to leave as-is.

# Features  
-Mandelbrot  
-Julia  
-Burning ship  
-Rotating color palette (P key)  
-Lockable julia set for exploration (L key)  
-On-Mouse zoom with mousewheel (finicky sometimes)  
-Parametrable iteration level at startup (16 to 256)  
-(Naively) Threaded  

# Bugs and Issues  
-Two typos in program usage  
-Double free in main.c:26 if initialisation fails  
