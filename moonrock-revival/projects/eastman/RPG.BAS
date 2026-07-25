DIM pavement(1000), bridgev(1000) AS INTEGER
DIM coasti1(1000), coasti2(1000), coasti3(1000), coasti4(1000) AS INTEGER
DIM coasto1(1000), coasto2(1000), coasto3(1000), coasto4(1000) AS INTEGER
DIM coastsl(1000), coastsr(1000), coastsu(1000), coastsd(1000) AS INTEGER
DIM back(16000), grass(1000), mountain(1000), bridgeh(1000) AS INTEGER
DIM eraseguy(1000), water(1000), town(1000), physicalmap(77)  AS INTEGER
DIM guyfl(500), guyfr(500), guybl(500), guybr(500) AS INTEGER
DIM guyll(500), guylr(500), guyrl(500), guyrr(500) AS INTEGER
DIM townmap(77) AS STRING
DIM map(77) AS STRING

SCREEN 7, 0, 1, 1
PRINT "Loading..."
SCREEN 7, 0, 0, 1
GOSUB load
GOSUB background
GET (1, 1)-(320, 200), back
SCREEN 7, 0, 0, 0
CLS

x% = -1
y% = -1
FOR xmap% = 1 TO 11
  FOR ymap% = 1 TO 7
    mapsub% = (11 * (ymap% - 1)) + xmap%
    IF physicalmap(mapsub%) = 0 AND x% = -1 THEN
      x% = ((xmap% - 1) * 30) + 5
      y% = ((ymap% - 1) * 30) + 5
    END IF
  NEXT
NEXT
IF x% = -1 AND y% = -1 THEN
  SCREEN 12
  CLS
  PRINT "There isn't anywhere to stand on this map."
  WHILE INKEY$ <> "": WEND
  SLEEP
  GOTO ending
END IF

direction$ = "down"
stepstart! = TIMER
stepswitch% = 1
stepspeed% = 4
speed% = 1

currentscreen% = 0
xlast% = x%
ylast% = y%
PUT (0, 0), back
GET (x%, y%)-(x% + 20, y% + 20), eraseguy
GOSUB guy

idle:

xlast% = x%
ylast% = y%

key$ = INKEY$
IF INSTR(key$, leftkey$) <> 0 THEN x% = x% - speed%: direction$ = "left"
IF INSTR(key$, rightkey$) <> 0 THEN x% = x% + speed%: direction$ = "right"
IF INSTR(key$, upkey$) <> 0 THEN y% = y% - speed%: direction$ = "up"
IF INSTR(key$, downkey$) <> 0 THEN y% = y% + speed%: direction$ = "down"
IF INSTR(key$, escape$) <> 0 THEN GOTO ending

GOSUB impact

IF x% <> xlast% OR y% <> ylast% THEN
  PUT (xlast%, ylast%), eraseguy, PSET
  GET (x%, y%)-(x% + 20, y% + 20), eraseguy
  GOSUB guy
END IF

IF TIMER >= stepstart! + (1 / stepspeed%) THEN
  stepstart! = TIMER
  stepswitch% = stepswitch% * -1
  PUT (x%, y%), eraseguy, PSET
  GOSUB guy
END IF

GOTO idle

