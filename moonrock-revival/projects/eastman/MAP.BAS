defaultstamp$ = "grass"
leftkey$ = CHR$(0) + "K"
rightkey$ = CHR$(0) + "M"
upkey$ = CHR$(0) + "H"
downkey$ = CHR$(0) + "P"
enter$ = CHR$(13)
escape$ = CHR$(27)

SCREEN 12
CLS

DIM coasti1(1000), coasti2(1000), coasti3(1000), coasti4(1000) AS INTEGER
DIM coasto1(1000), coasto2(1000), coasto3(1000), coasto4(1000) AS INTEGER
DIM coastsl(1000), coastsr(1000), coastsu(1000), coastsd(1000) AS INTEGER
DIM temp(1000), grass(1000), mountain(1000), water(1000) AS INTEGER
DIM town(1000), pavement(1000), bridgeh(1000), bridgev(1000) AS INTEGER
DIM map(77) AS STRING

PRINT "Loading..."

FOR stampcount% = 1 TO 12
  SELECT CASE stampcount%
  CASE 1
    OPEN "coasti1.pic" FOR INPUT AS #1
  CASE 2
    OPEN "coasti2.pic" FOR INPUT AS #1
  CASE 3
    OPEN "coasti3.pic" FOR INPUT AS #1
  CASE 4
    OPEN "coasti4.pic" FOR INPUT AS #1
  CASE 5
    OPEN "coasto1.pic" FOR INPUT AS #1
  CASE 6
    OPEN "coasto2.pic" FOR INPUT AS #1
  CASE 7
    OPEN "coasto3.pic" FOR INPUT AS #1
  CASE 8
    OPEN "coasto4.pic" FOR INPUT AS #1
  CASE 9
    OPEN "coastsu.pic" FOR INPUT AS #1
  CASE 10
    OPEN "coastsd.pic" FOR INPUT AS #1
  CASE 11
    OPEN "coastsl.pic" FOR INPUT AS #1
  CASE 12
    OPEN "coastsr.pic" FOR INPUT AS #1
  END SELECT
  INPUT #1, physical%
  INPUT #1, length%
  INPUT #1, height%
  total% = length% * height%
  FOR count% = 1 TO total%
    INPUT #1, temp%
    SELECT CASE stampcount%
    CASE 1
      coasti1(count%) = temp%
    CASE 2
      coasti2(count%) = temp%
    CASE 3
      coasti3(count%) = temp%
    CASE 4
      coasti4(count%) = temp%
    CASE 5
      coasto1(count%) = temp%
    CASE 6
      coasto2(count%) = temp%
    CASE 7
      coasto3(count%) = temp%
    CASE 8
      coasto4(count%) = temp%
    CASE 9
      coastsu(count%) = temp%
    CASE 10
      coastsd(count%) = temp%
    CASE 11
      coastsl(count%) = temp%
    CASE 12
      coastsr(count%) = temp%
    END SELECT
  NEXT
  CLOSE
NEXT

OPEN "bridgev.pic" FOR INPUT AS #1
INPUT #1, bridgevphysical%
INPUT #1, bridgevlength%
INPUT #1, bridgevheight%
bridgevtotal% = bridgevlength% * bridgevheight%
FOR count% = 1 TO bridgevtotal%
  INPUT #1, bridgev(count%)
NEXT
CLOSE

OPEN "bridgeh.pic" FOR INPUT AS #1
INPUT #1, bridgehphysical%
INPUT #1, bridgehlength%
INPUT #1, bridgehheight%
bridgehtotal% = bridgehlength% * bridgehheight%
FOR count% = 1 TO bridgehtotal%
  INPUT #1, bridgeh(count%)
NEXT
CLOSE

OPEN "pavement.pic" FOR INPUT AS #1
INPUT #1, pavementphysical%
INPUT #1, pavementlength%
INPUT #1, pavementheight%
pavementtotal% = pavementlength% * pavementheight%
FOR count% = 1 TO pavementtotal%
  INPUT #1, pavement(count%)
NEXT
CLOSE

OPEN "town.pic" FOR INPUT AS #1
INPUT #1, townphysical%
INPUT #1, townlength%
INPUT #1, townheight%
towntotal% = townlength% * townheight%
FOR count% = 1 TO towntotal%
  INPUT #1, town(count%)
NEXT
CLOSE

OPEN "grass.pic" FOR INPUT AS #1
INPUT #1, grassphysical%
INPUT #1, grasslength%
INPUT #1, grassheight%
grasstotal% = grasslength% * grassheight%
FOR count% = 1 TO grasstotal%
  INPUT #1, grass(count%)
