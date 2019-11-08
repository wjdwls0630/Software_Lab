from matplotlib import pyplot

khu = pyplot.imread('Pandas_3.png')

pyplot.figure()
pyplot.imshow(khu)
pyplot.axis('off')
pyplot.title('Original color image')

print(khu.shape)

R_channel = khu[:, :, 0]
G_channel = khu[:, :, 1]
B_channel = khu[:, :, 2]
khu_grayscale = 0.299 * R_channel + 0.587 * G_channel + 0.114 * B_channel

pyplot.figure()
pyplot.imshow(khu_grayscale, cmap='gray')
pyplot.axis('off')
pyplot.title('Grayscale image')
pyplot.savefig("Pandas_3_1.png")
pyplot.show()