background:
FOR xmap% = 1 TO 11
  FOR ymap% = 1 TO 7
    xmapput% = (xmap% * 30) - 30
    ymapput% = (ymap% * 30) - 30
    mapsub% = (11 * (ymap% - 1)) + xmap%
    IF area$ = "map" THEN stamp$ = map(mapsub%)
    IF area$ = "town" THEN stamp$ = townmap(mapsub%)
    IF INSTR(stamp$, "coast") <> 0 THEN
      physicalmap(mapsub%) = 0
      FOR xcount% = 1 TO 30
        FOR ycount% = 1 TO 30
          temp% = (30 * (ycount% - 1)) + xcount%
          SELECT CASE RIGHT$(stamp$, 2)
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
    SELECT CASE stamp$
    CASE "bridgev"
      physicalmap(mapsub%) = bridgevphysical%
      FOR xcount% = 1 TO bridgevlength%
        FOR ycount% = 1 TO bridgevheight%
          xput% = xmapput% + xcount%
          yput% = ymapput% + ycount% - (bridgevheight% - 30)
          temp% = (bridgevlength% * (ycount% - 1)) + xcount%
          temp% = bridgev(temp%)
          IF temp% <> -1 THEN PSET (xput%, yput%), temp%
        NEXT
      NEXT
    CASE "grass"
      physicalmap(mapsub%) = grassphysical%
      FOR xcount% = 1 TO grasslength%
        FOR ycount% = 1 TO grassheight%
          xput% = xmapput% + xcount%
          yput% = ymapput% + ycount% - (grassheight% - 30)
          temp% = (grasslength% * (ycount% - 1)) + xcount%
          temp% = grass(temp%)
          IF temp% <> -1 THEN PSET (xput%, yput%), temp%
        NEXT
      NEXT
    CASE "mountain"
      physicalmap(mapsub%) = mountainphysical%
      FOR xcount% = 1 TO mountainlength%
        FOR ycount% = 1 TO mountainheight%
          xput% = xmapput% + xcount%
          yput% = ymapput% + ycount% - (mountainheight% - 30)
          temp% = (mountainlength% * (ycount% - 1)) + xcount%
          temp% = mountain(temp%)
          IF temp% <> -1 THEN PSET (xput%, yput%), temp%
        NEXT
      NEXT
    CASE "town"
      physicalmap(mapsub%) = townphysical%
      FOR xcount% = 1 TO townlength%
        FOR ycount% = 1 TO townheight%
          xput% = xmapput% + xcount%
          yput% = ymapput% + ycount% - (townheight% - 30)
          temp% = (townlength% * (ycount% - 1)) + xcount%
          temp% = town(temp%)
          IF temp% <> -1 THEN PSET (xput%, yput%), temp%
        NEXT
      NEXT
    CASE "water"
      physicalmap(mapsub%) = waterphysical%
      FOR xcount% = 1 TO waterlength%
        FOR ycount% = 1 TO waterheight%
          xput% = xmapput% + xcount%
          yput% = ymapput% + ycount% - (waterheight% - 30)
          temp% = (waterlength% * (ycount% - 1)) + xcount%
          temp% = water(temp%)
          IF temp% <> -1 THEN PSET (xput%, yput%), temp%
        NEXT
      NEXT
    CASE "pavement"
      physicalmap(mapsub%) = pavementphysical%
      FOR xcount% = 1 TO pavementlength%
        FOR ycount% = 1 TO pavementheight%
          xput% = xmapput% + xcount%
          yput% = ymapput% + ycount% - (pavementheight% - 30)
          temp% = (pavementlength% * (ycount% - 1)) + xcount%
          temp% = pavement(temp%)
          IF temp% <> -1 THEN PSET (xput%, yput%), temp%
        NEXT
      NEXT
    CASE "bridgeh"
      physicalmap(mapsub%) = bridgehphysical%
      FOR xcount% = 1 TO bridgehlength%
        FOR ycount% = 1 TO bridgehheight%
          xput% = xmapput% + xcount%
          yput% = ymapput% + ycount% - (bridgehheight% - 30)
          temp% = (bridgehlength% * (ycount% - 1)) + xcount%
          temp% = bridgeh(temp%)
          IF temp% <> -1 THEN PSET (xput%, yput%), temp%
        NEXT
      NEXT
    END SELECT
  NEXT
NEXT
RETURN

guy:
FOR xcount% = 1 TO 20
  FOR ycount% = 1 TO 20
    temp% = (20 * (ycount% - 1)) + xcount%
    IF direction$ = "left" THEN
      IF stepswitch% = 1 THEN temp% = guylr(temp%)
      IF stepswitch% = -1 THEN temp% = guyll(temp%)
    END IF
    IF direction$ = "right" THEN
      IF stepswitch% = 1 THEN temp% = guyrr(temp%)
      IF stepswitch% = -1 THEN temp% = guyrl(temp%)
    END IF
    IF direction$ = "up" THEN
      IF stepswitch% = 1 THEN temp% = guybr(temp%)
      IF stepswitch% = -1 THEN temp% = guybl(temp%)
    END IF
    IF direction$ = "down" THEN
      IF stepswitch% = 1 THEN temp% = guyfr(temp%)
      IF stepswitch% = -1 THEN temp% = guyfl(temp%)
    END IF
    xput% = x% + xcount%
    yput% = y% + ycount%
    IF temp% <> -1 THEN PSET (xput%, yput%), temp%
  NEXT
NEXT
RETURN

ending:
SCREEN 12
CLS
PRINT "This has been a Flyin' Hawaiian production"
END

load:
PRINT "Loading..."
leftkey$ = CHR$(0) + "K"
rightkey$ = CHR$(0) + "M"
upkey$ = CHR$(0) + "H"
downkey$ = CHR$(0) + "P"
enter$ = CHR$(13)
escape$ = CHR$(27)
area$ = "map"

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