NEXT
CLOSE

OPEN "mountain.pic" FOR INPUT AS #1
INPUT #1, mountainphysical%
INPUT #1, mountainlength%
INPUT #1, mountainheight%
mountaintotal% = mountainlength% * mountainheight%
FOR count% = 1 TO mountaintotal%
  INPUT #1, mountain(count%)
NEXT
CLOSE

OPEN "water.pic" FOR INPUT AS #1
INPUT #1, waterphysical%
INPUT #1, waterlength%
INPUT #1, waterheight%
watertotal% = waterlength% * waterheight%
FOR count% = 1 TO watertotal%
  INPUT #1, water(count%)
NEXT
CLOSE

SCREEN 13
CLS
FOR count% = 1 TO 77
  map(count%) = defaultstamp$
NEXT

xcursor% = 0
ycursor% = 0
framecount% = 0
quick$ = defaultstamp$

idle:

xlast% = xcursor%
ylast% = ycursor%

key$ = INKEY$
IF key$ <> "" THEN framecount% = 0
IF key$ = escape$ THEN GOTO ending
IF key$ = rightkey$ THEN xcursor% = xcursor% + 30
IF key$ = leftkey$ THEN xcursor% = xcursor% - 30
IF key$ = upkey$ THEN ycursor% = ycursor% - 30
IF key$ = downkey$ THEN ycursor% = ycursor% + 30
IF key$ = enter$ AND xcursor% >= 0 AND xcursor% < 320 AND ycursor% >= 0 AND ycursor% < 200 THEN GOSUB change
IF key$ = "s" THEN GOSUB save
IF key$ = "o" THEN GOSUB opensaved
IF key$ = "m" THEN quick$ = "mountain": GOSUB quick
IF key$ = "w" THEN quick$ = "water": GOSUB quick
IF key$ = "g" THEN quick$ = "grass": GOSUB quick
IF key$ = "t" THEN quick$ = "town": GOSUB quick
IF key$ = " " THEN GOSUB quick

IF xcursor% < 0 THEN xcursor% = xlast%
IF xcursor% >= 320 THEN xcursor% = xlast%
IF ycursor% < 0 THEN ycursor% = ylast%
IF ycursor% >= 200 THEN ycursor% = ylast%

framecount% = framecount% + 1
IF framecount% > 10 THEN framecount% = 10
IF framecount% <= 1 THEN
  GOSUB makemap
  GOSUB cursor
END IF

GOTO idle

ending:
SCREEN 12
CLS
 PRINT "This has been a Flyin' Hawaiian Production"
END

