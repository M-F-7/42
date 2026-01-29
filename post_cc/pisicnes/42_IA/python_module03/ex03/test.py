from ImageProcessor import ImageProcessor
imp = ImageProcessor()
arr = imp.load("img.png")
# Output :
# Loading image of dimensions 200 x 200
from ColorFilter import ColorFilter
cf = ColorFilter()
# imp.display(arr)
# imp.display(cf.invert(arr))
# imp.display(cf.to_blue(arr))
# imp.display(cf.to_green(arr))
# imp.display(cf.to_red(arr))
# imp.display(cf.to_celluloid(arr))
imp.display(cf.to_grayscale(arr, 'm'))
# imp.display(cf.to_grayscale(arr, 'weight', r_weight=0.2, "g_weight"=0.3, 'b_weight'=0.5))
# imp.display(arr)