leftkey$ = CHR$(0) + "K"
rightkey$ = CHR$(0) + "M"
upkey$ = CHR$(0) + "H"
downkey$ = CHR$(0) + "P"
enter$ = CHR$(13)
escape$ = CHR$(27)

DIM old(1000), picture(10000) AS INTEGER
FOR count% = 1 TO 10000
  picture(count%) = -1
NEXT

SCREEN 12
CLS
PRINT "-STAMP EDITOR-"
PRINT : PRINT "What do you want the length of your stamp to be?"
INPUT ">", length%
PRINT : PRINT "What do you want the height of your stamp to be?"
INPUT ">", height%
PRINT : PRINT "Please enter the physical value:"
INPUT ">", physical%
PRINT : PRINT "Press H for help."
PRINT "Any key to continue..."
SLEEP
WHILE INKEY$ <> "": WEND

SCREEN 13
framecount% = 0
x% = length% \ 2
y% = height% \ 2
c% = 15
 
idle:

  key$ = INKEY$
  IF key$ <> "" THEN framecount% = 0
  IF key$ = leftkey$ THEN x% = x% - 1
  IF key$ = rightkey$ THEN x% = x% + 1
  IF key$ = upkey$ THEN y% = y% - 1
  IF key$ = downkey$ THEN y% = y% + 1
  IF key$ = escape$ THEN
    GOTO ending
  END IF
  IF key$ = "x" THEN GOSUB coords
  IF key$ = "s" THEN GOSUB save
  IF key$ = "c" THEN GOSUB ChooseColor
  IF key$ = "o" THEN GOSUB openfile
  IF key$ = "h" THEN GOSUB help
  IF key$ = "n" THEN GOSUB new
  IF key$ = "f" THEN GOSUB flip
  IF key$ = "d" THEN GOSUB dimensions
  IF key$ = "r" THEN GOSUB rotate
  IF key$ = "v" THEN GOSUB flipvert
  IF key$ = "b" THEN GOSUB drawboth
  IF key$ = "l" AND x% > 0 AND x% <= length% AND y% > 0 AND y% <= height% THEN GOSUB drawline
  IF key$ = enter$ AND x% > 0 AND x% <= length% AND y% > 0 AND y% <= height% THEN
    temp% = (length% * (y% - 1)) + x%
    picture(temp%) = c%
  END IF

  framecount% = framecount% + 1
  IF framecount% > 10 THEN framecount% = 10
  IF framecount% <= 1 THEN
    CLS
    GOSUB frame
    GOSUB stamp
    GOSUB cursor
  END IF

GOTO idle

ending:
SCREEN 12
CLS
PRINT "This has been a Flyin' Hawaiian Production!"
END

frame:
FOR yput% = 0 TO height% + 1
  PSET (length% + 1, yput%), 15
NEXT
FOR xput% = 0 TO length% + 1
  PSET (xput%, height% + 1), 15
NEXT
FOR yput% = 0 TO height% + 1
  PSET (0, yput%), 15
NEXT
FOR xput% = 0 TO length% + 1
  PSET (xput%, 0), 15
NEXT
RETURN

stamp:
FOR xput% = 1 TO length%
  FOR yput% = 1 TO height%
    temp% = (length% * (yput% - 1)) + xput%
    temp% = picture(temp%)
    IF temp% <> -1 THEN PSET (xput%, yput%), temp%
  NEXT
NEXT
RETURN

cursor:
FOR count% = 1 TO 7
  xput% = count% + x%
  yput% = count% + y%
  IF count% <= 5 THEN
    PSET (xput%, y% + 1), 14
    PSET (x% + 1, yput%), 14
  END IF
  PSET (xput%, yput%), 14
NEXT
RETURN

save:
SCREEN 12
CLS
LOCATE 1, 37
PRINT "-SAVING-"
PRINT : PRINT "Please enter the filename that you want to save to:"
INPUT ">", file$
IF file$ = "" THEN file$ = "temp.pic"
IF INSTR(file$, ".") = 0 THEN file$ = file$ + ".pic"
OPEN file$ FOR OUTPUT AS #1
IF INSTR(file$, "guy") = 0 THEN PRINT #1, physical%
PRINT #1, length%
PRINT #1, height%
total% = length% * height%
FOR count% = 1 TO total%
  PRINT #1, picture(count%)
NEXT
CLOSE
SCREEN 13
RETURN

ChooseColor:
SCREEN 12
CLS
LOCATE 1, 34
PRINT "-CHOOSE COLOR-"
PRINT : PRINT " -1 Transparent"
FOR count% = 0 TO 15
  COLOR count%
  PRINT count%
NEXT
COLOR 15
  
