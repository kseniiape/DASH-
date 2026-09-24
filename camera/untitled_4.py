import sensor, image, time, math, pyb

robot = 2  # 2 - g, 1 - f
is_draw = 0 #1 - yes, 2 - no

if robot == 1:
    yellow_threshold = [(0, 100, 14, 32, 32, 127)]
    blue_threshold = [(0, 100, -128, -5, -128, -1)]
    red_threshold = [(0, 100, 35, 58, 22, 32)]
    gain = 17
    center = [167, 110]
    white = (63, 60, 63)
    gamm, contrst, brightnss = 0.8, 1.5, 0.0
else:
    yellow_threshold = [(0, 100, -128, 127, 23, 127)]
    blue_threshold = [(0, 100, -128, 0, -128, -6)]
    red_threshold = [(0, 100, 24, 127, 15, 127)]
    gain = 25
    center = [168, 122]
    white = (61, 60, 65)
    gamm, contrst, brightnss = 0.8, 1.5, 0.0

img_radius = 135
exposure = 60000  # Короткая выдержка под высокий FPS
exposure_scale = 0.4

red_led = pyb.LED(2)

# --- ИНИЦИАЛИЗА СЕНСОРА (Правильный порядок) ---
sensor.reset()
#sensor.set_pixformat(sensor.RGB565)
#sensor.set_framesize(sensor.QQVGA)
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)

sensor.set_contrast(3)
sensor.set_saturation(3)
sensor.set_brightness(1)

# 1. Включаем автоматы для прогрева и первичной калибровки
sensor.set_auto_gain(True)
sensor.set_auto_whitebal(True)
sensor.set_auto_exposure(True)
clock = time.clock()
sensor.skip_frames(time=1000)
print(sensor.get_rgb_gain_db())


#current_exposure = sensor.get_exposure_us()
#sensor.set_auto_exposure(True, exposure_us=int(current_exposure * exposure_scale))
#sensor.skip_frames(time=500)


# 2. Переключаем на рабочее разрешение и ЖЕСТКО фиксируем параметры


sensor.set_auto_gain(False, gain_db=gain)
sensor.set_auto_whitebal(False, rgb_gain_db=white)
#sensor.set_auto_whitebal(False)
sensor.set_auto_exposure(False, exposure_us=exposure)
#sensor.skip_frames(time=500)

# UART
uart = pyb.UART(3, 115200, timeout=100, timeout_char=100)
uart.init(115200, bits=8, parity=False, stop=1, timeout_char=100)

# ROI вокруг зеркала
mirror_roi = (
    max(0, center[0] - img_radius),
    max(0, center[1] - img_radius),
    min(sensor.width(), img_radius * 2),
    min(sensor.height(), img_radius * 2)
)

# Подготовка маски (черное за пределами зеркала)
mask_img = sensor.snapshot().copy()
mask_img.draw_rectangle(0, 0, sensor.width(), sensor.height(), color=(255, 255, 255), fill=True)
mask_img.draw_circle(center[0], center[1], img_radius, color=(0, 0, 0), fill=True)

distance = [
    [210, 127], [175, 122], [165, 121], [155, 118], [145, 117],
    [140, 116], [135, 115], [130, 114], [125, 112], [115, 111],
    [110, 109], [105, 108], [100, 106], [95, 103], [90, 101],
    [85, 100], [80, 97], [75, 94], [70, 89], [65, 85],
    [60, 82], [55, 78], [50, 73], [45, 67], [40, 61],
    [35, 54], [30, 47], [25, 41], [20, 37], [15, 36], [10, 25]
]

distance_ball = [
    [210, 125], [175, 122], [165, 120], [155, 118], [145, 116],
    [140, 115], [135, 114], [130, 112], [125, 111], [115, 107],
    [110, 106], [105, 105], [100, 102], [95, 100], [90, 97],
    [85, 94], [80, 91], [75, 88], [70, 84], [65, 80],
    [60, 73], [55, 67], [50, 61], [45, 53], [40, 44],
    [35, 36], [30, 26], [25, 23], [20, 18], [15, 10], [10, 5]
]

def crc8_fast(data_bytes):
    crc = 0xFF
    for b in data_bytes:
        crc ^= b
        for _ in range(8):
            if crc & 0x80:
                crc = ((crc << 1) ^ 0x31) & 0xFF
            else:
                crc = (crc << 1) & 0xFF
    return crc

