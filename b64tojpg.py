import base64
import pymysql
from PIL import Image
from io import BytesIO

db = pymysql.connect(
    host='localhost',
    user='me',
    passwd='1234',
    db='mydb',
    charset='utf8'
)

cursor = db.cursor()
sql = 'select * from images;'
cursor.execute(sql)
res = cursor.fetchall()
i = 0
for x in res:
    #imgstring= x[1]
    imgstring = x[1][23:]
    #print(imgstring)
    #plus = '=' * (4-len(imgstring) % 4)
    #plus = bytes(plus, encoding='utf=8')
    #print(plus)
    #imgstring_new = imgstring + bytes('='*(4-len(imgstring) % 4), encoding='utf-8')
    #imgstring += bytes("=" * ((4 - len(imgstring) % 4) % 4), encoding='utf-8')
    print(imgstring)
    #imgdata = base64.b64decode(imgstring_new)
    #print(imgstring_new)
    #imgdata = base64.b64decode(imgstring)
    filename = 'image' + str(i) + '.jpg'

    with open(filename, "wb") as f:
        #fh.write(base64.urlsafe_b64decode(imgstring))    #with open(filename, 'wb') as f:
        #f.write(base64.decodestring(imgstring))
        #f.write(imgdata)
        imgstring += b''
        print(imgstring[-10:])
        f.write(base64.b64decode(imgstring))
    i += 1
db.close()

# imgdata = base64.b64decode(imgstring)
# filename = 'some_image.jpg'  # I assume you have a way of picking unique filenames
# with open(filename, 'wb') as f:
#     f.write(imgdata)