OPEN "temp.map" FOR INPUT AS #1
INPUT #1, length%
INPUT #1, height%
total% = length% * height%
FOR count% = 1 TO 77
  INPUT #1, map(count%)
NEXT
CLOSE
OPEN "town.map" FOR INPUT AS #1
INPUT #1, length%
INPUT #1, height%
FOR count% = 1 TO length% * height%
  INPUT #1, townmap(count%)
NEXT
CLOSE

FOR stampcount% = 1 TO 8
  SELECT CASE stampcount%
  CASE 1
    OPEN "guyfl.pic" FOR INPUT AS #1
  CASE 2
    OPEN "guyfr.pic" FOR INPUT AS #1
  CASE 3
    OPEN "guybl.pic" FOR INPUT AS #1
  CASE 4
    OPEN "guybr.pic" FOR INPUT AS #1
  CASE 5
    OPEN "guyll.pic" FOR INPUT AS #1
  CASE 6
    OPEN "guylr.pic" FOR INPUT AS #1
  CASE 7
    OPEN "guyrl.pic" FOR INPUT AS #1
  CASE 8
    OPEN "guyrr.pic" FOR INPUT AS #1
  END SELECT
  INPUT #1, length%
  INPUT #1, height%
  total% = length% * height%
  FOR count% = 1 TO total%
    INPUT #1, temp%
    SELECT CASE stampcount%
    CASE 1
      guyfl(count%) = temp%
    CASE 2
      guyfr(count%) = temp%
    CASE 3
      guybl(count%) = temp%
    CASE 4
      guybr(count%) = temp%
    CASE 5
      guyll(count%) = temp%
    CASE 6
      guylr(count%) = temp%
    CASE 7
      guyrl(count%) = temp%
    CASE 8
      guyrr(count%) = temp%
    END SELECT
  NEXT
  CLOSE
NEXT
RETURN

impact:

IF x% < 1 THEN x% = 1
IF x% > 300 THEN x% = 300
IF y% < 1 THEN y% = 1
IF y% > 180 THEN y% = 180

IF area$ = "town" THEN
  IF x% <= 1 OR x% >= 300 OR y% <= 1 OR y% >= 180 THEN
    IF xquad% = 1 AND yquad% = 0 THEN xentering% = xentering% + 20
    IF xquad% = 0 AND yquad% = 1 THEN yentering% = yentering% + 20
    IF xquad% = 1 AND yquad% = 1 THEN xentering% = xentering% + 20: yentering% = yentering% + 20
    x% = (xentering% - (xentering% MOD 30)) + 5
    y% = (yentering% - (yentering% MOD 30)) + 5
    SELECT CASE direction$
    CASE "up"
      y% = y% - 31
    CASE "down"
      y% = y% + 31
    CASE "right"
      x% = x% + 31
    CASE "left"
      x% = x% - 31
    END SELECT
    SCREEN 7, 0, 0, 1
    xlast% = x%
    ylast% = y%
    area$ = "map"
    CLS
    GOSUB background
    GET (1, 1)-(320, 200), back
    CLS
    PUT (0, 0), back
    GET (x%, y%)-(x% + 20, y% + 20), eraseguy
    GOSUB guy
    SCREEN 7, 0, 0, 0
  END IF
END IF

FOR xcount% = 0 TO 1
  FOR ycount% = 0 TO 1
    xtemp% = x% + (xcount% * 20)
    ytemp% = y% + (ycount% * 20)
    xmap% = xtemp% - (xtemp% MOD 30)
    ymap% = ytemp% - (ytemp% MOD 30)
    xmap% = (xmap% + 30) \ 30
    ymap% = (ymap% + 30) \ 30
    mapsub% = (11 * (ymap% - 1)) + xmap%
    currentphysical% = physicalmap(mapsub%)
    IF currentphysical% = 1 THEN
      x% = xlast%
      y% = ylast%
      PUT (xlast%, ylast%), eraseguy, PSET
      GET (x%, y%)-(x% + 20, y% + 20), eraseguy
      GOSUB guy
    END IF
    IF currentphysical% = 2 THEN
      xentering% = x%
      yentering% = y%
      directionentering$ = direction$
      xquad% = xcount%
      yquad% = ycount%
      CLS
      area$ = "town"
      IF direction$ = "left" THEN x% = 290: y% = 100
      IF direction$ = "right" THEN x% = 10: y% = 100
      IF direction$ = "up" THEN x% = 160: y% = 170
      IF direction$ = "down" THEN x% = 160: y% = 10
      SCREEN 7, 0, 0, 1
      GOSUB background
      GET (1, 1)-(320, 200), back
      CLS
      PUT (0, 0), back
      GET (x%, y%)-(x% + 20, y% + 20), eraseguy
      SCREEN 7, 0, 0, 0
    END IF
  NEXT