makemap:
FOR xmap% = 1 TO 11
  FOR ymap% = 1 TO 7
    subscript% = (11 * (ymap% - 1)) + xmap%
    current$ = map(subscript%)
    xmapput% = (xmap% * 30) - 30
    ymapput% = (ymap% * 30) - 30
    IF INSTR(current$, "coast") <> 0 THEN
      FOR xcount% = 1 TO 30
        FOR ycount% = 1 TO 30
          temp% = (30 * (ycount% - 1)) + xcount%
          temp$ = RIGHT$(current$, 2)
          SELECT CASE temp$
          CASE "i1"
            currentc% = coasti1(temp%)
          CASE "i2"
            currentc% = coasti2(temp%)
          CASE "i3"
            currentc% = coasti3(temp%)
          CASE "i4"
            currentc% = coasti4(temp%)
          CASE "o1"
            currentc% = coasto1(temp%)
          CASE "o2"
            currentc% = coasto2(temp%)
          CASE "o3"
            currentc% = coasto3(temp%)
          CASE "o4"
            currentc% = coasto4(temp%)
          CASE "sl"
            currentc% = coastsl(temp%)
          CASE "sr"
            currentc% = coastsr(temp%)
          CASE "su"
            currentc% = coastsu(temp%)
          CASE "sd"
            currentc% = coastsd(temp%)
          END SELECT
          xput% = xcount% + xmapput%
          yput% = ycount% + ymapput%
          IF currentc% <> -1 THEN PSET (xput%, yput%), currentc%
        NEXT
      NEXT
    END IF
    SELECT CASE current$
    CASE "bridgev"
      FOR xcount% = 1 TO bridgevlength%
        FOR ycount% = 1 TO bridgevheight%
          temp% = (bridgevlength% * (ycount% - 1)) + xcount%
          currentc% = bridgev(temp%)
          xput% = xcount% + xmapput%
          yput% = ycount% + ymapput% - (bridgevheight% - 30)
          IF currentc% <> -1 THEN PSET (xput%, yput%), currentc%
        NEXT
      NEXT
    CASE "bridgeh"
      FOR xcount% = 1 TO bridgehlength%
        FOR ycount% = 1 TO bridgehheight%
          temp% = (bridgehlength% * (ycount% - 1)) + xcount%
          currentc% = bridgeh(temp%)
          xput% = xcount% + xmapput%
          yput% = ycount% + ymapput% - (bridgehheight% - 30)
          IF currentc% <> -1 THEN PSET (xput%, yput%), currentc%
        NEXT
      NEXT
    CASE "pavement"
      FOR xcount% = 1 TO pavementlength%
        FOR ycount% = 1 TO pavementheight%
          temp% = (pavementlength% * (ycount% - 1)) + xcount%
          currentc% = pavement(temp%)
          xput% = xcount% + xmapput%
          yput% = ycount% + ymapput% - (pavementheight% - 30)
          IF currentc% <> -1 THEN PSET (xput%, yput%), currentc%
        NEXT
      NEXT
    CASE "grass"
      FOR xcount% = 1 TO grasslength%
        FOR ycount% = 1 TO grassheight%
          temp% = (grasslength% * (ycount% - 1)) + xcount%
          currentc% = grass(temp%)
          xput% = xcount% + xmapput%
          yput% = ycount% + ymapput% - (grassheight% - 30)
          IF currentc% <> -1 THEN PSET (xput%, yput%), currentc%
        NEXT
      NEXT
    CASE "mountain"
      FOR xcount% = 1 TO mountainlength%
        FOR ycount% = 1 TO mountainheight%
          temp% = (mountainlength% * (ycount% - 1)) + xcount%
          currentc% = mountain(temp%)
          xput% = xcount% + xmapput%
          yput% = ycount% + ymapput% - (mountainheight% - 30)
          IF currentc% <> -1 THEN PSET (xput%, yput%), currentc%
        NEXT
      NEXT
    CASE "water"
      FOR xcount% = 1 TO waterlength%
        FOR ycount% = 1 TO waterheight%
          temp% = (waterlength% * (ycount% - 1)) + xcount%
          currentc% = water(temp%)
          xput% = xcount% + xmapput%
          yput% = ycount% + ymapput% - (waterheight% - 30)
          IF currentc% <> -1 THEN PSET (xput%, yput%), currentc%
        NEXT
      NEXT
    CASE "town"
      FOR xcount% = 1 TO townlength%
        FOR ycount% = 1 TO townheight%
          temp% = (townlength% * (ycount% - 1)) + xcount%
          currentc% = town(temp%)
          xput% = xcount% + xmapput%
          yput% = ycount% + ymapput% - (townheight% - 30)
          IF currentc% <> -1 THEN PSET (xput%, yput%), currentc%
        NEXT
      NEXT
    END SELECT
  NEXT
NEXT
RETURN

cursor:
LINE (xcursor% + 1, ycursor% + 1)-(xcursor% + 30, ycursor% + 1), 14
LINE (xcursor% + 1, ycursor% + 1)-(xcursor% + 1, ycursor% + 30), 14
LINE (xcursor% + 30, ycursor% + 1)-(xcursor% + 30, ycursor% + 30), 14
LINE (xcursor% + 1, ycursor% + 30)-(xcursor% + 30, ycursor% + 30), 14
RETURN

change:
xmap% = (xcursor% + 30) \ 30
ymap% = (ycursor% + 30) \ 30
subscript% = (11 * (ymap% - 1)) + xmap%
oldname$ = map(subscript%)

OPEN "left.pic" FOR INPUT AS #1
INPUT #1, templength%
INPUT #1, tempheight%
temptotal% = templength% * tempheight%
FOR count% = 1 TO temptotal%
  INPUT #1, temp(count%)
NEXT
FOR xcount% = 1 TO templength%
  FOR ycount% = 1 TO tempheight%
    temp% = (templength% * (ycount% - 1)) + xcount%
    temp% = temp(temp%)
    xput% = xcount% + (xcursor% - 15)
    yput% = ycount% + ycursor%
    IF temp% <> -1 THEN PSET (xput%, yput%), temp%
  NEXT
NEXT
CLOSE
OPEN "right.pic" FOR INPUT AS #1
INPUT #1, templength%
INPUT #1, tempheight%
temptotal% = templength% * tempheight%
FOR count% = 1 TO temptotal%
  INPUT #1, temp(count%)