data = bytearray(7)

def send_data(num1, num2, num3, num4, num5, num6):
    red_led.on()
    data[0] = max(0, min(253, int(num1 / 3)))
    data[1] = max(0, min(253, int(num2 / 2)))
    data[2] = max(0, min(253, int(num3 / 3)))
    data[3] = max(0, min(253, int(num4 / 2)))
    data[4] = max(0, min(253, int(num5 / 3)))
    data[5] = max(0, min(253, int(num6 / 2)))
    data[6] = crc8_fast(data[:6])

    uart.writechar(255)
    uart.write(data)
    red_led.off()

def linearize_fast(p_dist, dist_table):
    for i, mas in enumerate(dist_table):
        if p_dist >= mas[1]:
            if i == 0:
                return mas[0]
            x1, y1 = dist_table[i][1], dist_table[i][0]
            x2, y2 = dist_table[i-1][1], dist_table[i-1][0]
            if x2 == x1:
                return y1
            return int(((p_dist - x1) / (x2 - x1)) * (y2 - y1) + y1)
    return dist_table[-1][0]

# --- ОСНОВНОЙ ЦИКЛ ---


while True:
    clock.tick()
    img = sensor.snapshot().gamma_corr(gamma=gamm, contrast=contrst, brightness=brightnss)


    # Зачерняет всё за пределами круга зеркала
    img.sub(mask_img)

    # Желтые ворота
    yellow_angle, yellow_distance = 0, 0
    max_area = 0
    for blob in img.find_blobs(yellow_threshold, roi=mirror_roi, pixels_threshold=30, area_threshold=200, merge=True, margin=15):
        area = blob.w() * blob.h()
        if area > max_area:
            max_area = area
            yx = blob.cx() - center[0]
            yy = blob.cy() - center[1]
            p_dist = math.sqrt(yx * yx + yy * yy)
            yellow_distance = linearize_fast(p_dist, distance)
            yellow_angle = (int(math.atan2(yx, yy) * 57.3) + 180) % 360
            if is_draw:

                img.draw_rectangle(blob[0], blob[1], blob[2], blob[3],(255,255,0), 2)

                #img.draw_line(center[0], center[1], blob.cx(), blob.cy(), (255,255,0), thickness = 2)
                img.draw_circle(blob.cx(), blob.cy(), 3, (255,255,0), fill = True)

    # Синие ворота
    blue_angle, blue_distance = 0, 0
    max_area = 0
    for blob in img.find_blobs(blue_threshold, roi=mirror_roi, pixels_threshold=30, area_threshold=200, merge=True, margin=15):
        area = blob.w() * blob.h()
        if area > max_area:
            max_area = area
            bx = blob.cx() - center[0]
            by = blob.cy() - center[1]
            p_dist = math.sqrt(bx * bx + by * by)
            blue_distance = linearize_fast(p_dist, distance)
            blue_angle = (int(math.atan2(bx, by) * 57.3) + 180) % 360

            if is_draw:
                img.draw_rectangle(blob[0], blob[1], blob[2], blob[3],(0,0,255), 2)
                #img.draw_line(center[0], center[1], blob.cx(), blob.cy(), (0,0,255), thickness = 2)
                img.draw_circle(blob.cx(), blob.cy(), 3, (0,0,255), fill = True)

    # Мяч
    ball_angle, ball_distance = 0, 0
    max_area = 0
    for blob in img.find_blobs(red_threshold, roi=mirror_roi, pixels_threshold=3, area_threshold=6, merge=True, margin=0):
        if blob.area() > max_area:
            max_area = blob.area()
            rx = blob.cx() - center[0]
            ry = blob.cy() - center[1]
            p_dist = math.sqrt(rx * rx + ry * ry)
            ball_distance = linearize_fast(p_dist, distance_ball)
            ball_angle = (int(math.atan2(rx, ry) * 57.3) + 180) % 360
            if is_draw:
                img.draw_circle(blob.cx(), blob.cy(), 20, (255, 255, 255), 4)

    # Отправка результатов по UART
    send_data(yellow_angle, yellow_distance, blue_angle, blue_distance, ball_angle, ball_distance)
    #print(clock.fps())
