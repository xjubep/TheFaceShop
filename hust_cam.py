# 버튼 눌러서 사진 찍은 후 현재 시각.png로 rpi에 저장
# mysql에 시각 정보 저장
# aws server로 사진 전송 (scp)
from picamera import PiCamera
from time import sleep
from gpiozero import Button
from datetime import datetime
import pymysql
from subprocess import call

button = Button(21) # gpio 21 button 연결

SAVE_DIR = '/home/pi/hust/camera/'
USER_ID = 'java'
PEM = 'kangsy-key.pem'
RECEIVING_DIR = '/home/ubuntu/xjubep/TheFaceShop/camera/'
USER = 'ubuntu'
SERVER_IP = '3.21.37.105'

# FILE_NAME 생성
def getDatetime(now):
    year = str(now.year)
    month = str(now.month)
    day = str(now.day)
    hour = str(now.hour)
    minute = str(now.minute)
    second = str(now.second)

    if now.month < 10:
        month = '0' + month
    if now.day < 10:
        day = '0' + day
    if now.hour < 10:
        hour = '0' + hour
    if now.minute < 10:
        minute = '0' + minute
    if now.second < 10:
        second = '0' + second

    return year + month + day + hour + minute + second

while True:
    # db 연결
    db = pymysql.connect(
        host=SERVER_IP,
        user='me',
        passwd='1234',
        db='skin',
        charset='utf8'
    )

    cursor = db.cursor()
    sql = 'insert into imagesPi(id, imageName) values (%s, %s)'

    # 사진 찍기
    with PiCamera() as camera:
        #camera.rotation = 180
        camera.resolution = (1500, 1000)
        camera.start_preview()
        button.wait_for_press()
        FILE_NAME = getDatetime(datetime.now()) #ex 20200515130112
        SENDING_FILE = SAVE_DIR + FILE_NAME + '.png'
        camera.capture(SENDING_FILE, format='png')
        camera.stop_preview()

        # db insert
        cursor.execute(sql, (USER_ID, FILE_NAME))
        db.commit()

    db.close()

    # scp로 파일 전송
    cmd = 'scp -i ' + PEM + ' ' + SENDING_FILE + ' ' + USER +'@'
    cmd += SERVER_IP + ':' + RECEIVING_DIR
    #print (cmd)
    call(cmd.split())