NEXT
FOR xcount% = 1 TO templength%
  FOR ycount% = 1 TO tempheight%
    temp% = (templength% * (ycount% - 1)) + xcount%
    temp% = temp(temp%)
    xput% = xcount% + (xcursor% + 30)
    yput% = ycount% + ycursor%
    IF temp% <> -1 THEN PSET (xput%, yput%), temp%
  NEXT
NEXT
CLOSE

newname$ = oldname$
key$ = ""
WHILE key$ <> enter$
  IF INSTR(newname$, "coast") <> 0 THEN
    FOR xcount% = 1 TO 30
      FOR ycount% = 1 TO 30
        temp% = (30 * (ycount% - 1)) + xcount%
        SELECT CASE RIGHT$(newname$, 2)
        CASE "i1"
          currentc% = coasti1(temp%)
        CASE "i2"
          currentc% = coasti2(temp%)
        CASE "i3"
          currentc% = coasti3(temp%)
        CASE "i4"
          currentc% = coasti4(temp%)
        CASE "o1"
          currentc% = coasto1(temp%)
        CASE "o2"
          currentc% = coasto2(temp%)
        CASE "o3"
          currentc% = coasto3(temp%)
        CASE "o4"
          currentc% = coasto4(temp%)
        CASE "sl"
          currentc% = coastsl(temp%)
        CASE "sr"
          currentc% = coastsr(temp%)
        CASE "su"
          currentc% = coastsu(temp%)
        CASE "sd"
          currentc% = coastsd(temp%)
        END SELECT
        xput% = xcount% + xcursor%
        yput% = ycount% + ycursor%
        IF currentc% <> -1 THEN PSET (xput%, yput%), currentc%
      NEXT
    NEXT
  END IF
  SELECT CASE newname$
  CASE "bridgev"
    FOR xcount% = 1 TO bridgevlength%
      FOR ycount% = 1 TO bridgevheight%
        temp% = (bridgevlength% * (ycount% - 1)) + xcount%
        currentc% = bridgev(temp%)
        xput% = xcount% + xcursor%
        yput% = ycount% + ycursor% - (bridgevheight% - 30)
        IF currentc% <> -1 THEN PSET (xput%, yput%), currentc%
      NEXT
    NEXT
  CASE "bridgeh"
    FOR xcount% = 1 TO bridgehlength%
      FOR ycount% = 1 TO bridgehheight%
        temp% = (bridgehlength% * (ycount% - 1)) + xcount%
        currentc% = bridgeh(temp%)
        xput% = xcount% + xcursor%
        yput% = ycount% + ycursor% - (bridgehheight% - 30)
        IF currentc% <> -1 THEN PSET (xput%, yput%), currentc%
      NEXT
    NEXT
  CASE "pavement"
    FOR xcount% = 1 TO pavementlength%
      FOR ycount% = 1 TO pavementheight%
        temp% = (pavementlength% * (ycount% - 1)) + xcount%
        currentc% = pavement(temp%)
        xput% = xcount% + xcursor%
        yput% = ycount% + ycursor% - (pavementheight% - 30)
        IF currentc% <> -1 THEN PSET (xput%, yput%), currentc%
      NEXT
    NEXT
  CASE "grass"
    FOR xcount% = 1 TO grasslength%
      FOR ycount% = 1 TO grassheight%
        temp% = (grasslength% * (ycount% - 1)) + xcount%
        currentc% = grass(temp%)
        xput% = xcount% + xcursor%
        yput% = ycount% + ycursor% - (grassheight% - 30)
        IF currentc% <> -1 THEN PSET (xput%, yput%), currentc%
      NEXT
    NEXT
  CASE "mountain"
    FOR xcount% = 1 TO mountainlength%
      FOR ycount% = 1 TO mountainheight%
        temp% = (mountainlength% * (ycount% - 1)) + xcount%
        currentc% = mountain(temp%)
        xput% = xcount% + xcursor%
        yput% = ycount% + ycursor% - (mountainheight% - 30)
        IF currentc% <> -1 THEN PSET (xput%, yput%), currentc%
      NEXT
    NEXT
  CASE "water"
    FOR xcount% = 1 TO waterlength%
      FOR ycount% = 1 TO waterheight%
        temp% = (waterlength% * (ycount% - 1)) + xcount%
        currentc% = water(temp%)
        xput% = xcount% + xcursor%
        yput% = ycount% + ycursor% - (waterheight% - 30)
        IF currentc% <> -1 THEN PSET (xput%, yput%), currentc%
      NEXT
    NEXT
  CASE "town"
    FOR xcount% = 1 TO townlength%
      FOR ycount% = 1 TO townheight%
        temp% = (townlength% * (ycount% - 1)) + xcount%
        currentc% = town(temp%)
        xput% = xcount% + xcursor%
        yput% = ycount% + ycursor% - (townheight% - 30)
        IF currentc% <> -1 THEN PSET (xput%, yput%), currentc%
      NEXT
    NEXT
  END SELECT
  lastname$ = newname$
  key$ = INKEY$
  WHILE lastname$ = newname$ AND key$ <> enter$
    IF key$ = escape$ THEN GOTO ending
    IF key$ = leftkey$ OR key$ = upkey$ THEN
      SELECT CASE newname$
      CASE "grass"
        newname$ = "coastsu"
      CASE "mountain"
        newname$ = "grass"
      CASE "pavement"
        newname$ = "mountain"
      CASE "town"
        newname$ = "pavement"
      CASE "water"
        newname$ = "town"
      CASE "bridgev"
        newname$ = "water"
      CASE "bridgeh"
        newname$ = "bridgev"
      CASE "coasti1"
        newname$ = "bridgeh"
      CASE "coasti2"
        newname$ = "coasti1"
      CASE "coasti3"
        newname$ = "coasti2"
      CASE "coasti4"
        newname$ = "coasti3"
      CASE "coasto1"
        newname$ = "coasti4"
      CASE "coasto2"
        newname$ = "coasto1"
      CASE "coasto3"
        newname$ = "coasto2"
      CASE "coasto4"
        newname$ = "coasto3"
      CASE "coastsl"
        newname$ = "coasto4"
      CASE "coastsr"
        newname$ = "coastsl"
      CASE "coastsd"
        newname$ = "coastsr"
      CASE "coastsu"
        newname$ = "coastsd"
      END SELECT
    END IF
    IF key$ = rightkey$ OR key$ = downkey$ THEN
      SELECT CASE newname$
      CASE "grass"
        newname$ = "mountain"
      CASE "mountain"
        newname$ = "pavement"
      CASE "pavement"
        newname$ = "town"
      CASE "town"
        newname$ = "bridgev"
      CASE "bridgev"
        newname$ = "bridgeh"
      CASE "bridgeh"
        newname$ = "water"
      CASE "water"
        newname$ = "coasti1"
      CASE "coasti1"
        newname$ = "coasti2"
      CASE "coasti2"
        newname$ = "coasti3"
      CASE "coasti3"
        newname$ = "coasti4"
      CASE "coasti4"
        newname$ = "coasto1"
      CASE "coasto1"
        newname$ = "coasto2"
      CASE "coasto2"
        newname$ = "coasto3"
      CASE "coasto3"
        newname$ = "coasto4"
      CASE "coasto4"
        newname$ = "coastsl"
      CASE "coastsl"
        newname$ = "coastsr"
      CASE "coastsr"
        newname$ = "coastsd"
      CASE "coastsd"
        newname$ = "coastsu"
      CASE "coastsu"
        newname$ = "grass"
      END SELECT
    END IF
    key$ = INKEY$
  WEND