NEXT
RETURN

bottom:
FOR xmap% = 1 TO 11
  xmapput% = (xmap% * 30) - 30
  ymapput% = (7 * 30) - 30
  mapsub% = (11 * (7 - 1)) + xmap%
  IF area$ = "map" THEN stamp$ = map(mapsub%)
  IF area$ = "town" THEN stamp$ = townmap(mapsub%)
  xmapput% = xmapput% - 1
  ymapput% = ymapput% - 1
  IF INSTR(stamp$, "coast") <> 0 THEN
    FOR xcount% = 1 TO 30
      FOR ycount% = 1 TO 30
        temp% = (30 * (ycount% - 1)) + xcount%
        SELECT CASE RIGHT$(stamp$, 2)
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
  SELECT CASE stamp$
  CASE "bridgeh"
  FOR xcount% = 1 TO bridgehlength%
    FOR ycount% = 1 TO bridgehheight%
      xput% = xmapput% + xcount%
      yput% = ymapput% + ycount% - (bridgehheight% - 30)
      temp% = (bridgehlength% * (ycount% - 1)) + xcount%
      temp% = bridgeh(temp%)
      IF temp% <> -1 THEN PSET (xput%, yput%), temp%
    NEXT
  NEXT
  CASE "bridgev"
  FOR xcount% = 1 TO bridgevlength%
    FOR ycount% = 1 TO bridgevheight%
      xput% = xmapput% + xcount%
      yput% = ymapput% + ycount% - (bridgevheight% - 30)
      temp% = (bridgevlength% * (ycount% - 1)) + xcount%
      temp% = bridgev(temp%)
      IF temp% <> -1 THEN PSET (xput%, yput%), temp%
    NEXT
  NEXT
  CASE "grass"
  FOR xcount% = 1 TO grasslength%
    FOR ycount% = 1 TO grassheight%
      xput% = xmapput% + xcount%
      yput% = ymapput% + ycount% - (grassheight% - 30)
      temp% = (grasslength% * (ycount% - 1)) + xcount%
      temp% = grass(temp%)
      IF temp% <> -1 THEN PSET (xput%, yput%), temp%
    NEXT
  NEXT
  CASE "mountain"
    FOR xcount% = 1 TO mountainlength%
      FOR ycount% = 1 TO mountainheight%
        xput% = xmapput% + xcount%
        yput% = ymapput% + ycount% - (mountainheight% - 30)
        temp% = (mountainlength% * (ycount% - 1)) + xcount%
        temp% = mountain(temp%)
        IF temp% <> -1 THEN PSET (xput%, yput%), temp%
      NEXT
    NEXT
  CASE "town"
     FOR xcount% = 1 TO townlength%
      FOR ycount% = 1 TO townheight%
        xput% = xmapput% + xcount%
        yput% = ymapput% + ycount% - (townheight% - 30)
        temp% = (townlength% * (ycount% - 1)) + xcount%
        temp% = town(temp%)
        IF temp% <> -1 THEN PSET (xput%, yput%), temp%
      NEXT
    NEXT
  CASE "water"
    FOR xcount% = 1 TO waterlength%
      FOR ycount% = 1 TO waterheight%
        xput% = xmapput% + xcount%
        yput% = ymapput% + ycount% - (waterheight% - 30)
        temp% = (waterlength% * (ycount% - 1)) + xcount%
        temp% = water(temp%)
        IF temp% <> -1 THEN PSET (xput%, yput%), temp%
      NEXT
    NEXT
  END SELECT
NEXT
RETURN

