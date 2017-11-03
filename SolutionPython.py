import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.
MAXITER = 300
steps = 0 
Igotthemoves = []
bender = {'x': 0, 'y': 0, 'breaker': -1, 'priority': -1, 'direction': 'SOUTH'} 
def townmap(MAP):
    for x in range(c):
        print(MAP[x])
    return

def findsymb(MAP, c, symb):
    for x in range(c):
        if symb in MAP[x]:
            y = MAP[x].index(symb)
            break
    return (x, y)
    
    
    
def wherenext(BENDER):
    nx = BENDER['x']
    ny = BENDER['y']
    CUR_DIR = BENDER['direction']
    if CUR_DIR == 'SOUTH':
        nx += 1
    if CUR_DIR == 'WEST':
        ny -= 1
    if CUR_DIR == 'NORTH':
        nx -= 1
    if CUR_DIR == 'EAST':
        ny += 1
    return (nx, ny)



def suicide(BENDER, MAP, C):
    x = BENDER['x']
    y = BENDER['y']
    (sx, sy) = findsymb(MAP, C, '$')
    if sx == x and sy == y:
        return True
    else:
        return False
        


def canproceed(NX, NY, BENDER, MAP):
    MP = MAP[NX][NY]
    CUR_DIR = BENDER['direction']
    if MP == '#':
        return False
    elif MP == 'X' and BENDER['breaker'] == -1:
        return False
    else:
        return True

def findtele(X, Y, MAP, c):
    y = 0
    for x in range(c):
        if ('T' in MAP[x]) and (x != X) and (y != Y):
            y = MAP[x].index('T')
            break
    return (x, y)
    
def teleport(MAP, BENDER, C):
    (BENDER['x'], BENDER['y']) = findtele(BENDER['x'], BENDER['y'], MAP , C)
    return BENDER
    

def removeObstacle(NX, NY, MAP, r, c):

    Sel = []
    MAPR = []
    for y in range(c):
        if y == NY:
            MAPR.append('V')
        else:
            MAPR.append(MAP[NX][y])
    
    HAVE = "".join(MAPR)
    for x in range(r):
            if x == NX:
                Sel.append(HAVE)
            else:
                Sel.append(MAP[x])

    return Sel
    
    
def updateBender(nx, ny, C, BENDER, MAP):
    
    BENDER['x'] = nx
    BENDER['y'] = ny
    MP = MAP[nx][ny]
    
    if MP == 'B':
        BENDER['breaker'] *= -1 
    if MP == 'I':
        BENDER['priority'] *= -1
    if MP == 'S':
        BENDER['direction'] = 'SOUTH'
    if MP == 'E':
        BENDER['direction'] = 'EAST'
    if MP == 'N':
        BENDER['direction'] = 'NORTH'
    if MP == 'W':
        BENDER['direction'] = 'WEST'
    if MP == 'T':
        BENDER = teleport(MAP, BENDER, C)
        
    return BENDER

def obstacle1(NX, NY, BENDER, MAP):
    
    LOOP = ['SOUTH','EAST','NORTH', 'WEST']
    ind = 0
    while canproceed(NX, NY, BENDER, MAP) == False: 
        if BENDER['priority'] == -1:
            BENDER['direction'] = LOOP[ind]
            (NX, NY) = wherenext(BENDER)
            ind+=1
        else:
            BENDER['direction'] = LOOP[ind+3]
            (NX, NY) = wherenext(BENDER)
            ind-=1
    return (BENDER, NX, NY)
        
    
r, c = [int(i) for i in input().split()]
maps = []
for i in range(c):
    maps.append(input())


# townmap(maps)
(bender['x'], bender['y']) = findsymb(maps, c, '@')

(sx, sy) = findsymb(maps, c,'$')

while (bender['x'] != sx) or (bender['y'] != sy): 

    (nx, ny) = wherenext(bender)
    if steps > 300:
        break
    
    if canproceed(nx, ny, bender, maps) == False:
        (bender, nx, ny) = obstacle1(nx, ny, bender, maps)
    Igotthemoves.append(bender['direction'])
    
    bender = updateBender(nx, ny, c, bender, maps)
    if maps[bender['x']][bender['y']] == 'X' and bender['breaker'] == 1:
        maps = removeObstacle(nx, ny, maps, r, c)
    steps+=1

if steps > 300:
    print('LOOP')
else:
    for i in Igotthemoves: 
        print(i)