WEND
map(subscript%) = newname$
quick$ = newname$
RETURN

save:
SCREEN 12
CLS
LOCATE 1, 37
PRINT "-SAVE-"
PRINT : PRINT "Please enter the name of the file that you want to save to:"
INPUT ">", file$
IF file$ = "" THEN file$ = "temp.map"
IF INSTR(file$, ".") = 0 THEN file$ = file$ + ".map"
OPEN file$ FOR OUTPUT AS #1
PRINT #1, "11"
PRINT #1, "7"
FOR count% = 1 TO 77
  PRINT #1, map(count%)
NEXT
CLOSE
SCREEN 13
CLS
RETURN

opensaved:
SCREEN 12
CLS
LOCATE 1, 37
PRINT "-OPEN-"
PRINT : PRINT "Please enter the name of the file that you want to open:"
INPUT ">", file$
IF file$ = "" THEN file$ = "temp.map"
IF INSTR(file$, ".") = 0 THEN file$ = file$ + ".map"
OPEN file$ FOR INPUT AS #1
INPUT #1, maplength%
INPUT #1, mapheight%
FOR count% = 1 TO 77
  INPUT #1, map(count%)
NEXT
CLOSE
SCREEN 13
CLS
RETURN

quick:
xmap% = (xcursor% + 30) \ 30
ymap% = (ycursor% + 30) \ 30
subscript% = (11 * (ymap% - 1)) + xmap%
map(subscript%) = quick$
RETURN

