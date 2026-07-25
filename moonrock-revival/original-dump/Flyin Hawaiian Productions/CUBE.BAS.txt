SCREEN 12
RANDOMIZE (TIMER)
leftkey$ = CHR$(0) + "K": rightkey$ = CHR$(0) + "M"
upkey$ = CHR$(0) + "H": downkey$ = CHR$(0) + "P"
enter$ = CHR$(13): escape$ = CHR$(27)

TYPE angles
  xth AS DOUBLE
  yth AS DOUBLE
END TYPE

TYPE displacement
  x AS DOUBLE
  y AS DOUBLE
  z AS DOUBLE
END TYPE

TYPE screenPoint
  x AS DOUBLE
  y AS DOUBLE
END TYPE

TYPE vertice
  x AS DOUBLE
  y AS DOUBLE
  z AS DOUBLE
END TYPE

DIM disp(8) AS screenPoint
DIM cube(8) AS vertice
DIM location AS displacement
DIM eye AS angles
DIM order(24), xi, yi, zi, i, j, k, side, corner AS INTEGER
DIM radius, pi, th, xth, yth AS DOUBLE

GOSUB orderinit

pi = 3.141592654#

new:

i = 0
FOR xi = -5 TO 5 STEP 10
  FOR yi = -5 TO 5 STEP 10
    FOR zi = -5 TO 5 STEP 10
      i = i + 1
      cube(i).x = xi
      cube(i).y = yi
      cube(i).z = zi
    NEXT
  NEXT
NEXT

location.x = (RND * 20) - 10
location.y = (RND * 20) - 10
location.z = (RND * 20) - 10
FOR i = 1 TO 8
  cube(i).x = cube(i).x + location.x
  cube(i).y = cube(i).y + location.y
  cube(i).z = cube(i).z + location.z
NEXT
new! = TIMER
axis% = INT(RND * 3) + 1
IF INT(RND * 2) + 1 = 1 THEN d! = pi / 50 ELSE d! = pi / -50
colour% = INT(RND * 14) + 1

idle:

IF TIMER >= new! + 10 THEN GOTO new

IF axis% = 1 THEN GOSUB xspin
IF axis% = 2 THEN GOSUB yspin
IF axis% = 3 THEN GOSUB zspin

FOR i = 1 TO 8
  xth = cube(i).x / (cube(i).z + 25)
  yth = cube(i).y / (cube(i).z + 25)
  xth = xth - eye.xth
  yth = yth + eye.yth
  disp(i).x = (xth * 320) + 320
  disp(i).y = (yth * 240) + 240
NEXT

CLS
GOSUB render
'GOSUB dot

start! = TIMER
WHILE TIMER < start! + .01: WEND

key$ = INKEY$

IF key$ = upkey$ THEN eye.yth = eye.yth + (pi / 25)
IF key$ = downkey$ THEN eye.yth = eye.yth - (pi / 25)
IF key$ = leftkey$ THEN eye.xth = eye.xth - (pi / 25)
IF key$ = rightkey$ THEN eye.xth = eye.xth + (pi / 25)
IF key$ = enter$ THEN
  eye.xth = 0
  eye.yth = 0
END IF
IF key$ <> escape$ THEN GOTO idle

CLS
PRINT "This has been a Flyin' Hawaiian Production"
END


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

render:
FOR i = 1 TO 4
  j = i + 4
  LINE (disp(i).x, disp(i).y)-(disp(j).x, disp(j).y), colour%
NEXT
FOR i = 1 TO 2
  j = i + 2
  LINE (disp(i).x, disp(i).y)-(disp(j).x, disp(j).y), colour%
  k = i + 4
  j = k + 2
  LINE (disp(k).x, disp(k).y)-(disp(j).x, disp(j).y), colour%
NEXT
FOR i = 1 TO 7 STEP 2
  j = i + 1
  LINE (disp(i).x, disp(i).y)-(disp(j).x, disp(j).y), colour%
