#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import cv2 as cv

OLED_WIDTH = 128    # Pixel width of OLED 
OLED_HEIGHT = 32    # Pixel height of OLED
THRESHOLD = 127     # Threshold to use to classify pixels 
DEBUG_ON = False    # For debugging purposes

"""Returns byte array generated from vertical scanning"""
def vertical_write(img): 
    data = []
    for i in range(0, OLED_HEIGHT, 8):
        for j in range(OLED_WIDTH):
            column = [row[j] for row in img]
            byte_arr = bytearray(column)
            subcol = byte_arr[i:i+8]

            byte = 0
            for n, bit in enumerate(subcol[::-1]):
                byte += 2**(7-n) if bit == 255 else 0
            data.append(byte)
    return data

"""Returns byte array generated from horizontal scanning"""
def horizontal_write(img):
    data = []
    byte_arr = bytearray(img)
    
    # Packing bits, see: https://www.mfitzp.com/tutorials/displaying-images-oled-displays/
    for i in range (0, len(byte_arr), 8):
        byte = 0
        for n, bit in enumerate(byte_arr[i:i+8]):
            byte += 2**(7-n) if bit == 255 else 0
        data.append(byte)
    return data

if len(sys.argv) == 2: 
    # Read image as grayscale
    img = cv.imread(sys.argv[1], cv.IMREAD_GRAYSCALE)

    if img is None:
        print(f'Error: There was an issue opening the image [{sys.argv[1]}]')
        sys.exit(1)

    # Convert image to black and white
    bw_img = cv.threshold(img, THRESHOLD, 255, cv.THRESH_BINARY)[1]

    x_dim = bw_img.shape[1]
    y_dim = bw_img.shape[0]

    if x_dim < OLED_WIDTH or y_dim < OLED_HEIGHT:
        print(f'Error: The image provided is too small ({x_dim}x{y_dim})! Please use an image that is at least {OLED_WIDTH}x{OLED_HEIGHT}')
        sys.exit(1)

    x_scale = OLED_WIDTH / x_dim
    y_scale = OLED_HEIGHT / y_dim 
    scale_factor = max(x_scale, y_scale)
    print(f'Scale factor is [{scale_factor}]')

    dim = (int(x_dim * scale_factor), int(y_dim * scale_factor))

    # Resize the image
    # TODO: figure out which interpolation method you want
    resized = cv.resize(bw_img, dim, interpolation = cv.INTER_CUBIC)
 
    if DEBUG_ON: 
        print(f'Image dimensions after resizing: [{resized.shape}]')
        cv.imshow("Resized image: ", resized)
        cv.waitKey(0)
        cv.destroyAllWindows()

    # Crop the image to the right size
    cropped = resized[0:OLED_HEIGHT, 0:OLED_WIDTH]

    if DEBUG_ON:
        print(f'Image dimensions after cropping: [{cropped.shape}]')
        cv.imshow("Cropped image: ", cropped)
        cv.waitKey(0)
        cv.destroyAllWindows()

    # Save the file
    filename = 'edit-' + sys.argv[1]
    cv.imwrite(filename, cropped)

    # Get byte array of image
    data = vertical_write(cropped)
    
    result = ''
    # Building output string
    for index, element in enumerate(data):
        result += '0x{:02x}'.format(element)

        if (index < len(data) - 1):
            result += ','

            if (index % 16 == 15):
                result += '\n'
            else:
                result += ' '

    print(result)