Name: Abdullah Khan
Student #: 250907213
Group #: 35

***This is a guide on how to compile and run the individual parts of the program!

How to create the object files for each function:

Type the following command that corresponds to the function you would like into the terminal once you are in the proper directory.
This will generate the object file which is how you will run the program.

mymv: g++ mymv.cpp File.cpp File.h -o mymv
mycp: g++ mycp.cpp File.cpp File.h -o mycp
myls: g++ myls.cpp File.cpp File.h -o myls
mycat: g++ mycat.cpp File.cpp File.h -o mycat
myrm: g++ myrm.cpp File.cpp File.h -o myrm
mydiff: g++ mydiff.cpp File.cpp File.h -o mydiff
mystat: g++ mystat.cpp File.cpp File.h -o mystat

Once you have the the object file for the program called:
mymv
mycp
myls
mycat
myrm
mydiff
mystat

You can run the files by putting the './' in front. This is treated as your first argument for running the program.
For example: 
./mymv
./mycp
./myls
./mycat
./myrm
./mydiff
./mystat

Now here are the specific arguments you need to run the functionality of the program:
./mymv [oldname] [newname] 
./mymv [pathname1/oldname] [pathname2/newname]

./mycp [oldname] [newname]
./mycp [pathname1/oldname] [pathname2/newname]

./myls 
./myls [filename]
./myls [dirname]
./myls -l
./myls -l [filename]
./myls -l [dirname]

./mycat [filename1] [filename2] ... [n]

./myrm [filename1]

./mydiff [filename1] [filename2]

./mystat [filename]