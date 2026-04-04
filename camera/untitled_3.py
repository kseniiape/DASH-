
import sensor, image, time, math, pyb

robot =  2#2 - g, 1 - f


if robot == 1:

    EXPOSURE_TIME_SCALE = 0.4
    yellow_threshold = [(0, 100, -128, 127, 26, 127)]
    blue_threshold = [(0, 100, -128, -7, -128, -4)]
    red_threshold = [(0, 100, 16, 75, 18, 44)]
    exposure = 140_000
    gain = 20
    center  = [167,110]
    white = (63, 60, 62)

else:

    EXPOSURE_TIME_SCALE = 0.4

    EXPOSURE_TIME_SCALE = 0.4
    yellow_threshold = [(0, 100, -128, 127, 26, 127)]
    blue_threshold = [(0, 100, -128, -7, -128, -4)]
    red_threshold = [(0, 100, 9, 30, 14, 24)]
    exposure = 140_000
    gain = 20
    center  = [166,125]
    white = (63, 60, 62)


img_radius = 135
red_led = pyb.LED(2)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.set_auto_gain(True)
sensor.set_auto_whitebal(True)


sensor.set_auto_exposure(True)
current_exposure_time_in_microseconds = sensor.get_exposure_us()
sensor.set_auto_exposure(True, \
    exposure_us = int(current_exposure_time_in_microseconds* EXPOSURE_TIME_SCALE))
clock = time.clock()
sensor.skip_frames(time = 500)
print(sensor.get_rgb_gain_db())

sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_auto_gain(False, gain_db=gain)
sensor.set_auto_whitebal(False, rgb_gain_db = white)
sensor.set_auto_whitebal(False)
sensor.set_auto_exposure(False)
current_exposure_time_in_microseconds =  sensor.get_exposure_us()
sensor.set_auto_exposure(False, exposure_us = exposure)
#clock = time.clock()
sensor.skip_frames(time = 1000)

uart = pyb.UART(3, 115200, timeout = 100, timeout_char = 100)
uart.init(115200, bits=8, parity=False, stop=1, timeout_char=100)

image_height = sensor.height()
image_width = sensor.width()

ball_roundness = 0

my_blob_x = 0
my_blob_y = 0
ball_angle = 0
ball_distance = 0

old_area = 0
yellow_angle = 0
blue_angle = 0
yellow_distance = 0
blue_distance = 0

distance = [
            [210, 123],
            [175, 121],
            [165, 120],
            [155, 118],
            [145, 116],
            [140, 115],
            [135, 113],
            [125, 111],
            [120, 110],
            [115, 108],
            [110, 105],
            [105, 103],
            [100, 101],
            [95, 98],
            [90, 96],
            [85, 94],
            [80, 92],
            [75, 89],
            [70, 83],
            [65, 79],
            [60, 74],
            [55, 71],
            [50, 65],
            [45, 59],
            [40, 52],
            [35, 45],
            [30, 38],
            [25, 33],
            [20, 31],
            [15, 28],
            [10, 25],
                    ]

def get_distance(x, y):
    p_dist = math.sqrt(math.pow(x, 2) + math.pow(y, 2))
    return p_dist

def crc8(data, len): #function that calculates check sum
    crc = 0xFF
    j = 0
    for i in range(0, len):
        crc = crc ^ data[i];
        for j in range(0, 8):
            if (crc & 0x80):
                crc = (crc << 1) ^ 0x31
            else:
             crc = crc << 1
    return crc

data = bytearray(7)

def send_data (num1, num2, num3, num4, num5, num6):
    uart.writechar(255)
    red_led.on()
    # num1 = int((num1) / 3) + 127
    # num2 = int((num2) / 2) + 127
    # num3 = int((num3) / 3) + 127
    #num4 = int((num4) /2) + 127
    num1 = int((num1) / 3)
    num2 = int((num2) / 2)
    num3 = int((num3) / 3)
    num4 = int((num4) / 2)
    num5 = int((num5) / 3)
    num6 = int((num6) / 2)

    if num1 + 127 > 253:
       data[0] = 253
    elif num1 + 127 < 0:
       data[0] = 0
    else:
       data[0] = num1

    if num2 + 127 > 253:
        data[1] = 253
    elif num2 + 127 < 0:
        data[1] = 0
    else:
        data[1] = num2

    if num3 + 127 > 253:
        data[2] = 253
    elif num3 + 127 < 0:
        data[2] = 0
    else:
        data[2] = num3

    if num4 + 127 > 253:
        data[3] = 253
    elif num4 + 127 < 0:
        data[3] = 0
    else:
        data[3] = num4

    if num5 + 127 > 253:
       data[4] = 253
    elif num5 + 127 < 0:
       data[4] = 0
    else:
       data[4] = num5

    if num6 + 127 > 253:
       data[5] = 253
    elif num6 + 127 < 0:
       data[5] = 0
    else:
       data[5] = num6
    data[6] = crc8(data, 6)


    uart.writechar(int(data[0]))
    uart.writechar(int(data[1]))
    uart.writechar(int(data[2]))
    uart.writechar(int(data[3]))
    uart.writechar(int(data[4]))
    uart.writechar(int(data[5]))
    uart.writechar(int(data[6]))
    red_led.off()