NEXT
RETURN

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

xspin:
FOR i = 1 TO 8
  th = ATN((cube(i).y - location.y) / (cube(i).z - location.z))
  IF (cube(i).y - location.y) > 0 AND (cube(i).z - location.z) < 0 THEN th = th + pi
  IF (cube(i).y - location.y) < 0 AND (cube(i).z - location.z) < 0 THEN th = th + pi
  th = th + d!
  cube(i).z = COS(th) * 10 + location.z
  cube(i).y = SIN(th) * 10 + location.y
NEXT
RETURN

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

yspin:
FOR i = 1 TO 8
  th = ATN((cube(i).z - location.z) / (cube(i).x - location.x))
  IF (cube(i).z - location.z) > 0 AND (cube(i).x - location.x) < 0 THEN th = th + pi
  IF (cube(i).z - location.z) < 0 AND (cube(i).x - location.x) < 0 THEN th = th + pi
  th = th + d!
  cube(i).x = COS(th) * 10 + location.x
  cube(i).z = SIN(th) * 10 + location.z
NEXT
RETURN

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

zspin:
FOR i = 1 TO 8
  th = ATN((cube(i).y - location.y) / (cube(i).x - location.x))
  IF (cube(i).y - location.y) > 0 AND (cube(i).x - location.x) < 0 THEN th = th + pi
  IF (cube(i).y - location.y) < 0 AND (cube(i).x - location.x) < 0 THEN th = th + pi
  th = th + d!
  cube(i).x = COS(th) * 10 + location.x
  cube(i).y = SIN(th) * 10 + location.y
NEXT
RETURN

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

dot:
i = 0
FOR side = 1 TO 6
  xsum! = 0: ysum! = 0: zsum! = 0: xdist! = 0: ydist! = 0
  FOR corner = 1 TO 4
    i = i + 1
    xsum! = xsum! + disp(order(i)).x
    ysum! = ysum! + disp(order(i)).y
    zsum! = zsum! + cube(order(i)).z
    IF i MOD 4 = corner THEN PRINT "equal!"
    IF i MOD 4 = 1 OR i MOD 4 = 2 THEN xdist! = xdist! + (disp(order(i + 2)).x - disp(order(i)).x)
    IF i MOD 4 = 1 OR i MOD 4 = 2 THEN ydist! = ydist! + (disp(order(i + 2)).y - disp(order(i)).y)
  NEXT
  PSET (xsum! / 4, ysum! / 4), 14
  CIRCLE (xsum! / 4, ysum! / 4), 10 - (zsum! / 4), 14
  CIRCLE (xsum! / 4, ysum! / 4), 10 - (zsum! / 4), 14, , , (ydist! / 2) / (xdist! / 2)
NEXT
RETURN

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

orderinit:
FOR i = 1 TO 24
  IF i >= 1 AND i <= 4 THEN order(i) = i
  IF i >= 5 AND i <= 8 THEN order(i) = i
  IF i >= 9 AND i <= 10 THEN order(i) = i - 6
  IF i >= 11 AND i <= 12 THEN order(i) = i - 4
  IF i >= 13 AND i <= 14 THEN order(i) = i - 12
  IF i >= 15 AND i <= 16 THEN order(i) = i - 10
  SELECT CASE i
    CASE 17
    order(i) = 1
    CASE 18
    order(i) = 3
    CASE 19
    order(i) = 5
    CASE 20
    order(i) = 7
    CASE 21
    order(i) = 2
    CASE 22
    order(i) = 4
    CASE 23
    order(i) = 6
    CASE 24
    order(i) = 8
  END SELECT
NEXT
k = 0
FOR i = 1 TO 6
  FOR j = 1 TO 4
    k = k + 1
    LOCATE j, i * 3
    PRINT order(k)
  NEXT
  PRINT
NEXT
RETURN