PRINT : PRINT "Pick your color:"
INPUT ">", c%
WHILE c% < -1 OR c% > 15
  PRINT "Enter a value between -1 and 15:"
  INPUT ">", c%
WEND
SCREEN 13
RETURN

openfile:
SCREEN 12
CLS
PRINT "Enter the name of the file:"
INPUT ">", file$
IF file$ = "" THEN file$ = "temp.pic"
IF INSTR(file$, ".") = 0 THEN file$ = file$ + ".pic"
OPEN file$ FOR INPUT AS #1
IF INSTR(file$, "guy") = 0 THEN INPUT #1, physical%
INPUT #1, length%
INPUT #1, height%
total% = length% * height%
FOR count% = 1 TO total%
  INPUT #1, temp%
  picture(count%) = temp%
NEXT
CLOSE
SCREEN 13
RETURN

help:
SCREEN 12
CLS
LOCATE 1, 37
PRINT "-HELP-"
PRINT : PRINT "Here are your options:"
PRINT "H- help"
PRINT "L- fills with selected color from cursor down"
PRINT "B- fills with selected color in both directions sideways from cursor"
PRINT "C- choose color"
PRINT "S- save picture"
PRINT "O- open saved picture"
PRINT "F- flip picture horizontally"
PRINT "V- flip picture vertically"
PRINT "N- makes new stamp with selected color"
PRINT "D- change dimensions of stamp"
PRINT "R- rotate stamp (square stamps only)"
PRINT "Enter- draw with current color"
PRINT "Arrows- move cursor"
PRINT "Escape- quit"
SLEEP
SCREEN 13
RETURN

new:
total% = length% * height%
FOR xput% = 1 TO length%
  FOR yput% = 1 TO height%
    temp% = (length% * (yput% - 1)) + xput%
    picture(temp%) = c%
  NEXT
NEXT
RETURN

drawline:
temp% = (length% * (y% - 1)) + x%
temp% = picture(temp%)
fillc% = temp%
IF fillc% = c% THEN GOTO skip
yput% = y%
DO
  temp% = (length% * (yput% - 1)) + x%
  picture(temp%) = c%
  yput% = yput% + 1
  temp% = (length% * (yput% - 1)) + x%
  temp% = picture(temp%)
LOOP WHILE temp% = fillc% AND yput% <= height%
skip:
RETURN

coords:
CLS
temp% = (height% + 1) - y%
PRINT x%; temp%
SLEEP
RETURN

flip:
FOR count% = 1 TO total%
  old(count%) = picture(count%)
NEXT
FOR xcount% = 1 TO length%
  FOR ycount% = 1 TO height%
    oldsub% = (length% * (ycount% - 1)) + xcount%
    newsub% = (length% * (ycount% - 1)) + (length% - xcount% + 1)
    picture(newsub%) = old(oldsub%)
  NEXT
NEXT
RETURN
  
dimensions:
SCREEN 12
CLS
PRINT "Your stamp is currently"; length%; "pixels wide and"; height%; "pixels high."
PRINT : PRINT "Please enter your new width:"
INPUT ">", length%
PRINT "Please enter your new height:"
INPUT ">", height%
CLS
SCREEN 13
CLS
RETURN

rotate:
IF length% <> height% THEN RETURN
FOR count% = 1 TO total%
  old(count%) = picture(count%)
NEXT
FOR xcount% = 1 TO length%
  FOR ycount% = 1 TO height%
    oldsub% = (length% * (ycount% - 1)) + xcount%
    newsub% = (length% * (xcount% - 1)) + (height% + 1 - ycount%)
    picture(newsub%) = old(oldsub%)
  NEXT
NEXT
RETURN

flipvert:
FOR count% = 1 TO total%
  old(count%) = picture(count%)
NEXT
FOR xcount% = 1 TO length%
  FOR ycount% = 1 TO height%
    oldsub% = (length% * (ycount% - 1)) + xcount%
    newsub% = (length% * (height% + 1 - ycount% - 1)) + xcount%
    picture(newsub%) = old(oldsub%)
  NEXT
NEXT
RETURN

drawboth:
temp% = (length% * (y% - 1)) + x%
fillc% = picture(temp%)
IF fillc% = c% THEN RETURN
xput% = x%
DO
  temp% = (length% * (y% - 1)) + xput%
  picture(temp%) = c%
  xput% = xput% + 1
  temp% = (length% * (y% - 1)) + xput%
  temp% = picture(temp%)
LOOP WHILE temp% = fillc% AND xput% <= length%
xput% = x%
DO
  temp% = (length% * (y% - 1)) + xput%
  picture(temp%) = c%
  xput% = xput% - 1
  temp% = (length% * (y% - 1)) + xput%
  temp% = picture(temp%)
LOOP WHILE temp% = fillc% AND xput% >= 1
RETURN

