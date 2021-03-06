import pygame as pg

from _thread import *

from Network import Network
from Player import *
import Config
from Ball import Ball

width = Config.WindowWidth
height = Config.WindowHeight

pg.font.init()

win = pg.display.set_mode((width,height+Config.ScoreBoardHeight))
pg.display.set_caption("Client")
image = pg.image.load(r'images\BackgroundImage.jpg')
#image = pg.transform.scale(pg.image.load(r'images\bg.jpg'), (width,height))
mandel_wut=[pg.transform.scale(pg.image.load(r'images\\Mandel1.jpg'), (width,height+Config.ScoreBoardHeight)),
            pg.transform.scale(pg.image.load(r'images\\Mandel2.jpg'), (width,height+Config.ScoreBoardHeight)),
            pg.transform.scale(pg.image.load(r'images\\Mandel3.jpg'), (width,height+Config.ScoreBoardHeight)),
            pg.transform.scale(pg.image.load(r'images\\Mandel4.jpg'), (width,height+Config.ScoreBoardHeight)),
            pg.transform.scale(pg.image.load(r'images\\Mandel5.jpg'), (width,height+Config.ScoreBoardHeight)),
            pg.transform.scale(pg.image.load(r'images\\Mandel6.jpg'), (width,height+Config.ScoreBoardHeight)),
            pg.transform.scale(pg.image.load(r'images\\Mandel7.jpg'), (width,height+Config.ScoreBoardHeight)),
            pg.transform.scale(pg.image.load(r'images\\Mandel8.jpg'), (width,height+Config.ScoreBoardHeight))]
#soundObj = pg.mixer.Sound('sounds\mixkit-retro-game-notification-212.wav')
#soundObj2 = pg.mixer.Sound('sounds\mixkit-arcade-retro-game-over-213.wav')
sounds=[pg.mixer.Sound('sounds\BallHit.wav'),pg.mixer.Sound('sounds\BallMiss.wav')]

PlayerID=-1

font = pg.font.Font('font\Creamy Coconut.ttf', 32)

def show_score(win,score_value,x, y):
    if x==Config.ScoreBoardHeight and y==Config.WindowHeight:
        score = font.render("Score : " + str(score_value), True, (255, 0, 0))
    if x==Config.WindowWidth-2*Config.ScoreBoardHeight and y==Config.WindowHeight:
        score = font.render("Score : " + str(score_value), True, (0, 255, 0))
    if x==Config.ScoreBoardHeight and y==Config.WindowHeight+(Config.ScoreBoardHeight/2):
        score = font.render("Score : " + str(score_value), True, (0, 0, 250))
    if x==Config.WindowWidth-2*Config.ScoreBoardHeight and y==Config.WindowHeight+(Config.ScoreBoardHeight/2):
        score = font.render("Score : " + str(score_value), True, (128, 128, 0))
    win.blit(score, (x, y))

fun=0
ptr=0
def redrawWindow(win,players,ball,scores):
    normal=60
    mandel=15
    global ptr
    global fun
    fun+=1
    win.fill((255,255,255))
    if fun>normal and fun<normal+mandel:
        win.blit(mandel_wut[ptr],(0,0))
    else:
        win.blit(image, (0, 0))
    if fun>normal+mandel:
        ptr+=1
        ptr=ptr%(len(mandel_wut))
        fun=0
    for p in players:
        if p.isActive:
            p.draw(win)
            if p.id==0:
                show_score(win,scores[p.id],Config.ScoreBoardHeight,Config.WindowHeight)
            if p.id==1:
                show_score(win,scores[p.id],Config.WindowWidth-2*Config.ScoreBoardHeight,Config.WindowHeight)
            if p.id==2:
                show_score(win,scores[p.id],Config.ScoreBoardHeight,Config.WindowHeight+(Config.ScoreBoardHeight/2))
            if p.id==3:
                show_score(win,scores[p.id],Config.WindowWidth-2*Config.ScoreBoardHeight,Config.WindowHeight+(Config.ScoreBoardHeight/2))
    
    ball.draw(win)
    pg.display.update()



def main():
    run=True
    n=Network()
    p=n.getP()
    global PlayerID
    PlayerID=p.id
    pg.display.set_caption("Player "+str(PlayerID+1))
    clock=pg.time.Clock()
    pg.mixer.music.load(r'sounds\\BackgroundSound.wav')
    pg.mixer.music.play(-1)
    while run:
        clock.tick(Config.FPS)
        data=n.send(p)
        for event in pg.event.get():
            if event.type ==pg.QUIT:
                run =False
                pg.quit()
        music=data[3]
        for m in music:
            sounds[m].play()
        #print(data)
        p.move()
        redrawWindow(win,data[0],data[1],data[2])

main()