lastguy:
count% = 1
FOR xadjustcount% = 0 TO 1
  FOR yadjustcount% = 0 TO 1
    xtemp% = xlast% + (xadjustcount% * 20)
    ytemp% = ylast% + (yadjustcount% * 20)
    xmapput% = xtemp% - (xtemp% MOD 30)
    ymapput% = ytemp% - (ytemp% MOD 30)
    xmap% = (xmapput% + 30) \ 30
    ymap% = (ymapput% + 30) \ 30
    mapsub% = (11 * (ymap% - 1)) + xmap%
    stamp$ = map(mapsub%)
    xmapput% = xmapput% - 1
    ymapput% = ymapput% - 1
    IF INSTR(stamp$, "coast") <> 0 THEN
      FOR xcount% = 1 TO 30
        FOR ycount% = 1 TO 30
          temp% = (30 * (ycount% - 1)) + xcount%
          SELECT CASE RIGHT$(stamp$, 2)
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
    SELECT CASE stamp$
    CASE "grass"
      FOR xcount% = 1 TO grasslength%
        FOR ycount% = 1 TO grassheight%
          xput% = xmapput% + xcount%
          yput% = ymapput% + ycount% - (grassheight% - 30)
          temp% = (grasslength% * (ycount% - 1)) + xcount%
          temp% = grass(temp%)
          IF temp% <> -1 THEN PSET (xput%, yput%), temp%
        NEXT
    NEXT
    CASE "mountain"
      FOR xcount% = 1 TO mountainlength%
        FOR ycount% = 1 TO mountainheight%
          xput% = xmapput% + xcount%
          yput% = ymapput% + ycount% - (mountainheight% - 30)
          temp% = (mountainlength% * (ycount% - 1)) + xcount%
          temp% = mountain(temp%)
          IF temp% <> -1 THEN PSET (xput%, yput%), temp%
        NEXT
      NEXT
    CASE "town"
      FOR xcount% = 1 TO townlength%
        FOR ycount% = 1 TO townheight%
          xput% = xmapput% + xcount%
          yput% = ymapput% + ycount% - (townheight% - 30)
          temp% = (townlength% * (ycount% - 1)) + xcount%
          temp% = town(temp%)
          IF temp% <> -1 THEN PSET (xput%, yput%), temp%
        NEXT
      NEXT
    CASE "water"
      FOR xcount% = 1 TO waterlength%
        FOR ycount% = 1 TO waterheight%
          xput% = xmapput% + xcount%
          yput% = ymapput% + ycount% - (waterheight% - 30)
          temp% = (waterlength% * (ycount% - 1)) + xcount%
          temp% = water(temp%)
          IF temp% <> -1 THEN PSET (xput%, yput%), temp%
        NEXT
      NEXT
    END SELECT
  NEXT
NEXT
RETURN


side:
FOR ymap% = 1 TO 7
  xmapput% = (11 * 30) - 30
  ymapput% = (ymap% * 30) - 30
  mapsub% = (11 * (ymap% - 1)) + 11
  IF area$ = "map" THEN stamp$ = map(mapsub%)
  IF area$ = "town" THEN stamp$ = townmap(mapsub%)
  xmapput% = xmapput% - 1
  ymapput% = ymapput% - 1
  IF INSTR(stamp$, "coast") <> 0 THEN
    FOR xcount% = 1 TO 30
      FOR ycount% = 1 TO 30
        temp% = (30 * (ycount% - 1)) + xcount%
        SELECT CASE RIGHT$(stamp$, 2)
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
  SELECT CASE stamp$
  CASE "grass"
  FOR xcount% = 1 TO grasslength%
    FOR ycount% = 1 TO grassheight%
      xput% = xmapput% + xcount%
      yput% = ymapput% + ycount% - (grassheight% - 30)
      temp% = (grasslength% * (ycount% - 1)) + xcount%
      temp% = grass(temp%)
      IF temp% <> -1 THEN PSET (xput%, yput%), temp%
    NEXT
  NEXT
  CASE "mountain"
    FOR xcount% = 1 TO mountainlength%
      FOR ycount% = 1 TO mountainheight%
        xput% = xmapput% + xcount%
        yput% = ymapput% + ycount% - (mountainheight% - 30)
        temp% = (mountainlength% * (ycount% - 1)) + xcount%
        temp% = mountain(temp%)
        IF temp% <> -1 THEN PSET (xput%, yput%), temp%
      NEXT
    NEXT
  CASE "town"
     FOR xcount% = 1 TO townlength%
      FOR ycount% = 1 TO townheight%
        xput% = xmapput% + xcount%
        yput% = ymapput% + ycount% - (townheight% - 30)
        temp% = (townlength% * (ycount% - 1)) + xcount%
        temp% = town(temp%)
        IF temp% <> -1 THEN PSET (xput%, yput%), temp%
      NEXT
    NEXT
  CASE "water"
    FOR xcount% = 1 TO waterlength%
      FOR ycount% = 1 TO waterheight%
        xput% = xmapput% + xcount%
        yput% = ymapput% + ycount% - (waterheight% - 30)
        temp% = (waterlength% * (ycount% - 1)) + xcount%
        temp% = water(temp%)
        IF temp% <> -1 THEN PSET (xput%, yput%), temp%
      NEXT
    NEXT
  END SELECT
NEXT
RETURN