def linearize(num):
    num = abs(num)
    i = -1
    old_err = 1000
    for mas in distance:
        err = num - abs(mas[1])
        if(abs(old_err)) > abs(err):
            i+= 1
        else:
            break
        old_err = err
    result = 0
    x1 = 0
    x2 = 0
    y1 = 0
    y2 = 0
    if err != 0:
        if i < len(distance)-1:
            if i > 0:
                if num > distance[i][1]:
                    x1 = distance[i][1]
                    x2 = distance[i-1][1]
                    y1 = distance[i][0]
                    y2 = distance[i-1][0]

                else:
                    x2 = distance[i][1]
                    x1 = distance[i + 1][1]
                    y1 = distance[i + 1][0]
                    y2 = distance[i][0]
                if x2 != x1:
                    result = ((num - x1)/(x2 - x1))*(y2 - y1) + y1
                    # result = ((num - x1)/(0.0))*(y2 - y1) + y1
                else:
                    result = ((num - x1)/(x2 - x1 + 1))*(y2 - y1) + y1
                    # result = ((num - x1)/(0.0))*(y2 - y1) + y1
            else:
                result = distance[0][0]
        else:
          result = distance[-1][0]
    else:
        result = distance[i][0]
    return result



while True:
    clock.tick()
    img = sensor.snapshot().mask_circle(center[0], center[1], img_radius)
    old_area = 0
    img.draw_circle(center[0], center[1], 3, (0, 0, 0), fill = True)

    for blob in img.find_blobs(yellow_threshold, pixels_threshold=30, area_threshold=300, merge=True, margin = 20):
        if(blob[2] * blob[3] > old_area and blob[2] * blob[3] > 60):
            old_area = blob[2] * blob[3]
            yellow = [blob.x(), blob.y(), blob.x()+blob.w(),blob.y()+blob.h(), blob.cx(), blob.cy(), blob.w(), blob.h()]
            yellow_x = blob.cx() - center[0]
            yellow_y = blob.cy() - center[1]
            img.draw_rectangle(blob[0], blob[1], blob[2], blob[3],(255,255,0), 2)
            img.draw_line(center[0], center[1], blob.cx(), blob.cy(), (255,255,0), thickness = 2)
            img.draw_circle(blob.cx(), blob.cy(), 3, (255,255,0), fill = True)
            yellow_distance = linearize(get_distance(yellow_x, yellow_y))
            yellow_angle = math.floor(math.atan2(yellow_x, yellow_y) * 57.3)+90
    if(old_area < 50):
        yellow_distance = 0

    if(yellow_angle > 360):
        yellow_angle -= 360
    elif(yellow_angle < 0):
        yellow_angle += 360
    #print("yellow_distance =", yellow_distance)
    #print("yellow_angle =", yellow_angle)

    old_area = 0

    for blob in img.find_blobs(blue_threshold, pixels_threshold=30, area_threshold=300, merge=True, margin = 20):
        if(blob[2] * blob[3] > old_area and blob[2] * blob[3] > 60):
            old_area = blob[2] * blob[3]
            blue = [blob.x(), blob.y(), blob.x()+blob.w(),blob.y()+blob.h(), blob.cx(), blob.cy(), blob.w(), blob.h()]
            blue_x = blob.cx() - center[0]
            blue_y = blob.cy() - center[1]
            img.draw_rectangle(blob[0], blob[1], blob[2], blob[3],(0,0,255), 2)
            img.draw_line(center[0], center[1], blob.cx(), blob.cy(), (0,0,255), thickness = 2)
            img.draw_circle(blob.cx(), blob.cy(), 3, (0,0,255), fill = True)
            blue_distance = linearize(get_distance(blue_x, blue_y))
            blue_angle = math.floor(math.atan2(blue_x, blue_y) * 57.3)+90


    if(old_area < 50):
        blue_distance = 0
    #print("blue_distance =", blue_distance)
    #print("blue_angle =", blue_angle)
    if(blue_angle > 360):
        blue_angle -= 360
    elif(blue_angle < 0):
        blue_angle += 360

    old_area = 0
    old_roundness = 0
    max_area = 0
    ball_distance = 0
    for blob in img.find_blobs(red_threshold, pixels_threshold=0, area_threshold=0, merge=True, margin = 10):
        if blob.area() >= 7 and blob.area() < 350:
            if blob.compactness() > old_roundness:
                old_roundness = blob.compactness()
                my_blob = blob
                max_area = blob.area()
                my_blob_x = blob.cx()
                my_blob_y = blob.cy()
                ball_x = (my_blob_x - center[0])
                ball_y = (my_blob_y - center[1])
                ball_distance = linearize(get_distance(ball_x, ball_y))
                ball_angle = math.floor(math.atan2(ball_x, ball_y) * 57.3) + 90
                img.draw_circle(my_blob_x, my_blob_y, 20, (255, 255, 255), 4)
    #print(max_area)

    #print("ball_distance =", ball_distance)
    #print("ball_angle =", ball_angle)
    #img.draw_line(yellow[4], yellow[5], blue[4], blue[5], (255, 255, 255), 2) #line between centers of gates


    if(ball_angle > 360):
        ball_angle -= 360
    elif(ball_angle < 0):
        ball_angle += 360




    #send_data(yellow_angle, yellow_distance, blue_angle, blue_distance)
    send_data(yellow_angle, yellow_distance, blue_angle, blue_distance, ball_angle, ball_distance)

